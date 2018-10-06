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
		static Vector2 mousePoint;
		static Rectangle playButton;
		static Rectangle creditsButton;
		static Rectangle exitButton;

		void showMenu()
		{
			UpdateMenu();

			DrawText(FormatText("ASTEROIDS"), Game::HALF_SCREENWIDTH - (MeasureText("ASTEROIDS", FONT_SIZE_TITLE) / DIVIDER_MEASURE_TEXT), Game::SCREENHEIGHT / GAMETITLE_LINE_DIVIDER, FONT_SIZE_TITLE, GREEN);
			DrawText(FormatText("Press Enter to Play"), Game::HALF_SCREENWIDTH - (MeasureText("Press Enter to Play", FONT_SIZE_OPTIONS) / DIVIDER_MEASURE_TEXT), Game::SCREENHEIGHT / OPTIONS_LINE_DIVIDER, FONT_SIZE_OPTIONS, DARKGRAY);
			DrawText(FormatText("Press C Credits"), Game::HALF_SCREENWIDTH - (MeasureText("Press C Credits", FONT_SIZE_OPTIONS) / DIVIDER_MEASURE_TEXT), Game::SCREENHEIGHT / OPTIONS_LINE_DIVIDER + FONT_SIZE_OPTIONS , FONT_SIZE_OPTIONS, DARKGRAY);
			DrawText(FormatText("Press Esc to Exit"), Game::HALF_SCREENWIDTH - (MeasureText("Press Esc to exit", FONT_SIZE_OPTIONS) / DIVIDER_MEASURE_TEXT), Game::SCREENHEIGHT / OPTIONS_LINE_DIVIDER + (FONT_SIZE_OPTIONS * 2), FONT_SIZE_OPTIONS, DARKGRAY);
			DrawText(FormatText("Version 0.2"), Game::HALF_SCREENWIDTH - (MeasureText("Version 0.2", FONT_SIZE_VERSION) / DIVIDER_MEASURE_TEXT), Game::SCREENHEIGHT / VERSION_LINE_DIVIDER + FONT_SIZE_OPTIONS, FONT_SIZE_VERSION, DARKGRAY);
			
		}
		void UpdateMenu()
		{

			//mousePoint = GetMousePosition();


			//if (CheckCollisionPointRec(mousePoint, colorsRecs[i]))
			//{
			//	colors[i].a = 120;

			//	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
			//		selected[i] = !selected[i];
			//}
			//else 
			//	colors[i].a = 255;

			if (IsKeyPressed(KEY_ENTER))
			{
				menu = false;
			}
			if (IsKeyPressed(KEY_C))
			{
				menu = false;
				Credits::credits = true;
			}
			if (IsKeyPressed(KEY_ESCAPE))
				CloseWindow();
		}
	}
}