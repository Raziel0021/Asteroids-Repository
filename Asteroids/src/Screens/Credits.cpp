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

		static Vector2 mousePoint;
		static Rectangle backButton;
		static const float MULTIPLIER_BUTTON_WIDTH = 1.15f;
		static const float SPACE_BETWEEN_LINES = 1.3f;

		void initCreditsButtons()
		{
			backButton = { (float)Game::HALF_SCREENWIDTH - (MeasureText("Back", FONT_SIZE)* MULTIPLIER_BUTTON_WIDTH / DIVIDER_MEASURE_TEXT),
				(float)Game::SCREENHEIGHT / HELPER_LINE_DIVIDER + FONT_SIZE,
				(float)MeasureText("Back", FONT_SIZE)* MULTIPLIER_BUTTON_WIDTH ,
				(float)FONT_SIZE };
		}
		void showCredits()
		{
			initCreditsButtons();
			updateCredits();

			DrawText(FormatText("ASTEROIDS"), Game::HALF_SCREENWIDTH - (MeasureText("ASTEROIDS", FONT_SIZE_TITLE) / DIVIDER_MEASURE_TEXT), Game::SCREENHEIGHT / GAMETITLE_LINE_DIVIDER, FONT_SIZE_TITLE, GREEN);
			DrawText(FormatText("Credits"), Game::HALF_SCREENWIDTH - (MeasureText("Credits", FONT_SIZE) / DIVIDER_MEASURE_TEXT), Game::SCREENHEIGHT / CREDITS_LINE_DIVIDER, FONT_SIZE, DARKGRAY);
			DrawText(FormatText("Héctor Iván Pereira"), Game::HALF_SCREENWIDTH - (MeasureText("Hector Ivan Pereira", FONT_SIZE) / DIVIDER_MEASURE_TEXT), Game::SCREENHEIGHT / LINE_DIVIDER, FONT_SIZE, DARKGRAY);
			DrawText(FormatText("Assets Library"), Game::HALF_SCREENWIDTH - (MeasureText("Assets Library", FONT_SIZE) / DIVIDER_MEASURE_TEXT), Game::SCREENHEIGHT / LINE_DIVIDER + FONT_SIZE, FONT_SIZE, DARKGRAY);
			DrawText(FormatText("Raylib, boscaceoil.net"), Game::HALF_SCREENWIDTH - (MeasureText("Raylib, Freesounds.org", FONT_SIZE) / DIVIDER_MEASURE_TEXT), Game::SCREENHEIGHT / LINE_DIVIDER + FONT_SIZE * 2, FONT_SIZE, DARKGRAY);
			DrawText(FormatText("Music"), Game::HALF_SCREENWIDTH - (MeasureText("Music", FONT_SIZE) / DIVIDER_MEASURE_TEXT), Game::SCREENHEIGHT / LINE_DIVIDER + FONT_SIZE * 3, FONT_SIZE, DARKGRAY);
			DrawText(FormatText("Héctor Iván Pereira"), Game::HALF_SCREENWIDTH - (MeasureText("Héctor Iván Pereira", FONT_SIZE) / DIVIDER_MEASURE_TEXT), Game::SCREENHEIGHT / LINE_DIVIDER + FONT_SIZE * 4, FONT_SIZE, DARKGRAY);
			DrawText(FormatText(""), Game::HALF_SCREENWIDTH - (MeasureText("", FONT_SIZE_URL) / DIVIDER_MEASURE_TEXT), Game::SCREENHEIGHT / LINE_DIVIDER + FONT_SIZE * 5, FONT_SIZE_URL, DARKGRAY);
			DrawText(FormatText("Sounds"), Game::HALF_SCREENWIDTH - (MeasureText("Sounds", FONT_SIZE) / DIVIDER_MEASURE_TEXT), Game::SCREENHEIGHT / LINE_DIVIDER + FONT_SIZE * 6, FONT_SIZE, DARKGRAY);
			DrawText(FormatText("Héctor Iván Pereira"), Game::HALF_SCREENWIDTH - (MeasureText("Héctor Iván Pereira", FONT_SIZE) / DIVIDER_MEASURE_TEXT), Game::SCREENHEIGHT / LINE_DIVIDER + FONT_SIZE * 7, FONT_SIZE, DARKGRAY);
			DrawText(FormatText(""), Game::HALF_SCREENWIDTH - (MeasureText("", FONT_SIZE_URL) / DIVIDER_MEASURE_TEXT), Game::SCREENHEIGHT / LINE_DIVIDER + FONT_SIZE * 8, FONT_SIZE_URL, DARKGRAY);
			DrawText(FormatText(""), Game::HALF_SCREENWIDTH - (MeasureText("", FONT_SIZE_URL) / DIVIDER_MEASURE_TEXT), Game::SCREENHEIGHT / LINE_DIVIDER + (FONT_SIZE * 8) + FONT_SIZE_URL, FONT_SIZE_URL, DARKGRAY);

			DrawRectangle(backButton.x, backButton.y, backButton.width, backButton.height, LIGHTGRAY);
			DrawText(FormatText("Back"), Game::HALF_SCREENWIDTH - (MeasureText("Back", FONT_SIZE) / DIVIDER_MEASURE_TEXT), Game::SCREENHEIGHT / HELPER_LINE_DIVIDER + FONT_SIZE, FONT_SIZE, DARKGRAY);
			
			DrawText(FormatText("Version 1.0"), Game::HALF_SCREENWIDTH - (MeasureText("Version 1.0", FONT_SIZE_HELPER) / DIVIDER_MEASURE_TEXT), Game::SCREENHEIGHT / VERSION_LINE_DIVIDER + FONT_SIZE, FONT_SIZE_HELPER, DARKGRAY);
			
		}
		void updateCredits()
		{
			mousePoint = GetMousePosition();

			if (CheckCollisionPointRec(mousePoint, backButton))
			{
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
				{
					MainMenu::menu = true;
					credits = false;
				}
			}

		}
	}
}