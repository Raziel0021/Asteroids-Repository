#include "GameManager.h"

#include <raylib.h>

#include "GamePlay.h"
#include "Screens/MainMenu.h"
#include "Screens/Credits.h"
#include "Screens/GameOver.h"

using namespace Game;
using namespace MainMenu;
namespace Game 
{
	const int SCREENWIDTH = 1080;
	const int SCREENHEIGHT = 900;
	const float HALF_SCREENHEIGHT = SCREENHEIGHT / 2;
	const float HALF_SCREENWIDTH = SCREENWIDTH / 2;
	namespace GameManager 
	{
		void Run() 
		{
			InitializeApp();
			GamePlay::InitGame();
			while (!WindowShouldClose())
			{
				if (!GamePlay::gameover && !GamePlay::victory && !menu && !Credits::credits) {
					GamePlay::Play();	
				}
				Draw();
			}
		}
		void Draw() 
		{
			BeginDrawing();
			ClearBackground(BLACK);
			if (!GamePlay::gameover && !GamePlay::victory && !menu && !Credits::credits)
			{
				GamePlay::DrawGame();
			}
			else if (menu)
			{
				MainMenu::showMenu();
			}
			else if (Credits::credits)
			{
				Credits::showCredits();
			}
			else if (GamePlay::gameover || GamePlay::victory)
			{
				EndOfGame::showGameOver();
			}
			EndDrawing();
		}

		void InitializeApp()
		{
			// Initialization
			InitWindow(SCREENWIDTH, SCREENHEIGHT, "Asteroids");
			//SetExitKey(0);
			
			//#define AUDIO

			#ifdef AUDIO	
			InitAudioDevice();
			ping = LoadSound("res/ping.ogg");
			pong = LoadSound("res/pong.wav");
			music = LoadMusicStream("res/michorvath.ogg");
			PlayMusicStream(music);
			#endif // AUDIO
		}
		void UnloadGame()
		{
			CloseAudioDevice();
			CloseWindow();
			// TODO: Unload all dynamic loaded data (textures, sounds, models...)
		}
	}
}