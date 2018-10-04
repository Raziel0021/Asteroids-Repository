#include "Screens/MainMenu.h"

#include <raylib.h>

#include "Game\GameManager.h"
#include "Credits.h"

using namespace Game;
namespace Game {

	namespace MainMenu
	{
		static const int FONT_SIZE_TITLE = 100;
		static const int FONT_SIZE_OPTIONS = 50;
		static const int FONT_SIZE_VERSION = FONT_SIZE_OPTIONS / 2;
		static const int DIVIDER_MEASURE_TEXT = 2;
		static const int GAMETITLE_LINE_DIVIDER = 6;
		static const int OPTIONS_LINE_DIVIDER = 3;
		static const float VERSION_LINE_DIVIDER = 1.7;
		bool menu;

		void showMenu()
		{
			DrawText(FormatText("ASTEROIDS"), Game::HALF_SCREENWIDTH - (MeasureText("ASTEROIDS", FONT_SIZE_TITLE) / DIVIDER_MEASURE_TEXT), Game::SCREENHEIGHT / GAMETITLE_LINE_DIVIDER, FONT_SIZE_TITLE, GREEN);
			DrawText(FormatText("Press Enter to Play"), Game::HALF_SCREENWIDTH - (MeasureText("Press Enter to Play", FONT_SIZE_OPTIONS) / DIVIDER_MEASURE_TEXT), Game::SCREENHEIGHT / OPTIONS_LINE_DIVIDER, FONT_SIZE_OPTIONS, DARKGRAY);
			DrawText(FormatText("2.Credits"), Game::HALF_SCREENWIDTH - (MeasureText("2.Credits", FONT_SIZE_OPTIONS) / DIVIDER_MEASURE_TEXT), Game::SCREENHEIGHT / OPTIONS_LINE_DIVIDER + FONT_SIZE_OPTIONS , FONT_SIZE_OPTIONS, DARKGRAY);
			DrawText(FormatText("Press Esc to Exit"), Game::HALF_SCREENWIDTH - (MeasureText("Press Esc to exit", FONT_SIZE_OPTIONS) / DIVIDER_MEASURE_TEXT), Game::SCREENHEIGHT / OPTIONS_LINE_DIVIDER + (FONT_SIZE_OPTIONS * 2), FONT_SIZE_OPTIONS, DARKGRAY);
			DrawText(FormatText("Version 0.01"), Game::HALF_SCREENWIDTH - (MeasureText("Version 0.01", FONT_SIZE_VERSION) / DIVIDER_MEASURE_TEXT), Game::SCREENHEIGHT / VERSION_LINE_DIVIDER + FONT_SIZE_OPTIONS, FONT_SIZE_VERSION, DARKGRAY);
			UpdateMenu();
		}
		void UpdateMenu()
		{
			if (IsKeyPressed(KEY_ENTER))
			{
				menu = false;
			}
			if (IsKeyPressed(KEY_TWO))
			{
				menu = false;
				Credits::credits = true;
			}
			if (IsKeyPressed(KEY_ESCAPE))
				CloseWindow();
		}
	}
}