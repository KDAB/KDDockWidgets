/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef KD_LAYOUTSAVER_H
#define KD_LAYOUTSAVER_H

/**
 * @file
 * @brief Class to save and restore dockwidget layouts.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

#include "kddockwidgets/docks_export.h"

#include "kddockwidgets/KDDockWidgets.h"

QT_BEGIN_NAMESPACE
class QByteArray;
QT_END_NAMESPACE

class TestDocks;

namespace KDDockWidgets {

namespace Core {
class DockWidget;
class FloatingWindow;
class MainWindow;
}

/**
 * @brief LayoutSaver allows to save or restore layouts.
 *
 * You can save a layout to a file or to a byte array.
 * JSON is used as the serialized format.
 *
 * Example:
 *     LayoutSaver saver;
 *
 *     // Save to a file:
 *     saver.saveToFile(filename);
 *
 * The counterpart of saveToFile() is restoreFromFile().
 *
 * You can also save to a QByteArray instead, with serializeLayout().
 * The counterpart of serializeLayout() is restoreLayout();
 */
class DOCKS_EXPORT LayoutSaver
{
public:
    ///@brief Constructor. Construction on the stack is suggested.
    explicit LayoutSaver(RestoreOptions options = RestoreOption_None);

    ///@brief Destructor.
    ~LayoutSaver();

    ///@brief returns whether a restore (@ref restoreLayout) is in progress
    static bool restoreInProgress();

    /**
     * @brief saves the layout to JSON file
     * @param jsonFilename the filename where the layout will be saved to
     * @return true on success
     */
    bool saveToFile(const QString &jsonFilename);

    /**
     * @brief restores the layout from a JSON file
     * @param jsonFilename the filename containing a saved layout
     * @return true on success
     */
    bool restoreFromFile(const QString &jsonFilename);

    /**
     * @brief saves the layout into a byte array
     */
    QByteArray serializeLayout() const;

    /**
     * @brief restores the layout from a byte array
     * All MainWindows and DockWidgets should have been created before calling
     * this function.
     *
     * If not all DockWidgets can be created beforehand then make sure to set
     * a DockWidget factory via Config::setDockWidgetFactoryFunc()
     *
     * @sa Config::setDockWidgetFactoryFunc()
     *
     * @return true on success
     */
    bool restoreLayout(const QByteArray &);

    /**
     * @brief returns a list of dock widgets which were restored since the last
     * @ref restoreLayout() or @ref restoreFromFile()
     *
     * Useful since some dock widgets can be new, and hence not be included in the last saved
     * layout.
     *
     * You can use KDDockWidgets::controllersToViews(layoutSaver.restoredDockWidgets()) to
     * get the corresponding QtWidgets::DockWidget* instead of Core::DockWidget*
     */
    Vector<Core::DockWidget *> restoredDockWidgets() const;

    /**
     * @brief Sets the list of affinity names for which restore and save will be applied on.
     * Allows to save/restore only a subset of the windows.
     * Empty by default, all windows are subject to save/restore.
     * Any window with empty affinity will also be subject to save/restore, regardless of @p
     * affinityNames.
     */
    void setAffinityNames(const Vector<QString> &affinityNames);

    /**
     * @brief Restricts saving to the specified window.
     *
     * Call it once per window you want to save. Not calling it at all, which is the default,
     * saves every window.
     *
     * Use this to save and restore a single top-level window, for example the layout of
     * whatever is currently docked into one main window, or the contents of one floating
     * window. A window is always saved in full; saving only some of the dock widgets inside a
     * window is not supported.
     *
     * Restoring needs no counterpart call. A layout saved this way only describes the windows
     * you selected, so restoring it only touches those, and leaves every other window alone.
     * Dock widgets that were saved but have since moved elsewhere are moved back.
     *
     * Only affects saving. Has no effect on restoring.
     */
    void addWindowToSave(Core::MainWindow *);
    void addWindowToSave(Core::FloatingWindow *);

    /**
     * @brief Overload that saves the top-level window @p dockWidget is currently in.
     * Does nothing if the dock widget is closed, as it's then in no window.
     */
    void addWindowToSave(Core::DockWidget *dockWidget);

    /**
     * @brief Overload that takes a main window's unique name.
     * The main window doesn't need to exist yet when this is called, only when saving.
     */
    void addMainWindowToSave(const QString &uniqueName);

    /// @brief Undoes any addWindowToSave() call, going back to saving every window
    void clearWindowsToSave();

    /**
     * @brief Returns the list of opened dock widgets in the specified layout
     *
     * This operation does not have side-effects, no dock widget will be actually restored.
     */
    static Vector<QString> openedDockWidgetsInLayout(const QString &jsonFilename);
    static Vector<QString> openedDockWidgetsInLayout(const QByteArray &serialized);

    static Vector<QString> sideBarDockWidgetsInLayout(const QString &jsonFilename);
    static Vector<QString> sideBarDockWidgetsInLayout(const QByteArray &serialized);

    /// @internal Returns the private-impl. Not intended for public use.
    class Private;
    Private *dptr() const;

    struct Layout;
    struct SaveScope;
    struct MainWindow;
    struct FloatingWindow;
    struct DockWidget;
    struct Position;
    struct MultiSplitter;
    struct Group;
    struct Placeholder;
    struct ScalingInfo;
    struct ScreenInfo;

private:
    KDDW_DELETE_COPY_CTOR(LayoutSaver)
    friend class ::TestDocks;

    Private *const d;
};
}

#endif
