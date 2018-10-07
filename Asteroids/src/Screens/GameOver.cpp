#include "GameOver.h"

#include <raylib.h>

#include "Game\GamePlay.h"
#include "Game/GameManager.h"
#include "MainMenu.h"

using namespace Game;
using namespace GamePlay;
namespace Game {
	namespace EndOfGame
	{
		static const int FONT_SIZE_TITLE = 70;
		static const int FONT_SIZE_OPTIONS = 50;
		static const int DIVIDER_MEASURE_TEXT = 2;
		static const float TITLE_LINE_DIVIDER = 4.5;
		static const int WINNER_LINE_DIVIDER = 3;
		static const float OPTIONS_LINE_DIVIDER = 2.5f;
		static const float MULTIPLIER_BUTTON_WIDTH = 1.15f;
		static const float SPACE_BETWEEN_LINES = 1.3f;
		static Vector2 mousePoint;

		static Rectangle menuButton;
		static Rectangle exitButton;
		void initGameOverButtons()
		{
			menuButton = { (float)Game::HALF_SCREENWIDTH - (MeasureText("Menu", FONT_SIZE_OPTIONS)* MULTIPLIER_BUTTON_WIDTH / DIVIDER_MEASURE_TEXT),
				(float)Game::SCREENHEIGHT / OPTIONS_LINE_DIVIDER + FONT_SIZE_TITLE,
				(float)MeasureText("Menu", FONT_SIZE_OPTIONS)* MULTIPLIER_BUTTON_WIDTH ,
				(float)FONT_SIZE_OPTIONS };
			exitButton = { (float)Game::HALF_SCREENWIDTH - (MeasureText("Exit", FONT_SIZE_OPTIONS)* MULTIPLIER_BUTTON_WIDTH / DIVIDER_MEASURE_TEXT),
				(float)Game::SCREENHEIGHT / OPTIONS_LINE_DIVIDER + (FONT_SIZE_OPTIONS +FONT_SIZE_TITLE)* SPACE_BETWEEN_LINES,
				(float)MeasureText("Exit", FONT_SIZE_OPTIONS)* MULTIPLIER_BUTTON_WIDTH,
				(float)FONT_SIZE_OPTIONS };
		}
		void showGameOver()
		{
			initGameOverButtons();
			updateGameOver();
			if (victory) 
			{
				DrawText(FormatText("Game Over"), Game::HALF_SCREENWIDTH - (MeasureText("Game Over", FONT_SIZE_TITLE) / DIVIDER_MEASURE_TEXT), Game::SCREENHEIGHT / TITLE_LINE_DIVIDER, FONT_SIZE_TITLE, DARKGRAY);
				DrawText(FormatText("Victory"), Game::HALF_SCREENWIDTH - (MeasureText("Victory", FONT_SIZE_TITLE) / DIVIDER_MEASURE_TEXT), Game::SCREENHEIGHT / WINNER_LINE_DIVIDER, FONT_SIZE_TITLE, GREEN);
				
				DrawRectangle(menuButton.x, menuButton.y, menuButton.width, menuButton.height, LIGHTGRAY);
				DrawText(FormatText("Menu"), Game::HALF_SCREENWIDTH - (MeasureText("Menu", FONT_SIZE_OPTIONS) / DIVIDER_MEASURE_TEXT), Game::SCREENHEIGHT / OPTIONS_LINE_DIVIDER + FONT_SIZE_TITLE, FONT_SIZE_OPTIONS, DARKGRAY);
				
				DrawRectangle(exitButton.x, exitButton.y, exitButton.width, exitButton.height, LIGHTGRAY);
				DrawText(FormatText("Exit"), Game::HALF_SCREENWIDTH - (MeasureText("Exit", FONT_SIZE_OPTIONS) / DIVIDER_MEASURE_TEXT), Game::SCREENHEIGHT / OPTIONS_LINE_DIVIDER + (FONT_SIZE_TITLE + FONT_SIZE_OPTIONS) * SPACE_BETWEEN_LINES, FONT_SIZE_OPTIONS, DARKGRAY);

			}
			else if(gameover)
			{
				DrawText(FormatText("Game Over"), Game::HALF_SCREENWIDTH - (MeasureText("Game Over", FONT_SIZE_TITLE) / DIVIDER_MEASURE_TEXT), Game::SCREENHEIGHT / TITLE_LINE_DIVIDER, FONT_SIZE_TITLE, DARKGRAY);
				DrawText(FormatText("You have been DESTROYED"), Game::HALF_SCREENWIDTH - (MeasureText("You have been DESTROYED", FONT_SIZE_TITLE) / DIVIDER_MEASURE_TEXT), Game::SCREENHEIGHT / WINNER_LINE_DIVIDER, FONT_SIZE_TITLE, RED);
				
				DrawRectangle(menuButton.x, menuButton.y, menuButton.width, menuButton.height, LIGHTGRAY);
				DrawText(FormatText("Menu"), Game::HALF_SCREENWIDTH - (MeasureText("Menu", FONT_SIZE_OPTIONS) / DIVIDER_MEASURE_TEXT), Game::SCREENHEIGHT / OPTIONS_LINE_DIVIDER + FONT_SIZE_TITLE, FONT_SIZE_OPTIONS, DARKGRAY);
				
				DrawRectangle(exitButton.x, exitButton.y, exitButton.width, exitButton.height, LIGHTGRAY);
				DrawText(FormatText("Exit"), Game::HALF_SCREENWIDTH - (MeasureText("Exit", FONT_SIZE_OPTIONS) / DIVIDER_MEASURE_TEXT), Game::SCREENHEIGHT / OPTIONS_LINE_DIVIDER + (FONT_SIZE_TITLE + FONT_SIZE_OPTIONS) * SPACE_BETWEEN_LINES, FONT_SIZE_OPTIONS, DARKGRAY);

			}
		}
		void updateGameOver()
		{
			mousePoint = GetMousePosition();
			if (gameover || victory) {
				if (CheckCollisionPointRec(mousePoint, menuButton))
				{
					if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
					{
						GamePlay::InitGame();
						MainMenu::menu = true;
					}
				}

				if (CheckCollisionPointRec(mousePoint, exitButton))
				{
					if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
					{
						CloseWindow();
					}
				}
			}
		}
	}
}