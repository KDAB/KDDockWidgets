// Copyright 2013 The Flutter Authors. All rights reserved.
// Copyright 2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
// Use of this source code is governed by a BSD-style license that can be
// found in the flutter engine LICENSE file.

// GlFW integration copied by from flutter's engine/examples/glfw/FlutterEmbedderGLFW.cc
// Qt integration code done by KDAB

#include "tests_embedder.h"

#include "../../src/flutter/Platform.h"

#include <cassert>
#include <chrono>
#include <iostream>

#include "GLFW/glfw3.h"
#include "embedder.h"

#include <QDebug>
#include <QFileInfo>

// This value is calculated after the window is created.
static double g_pixelRatio = 1.0;
static const size_t kInitialWindowWidth = 800;
static const size_t kInitialWindowHeight = 600;

static_assert(FLUTTER_ENGINE_VERSION == 1,
              "This Flutter Embedder was authored against the stable Flutter "
              "API at version 1. There has been a serious breakage in the "
              "API. Please read the ChangeLog and take appropriate action "
              "before updating this assertion");

void GLFWcursorPositionCallbackAtPhase(GLFWwindow *window,
                                       FlutterPointerPhase phase,
                                       double x,
                                       double y)
{
    FlutterPointerEvent event = {};
    event.struct_size = sizeof(event);
    event.phase = phase;
    event.x = x * g_pixelRatio;
    event.y = y * g_pixelRatio;
    event.timestamp =
        size_t(std::chrono::duration_cast<std::chrono::microseconds>(
                   std::chrono::high_resolution_clock::now().time_since_epoch())
                   .count());
    FlutterEngineSendPointerEvent(
        reinterpret_cast<FlutterEngine>(glfwGetWindowUserPointer(window)), &event,
        1);
}

void GLFWcursorPositionCallback(GLFWwindow *window, double x, double y)
{
    GLFWcursorPositionCallbackAtPhase(window, FlutterPointerPhase::kMove, x, y);
}

void GLFWmouseButtonCallback(GLFWwindow *window,
                             int key,
                             int action,
                             int /*mods*/)
{
    if (key == GLFW_MOUSE_BUTTON_1 && action == GLFW_PRESS) {
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        GLFWcursorPositionCallbackAtPhase(window, FlutterPointerPhase::kDown, x, y);
        glfwSetCursorPosCallback(window, GLFWcursorPositionCallback);
    }

    if (key == GLFW_MOUSE_BUTTON_1 && action == GLFW_RELEASE) {
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        GLFWcursorPositionCallbackAtPhase(window, FlutterPointerPhase::kUp, x, y);
        glfwSetCursorPosCallback(window, nullptr);
    }
}

static void GLFWKeyCallback(GLFWwindow *window,
                            int key,
                            int /*scancode*/,
                            int action,
                            int /*mods*/)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void GLFWwindowSizeCallback(GLFWwindow *window, int width, int height)
{
    FlutterWindowMetricsEvent event = {};
    event.struct_size = sizeof(event);
    event.width = size_t(width * g_pixelRatio);
    event.height = size_t(height * g_pixelRatio);
    event.pixel_ratio = g_pixelRatio;
    FlutterEngineSendWindowMetricsEvent(
        reinterpret_cast<FlutterEngine>(glfwGetWindowUserPointer(window)),
        &event);
}
void GLFW_ErrorCallback(int error, const char *description)
{
    std::cout << "GLFW Error: (" << error << ") " << description << std::endl;
}

namespace KDDockWidgets::flutter {

static TestsEmbedder *s_testsEmbedder = nullptr;


TestsEmbedder *TestsEmbedder::self()
{
    return s_testsEmbedder;
}

TestsEmbedder::TestsEmbedder(int &argc, char **argv)
    : m_argc(argc)
    , m_argv(argv)
{
    Q_ASSERT(!s_testsEmbedder);
    s_testsEmbedder = this;

    init(QStringLiteral(FLUTTER_TEST_MAIN), QStringLiteral("%1/icudtl.dat").arg(QLatin1String(FLUTTER_ICUDTL_DIR)));
}

TestsEmbedder::~TestsEmbedder()
{
    deinit();
    s_testsEmbedder = nullptr;
}

void TestsEmbedder::init(const QString &projectPath, const QString &icudtlPath)
{
    if (!QFileInfo::exists(projectPath) || !QFileInfo::exists(icudtlPath))
        qFatal("Either icudtl or project path not found");


    glfwSetErrorCallback(GLFW_ErrorCallback);

    int result = glfwInit();
    if (result != GLFW_TRUE)
        qFatal("Could not initialize GLFW");

#if defined(Q_OS_LINUX)
    glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_EGL_CONTEXT_API);
#endif

