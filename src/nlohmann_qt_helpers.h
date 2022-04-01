/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Waqar Ahmed <waqar.ahmed@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include <nlohmann/json.hpp>

#include <QVariantMap>
#include <QDebug>

#include <iostream>

QT_BEGIN_NAMESPACE

inline void from_json(const nlohmann::json &j, QString &string)
{
    string = QString::fromStdString(j.get<std::string>());
}

inline void to_json(nlohmann::json &j, const QString &s)
{
    j = s.toStdString();
}

inline void to_json(nlohmann::json& j, const QVariantList& list);
inline void from_json(const nlohmann::json& j, QVariantList& list);
inline void to_json(nlohmann::json& j, const QVariantMap& map);
inline void from_json(const nlohmann::json& j, QVariantMap& map);

inline void from_json(const nlohmann::json &j, QVariant& variant)
{
    if (j.is_null())
    {
        variant = QVariant::fromValue(nullptr);
    }
    else if (j.is_number_unsigned())
    {
        variant = QVariant::fromValue(j.get<quint64>());
    }
    else if (j.is_number_integer())
    {
        variant = QVariant::fromValue(j.get<qint64>());
    }
    else if (j.is_number_float())
    {
        variant = QVariant::fromValue(j.get<qreal>());
    }
    else if (j.is_string())
    {
        variant = QVariant::fromValue(j.get<QString>());
    }
    else if (j.is_boolean())
    {
        variant = QVariant::fromValue(j.get<bool>());
    }
    else if (j.is_array())
    {
        QVariantList list;
        from_json(j, list);
        variant = list;
    }
    else if (j.is_object())
    {
        QVariantMap map;
        from_json(j, map);
        variant = map;
    }
}

inline void to_json(nlohmann::json& j, const QVariant& variant)
{
    if (!variant.isValid()) {
        qWarning() << Q_FUNC_INFO << "Unexpected invalid variant";
        return;
    }

    auto type = static_cast<QMetaType::Type>(variant.type());

    if (type == QMetaType::QVariantList)
    {
        to_json(j, variant.value<QVariantList>());
    }
    else if (type == QMetaType::QVariantMap)
    {
        to_json(j, variant.value<QVariantMap>());
    }
    else if (type == QMetaType::QString)
    {
        j = variant.toString().toStdString();
    }
    else if (type == QMetaType::Double)
    {
        j = variant.toDouble();
    }
    else if (type == QMetaType::Bool)
    {
        j = variant.toBool();
    }
    else if (type == QMetaType::Int)
    {
        j = variant.toInt();
    }
    else if (type == QMetaType::UInt)
    {
        j = variant.toUInt();
    }
    else
    {
        qWarning() << Q_FUNC_INFO << "Unexpected type << " << type;
        j.clear();
    }
}

inline void to_json(nlohmann::json& j, const QVariantList& list)
{
    j = nlohmann::json::array();

    for (auto it = list.cbegin(), end = list.cend(); it != end; ++it) {
        nlohmann::json serialized;
        to_json(serialized, *it);
        j.push_back(serialized);
    }
}

inline void from_json(const nlohmann::json& j, QVariantList& list)
{
    if (!j.is_array()) {
        Q_UNUSED(list)
        list.clear();
        qWarning() << Q_FUNC_INFO << "Unexpected j not an array";
        return;
    }

    list.reserve((int)j.size());
    for (const auto &v : j) {
        QVariant var;
        from_json(v, var);
        list.push_back(var);
    }
}

inline void to_json(nlohmann::json& j, const QVariantMap& map)
{
    j = nlohmann::json::object();

    for (auto it = std::cbegin(map); it != std::cend(map); ++it) {
        nlohmann::json serialized;
        to_json(serialized, it.value());
        j[it.key().toStdString()] = serialized;
    }
}

inline void from_json(const nlohmann::json& j, QVariantMap& map)
{
    for (const auto &v : j.items()) {
        QVariant var;
        from_json(v.value(), var);
        const QString key = QString::fromStdString(v.key());
        map[key] = var;
    }
}

QT_END_NAMESPACE
