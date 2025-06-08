# 3rdparty

Here we list which 3rdparty software used and possibly shipped by KDDW and their respective licenses.

## Runtime dependencies

### nlohmann JSON

JSON c++ library.<br>
Copyright 2013 - 2025 Niels Lohmann <https://nlohmann.me>
[code](src/3rdparty/nlohmann/nlohmann/json.hpp)<br>
[MIT licensed](LICENSES/MIT.txt)

### KDBindings

Non-Qt signal/slot implementation.

Copyright 2021 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
`src/3rdparty/kdbindings/genindex_array.h` is Copyright 2021 Jeremy Burns
[code](src/3rdparty/kdbindings/)<br>
[MIT licensed](LICENSES/MIT.txt)

### KDStlContainerAdaptor

Only used for a Flutter build.
Replacement for QVector.

Copyright (C) 2021 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
[code](src/3rdparty/kdtoolbox/KDStlContainerAdaptor.h)<br>
[MIT licensed](LICENSES/MIT.txt)

## Build-time / CI tests 3rdparty

These dependencies are only used during build or other CI purposes like running tests.

### ECM

CMake build helpers.

[code](cmake/ECM/modules/)<br>
[BSD licensed](LICENSES/BSD-3-Clause.txt)

### doxygen-awesome.css

Template to generate documentation.

[code](docs/api/doxygen-awesome.css)<br>
[MIT licensed](LICENSES/MIT.txt)

### Flutter embedder and generated files

Only used for a flutter build and only during tests.

[code](tests/flutter_tests_embedder) and [code](examples/flutter)<br>
[BSD licensed](LICENSES/BSD-3-Clause.txt)
