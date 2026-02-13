#include "raylib.h"

int main() {
    InitWindow(800, 600, "Pi 5 GLES Test");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Hej Raspberry Pi 5!", 100, 300, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
