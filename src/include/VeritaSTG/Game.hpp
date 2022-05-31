/************************************************\
 * VeritaSTG: Game.hpp                          *
 * Defines the main game class.                 *
 *                                              *
 * Licensed under the MIT license.              *
\************************************************/

#pragma once

#include <string>
#include <fstream>
#include <concepts>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "CallbackRegistry.hpp"
#include "ResourceEngineWrapper.hpp"
#include "ResourcePool.hpp"

namespace VeritaSTG {

    enum class InitState {
        Uninitialized,
        Initializing,
        Initialized,
        Running,
        Destroyed,
    };

    class Game {
        // Resources
        GLFWwindow* window; // TEMPORARY: there will be a Renderer soon
        ResourceEngineWrapper resEngines;
        ResourcePool resPool;

        // Threads
        // Coming soon...

        // Miscellaneous State Variables
        InitState state = InitState::Uninitialized;

        CallbackRegistry cbReg;
    public:
        ~Game();

        int Initialize(void);
        void Run(void);
        void Cleanup(void);

        inline ResourceEngineWrapper* GetResourceEngineWrapper(void) { return &resEngines; }
        inline ResourcePool* GetResourcePool(void) { return &resPool; }
    };
}
