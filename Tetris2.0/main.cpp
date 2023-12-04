#include <raylib.h>
#include "game.h"


double lastUpdateTime = 0;

bool EventTriggerred(double interval)
{
	double currentTime = GetTime();
	if (currentTime - lastUpdateTime >= interval)
	{
		lastUpdateTime = currentTime;
		return true;
	}
	return false;
}

int main()
{
	Color darkBlue = { 44, 44, 127, 255 };
	InitWindow(300, 600, "raylib Tetris");
	SetTargetFPS(60);

	Game game = Game();


	while (WindowShouldClose() == false)
	{
		game.HandleInput();
		if (EventTriggerred(0.5))
		{
			game.MoveBlockDown();
		}

		BeginDrawing();
		ClearBackground(darkBlue); // §æ§à§ß
		game.Draw();
		EndDrawing();
	}

	CloseWindow();
}