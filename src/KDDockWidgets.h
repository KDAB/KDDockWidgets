/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

/**
 * @file
 * @brief File with KDDockWidgets namespace-level enums and methods.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

#ifndef KD_KDDOCKWIDGETS_H
#define KD_KDDOCKWIDGETS_H

#include <QObject>

#ifdef Q_OS_WIN
// Only on Windows, where this is popular. On linux it the Qt::Tool windows need reparenting. Untested on macOS.
# define KDDOCKWIDGETS_SUPPORTS_NESTED_MAINWINDOWS
#endif



namespace KDDockWidgets
{
    enum Location {
        Location_None,
        Location_OnLeft, ///> Left docking location
        Location_OnTop,  ///> Top docking location
        Location_OnRight, ///> Right docking location
        Location_OnBottom ///> Bottom docking location
    };

    enum MainWindowOption {
        MainWindowOption_None = 0, ///> No option set
        MainWindowOption_HasCentralFrame = 1 ///> Makes the MainWindow always have a central frame, for tabbing documents
    };
    Q_DECLARE_FLAGS(MainWindowOptions, MainWindowOption)

    enum AddingOption {
        AddingOption_None = 0, ///> No option set
        AddingOption_StartHidden ///< Don't show the dock widget when adding it
    };

    ///@internal
    enum FrameOption {
        FrameOption_None = 0,
        FrameOption_AlwaysShowsTabs = 1,
        FrameOption_IsCentralFrame = 2,
        FrameOption_IsOverlayed = 4
    };
    Q_DECLARE_FLAGS(FrameOptions, FrameOption)

    enum RestoreOption {
        RestoreOption_None = 0,
        RestoreOption_RelativeToMainWindow = 1, ///< Skips restoring the main window geometry and the restored dock widgets will use relative sizing.
                                                ///< Loading layouts won't change the main window geometry and just use whatever the user has at the moment.
    };
    Q_DECLARE_FLAGS(RestoreOptions, RestoreOption)

    ///@brief When a widget is added we need to figure out what's a decent size for it
    ///This enum specifies the different ways to calculate it
    enum class DefaultSizeMode {
        ItemSize, ///< Simply uses the Item::size() of the item being added. Actual used size might be smaller if our window isn't big enough.
        Fair, ///< Gives an equal relative size as the items that are already in the layout
        FairButFloor, ///< Equal to fair, but if the item is smaller than the fair suggestion, then that small size is used.
        SizePolicy, ///< Uses the item's sizeHint() and sizePolicy()
    };

    enum class DropIndicatorType {
        Classic,   ///< The default
        Segmented
    };

    ///@internal
    inline QString locationStr(Location loc)
    {
        switch (loc) {
        case KDDockWidgets::Location_None:
            return QStringLiteral("none");
        case KDDockWidgets::Location_OnLeft:
            return QStringLiteral("left");
        case KDDockWidgets::Location_OnTop:
            return QStringLiteral("top");
        case KDDockWidgets::Location_OnRight:
            return QStringLiteral("right");
        case KDDockWidgets::Location_OnBottom:
            return QStringLiteral("bottom");
        }

        return QString();
    }

    /// @brief Each main window supports 4 sidebars
    enum class SideBarLocation {
        None,
        North,
        East,
        West,
        South
    };

    ///@internal
    inline uint qHash(SideBarLocation loc, uint seed)
    {
        return ::qHash(static_cast<uint>(loc), seed);
    }
}

Q_DECLARE_OPERATORS_FOR_FLAGS(KDDockWidgets::FrameOptions)

#endif
