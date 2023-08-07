// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license:

// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
//       copyright notice, this list of conditions and the following
//       disclaimer in the documentation and/or other materials provided
//       with the distribution.
//     * Neither the name of Google Inc. nor the names of its
//       contributors may be used to endorse or promote products derived
//       from this software without specific prior written permission.

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
// ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
// ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// GlFW integration copied by from flutter's engine/examples/glfw/FlutterEmbedderGLFW.cc


#include "tests_embedder.h"

#include "../../src/flutter/Platform.h"
#include "../../src/core/Logging_p.h"

#include <cassert>
#include <chrono>
#include <iostream>
#include <filesystem>
#include <stdlib.h>

#include "GLFW/glfw3.h"
#include "flutter_embedder.h"

// This value is calculated after the window is created.
static double g_pixelRatio = 1.0;
static const size_t kInitialWindowWidth = 1600;
static const size_t kInitialWindowHeight = 1400;
static GLFWwindow *s_window = nullptr;

namespace fs = std::filesystem;

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

static std::optional<KDDockWidgets::Point> s_requestedPos;
void GLFWmouseButtonCallback(GLFWwindow *window,
                             int key,
                             int action,
                             int /*mods*/)
{
    if (key != GLFW_MOUSE_BUTTON_1)
        return;

    if (action != GLFW_PRESS && action != GLFW_RELEASE)
        return;

    double x, y;
    if (s_requestedPos == std::nullopt) {
        glfwGetCursorPos(window, &x, &y);
    } else {
        x = s_requestedPos->x();
        y = s_requestedPos->y();
    }

    if (action == GLFW_PRESS) {
        GLFWcursorPositionCallbackAtPhase(window, FlutterPointerPhase::kDown, x, y);
        glfwSetCursorPosCallback(window, GLFWcursorPositionCallback);
    }

    if (action == GLFW_RELEASE) {
        GLFWcursorPositionCallbackAtPhase(window, FlutterPointerPhase::kUp, x, y);
        glfwSetCursorPosCallback(window, nullptr);
    }
}

QCoro::Task<bool> kddw_fakeMouseButton(KDDockWidgets::Point globalPos, bool isPress)
{
    if (!s_window)
        co_return true;

    KDDW_TRACE("GLFW: kddw_fakeMouseButton({}, {})", globalPos, isPress);
    s_requestedPos = globalPos;
    GLFWmouseButtonCallback(s_window, GLFW_MOUSE_BUTTON_1, isPress ? GLFW_PRESS : GLFW_RELEASE, 0);
    s_requestedPos = std::nullopt;

    // Let the release render and rebuild stuff
    if (!isPress)
        co_await KDDockWidgets::flutter::Platform::platformFlutter()->tests_wait(1000);

    co_return true;
}

QCoro::Task<bool> kddw_fakeMouseMove(KDDockWidgets::Point globalPos)
{
    if (!s_window)
        co_return true;

    GLFWcursorPositionCallback(s_window, globalPos.x(), globalPos.y());

    co_await KDDockWidgets::flutter::Platform::platformFlutter()->tests_wait(10);
    co_return true;
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
    // Just so it works through ssh
    setenv("DISPLAY", ":0", 0);

    assert(!s_testsEmbedder);
    s_testsEmbedder = this;

    const auto icuPath = std::string(FLUTTER_ICUDTL_DIR) + std::string("/icudtl.dat");

    init(std::string(FLUTTER_TEST_MAIN), icuPath);
}

TestsEmbedder::~TestsEmbedder()
{
    deinit();
    s_testsEmbedder = nullptr;
}

void TestsEmbedder::init(const std::string &projectPath, const std::string &icudtlPath)
{
    if (!fs::exists(projectPath) || !fs::exists(icudtlPath)) {
        KDDW_ERROR("Either icudtl or project path not found");
        std::abort();
    }

    glfwSetErrorCallback(GLFW_ErrorCallback);

    int result = glfwInit();
    if (result != GLFW_TRUE) {
        KDDW_ERROR("Could not initialize GLFW");
        std::abort();
    }

#ifdef __linux__
    glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_EGL_CONTEXT_API);
