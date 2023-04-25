// Copyright 2013 The Flutter Authors. All rights reserved.
// Copyright 2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
// Use of this source code is governed by a BSD-style license that can be
// found in the flutter engine LICENSE file.

// GlFW integration copied by from flutter's engine/examples/glfw/FlutterEmbedderGLFW.cc
// Qt integration code done by KDAB

#pragma once

#include <string>

class QString;
class GLFWwindow;
struct _FlutterEngine;

namespace KDDockWidgets {

namespace flutter {

/// @brief a Flutter embedder that runs our C++ tests
/// So we don't have to port 200 tests from C++ to Dart
class TestsEmbedder
{
public:
    static TestsEmbedder *self();
    explicit TestsEmbedder(int &argc, char **argv);
    ~TestsEmbedder();

    int run();

private:
    void init(const QString &projectPath, const QString &icudtlPath);
    void deinit();
    bool runFlutter(GLFWwindow *window,
                    const std::string &project_path,
                    const std::string &icudtl_path);
    GLFWwindow *m_glfwWindow = nullptr;
    _FlutterEngine *m_flutterEngine = nullptr;

    const int m_argc;
    char *const *m_argv;
};

}

}
