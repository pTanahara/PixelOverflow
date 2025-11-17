#include "SDL3/SDL_render.h"
#include "core/context.hpp"
#include "core/types.hpp"
#include "render/framebuffer.hpp"
#include "render/renderer.hpp"
#include <cmath>
#include <cstdint>
#include <engine.hpp>
#include <debug.hpp>

#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>
#include <memory>

using namespace PixelOverflow;

Engine::Engine() {
    Context context = Context::get();

    u32 width = context.engine.width;
    u32 height = context.engine.height;
    u32 num_tiles = std::ceil((f32)width / context.render.tile_x) * std::ceil((f32)height / context.render.tile_y);

    renderer = std::make_unique<Renderer>(
        context.engine.width,
        context.engine.height,
        num_tiles,
        context.render.primitive_reserve_size,
        context.render.primitive_reserve_size_per_tile
    );

    if (SDL_Init(SDL_INIT_VIDEO) == false) {
        dprint("SDL_Init Error: ", SDL_GetError());
        return;
    } 

    window = SDL_CreateWindow(
        context.engine.title.c_str(),
        context.engine.width,
        context.engine.height,
        0
    );

    if (!window) {
        SDL_Quit();
        dprint("SDL_CreateWindow Error: ", SDL_GetError());
        return;
    } 

    sdl_renderer = SDL_CreateRenderer(window, nullptr);
    if (!sdl_renderer) {
        SDL_DestroyWindow(window);
        SDL_Quit();
        dprint("SDL_CreateRenderer Error: ", SDL_GetError());
        return;
    }

    if (DEBUG) {
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void) io;

        ImGui_ImplSDL3_InitForSDLRenderer(window, sdl_renderer);
        ImGui_ImplSDLRenderer3_Init(sdl_renderer);
    }

    running = true;

    dprint("SDL initialized successfully");
}

Engine::~Engine() {
    if (DEBUG) {
        ImGui_ImplSDL3_Shutdown();
        ImGui_ImplSDLRenderer3_Shutdown();
        ImGui::DestroyContext();
    }

    if (sdl_renderer) SDL_DestroyRenderer(sdl_renderer);
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();
}

void Engine::run() {
    Context context = Context::get();
    u32 width = context.engine.width;
    u32 height = context.engine.height;

    SDL_Texture* texture = SDL_CreateTexture(
        sdl_renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_STREAMING,
        width, height
    );

    SDL_FRect src = { 0, (float)height, (float)width, -(float)height }; // altura negativa

    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }

            ImGui_ImplSDL3_ProcessEvent(&event);
        }

        if (DEBUG) {
            ImGui_ImplSDL3_NewFrame();
            ImGui::NewFrame();

            ImGui::Begin("DEBUG");
            ImGui::Text("FPS: %.2f", ImGui::GetIO().Framerate);

            ImGui::End();
            ImGui::Render();
        }

        renderer->add_test_triangle();
        renderer->render_framebuffer();
        FramebufferLDR& framebuffer = renderer->get_framebuffer();
        
        SDL_UpdateTexture(texture, nullptr, framebuffer.pixels.data(), width * sizeof(uint32_t));

        SDL_RenderClear(sdl_renderer);
        SDL_RenderTexture(sdl_renderer, texture, nullptr, &src);

        if (DEBUG) ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), sdl_renderer);

        SDL_RenderPresent(sdl_renderer);

        //SDL_Delay(16);
    }
}

