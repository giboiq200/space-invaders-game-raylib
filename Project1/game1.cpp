#include <raylib.h>
#include <iostream>
#include <vector>

int width = 700;
int height = 700;

class Player {
public:
	int x = width/2;
	int y = height-30;
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
			x -= 4;
		}
		if (IsKeyDown(KEY_D)) {
			x += 4;
		}
		if (x < 0) {
			x = 0;
		}
		if (x + w > width) {
			x = width - w;
		}
		playerRec.x = (float)x;
	};
};

class Bullet {
public:
	Vector2 position;
	float radius = 5;
	bool active = false;

	Bullet(float x, float y) {
		position = { x,y };
		active = true;
	};
	
	void Update() {
		if (active) {
			position.y -= 4;

			if (position.y < 0) {
				active = false;
			}
		}
	};
	void Draw() {
		if (active) {
			DrawCircleV(position, radius, BLUE);
		}
	}
};


int main() {

	InitWindow(width,height,"Space invaders game");
	SetTargetFPS(60);
	Player player;
	std::vector<Bullet> bullets;
	//game loop
	while (!WindowShouldClose()) {
		//Update logic
		player.Update();
		if (IsKeyPressed(KEY_SPACE)) {
			bullets.push_back(Bullet(player.x + player.w / 2, player.y));
		}
		for (int i = 0; i < bullets.size(); i++) {
			bullets[i].Update();
		}
		BeginDrawing();
		ClearBackground(BLACK);
		player.Draw();
		for (int i = 0; i < bullets.size(); i++) {
			bullets[i].Draw();
		}
		EndDrawing();

	}
	CloseWindow();
}