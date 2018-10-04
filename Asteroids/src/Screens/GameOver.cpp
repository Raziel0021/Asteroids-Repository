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

		void showGameOver()
		{
			if (victory) 
			{
				DrawText(FormatText("Game Over"), Game::HALF_SCREENWIDTH - (MeasureText("Game Over", FONT_SIZE_TITLE) / DIVIDER_MEASURE_TEXT), Game::SCREENHEIGHT / TITLE_LINE_DIVIDER, FONT_SIZE_TITLE, DARKGRAY);
				DrawText(FormatText("Victory"), Game::HALF_SCREENWIDTH - (MeasureText("Victory", FONT_SIZE_TITLE) / DIVIDER_MEASURE_TEXT), Game::SCREENHEIGHT / WINNER_LINE_DIVIDER, FONT_SIZE_TITLE, GREEN);
				DrawText(FormatText("Press Enter Menu"), Game::HALF_SCREENWIDTH - (MeasureText("Press Enter Menu", FONT_SIZE_OPTIONS) / DIVIDER_MEASURE_TEXT), Game::SCREENHEIGHT / OPTIONS_LINE_DIVIDER + FONT_SIZE_TITLE, FONT_SIZE_OPTIONS, DARKGRAY);
				DrawText(FormatText("Press Esc Exit Game"), Game::HALF_SCREENWIDTH - (MeasureText("Press Esc Exit Game", FONT_SIZE_OPTIONS) / DIVIDER_MEASURE_TEXT), Game::SCREENHEIGHT / OPTIONS_LINE_DIVIDER + (FONT_SIZE_TITLE + FONT_SIZE_OPTIONS), FONT_SIZE_OPTIONS, DARKGRAY);

				updateGameOver();
			}
			else if(gameover)
			{
				DrawText(FormatText("Game Over"), Game::HALF_SCREENWIDTH - (MeasureText("Game Over", FONT_SIZE_TITLE) / DIVIDER_MEASURE_TEXT), Game::SCREENHEIGHT / TITLE_LINE_DIVIDER, FONT_SIZE_TITLE, DARKGRAY);
				DrawText(FormatText("You have been DESTROYED"), Game::HALF_SCREENWIDTH - (MeasureText("You have been DESTROYED", FONT_SIZE_TITLE) / DIVIDER_MEASURE_TEXT), Game::SCREENHEIGHT / WINNER_LINE_DIVIDER, FONT_SIZE_TITLE, RED);
				DrawText(FormatText("Press Enter Menu"), Game::HALF_SCREENWIDTH - (MeasureText("Press Enter Menu", FONT_SIZE_OPTIONS) / DIVIDER_MEASURE_TEXT), Game::SCREENHEIGHT / OPTIONS_LINE_DIVIDER + FONT_SIZE_TITLE, FONT_SIZE_OPTIONS, DARKGRAY);
				DrawText(FormatText("Press Esc Exit Game"), Game::HALF_SCREENWIDTH - (MeasureText("Press Esc Exit Game", FONT_SIZE_OPTIONS) / DIVIDER_MEASURE_TEXT), Game::SCREENHEIGHT / OPTIONS_LINE_DIVIDER + (FONT_SIZE_TITLE + FONT_SIZE_OPTIONS), FONT_SIZE_OPTIONS, DARKGRAY);

				updateGameOver();
			}
		}
		void updateGameOver()
		{
			if (IsKeyPressed(KEY_ESCAPE))
				CloseWindow();
			if (IsKeyPressed(KEY_ENTER))
			{
				GamePlay::InitGame();
				MainMenu::menu = true;
			}
		}
	}
}