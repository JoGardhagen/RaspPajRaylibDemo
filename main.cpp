#include "raylib.h"

int main() {
    InitWindow(800, 600, "Test Pi 5 Desktop");  // Skapa fönster

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Hej Pi 5 Desktop!", 200, 300, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
