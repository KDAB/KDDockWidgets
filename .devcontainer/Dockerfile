#
# This file is part of KDDockWidgets.
#
# SPDX-FileCopyrightText: 2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
# Author: Sérgio Martins <sergio.martins@kdab.com>
#
# SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only
#
# Contact KDAB at <info@kdab.com> for commercial licensing options.

# A minimal Dockerfile that's able to build and run KDDW tests.
# Tests are run with offscreen QPA
# This Dockerfile is just provided for demonstration purposes and not really used by CI.

# Instructions:
# docker build -t kddw-tests .
# docker run -it -v /data/sources/kddockwidgets/:/kddockwidgets/ -v ~/Qt/5.15.2/gcc_64/:/Qt5/ -v ~/Qt/6.6.0/gcc_64/:/Qt6/ --cap-add=SYS_PTRACE --security-opt seccomp=unconfined --ulimit nofile=1024:4096 -u 1000:1000 kddw-tests
# cd /kddockwidgets/
# cmake --preset=dev
# cd build-dev && ninja
# QT_QUICK_BACKEND=software ctest -j12

FROM ubuntu:22.04
MAINTAINER Sergio Martins (sergio.martins@kdab.com)

ENV TZ=Europe/Berlin
ENV LC_CTYPE=C.UTF-8
ENV PATH=$PATH:/Qt5/bin/:/Qt6/bin/
ENV LD_LIBRARY_PATH=/Qt5/lib/:/Qt6/lib/
ENV QT_QUICK_BACKEND=software

RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt update -qq
RUN apt install build-essential software-properties-common lld git cmake ninja-build \
                mesa-common-dev libglu1-mesa-dev libglib2.0-dev libfontconfig \
                libxkbcommon-dev mesa-utils libgl1-mesa-dev libglu1-mesa-dev \
                vim clang-tidy-14 valgrind pip libxslt-dev llvm libspdlog-dev clazy -y

RUN pip install shiboken6-generator==6.6.0 shiboken6==6.6.0 pyside6==6.6.0

RUN pip install --index-url=https://download.qt.io/official_releases/QtForPython \
              --trusted-host download.qt.io shiboken2-generator==5.15.2.1 shiboken2==5.15.2.1 pyside2==5.15.2.1

RUN mkdir /home/user && \
    groupadd -g 1000 defaultgroup && \
    useradd -u 1000 -g defaultgroup user -m && chown -R user /home/user
