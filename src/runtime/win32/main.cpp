/************************************************\
 * VeritaSTG: win32/main.cpp                    *
 * Windows entrypoint.                          *
 *                                              *
 * Licensed under the MIT license.              *
\************************************************/

#include <windows.h>
#include <string.h>

#include <VeritaSTG/Game.hpp>

int main(int argc, char* argv[]) {
    if (argc > 1 && _stricmp(argv[1], "-C") == 0 &&
        (AttachConsole(ATTACH_PARENT_PROCESS) || AllocConsole())
    ) {
        freopen("CONIN$",  "r", stdin); 
        freopen("CONOUT$", "w", stdout); 
        freopen("CONOUT$", "w", stderr);
    }

    VeritaSTG::Game game;

    int ret = game.Initialize();
    if (ret != 0) {
        return ret;
    } else {
        game.Run();
    }
    game.Cleanup();
    return 0;
}