#endif

    GLFWwindow *window = glfwCreateWindow(
        kInitialWindowWidth, kInitialWindowHeight, "KDDW tests", NULL, NULL);

    if (!window) {
        KDDW_ERROR("Could not create GLFW window.");
        std::abort();
    }

    int framebuffer_width, framebuffer_height;
    glfwGetFramebufferSize(window, &framebuffer_width, &framebuffer_height);
    g_pixelRatio = framebuffer_width * 1.0 / kInitialWindowWidth;

    const bool run_result = runFlutter(window, projectPath, icudtlPath);
    if (!run_result) {
        KDDW_ERROR("Could not run the Flutter engine.");
        std::abort();
    }

    glfwSetKeyCallback(window, GLFWKeyCallback);
    glfwSetWindowSizeCallback(window, GLFWwindowSizeCallback);
    glfwSetMouseButtonCallback(window, GLFWmouseButtonCallback);

    m_glfwWindow = window;
    s_window = window;
}

void TestsEmbedder::deinit()
{
    s_window = nullptr;

    if (m_flutterEngine) {
        const FlutterEngineResult res = FlutterEngineShutdown(m_flutterEngine);
        m_flutterEngine = nullptr;
        if (res != kSuccess)
            KDDW_WARN("TestsEmbedder::deinit: Could not stop flutter {}", int(res));
    }

    if (m_glfwWindow) {
        glfwDestroyWindow(m_glfwWindow);
        m_glfwWindow = nullptr;
    }

    glfwTerminate();
    KDDW_WARN("TestsEmbedder::deinit: glfw terminated}");
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

        glfwWaitEventsTimeout(1);
    }

    return 0;
}


static bool isAOT()
{
    const char *value = std::getenv("KDDW_FLUTTER_TESTS_USE_AOT");
    return value && std::string(value) == "1";
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
        static bool initial = true;
        if (initial) {
            // HACK: Fixes a GLFW black screen at startup which happens sometimes.
            // No idea how to fix it properly
            kddw_fakeMouseButton({ 1, 1 }, true);
            initial = false;
        }

        glfwSwapBuffers(static_cast<GLFWwindow *>(userdata));
        return true;
    };
    config.open_gl.fbo_callback = [](void *) -> uint32_t {
        return 0; // FBO0
    };
    config.open_gl.gl_proc_resolver = [](void *, const char *name) -> void * {
        return reinterpret_cast<void *>(glfwGetProcAddress(name));
    };

    // This directory is generated by `flutter build bundle`. Used both in AOT and JIT mode
    const std::string assets_path = project_path + "/build/flutter_assets";

    // flutter build linux --release , for AOT mode
    const std::string aot_elf = project_path + "/build/linux/x64/release/bundle/lib/libapp.so";

    FlutterEngineAOTData aot_data = nullptr;
    if (isAOT()) {
        const FlutterEngineAOTDataSource source = { .type = kFlutterEngineAOTDataSourceTypeElfPath, .elf_path = aot_elf.c_str() };
        auto res = FlutterEngineCreateAOTData(&source, &aot_data);
        if (res != kSuccess || !aot_data) {
            KDDW_ERROR("Could not prepare AOT data result={}", int(res));
            return false;
        }
    }

    FlutterProjectArgs args = {
        .struct_size = sizeof(FlutterProjectArgs),
        .assets_path = assets_path.c_str(),
        .icu_data_path =
            icudtl_path.c_str(), // Find this in your bin/cache directory.
        .command_line_argc = m_argc,
        .command_line_argv = m_argv,
        .aot_data = aot_data,
        .dart_entrypoint_argc = m_argc,
        .dart_entrypoint_argv = m_argv,
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
