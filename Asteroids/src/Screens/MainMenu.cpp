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
		static const float OPTIONS_LINE_DIVIDER = 3;
		static const float VERSION_LINE_DIVIDER = 1.7;
		static const float MULTIPLIER_BUTTON_WIDTH = 1.15f;
		static const float SPACE_BETWEEN_LINES = 1.3f;
		bool menu;
		static Vector2 mousePoint;
		
		static Rectangle playButton;
		static Rectangle creditsButton;
		static Rectangle exitButton;

		void initMenuButtons() 
		{
			playButton = { (float)Game::HALF_SCREENWIDTH - (MeasureText("Play", FONT_SIZE_OPTIONS)* MULTIPLIER_BUTTON_WIDTH / DIVIDER_MEASURE_TEXT),
						   (float)Game::SCREENHEIGHT / OPTIONS_LINE_DIVIDER,
						   (float)MeasureText("Play", FONT_SIZE_OPTIONS)* MULTIPLIER_BUTTON_WIDTH ,
						   (float)FONT_SIZE_OPTIONS};
			creditsButton = { (float)Game::HALF_SCREENWIDTH - (MeasureText("Credits", FONT_SIZE_OPTIONS)* MULTIPLIER_BUTTON_WIDTH / DIVIDER_MEASURE_TEXT),
							  (float)Game::SCREENHEIGHT / OPTIONS_LINE_DIVIDER + FONT_SIZE_OPTIONS *SPACE_BETWEEN_LINES,
							  (float)MeasureText("Credits", FONT_SIZE_OPTIONS)* MULTIPLIER_BUTTON_WIDTH ,
							  (float)FONT_SIZE_OPTIONS };
			exitButton = { (float)Game::HALF_SCREENWIDTH - (MeasureText("Exit", FONT_SIZE_OPTIONS)* MULTIPLIER_BUTTON_WIDTH / DIVIDER_MEASURE_TEXT),
						   (float)Game::SCREENHEIGHT / OPTIONS_LINE_DIVIDER + (FONT_SIZE_OPTIONS * 2)*SPACE_BETWEEN_LINES ,
						   (float)MeasureText("Exit", FONT_SIZE_OPTIONS)* MULTIPLIER_BUTTON_WIDTH ,
						   (float)FONT_SIZE_OPTIONS };
		}

		void showMenu()
		{
			initMenuButtons();
			UpdateMenu();

			DrawText(FormatText("ASTEROIDS"), Game::HALF_SCREENWIDTH - (MeasureText("ASTEROIDS", FONT_SIZE_TITLE) / DIVIDER_MEASURE_TEXT), Game::SCREENHEIGHT / GAMETITLE_LINE_DIVIDER, FONT_SIZE_TITLE, GREEN);
			
			DrawRectangle(playButton.x, playButton.y, playButton.width, playButton.height, LIGHTGRAY);
			DrawText(FormatText("Play"), Game::HALF_SCREENWIDTH - (MeasureText("Play", FONT_SIZE_OPTIONS) / DIVIDER_MEASURE_TEXT), Game::SCREENHEIGHT / OPTIONS_LINE_DIVIDER, FONT_SIZE_OPTIONS, DARKGRAY);
			
			DrawRectangle(creditsButton.x, creditsButton.y, creditsButton.width, creditsButton.height, LIGHTGRAY);
			DrawText(FormatText("Credits"), Game::HALF_SCREENWIDTH - (MeasureText("Credits", FONT_SIZE_OPTIONS) / DIVIDER_MEASURE_TEXT), Game::SCREENHEIGHT / OPTIONS_LINE_DIVIDER + FONT_SIZE_OPTIONS * SPACE_BETWEEN_LINES, FONT_SIZE_OPTIONS, DARKGRAY);
			
			DrawRectangle(exitButton.x, exitButton.y, exitButton.width, exitButton.height, LIGHTGRAY);
			DrawText(FormatText("Exit"), Game::HALF_SCREENWIDTH - (MeasureText("Exit", FONT_SIZE_OPTIONS) / DIVIDER_MEASURE_TEXT), Game::SCREENHEIGHT / OPTIONS_LINE_DIVIDER + (FONT_SIZE_OPTIONS * 2)*SPACE_BETWEEN_LINES, FONT_SIZE_OPTIONS, DARKGRAY);
			
			DrawText(FormatText("Version 0.2"), Game::HALF_SCREENWIDTH - (MeasureText("Version 0.2", FONT_SIZE_VERSION) / DIVIDER_MEASURE_TEXT), Game::SCREENHEIGHT / VERSION_LINE_DIVIDER + FONT_SIZE_OPTIONS, FONT_SIZE_VERSION, DARKGRAY);
			
		}
		void UpdateMenu()
		{

			mousePoint = GetMousePosition();

			if (CheckCollisionPointRec(mousePoint, playButton))
			{
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
				{
					menu = false;
				}
			}
			if (CheckCollisionPointRec(mousePoint, creditsButton))
			{
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
				{
					menu = false;
					Credits::credits = true;
				}
			}
			if (CheckCollisionPointRec(mousePoint, exitButton))
			{
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
					CloseWindow();
			}		
		}
	}
}