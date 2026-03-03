#include <raylib.h>
#include <iostream>

int main() {
	int width = 600;
	int height = 600;
	InitWindow(width,height,"Space invaders game");
	SetTargetFPS(60);
	//game loop
	while (!WindowShouldClose()) {
		//Update logic

		BeginDrawing();
		ClearBackground(BLACK);
		EndDrawing();

	}
	CloseWindow();
}