#include <raylib.h>
#include <iostream>

class Player {
public:
	int x = 300;
	int y = 550;
	int w = 20;
	int h = 20;
	Rectangle playerRec;
	Player() {
		playerRec = { (float)x, (float)y, (float)w, (float)h };
	}
	void Draw() {
		DrawRectangleRec(playerRec, GREEN);
	};
	void Update() {
		if (IsKeyDown(KEY_A)) {
			x -= 3;
		}
		if (IsKeyDown(KEY_D)) {
			x += 3;
		}
		if (x < 0) {
			x = 0;
		}
		if (x + w > 600) {
			x = 600 - w;
		}
		playerRec.x = (float)x;
	};
};


int main() {
	int width = 600;
	int height = 600;
	InitWindow(width,height,"Space invaders game");
	SetTargetFPS(60);
	Player player;
	//game loop
	while (!WindowShouldClose()) {
		//Update logic
		player.Update();

		BeginDrawing();
		ClearBackground(BLACK);
		player.Draw();
		EndDrawing();

	}
	CloseWindow();
}