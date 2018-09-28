#ifndef GAMEPLAY
#define GAMEPLAY
	
namespace Game {
	namespace GamePlay {
		
		extern bool gameover;
		extern bool pause;
		extern bool victory;

		void InitGame();
		void Play();
		void DrawGame();
	}
}

#endif // !GAMEPLAY
