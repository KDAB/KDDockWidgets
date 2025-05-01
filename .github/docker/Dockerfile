#
# This file is part of KDDockWidgets.
#
# SPDX-FileCopyrightText: 2025 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
# Author: Sérgio Martins <sergio.martins@kdab.com>
#
# SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only
#
# Contact KDAB at <info@kdab.com> for commercial licensing options.

# Docker container used by self-hosted runner

# docker build --build-arg GITHUB_RUNNER_TOKEN=<TOKEN> -t kddw_gh_runner .
# docker build --build-arg GITHUB_RUNNER_TOKEN=<TOKEN2> -t kddw_gh_runner2 .
# docker run -it kddw_gh_runner /home/ubuntu/actions-runner/run.sh

FROM ubuntu:24.04
MAINTAINER Sergio Martins (sergio.martins@kdab.com)

ARG GITHUB_RUNNER_TOKEN

ENV TZ=Europe/Berlin
ENV LC_CTYPE=C.UTF-8
ENV PATH=/home/ubuntu/.local/bin:$PATH

ENV IS_SELFHOSTED=1
ENV CTEST_PARALLEL_LEVEL=12

RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt update -qq && apt install build-essential software-properties-common lld git cmake ninja-build vim curl wget gdebi-core libdbus-glib-1-2 \
        mesa-common-dev libglu1-mesa-dev libglib2.0-dev libfontconfig \
        libxkbcommon-dev mesa-utils libgl1-mesa-dev libglu1-mesa-dev \
        libxkbcommon-x11-0 libssl-dev openssl unzip clang clang-tidy libgtk-3-dev \
        time xvfb python3-pip jq sudo libxml2-dev libxslt-dev \
        libx11-xcb1 \
        libxcb-glx0 \
        libxcb-keysyms1 \
        libxcb-image0 \
        libxcb-shm0 \
        libxcb-icccm4 \
        libxcb-sync1 \
        libxcb-xfixes0 \
        libxcb-shape0 \
        libxcb-render-util0 \
        -y

RUN ln -s /usr/bin/python3 /usr/bin/python
RUN rm /usr/lib/python3.12/EXTERNALLY-MANAGED

# Install GitHub command-line interface (gh)
# Instructions copied from https://github.com/cli/cli/blob/trunk/docs/install_linux.md
RUN mkdir -p -m 755 /etc/apt/keyrings \
    && curl -s https://cli.github.com/packages/githubcli-archive-keyring.gpg | tee /etc/apt/keyrings/githubcli-archive-keyring.gpg > /dev/null \
    && chmod go+r /etc/apt/keyrings/githubcli-archive-keyring.gpg \
    && echo "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/githubcli-archive-keyring.gpg] https://cli.github.com/packages stable main" | tee /etc/apt/sources.list.d/github-cli.list > /dev/null \
    && apt-get update \
    && apt-get install gh -y \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

RUN usermod -aG sudo ubuntu
RUN echo 'ubuntu ALL=(ALL) NOPASSWD:ALL' > /etc/sudoers.d/ubuntu
RUN chmod 0440 /etc/sudoers.d/ubuntu


# Install Qt

RUN pip install --no-cache-dir aqtinstall
RUN aqt install-qt linux desktop 6.6.0 gcc_64 --outputdir /opt/qt
RUN aqt install-qt linux desktop 5.15.2 gcc_64 --outputdir /opt/qt
ENV PATH=/opt/qt/5.15.2/gcc_64/bin/:/opt/qt/6.6.0/gcc_64/bin/:$PATH

# shiboken needs it for icu libs
ENV LD_LIBRARY_PATH=/opt/qt/6.6.0/gcc_64/lib/:$LD_LIBRARY_PATH

USER ubuntu
WORKDIR /home/ubuntu


# Install GitHub Actions runner
RUN mkdir actions-runner && cd actions-runner && \
    curl -o actions-runner-linux-x64-2.321.0.tar.gz -L https://github.com/actions/runner/releases/download/v2.321.0/actions-runner-linux-x64-2.321.0.tar.gz && \
    echo "ba46ba7ce3a4d7236b16fbe44419fb453bc08f866b24f04d549ec89f1722a29e  actions-runner-linux-x64-2.321.0.tar.gz" | shasum -a 256 -c && \
    tar xzf ./actions-runner-linux-x64-2.321.0.tar.gz && ./config.sh --labels ubuntu-latest,ubuntu-24.04 --url https://github.com/KDAB/KDDockWidgets --token $GITHUB_RUNNER_TOKEN
