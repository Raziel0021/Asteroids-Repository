#ifndef GAMEPLAY
#define GAMEPLAY

#include <raylib.h>

namespace Game {
	namespace GamePlay {

		extern Texture2D rocket;
		extern Texture2D asteroid;
		extern bool gameover;
		extern bool pause;
		extern bool victory;

		void InitGame();
		void Play();
		void DrawGame();
	}
}

#endif // !GAMEPLAY
