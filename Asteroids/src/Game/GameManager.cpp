#include "GameManager.h"

#include <raylib.h>

#include "GamePlay.h"
using namespace Game;
namespace Game 
{
	const int SCREENWIDTH = 1080;
	const int SCREENHEIGHT = 900;
	namespace GameManager 
	{
		void Run() 
		{
			InitializeApp();
			GamePlay::InitGame();
			while (!WindowShouldClose())
			{
				if (!GamePlay::gameover) {
					GamePlay::Play();
					Draw();
				}
			}
		}
		void Draw() 
		{
			BeginDrawing();
			ClearBackground(BLACK);
			if (!GamePlay::gameover)
			{
				GamePlay::DrawGame();
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