#
# This file is part of KDDockWidgets.
#
# SPDX-FileCopyrightText: 2024 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
# Author: Sérgio Martins <sergio.martins@kdab.com>
#
# SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only
#
# Contact KDAB at <info@kdab.com> for commercial licensing options.

# Dockerfile for qt6-asan GitHub Action

# Instructions for manual inspection:
# docker build -t kddw-qt6-asan .
# docker run -it -v /data/sources/kddockwidgets/:/kddockwidgets/ kddw-qt6-asan
# cd /kddockwidgets/
# cmake --preset=dev-asan6
# cd build-dev-asan6 && ninja
# ctest -j12

FROM ubuntu:24.04
MAINTAINER Sergio Martins (sergio.martins@kdab.com)

ENV TZ=Europe/Berlin
ENV LC_CTYPE=C.UTF-8
ENV PATH=$PATH:/Qt6/bin/
ENV LD_LIBRARY_PATH=/Qt6/lib/
ENV QT_QUICK_BACKEND=software
ENV LSAN_OPTIONS=detect_leaks=0

RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt update
RUN apt install build-essential software-properties-common lld git cmake ninja-build \
                mesa-common-dev libglu1-mesa-dev libglib2.0-dev libfontconfig \
                libxkbcommon-dev mesa-utils libgl1-mesa-dev libglu1-mesa-dev \
                libxslt-dev libspdlog-dev -y

RUN mkdir /sources/

RUN git clone https://code.qt.io/qt/qt5.git /sources/qt6
RUN cd /sources/qt6 && git switch 6.6 && perl init-repository --module-subset=qtbase,qtshadertools,qtdeclarative
RUN mkdir -p /build/qt6
RUN cd /build/qt6 && /sources/qt6/configure -prefix /Qt6/ -debug -sanitize address -- -DQT_BUILD_EXAMPLES=OFF
RUN cmake --build /build/qt6 --parallel
RUN cmake --install /build/qt6

COPY entrypoint.sh /entrypoint.sh
ENTRYPOINT ["/entrypoint.sh"]