    GLFWwindow *window = glfwCreateWindow(
        kInitialWindowWidth, kInitialWindowHeight, "KDDW tests", NULL, NULL);

    if (!window)
        qFatal("Could not create GLFW window.");

    int framebuffer_width, framebuffer_height;
    glfwGetFramebufferSize(window, &framebuffer_width, &framebuffer_height);
    g_pixelRatio = framebuffer_width * 1.0 / kInitialWindowWidth;

    const bool run_result = runFlutter(window, projectPath.toStdString(), icudtlPath.toStdString());
    if (!run_result)
        qFatal("Could not run the Flutter engine.");

    glfwSetKeyCallback(window, GLFWKeyCallback);
    glfwSetWindowSizeCallback(window, GLFWwindowSizeCallback);
    glfwSetMouseButtonCallback(window, GLFWmouseButtonCallback);

    m_glfwWindow = window;
}

void TestsEmbedder::deinit()
{
    if (m_flutterEngine) {
        const FlutterEngineResult res = FlutterEngineShutdown(m_flutterEngine);
        m_flutterEngine = nullptr;
        if (res == kSuccess)
            qDebug() << Q_FUNC_INFO << "Flutter stopped";
        else
            qDebug() << Q_FUNC_INFO << "Could not stop flutter" << res;
    }

    if (m_glfwWindow) {
        glfwDestroyWindow(m_glfwWindow);
        m_glfwWindow = nullptr;
    }

    glfwTerminate();
    qDebug() << Q_FUNC_INFO << "glfw terminated";
}

int TestsEmbedder::run()
{
    while (!glfwWindowShouldClose(m_glfwWindow)) {
        if (auto plat = KDDockWidgets::flutter::Platform::platformFlutter()) {
            auto result = plat->testsResult();
            if (result.has_value()) {
                return result.value();
            }
        }

        glfwPollEvents();
    }

    return 0;
}


bool TestsEmbedder::runFlutter(GLFWwindow *window,
                               const std::string &project_path,
                               const std::string &icudtl_path)
{
    FlutterRendererConfig config = {};
    config.type = kOpenGL;
    config.open_gl.struct_size = sizeof(config.open_gl);
    config.open_gl.make_current = [](void *userdata) -> bool {
        glfwMakeContextCurrent(static_cast<GLFWwindow *>(userdata));
        return true;
    };
    config.open_gl.clear_current = [](void *) -> bool {
        glfwMakeContextCurrent(nullptr); // is this even a thing?
        return true;
    };
    config.open_gl.present = [](void *userdata) -> bool {
        glfwSwapBuffers(static_cast<GLFWwindow *>(userdata));
        return true;
    };
    config.open_gl.fbo_callback = [](void *) -> uint32_t {
        return 0; // FBO0
    };
    config.open_gl.gl_proc_resolver = [](void *, const char *name) -> void * {
        return reinterpret_cast<void *>(glfwGetProcAddress(name));
    };

    // This directory is generated by `flutter build bundle`.
    const std::string assets_path = project_path + "/build/flutter_assets";

    FlutterProjectArgs args = {
        .struct_size = sizeof(FlutterProjectArgs),
        .assets_path = assets_path.c_str(),
        .icu_data_path =
            icudtl_path.c_str(), // Find this in your bin/cache directory.
        .command_line_argc = m_argc,
        .command_line_argv = m_argv,
        .dart_entrypoint_argc = m_argc,
        .dart_entrypoint_argv = m_argv
    };

    FlutterEngineResult result =
        FlutterEngineRun(FLUTTER_ENGINE_VERSION, &config, // renderer
                         &args, window, &m_flutterEngine);
    if (result != kSuccess || !m_flutterEngine) {
        std::cout << "Could not run the Flutter Engine." << std::endl;
        return false;
    }

    glfwSetWindowUserPointer(window, m_flutterEngine);
    GLFWwindowSizeCallback(window, kInitialWindowWidth, kInitialWindowHeight);

    return true;
}

}
