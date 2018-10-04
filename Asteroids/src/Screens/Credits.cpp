#include "Credits.h"

#include <raylib.h>

#include "Game/GameManager.h"
#include "MainMenu.h"

using namespace Game;
namespace Game {
	namespace Credits
	{
		static const int FONT_SIZE_TITLE = 50;
		static const int FONT_SIZE = 35;
		static const int FONT_SIZE_URL = 16;
		static const float FONT_SIZE_HELPER = FONT_SIZE / 2;
		static const int GAMETITLE_LINE_DIVIDER = 10;
		static const int CREDITS_LINE_DIVIDER = 5;
		static const float HELPER_LINE_DIVIDER = 1.2;
		static const float VERSION_LINE_DIVIDER = 1.1;
		static const int LINE_DIVIDER = 4;
		static const int DIVIDER_MEASURE_TEXT = 2;
		bool credits;
		void showCredits()
		{
			DrawText(FormatText("ASTEROIDS"), Game::HALF_SCREENWIDTH - (MeasureText("ASTEROIDS", FONT_SIZE_TITLE) / DIVIDER_MEASURE_TEXT), Game::SCREENHEIGHT / GAMETITLE_LINE_DIVIDER, FONT_SIZE_TITLE, GREEN);
			DrawText(FormatText("Credits"), Game::HALF_SCREENWIDTH - (MeasureText("Credits", FONT_SIZE) / DIVIDER_MEASURE_TEXT), Game::SCREENHEIGHT / CREDITS_LINE_DIVIDER, FONT_SIZE, DARKGRAY);
			DrawText(FormatText("H�ctor Iv�n Pereira"), Game::HALF_SCREENWIDTH - (MeasureText("Hector Ivan Pereira", FONT_SIZE) / DIVIDER_MEASURE_TEXT), Game::SCREENHEIGHT / LINE_DIVIDER, FONT_SIZE, DARKGRAY);
			DrawText(FormatText("Assets Library"), Game::HALF_SCREENWIDTH - (MeasureText("Assets Library", FONT_SIZE) / DIVIDER_MEASURE_TEXT), Game::SCREENHEIGHT / LINE_DIVIDER + FONT_SIZE, FONT_SIZE, DARKGRAY);
			DrawText(FormatText("Raylib, Freesounds.org"), Game::HALF_SCREENWIDTH - (MeasureText("Raylib, Freesounds.org", FONT_SIZE) / DIVIDER_MEASURE_TEXT), Game::SCREENHEIGHT / LINE_DIVIDER + FONT_SIZE * 2, FONT_SIZE, DARKGRAY);
			DrawText(FormatText("Music"), Game::HALF_SCREENWIDTH - (MeasureText("Music", FONT_SIZE) / DIVIDER_MEASURE_TEXT), Game::SCREENHEIGHT / LINE_DIVIDER + FONT_SIZE * 3, FONT_SIZE, DARKGRAY);
			DrawText(FormatText(""), Game::HALF_SCREENWIDTH - (MeasureText("", FONT_SIZE) / DIVIDER_MEASURE_TEXT), Game::SCREENHEIGHT / LINE_DIVIDER + FONT_SIZE * 4, FONT_SIZE, DARKGRAY);
			DrawText(FormatText(""), Game::HALF_SCREENWIDTH - (MeasureText("", FONT_SIZE_URL) / DIVIDER_MEASURE_TEXT), Game::SCREENHEIGHT / LINE_DIVIDER + FONT_SIZE * 5, FONT_SIZE_URL, DARKGRAY);
			DrawText(FormatText("Sounds"), Game::HALF_SCREENWIDTH - (MeasureText("Sounds", FONT_SIZE) / DIVIDER_MEASURE_TEXT), Game::SCREENHEIGHT / LINE_DIVIDER + FONT_SIZE * 6, FONT_SIZE, DARKGRAY);
			DrawText(FormatText(""), Game::HALF_SCREENWIDTH - (MeasureText("", FONT_SIZE) / DIVIDER_MEASURE_TEXT), Game::SCREENHEIGHT / LINE_DIVIDER + FONT_SIZE * 7, FONT_SIZE, DARKGRAY);
			DrawText(FormatText(""), Game::HALF_SCREENWIDTH - (MeasureText("", FONT_SIZE_URL) / DIVIDER_MEASURE_TEXT), Game::SCREENHEIGHT / LINE_DIVIDER + FONT_SIZE * 8, FONT_SIZE_URL, DARKGRAY);
			DrawText(FormatText(""), Game::HALF_SCREENWIDTH - (MeasureText("", FONT_SIZE_URL) / DIVIDER_MEASURE_TEXT), Game::SCREENHEIGHT / LINE_DIVIDER + (FONT_SIZE * 8) + FONT_SIZE_URL, FONT_SIZE_URL, DARKGRAY);
			DrawText(FormatText("Press Esc to back to Menu"), Game::HALF_SCREENWIDTH - (MeasureText("Press Esc to back to Menu", FONT_SIZE_HELPER) / DIVIDER_MEASURE_TEXT), Game::SCREENHEIGHT / HELPER_LINE_DIVIDER + FONT_SIZE, FONT_SIZE_HELPER, DARKGRAY);
			DrawText(FormatText("Version 0.1"), Game::HALF_SCREENWIDTH - (MeasureText("Version 0.1", FONT_SIZE_HELPER) / DIVIDER_MEASURE_TEXT), Game::SCREENHEIGHT / VERSION_LINE_DIVIDER + FONT_SIZE, FONT_SIZE_HELPER, DARKGRAY);
			updateCredits();
		}
		void updateCredits()
		{
			if (IsKeyPressed(KEY_ESCAPE))
			{
				MainMenu::menu = true;
				credits = false;
			}
		}
	}
}