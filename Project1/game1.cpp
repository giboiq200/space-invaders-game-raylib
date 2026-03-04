#include <raylib.h>
#include <iostream>
#include <vector>

enum GameState {
	Menu,
	Play,
	Pause,
	GameOver
};

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

class Enemy {
public:
	bool isactive = true;
	Rectangle enemyRect;
	Enemy(float x, float y) {
		enemyRect = { x,y,30,30 };
	};
	void Draw() {
		if (isactive) {
			DrawRectangleRec(enemyRect, RED);
		}
	};
	void Update() {
		if (isactive) {
			enemyRect.y += 1.5;
			if (enemyRect.y > 700) {
				isactive = false;
			}
		}
	};
};


int main() {

	InitWindow(width,height,"Space invaders game");
	SetTargetFPS(60);
	Player player;
	std::vector<Bullet> bullets;
	std::vector<Enemy> enemies;
	int spacing = 80;
	float spawnTimer = 0;
	float spawnInterval = 4.5;
	bool ispaused = false;
	int score = 0;

	GameState currentState = Menu;

	for (int i = 0; i < 7; i++) {
		enemies.push_back(Enemy(100 + i * spacing, 40));
	}
	//game loop
	while (!WindowShouldClose()) {
		switch (currentState)
		{
		case Menu:
			if (IsKeyPressed(KEY_ENTER)) {
				spawnTimer = 3;
				currentState = Play;
			}
			break;
		case Play:
			spawnTimer += GetFrameTime();
			if (spawnTimer >= spawnInterval) {
				for (int i = 0; i < 7; i++) {
					enemies.push_back(Enemy(100 + i * spacing, 40));
				}
				spawnTimer = 0;
			}
			//Update logic
			player.Update();
			if (IsKeyPressed(KEY_SPACE)) {
				bullets.push_back(Bullet(player.x + player.w / 2, player.y));
			}
			for (int i = 0; i < bullets.size(); i++) {
				bullets[i].Update();
			}
			for (auto& enemy : enemies) {
				enemy.Update();
			}
			//collision enemy bullet
			for (auto& bullet : bullets) {
				for (auto& enemy : enemies) {
					if (bullet.active && enemy.isactive && CheckCollisionCircleRec(bullet.position, bullet.radius, enemy.enemyRect)) {
						bullet.active = false;
						enemy.isactive = false;
						score += 10;
					}
				}
			}
			if (IsKeyPressed(KEY_P)) {
				currentState = Pause;
			}

			for (auto& enemy : enemies) {
				if (enemy.isactive && CheckCollisionRecs(enemy.enemyRect, player.playerRec)) {
					currentState = GameOver;
				}
			}
			DrawText(TextFormat("Score: %d", score), 600, 30, 20, GREEN);
			break;
		case Pause:
			if (IsKeyPressed(KEY_P)) {
				currentState = Play;
			}
			break;
		case GameOver:
			if (IsKeyPressed(KEY_R)) {
				enemies.clear();
				bullets.clear();
				spawnTimer = 0;
				score = 0;
				currentState = Menu;
			}
			break;
		}
		BeginDrawing();
		ClearBackground(BLACK);
		
		switch (currentState) {
		case Menu:
			DrawText("Space Invaders Menu", 200, 350, 30, YELLOW);
			DrawText("Press Enter to play", 200, 450, 20, LIGHTGRAY);
			break;
		case Play:
		case Pause:
			player.Draw();
			for (int i = 0; i < bullets.size(); i++) {
				bullets[i].Draw();
			}
			for (auto& enemy : enemies) {
				enemy.Draw();
			}
			if (currentState == Pause) {
				DrawText("PAUSED", 250, 350, 40, YELLOW);
			}
			DrawText(TextFormat("Score: %d", score), 600, 30, 20, GREEN);
			break;

		case GameOver:
			DrawText("Game Over", 250, 350, 40, RED);
			DrawText("Press R to restart", 200, 400, 30, GRAY);
			break;

		}
		
		EndDrawing();

	}
	CloseWindow();
}