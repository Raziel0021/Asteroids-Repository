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
	const int SCREENHEIGHT = 860;
	const float HALF_SCREENHEIGHT = SCREENHEIGHT / 2;
	const float HALF_SCREENWIDTH = SCREENWIDTH / 2;
	bool close=false;
	namespace GameManager 
	{
		void Run() 
		{
			InitializeApp();
			GamePlay::InitGame();
			while (!WindowShouldClose()&&!close)
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
			SetExitKey(0);
			
			GamePlay::rocket = LoadTexture("res/CohetePequeño.png");
			GamePlay::asteroid = LoadTexture("res/AsteroidePequeño.png");
			#define AUDIO

			#ifdef AUDIO	
				InitAudioDevice();
				GamePlay::shootSound = LoadSound("res/Shoot.wav");
				GamePlay::explosionSound = LoadSound("res/Explosion.wav");
				GamePlay::music = LoadMusicStream("res/BackgroundMusic.ogg");
				PlayMusicStream(GamePlay::music);
			#endif // AUDIO
		}
		void UnloadGame()
		{
			// TODO: Unload all dynamic loaded data (textures, sounds, models...)
			UnloadTexture (GamePlay::rocket);
			UnloadTexture(GamePlay::asteroid);
			#ifdef AUDIO
				UnloadSound(GamePlay::shootSound);
				UnloadSound(GamePlay::explosionSound);
				UnloadMusicStream(GamePlay::music);
				CloseAudioDevice();
			#endif // AUDIO
			close = true;
			
		}
	}
}