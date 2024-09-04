#include "include/game.h"
#include <raylib.h>

int main()
{
    SEAL* seal = seal_data("seal/game.seal");

    CELL_SIZE = seal_int(seal, "CELL_SIZE");

    DEBUG = seal_bool(seal, "DEBUG");
    FRICTION = seal_float(seal, "FRICTION");
    ROWS = seal_int(seal, "ROWS");
    COLS = seal_int(seal, "COLS");
    WIDTH = seal_int(seal, "WIDTH");
    HEIGHT = seal_int(seal, "HEIGHT");
    TITLE = seal_string(seal, "TITLE");
    FPS = seal_int(seal, "FPS");
    PARTICLE_MAX_SIZE = seal_int(seal, "PARTICLE_MAX_SIZE");

    InitWindow(WIDTH, HEIGHT, TITLE);
    InitAudioDevice();

    SetTargetFPS(FPS);

    SetExitKey(KEY_NULL);

    start();

    while(!WindowShouldClose())
    {
        update();
        BeginDrawing();
        ClearBackground(RAYWHITE);
        late_update();
        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();
    
    finish();

    return 0;
}