/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

/// A script to generate a random layout
/// $ dart tests/layout_fuzzer.dart layout_schema.json

import 'dart:convert';
import 'dart:io';
import 'dart:math';

final _random = Random();
const int _min_children_recursion_depth = 2;
const int _max_children_recursion_depth = 5;
int _current_children_recursion_depth = 0;
int _current_children_max_recursion_depth = 0;
int _current_string_count = 0;

// Returns between min and max, inclusive.
int generateNumber(int min, int max) {
  final int n = max - min + 1;
  return _random.nextInt(n) + min;
}

randomArrayElement(var array) {
  final index = generateNumber(0, array.length - 1);
  return array[index];
}

class Schema {
  final jsonSchema;
  final String propertyName;
  late final String type;

  Schema(this.jsonSchema, this.propertyName) {
    type = jsonSchema["type"];
  }

  static Schema fromJson(var jsonSchema, var propertyName) {
    if (jsonSchema["\$ref"] != null) {
      return Fuzzer.self.schemaForDefinition(jsonSchema["\$ref"], propertyName);
    }

    final type = jsonSchema["type"];

    if (type == "integer") {
      return IntegerSchema(jsonSchema, propertyName);
    } else if (type == "number") {
      return NumberSchema(jsonSchema, propertyName);
    } else if (type == "boolean") {
      return BooleanSchema(jsonSchema, propertyName);
    } else if (type == "array") {
      return ArraySchema(jsonSchema, propertyName);
    } else if (type == "object") {
      return ObjectSchema(jsonSchema, propertyName);
    } else if (type == "string") {
      return StringSchema(jsonSchema, propertyName);
    } else if (["lastOverlayedGeometries", "affinities"]
        .contains(propertyName)) {
      // lastOverlayedGeometries actually has "types" = [null, "array"],
      // but we can just use an empty array instead of honouring that null
      jsonSchema["type"] = "array";
      return ArraySchema(jsonSchema, propertyName);
    }

    throw "fromJson: Unsupported type=${type}; propName=$propertyName; json=${jsonSchema}";
  }

  bool isObject() {
    return type == "object";
  }

  bool isArray() {
    return type == "array";
  }

  bool isInteger() {
    return type == "integer";
  }

  bool isBoolean() {
    return type == "boolean";
  }

  bool isNumber() {
    return type == "number";
  }

  /// generates a sample matching this schema
  dynamic generate() {
    throw "Reimplement me!";
  }
}

class IntegerSchema extends Schema {
  List<int>? _possibleValues;
  IntegerSchema(var jsonSchema, String propertyName)
      : super(jsonSchema, propertyName) {
    if (jsonSchema["enum"] != null)
      _possibleValues = List<int>.from(jsonSchema["enum"]);
  }

  @override
  dynamic generate() {
    return _possibleValues == null
        ? generateNumber(0, 1000)
        : randomArrayElement(_possibleValues!);
  }
}

class NumberSchema extends Schema {
  NumberSchema(var jsonSchema, String propertyName)
      : super(jsonSchema, propertyName);

  @override
  dynamic generate() {
    // This is specific for KDDW
    final dpiValues = [1, 1.5, 2, 3];
    return randomArrayElement(dpiValues);
  }
}

class BooleanSchema extends Schema {
  BooleanSchema(var jsonSchema, String propertyName)
      : super(jsonSchema, propertyName);

  @override
  dynamic generate() {
    return generateNumber(0, 1) == 1;
  }
}

class StringSchema extends Schema {
  StringSchema(var jsonSchema, String propertyName)
      : super(jsonSchema, propertyName);

  @override
  dynamic generate() {
    _current_string_count++;
    return "somestring$_current_string_count";
  }
}

class ObjectSchema extends Schema {
  late final List<String> required;
  ObjectSchema(var jsonSchema, String propertyName)
      : super(jsonSchema, propertyName) {
    required = jsonSchema["required"] == null
        ? []
        : List.unmodifiable(jsonSchema["required"]);
  }

  List<Schema> properties() {
    List<Schema> props = [];

    Map<String, dynamic> propsJson = jsonSchema["properties"] ?? {};
    for (var e in propsJson.entries) {
      props.add(Schema.fromJson(e.value, e.key));
    }

    return props;
  }

  Schema? patternProperties() {
    Map<String, dynamic> props = jsonSchema["patternProperties"] ?? {};
    if (props.isNotEmpty) {
      final String definition = props.entries.first.value["\$ref"];
      return Fuzzer.self.schemaForDefinition(definition, propertyName);
    }

    return null;
  }

