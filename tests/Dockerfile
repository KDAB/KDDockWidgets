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
# docker run -it -v ~/Qt/5.15.2/gcc_64/:/Qt/ kddw-tests
# cd /KDDockWidgets/
# cmake --preset=dev
# cd build-dev && ninja
# QT_QUICK_BACKEND=software ctest -j12

FROM ubuntu:22.04
MAINTAINER Sergio Martins (sergio.martins@kdab.com)

ENV TZ=Europe/Berlin
ENV LC_CTYPE=C.UTF-8
ENV PATH=$PATH:/Qt/bin/
ENV LD_LIBRARY_PATH=/Qt/lib/

RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt update
RUN apt install build-essential software-properties-common lld git cmake ninja-build mesa-common-dev libglu1-mesa-dev libglib2.0-dev libfontconfig -y

WORKDIR /
RUN git clone https://github.com/KDAB/KDDockWidgets.git
WORKDIR /KDDockWidgets/
