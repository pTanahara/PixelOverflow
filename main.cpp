#include <debug.hpp>
#include <engine.hpp>

int main(int argc, char* argv[]) {
    dprint("Starting 3D Engine...");

    PixelOverflow::Engine engine;
    engine.run();

    dprint("Exiting 3D Engine...");
    return 0;
}

