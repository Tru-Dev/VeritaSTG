/************************************************\
 * VeritaSTG: win32/main.cpp                    *
 * Winodws entrypoint.                          *
 *                                              *
 * Licensed under the MIT license.              *
\************************************************/


#include <VeritaSTG/Game.hpp>

int main(void) {
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