  @override
  dynamic generate() {
    var json = {};

    for (final propSchema in properties()) {
      if (propSchema.propertyName == "children") {
        if (_current_children_recursion_depth ==
            _current_children_max_recursion_depth) {
          // "children" property can have children inside, we limit
          // recursion here. Usually a layout has like max 3 or so of nesting
          continue;
        }

        _current_children_recursion_depth++;
      }

      json[propSchema.propertyName] = propSchema.generate();
    }

    final Schema? _patternProps = patternProperties();
    if (_patternProps != null) {
      // TODO
    }

    return json;
  }
}

class ArraySchema extends Schema {
  Schema? _elementSchema;
  List<Schema>? _elementsSchemas;
  int? minItems;
  int? maxItems;
  ArraySchema(var jsonSchema, String propertyName)
      : super(jsonSchema, propertyName) {
    if (jsonSchema["items"] != null) {
      _elementSchema =
          Fuzzer.self.schemaForArray(jsonSchema["items"], propertyName);
    } else if (jsonSchema["prefixItems"] != null) {
      _elementsSchemas =
          Fuzzer.self.schemasForArray(jsonSchema["prefixItems"], propertyName);
    } else {
      throw "Expected items/prefixItems specification in array. name=$propertyName , json=${jsonSchema}";
    }

    minItems = jsonSchema["minItems"];
    maxItems = jsonSchema["maxItems"];
  }

  @override
  dynamic generate() {
    final int min = minItems ?? 0;
    final int max = maxItems ?? (min + 10);

    final int numElements = generateNumber(min, max);

    var result = [];

    for (int i = 0; i < numElements; ++i) {
      result.add(elementSchema(i).generate());
    }

    return result;
  }

  Schema elementSchema(int indexHint) {
    if (_elementSchema != null) return _elementSchema!;
    if (indexHint < _elementsSchemas!.length)
      return _elementsSchemas![indexHint];
    throw "Invalid index=$indexHint for ${_elementsSchemas}";
  }
}

class Fuzzer {
  final ObjectSchema schema;
  late final definitions;
  static late Fuzzer self;

  Fuzzer(this.schema) {
    self = this;
    definitions = schema.jsonSchema["definitions"];
    assert(schema.isObject());
  }

  dynamic run() {
    dynamic json = {};

    _current_children_recursion_depth = 0;
    _current_children_max_recursion_depth = generateNumber(
        _min_children_recursion_depth, _max_children_recursion_depth);

    generate(schema, json);
    return json;
  }

  Schema schemaForArray(var json, String propertyName) {
    if (json["\$ref"] != null) {
      return schemaForDefinition(json["\$ref"], propertyName);
    } else if (json["type"] != null) {
      return Schema.fromJson(json, propertyName);
    } else {
      throw "schemaForArray: Unknown schema for array";
    }
  }

  List<Schema> schemasForArray(var json, String propertyName) {
    List<Schema> schemas = [];
    for (var element in json) {
      final definition = element["\$ref"];
      schemas.add(schemaForDefinition(definition, propertyName));
    }

    return schemas;
  }

  /// Receives a string like "#/definitions/lastOverlayedGeometry"
  Schema schemaForDefinition(String definitionRef, String propertyName) {
    final prefix = "#/definitions/";
    if (!definitionRef.startsWith(prefix))
      throw "Invalid definition ref $definitionRef";
    definitionRef = definitionRef.replaceAll(prefix, "");
    final json = definitions[definitionRef];
    return Schema.fromJson(json, propertyName);
  }

  void generate(ObjectSchema currentSchema, dynamic generatedJson) {
    for (var p in currentSchema.properties()) {
      if (p.propertyName.isEmpty) {
        throw "Empty prop name";
      } else {
        generatedJson[p.propertyName] = p.generate();
      }
    }
  }
}

main(List<String> args) {
  if (args.length != 1) {
    print("Expected layout schema filename");
    return;
  }

  final schemaStr = File(args.first).readAsStringSync();
  final jsonSchema = jsonDecode(schemaStr);
  final fuzzer = Fuzzer(ObjectSchema(jsonSchema, ""));
  final result = fuzzer.run();

  JsonEncoder encoder = new JsonEncoder.withIndent('  ');
  String prettyprint = encoder.convert(result);
  print(prettyprint);
}
