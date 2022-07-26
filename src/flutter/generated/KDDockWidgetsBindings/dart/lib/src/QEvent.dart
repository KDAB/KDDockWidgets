/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

//tag=1052
import 'dart:ffi' as ffi;
import 'package:ffi/ffi.dart';
import 'TypeHelpers.dart';
import '../Bindings.dart';
import '../FinalizerHelpers.dart';

//tag=1051
var _dylib = Library.instance().dylib;
final _finalizer =
    _dylib.lookup<ffi.NativeFunction<Dart_WeakPersistentHandleFinalizer_Type>>(
        'c_QEvent_Finalizer');

//tag=1038
class QEvent_Type {
  static const None = 0;
  static const Timer = 1;
  static const MouseButtonPress = 2;
  static const MouseButtonRelease = 3;
  static const MouseButtonDblClick = 4;
  static const MouseMove = 5;
  static const KeyPress = 6;
  static const KeyRelease = 7;
  static const FocusIn = 8;
  static const FocusOut = 9;
  static const FocusAboutToChange = 23;
  static const Enter = 10;
  static const Leave = 11;
  static const Paint = 12;
  static const Move = 13;
  static const Resize = 14;
  static const Create = 15;
  static const Destroy = 16;
  static const Show = 17;
  static const Hide = 18;
  static const Close = 19;
  static const Quit = 20;
  static const ParentChange = 21;
  static const ParentAboutToChange = 131;
  static const ThreadChange = 22;
  static const WindowActivate = 24;
  static const WindowDeactivate = 25;
  static const ShowToParent = 26;
  static const HideToParent = 27;
  static const Wheel = 31;
  static const WindowTitleChange = 33;
  static const WindowIconChange = 34;
  static const ApplicationWindowIconChange = 35;
  static const ApplicationFontChange = 36;
  static const ApplicationLayoutDirectionChange = 37;
  static const ApplicationPaletteChange = 38;
  static const PaletteChange = 39;
  static const Clipboard = 40;
  static const Speech = 42;
  static const MetaCall = 43;
  static const SockAct = 50;
  static const WinEventAct = 132;
  static const DeferredDelete = 52;
  static const DragEnter = 60;
  static const DragMove = 61;
  static const DragLeave = 62;
  static const Drop = 63;
  static const DragResponse = 64;
  static const ChildAdded = 68;
  static const ChildPolished = 69;
  static const ChildRemoved = 71;
  static const ShowWindowRequest = 73;
  static const PolishRequest = 74;
  static const Polish = 75;
  static const LayoutRequest = 76;
  static const UpdateRequest = 77;
  static const UpdateLater = 78;
  static const EmbeddingControl = 79;
  static const ActivateControl = 80;
  static const DeactivateControl = 81;
  static const ContextMenu = 82;
  static const InputMethod = 83;
  static const TabletMove = 87;
  static const LocaleChange = 88;
  static const LanguageChange = 89;
  static const LayoutDirectionChange = 90;
  static const Style = 91;
  static const TabletPress = 92;
  static const TabletRelease = 93;
  static const OkRequest = 94;
  static const HelpRequest = 95;
  static const IconDrag = 96;
  static const FontChange = 97;
  static const EnabledChange = 98;
  static const ActivationChange = 99;
  static const StyleChange = 100;
  static const IconTextChange = 101;
  static const ModifiedChange = 102;
  static const MouseTrackingChange = 109;
  static const WindowBlocked = 103;
  static const WindowUnblocked = 104;
  static const WindowStateChange = 105;
  static const ReadOnlyChange = 106;
  static const ToolTip = 110;
  static const WhatsThis = 111;
  static const StatusTip = 112;
  static const ActionChanged = 113;
  static const ActionAdded = 114;
  static const ActionRemoved = 115;
  static const FileOpen = 116;
  static const Shortcut = 117;
  static const ShortcutOverride = 51;
  static const WhatsThisClicked = 118;
  static const ToolBarChange = 120;
  static const ApplicationActivate = 121;
  static const ApplicationActivated = 121;
  static const ApplicationDeactivate = 122;
  static const ApplicationDeactivated = 122;
  static const QueryWhatsThis = 123;
  static const EnterWhatsThisMode = 124;
  static const LeaveWhatsThisMode = 125;
  static const ZOrderChange = 126;
  static const HoverEnter = 127;
  static const HoverLeave = 128;
  static const HoverMove = 129;
  static const AcceptDropsChange = 152;
  static const ZeroTimerEvent = 154;
  static const GraphicsSceneMouseMove = 155;
  static const GraphicsSceneMousePress = 156;
  static const GraphicsSceneMouseRelease = 157;
  static const GraphicsSceneMouseDoubleClick = 158;
  static const GraphicsSceneContextMenu = 159;
  static const GraphicsSceneHoverEnter = 160;
  static const GraphicsSceneHoverMove = 161;
  static const GraphicsSceneHoverLeave = 162;
  static const GraphicsSceneHelp = 163;
  static const GraphicsSceneDragEnter = 164;
  static const GraphicsSceneDragMove = 165;
  static const GraphicsSceneDragLeave = 166;
  static const GraphicsSceneDrop = 167;
  static const GraphicsSceneWheel = 168;
  static const KeyboardLayoutChange = 169;
  static const DynamicPropertyChange = 170;
  static const TabletEnterProximity = 171;
  static const TabletLeaveProximity = 172;
  static const NonClientAreaMouseMove = 173;
  static const NonClientAreaMouseButtonPress = 174;
  static const NonClientAreaMouseButtonRelease = 175;
  static const NonClientAreaMouseButtonDblClick = 176;
  static const MacSizeChange = 177;
  static const ContentsRectChange = 178;
  static const MacGLWindowChange = 179;
  static const FutureCallOut = 180;
  static const GraphicsSceneResize = 181;
  static const GraphicsSceneMove = 182;
  static const CursorChange = 183;
  static const ToolTipChange = 184;
  static const NetworkReplyUpdated = 185;
  static const GrabMouse = 186;
  static const UngrabMouse = 187;
  static const GrabKeyboard = 188;
  static const UngrabKeyboard = 189;
  static const MacGLClearDrawable = 191;
  static const StateMachineSignal = 192;
  static const StateMachineWrapped = 193;
  static const TouchBegin = 194;
  static const TouchUpdate = 195;
  static const TouchEnd = 196;
  static const NativeGesture = 197;
  static const RequestSoftwareInputPanel = 199;
  static const CloseSoftwareInputPanel = 200;
  static const WinIdChange = 203;
  static const Gesture = 198;
  static const GestureOverride = 202;
  static const ScrollPrepare = 204;
  static const Scroll = 205;
  static const Expose = 206;
  static const InputMethodQuery = 207;
  static const OrientationChange = 208;
  static const TouchCancel = 209;
  static const ThemeChange = 210;
  static const SockClose = 211;
  static const PlatformPanel = 212;
  static const StyleAnimationUpdate = 213;
  static const ApplicationStateChange = 214;
  static const WindowChangeInternal = 215;
  static const ScreenChangeInternal = 216;
  static const PlatformSurface = 217;
  static const Pointer = 218;
  static const TabletTrackingChange = 219;
  static const User = 1000;
  static const MaxUser = 65535;
}

