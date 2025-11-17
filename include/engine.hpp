#pragma once

#include "render/renderer.hpp"
#include <SDL3/SDL.h>
#include <memory>


namespace PixelOverflow {
    class Engine {
        private:
            std::unique_ptr<Renderer> renderer = nullptr;

            SDL_Window* window = nullptr;
            SDL_Renderer* sdl_renderer = nullptr;
            bool running = false;

        public:
            Engine();
            ~Engine();

            void run();

    };
}

