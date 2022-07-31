/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
import 'dart:ffi' as ffi;
import 'package:ffi/ffi.dart';
import 'TypeHelpers.dart';
import '../Bindings.dart';
import '../FinalizerHelpers.dart';

var _dylib = Library.instance().dylib;

class Qt_CursorShape {
  static const ArrowCursor = 0;
  static const UpArrowCursor = 1;
  static const CrossCursor = 2;
  static const WaitCursor = 3;
  static const IBeamCursor = 4;
  static const SizeVerCursor = 5;
  static const SizeHorCursor = 6;
  static const SizeBDiagCursor = 7;
  static const SizeFDiagCursor = 8;
  static const SizeAllCursor = 9;
  static const BlankCursor = 10;
  static const SplitVCursor = 11;
  static const SplitHCursor = 12;
  static const PointingHandCursor = 13;
  static const ForbiddenCursor = 14;
  static const WhatsThisCursor = 15;
  static const BusyCursor = 16;
  static const OpenHandCursor = 17;
  static const ClosedHandCursor = 18;
  static const DragCopyCursor = 19;
  static const DragMoveCursor = 20;
  static const DragLinkCursor = 21;
  static const LastCursor = 21;
  static const BitmapCursor = 24;
  static const CustomCursor = 25;
}