class QEvent {
//tag=1060
  static var s_dartInstanceByCppPtr = Map<int, QEvent>();
  var _thisCpp = null;
  bool _needsAutoDelete = false;
  get thisCpp => _thisCpp;
  set thisCpp(var ptr) {
    _thisCpp = ptr;
    ffi.Pointer<ffi.Void> ptrvoid = ptr.cast<ffi.Void>();
    if (_needsAutoDelete)
      newWeakPersistentHandle?.call(this, ptrvoid, 0, _finalizer);
  }

  static bool isCached(var cppPointer) {
//tag=1024
    return s_dartInstanceByCppPtr.containsKey(cppPointer.address);
  }

//tag=1061
  factory QEvent.fromCache(var cppPointer, [needsAutoDelete = false]) {
    return (s_dartInstanceByCppPtr[cppPointer.address] ??
        QEvent.fromCppPointer(cppPointer, needsAutoDelete)) as QEvent;
  }
  QEvent.fromCppPointer(var cppPointer, [this._needsAutoDelete = false]) {
//tag=1024
    thisCpp = cppPointer;
  }
//tag=1025
  QEvent.init() {}
//tag=1023
//QEvent(QEvent::Type type)
  QEvent(int type) {
//tag=1075
    final voidstar_Func_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_ffi_Int32_FFI>>(
            'c_QEvent__constructor_Type')
        .asFunction();
    thisCpp = func(type);
    QEvent.s_dartInstanceByCppPtr[thisCpp.address] = this;
    registerCallbacks();
  }
//tag=1024

//tag=1027
// accept()
  accept() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>('c_QEvent__accept')
        .asFunction();
//tag=1030
    func(thisCpp);
  }
//tag=1024

//tag=1027
// ignore()
  ignore() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>('c_QEvent__ignore')
        .asFunction();
//tag=1030
    func(thisCpp);
  }
//tag=1024

//tag=1027
// isAccepted() const
  bool isAccepted() {
//tag=1028
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_QEvent__isAccepted')
        .asFunction();
//tag=1029
    return func(thisCpp) != 0;
  }

//tag=1024
  static
//tag=1027
// registerEventType(int hint)
      int registerEventType({int hint = -1}) {
//tag=1028
    final int_Func_int func = _dylib
        .lookup<ffi.NativeFunction<int_Func_ffi_Int32_FFI>>(
            'c_static_QEvent__registerEventType_int')
        .asFunction();
//tag=1031
    return func(hint);
  }
//tag=1024

//tag=1027
// setAccepted(bool accepted)
  setAccepted(bool accepted) {
//tag=1028
    final void_Func_voidstar_bool func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int8_FFI>>(
            'c_QEvent__setAccepted_bool')
        .asFunction();
//tag=1030
    func(thisCpp, accepted ? 1 : 0);
  }
//tag=1024

//tag=1027
// setSpontaneous()
  setSpontaneous() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_QEvent__setSpontaneous')
        .asFunction();
//tag=1030
    func(thisCpp);
  }
//tag=1024

//tag=1027
// spontaneous() const
  bool spontaneous() {
//tag=1028
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_QEvent__spontaneous')
        .asFunction();
//tag=1029
    return func(thisCpp) != 0;
  }
//tag=1024

//tag=1027
// type() const
  int type() {
//tag=1028
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>('c_QEvent__type')
        .asFunction();
//tag=1031
    return func(thisCpp);
  }

//tag=1022
  void release() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_QEvent__destructor')
        .asFunction();
    func(thisCpp);
  }

//tag=1019
  String cFunctionSymbolName(int methodId) {
    switch (methodId) {
    }
    return "";
  }

  static String methodNameFromId(int methodId) {
    switch (methodId) {
    }
    throw Error();
  }

//tag=1020
  void registerCallbacks() {
    assert(thisCpp != null);
    final RegisterMethodIsReimplementedCallback registerCallback = _dylib
        .lookup<ffi.NativeFunction<RegisterMethodIsReimplementedCallback_FFI>>(
            'c_QEvent__registerVirtualMethodCallback')
        .asFunction();
  }
}
