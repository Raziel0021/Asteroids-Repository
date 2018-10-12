#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

namespace Game
{
	extern const int SCREENWIDTH;
	extern const int SCREENHEIGHT;
 	extern const float HALF_SCREENHEIGHT ;
	extern const float HALF_SCREENWIDTH;
	extern bool close;
	namespace GameManager
	{
		void Run();
		void Draw();
		void InitializeApp();
		void UnloadGame();
	}
}

#endif // !GAMEMANAGER