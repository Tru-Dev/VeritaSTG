/************************************************\
 * VeritaSTG: Game.cpp                          *
 * Root engine implementation.                  *
 *                                              *
 * Licensed under the MIT license.              *
\************************************************/

#include <VeritaSTG/Game.hpp>

#include <iostream>
#include <fstream>
#include <string>

#include <miniaudio.h>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <VeritaSTG/GlobalEventContext.hpp>
#include <VeritaSTG/ResourceEngineWrapper.hpp>
#include <VeritaSTG/log.hpp>

VeritaSTG::Game::~Game() {
    if (state != VeritaSTG::InitState::Uninitialized && state != VeritaSTG::InitState::Destroyed)
        Cleanup();
}

int VeritaSTG::Game::Initialize(void) {
    state = VeritaSTG::InitState::Initializing;

    resEngines.Initialize();

    glfwSetErrorCallback([](int error, const char* description) {
        VeritaSTG::Log(VeritaSTG::LogLevel::Error,
            fmt::format("GLFW:\n{}\nError code: {:#010x}", description, error)
        );
    });

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    window = glfwCreateWindow(800, 600, "VeritaSTG", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    
    int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0) {
        VeritaSTG::Log(VeritaSTG::LogLevel::Error, "Failed to initialize OpenGL context.");
        return -1;
    }

    VeritaSTG::Log(VeritaSTG::LogLevel::Info, fmt::format(
        "Loaded OpenGL version {}.{}",
        GLAD_VERSION_MAJOR(version),
        GLAD_VERSION_MINOR(version)
    ));

    glfwSetWindowUserPointer(window, static_cast<void*>(this));

    cbReg.SetInitCallback(
        [](GlobalEventContext<OnceData>* ctx){ ctx->LoadMusic("test_mus", "test.ogg"); }
    );
    cbReg.SetKeyCallback([](GlobalEventContext<KeyData>* ctx){
        auto k = ctx->GetEventData();
        
        if (k.action == GLFW_PRESS) {
            ctx->StopMusic("test_mus");
            if (k.key == GLFW_KEY_SPACE) {
                ctx->PlayMusic("test_mus");
            }
        }
    });

    state = VeritaSTG::InitState::Initialized;
    return 0;
}

void VeritaSTG::Game::Run(void) {
    // If the callback returns non-zero, there is no callback.
    if (cbReg.Init(GlobalEventContext<OnceData>(
        &(resEngines), &(resPool), // Resources
        {glfwGetTime()} // Event data
    )) != 0) VeritaSTG::Log(
        VeritaSTG::LogLevel::Warning,
        "The init event was raised, but there is no init callback registered!"
    );

    state = VeritaSTG::InitState::Running;

    glfwSetKeyCallback(window,
    [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        VeritaSTG::Game* self = static_cast<VeritaSTG::Game*>(glfwGetWindowUserPointer(window));
        // If the callback returns non-zero, there is no callback.
        if (self->cbReg.Key(GlobalEventContext<KeyData>(
            &(self->resEngines), &(self->resPool), // Resources
            {key, scancode, action, mods} // Event data
        )) != 0) VeritaSTG::Log(
            VeritaSTG::LogLevel::Warning,
            "A key event was raised, but there is no key callback registered!"
        );
    });

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        // No renderer yet.

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void VeritaSTG::Game::Cleanup(void) {
    glfwTerminate();
    VeritaSTG::CloseLogFile();
    resEngines.Uninitialize();
    state = VeritaSTG::InitState::Destroyed;
}
