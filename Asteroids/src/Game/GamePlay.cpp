#include "GamePlay.h"

#include <raylib.h>
#include <cmath>

#include "GameManager.h"
#include "Screens/MainMenu.h"

using namespace Game;
namespace Game {
	namespace GamePlay {
		const int PLAYER_BASE_SIZE = 20;
		const float PLAYER_SPEED = 300.0f;
		const int PLAYER_MAX_SHOOTS = 10;

		const float METEOR_SPEED = 250;
		const int MAX_BIG_METEORS = 4;
		const int MAX_MEDIUM_METEORS = 8;
		const int MAX_SMALL_METEORS = 16;

		struct Player 
		{
			Vector2 position;
			Vector2 speed;
			float acceleration;
			float rotation;
			Vector3 collider;
			Color color;
		};

		struct Shoot 
		{
			Vector2 position;
			Vector2 speed;
			float radius;
			float rotation;
			int lifeSpawn;
			bool active;
			Color color;
		};

		struct Meteor 
		{
			Vector2 position;
			Vector2 speed;
			float radius;
			bool active;
			Color color;
		};

		bool gameover;
		bool pause;
		bool victory;

		float shipHeight;

		Player player;
		Shoot shoot[PLAYER_MAX_SHOOTS];
		Meteor bigMeteor[MAX_BIG_METEORS];
		Meteor mediumMeteor[MAX_MEDIUM_METEORS];
		Meteor smallMeteor[MAX_SMALL_METEORS];

		int midMeteorsCount;
		int smallMeteorsCount;
		int destroyedMeteorsCount;

		
		static float initPosX, initPosY;
		static float initVelX, initVelY;
		static int correctRange;

		static const float HALF_PLAYER_BASE_SIZE = PLAYER_BASE_SIZE / 2;
		static const float HALF_SCREENHEIGHT = SCREENHEIGHT / 2;
		static const float HALF_SCREENWIDTH = SCREENWIDTH / 2;
		static const Vector2 INIT_SPEED = {0,0};
		static const Vector2 INIT_POSITION = { 0,0 };
		static const short INIT_ACCELRATION = 0;
		static const short INIT_ROTATION = 0;
		static const short BASE_SPEED_ROTATION = 150;
		static const float BASE_ACCELERATION = 0.04f;
		static const float BASE_DESACCELERATION = 0.02f;
		static const short MAX_ACCELERATION = 1;
		static const short ZERO_ACCELERATION = 0;
		static const short INIT_COUNT = 0;
		static const short INIT_SHOOT_RADIUS = 2;
		static const float SHOOT_SPEED = 1.5;
		static const short INIT_BIG_METEOR_RADIUS = 40;
		static const short INIT_MEDIUM_METEOR_RADIUS = INIT_BIG_METEOR_RADIUS /2;
		static const short INIT_SMALL_METEOR_RADIUS = INIT_MEDIUM_METEOR_RADIUS/2;
		static const short INIT_LIFE_SPAWN = 0;
		static const float SHOOT_MAX_LIFETIME = 0.1f;
		static const short LIM_RANGE = 150;
		static const float SHIPHEIGHT_DIVIDER = 2.5f;
		static const short SHIP_COLLIDER_Z = 10;
		static const short PAIR_DIVIDER = 2;

		static const float ALPHA_DEACTIVATE_METEOR = 0.3f;
		void InitGame() 
		{
			MainMenu::menu = true;
			correctRange = false;
			victory = false;
			pause = false;
			gameover = false;
			shipHeight = (HALF_PLAYER_BASE_SIZE) / tanf(20 * DEG2RAD);

			//Init Player
			player.position = { HALF_SCREENWIDTH,HALF_SCREENHEIGHT - shipHeight / 2 };
			player.speed = INIT_SPEED;
			player.acceleration = INIT_ACCELRATION;
			player.rotation = INIT_ROTATION;
			player.collider = { player.position.x+sin(player.rotation*DEG2RAD)*(shipHeight/2.5f),player.position.y - cos(player.rotation*DEG2RAD)*(shipHeight/2.5f),12};
			player.color = DARKGREEN;

			destroyedMeteorsCount = INIT_COUNT;

			//Init Shoot
			for (int i = 0; i < PLAYER_MAX_SHOOTS; i++) 
			{
				shoot[i].position = INIT_POSITION;
				shoot[i].speed = INIT_SPEED;
				shoot[i].radius = INIT_SHOOT_RADIUS;
				shoot[i].active = false;
				shoot[i].lifeSpawn = INIT_LIFE_SPAWN;
				shoot[i].color = LIGHTGRAY;
			}
			for (int i = 0; i < MAX_BIG_METEORS; i++) 
			{
				initPosX = GetRandomValue(0, SCREENWIDTH);
				while (!correctRange) 
				{
					if ((initPosX > HALF_SCREENWIDTH - LIM_RANGE) && (initPosX < HALF_SCREENWIDTH + LIM_RANGE))
						initPosX = GetRandomValue(0, SCREENWIDTH);
					else
						correctRange = true;
				}

				correctRange = false;

				initPosY = GetRandomValue(0, SCREENHEIGHT);
				while (!correctRange)
				{
					if ((initPosY > HALF_SCREENHEIGHT - LIM_RANGE) && (initPosY < HALF_SCREENHEIGHT + LIM_RANGE))
						initPosY = GetRandomValue(0, SCREENHEIGHT);
					else
						correctRange = true;
				}
				bigMeteor[i].position = { initPosX,initPosY };

				correctRange = false;
				initVelX = GetRandomValue(-METEOR_SPEED, METEOR_SPEED);
				initVelY = GetRandomValue(-METEOR_SPEED, METEOR_SPEED);
				while (!correctRange) 
				{
					if (initVelX == 0 && initVelY == 0)
					{
						initVelX = GetRandomValue(-METEOR_SPEED, METEOR_SPEED);
						initVelY = GetRandomValue(-METEOR_SPEED, METEOR_SPEED);
					}
					else
						correctRange=true;
				}

				bigMeteor[i].speed = { initVelX,initVelY };
				bigMeteor[i].radius = INIT_BIG_METEOR_RADIUS;
				bigMeteor[i].active = true;
				bigMeteor[i].color = WHITE;
			}
			for (int i = 0; i < MAX_MEDIUM_METEORS; i++)
			{
				mediumMeteor[i].position = INIT_POSITION;
				mediumMeteor[i].speed = INIT_SPEED;
				mediumMeteor[i].radius = INIT_MEDIUM_METEOR_RADIUS;
				mediumMeteor[i].active = false;
				mediumMeteor[i].color = WHITE;
			}
			for (int i = 0; i < MAX_SMALL_METEORS; i++)
			{
				smallMeteor[i].position = INIT_POSITION;
				smallMeteor[i].speed = INIT_SPEED;
				smallMeteor[i].radius = INIT_SMALL_METEOR_RADIUS;
				smallMeteor[i].active = false;
				smallMeteor[i].color = WHITE;
			}
			midMeteorsCount = INIT_COUNT;
			smallMeteorsCount = INIT_COUNT;
		}

		void Play() 
		{
			//#define AUDIO
			#ifdef AUDIO
				UpdateAudioStream(music);
			#endif // AUDIO
			
			if (!pause) 
			{
				//Player: rotation
				if (IsKeyDown(KEY_A))
					player.rotation -= BASE_SPEED_ROTATION * GetFrameTime();
				if (IsKeyDown(KEY_D))
					player.rotation += BASE_SPEED_ROTATION * GetFrameTime();;

				//Player: speed
				player.speed.x = sin(player.rotation * DEG2RAD)*PLAYER_SPEED;
				player.speed.y = cos(player.rotation * DEG2RAD)*PLAYER_SPEED;

				//Player: acceleration
				if (IsKeyDown(KEY_W))
				{
					if (player.acceleration < MAX_ACCELERATION) 
						player.acceleration += BASE_ACCELERATION ;
				}
				else
				{
					if (player.acceleration > ZERO_ACCELERATION)
						player.acceleration -= BASE_DESACCELERATION ;
					else if (player.acceleration < ZERO_ACCELERATION)
						player.acceleration = ZERO_ACCELERATION;					
				}
				if (IsKeyDown(KEY_S))
				{
					if (player.acceleration > ZERO_ACCELERATION)
						player.acceleration -= BASE_ACCELERATION ;
					else
						if (player.acceleration < ZERO_ACCELERATION)
							player.acceleration = ZERO_ACCELERATION;
				}

				//Player: Movement
				player.position.x += (player.speed.x*player.acceleration)* GetFrameTime();
				player.position.y -= (player.speed.y*player.acceleration)* GetFrameTime();

				//Collision: Player vs Walls
				if (player.position.x > SCREENWIDTH + shipHeight)
					player.position.x = -(shipHeight);
				else if (player.position.x < -(shipHeight))
					player.position.x = SCREENWIDTH + shipHeight;
				if (player.position.y > (SCREENHEIGHT + shipHeight))
					player.position.y = -(shipHeight);
				else if (player.position.y < -(shipHeight))
					player.position.y = SCREENHEIGHT + shipHeight;

				//Player shoot logic

				if (IsKeyPressed(KEY_SPACE))
				{
					for (int i = 0; i < PLAYER_MAX_SHOOTS; i++)
					{
						if (!shoot[i].active) 
						{
							shoot[i].position = { player.position.x + sin(player.rotation*DEG2RAD)*(shipHeight) ,player.position.y - cos(player.rotation*DEG2RAD)*(shipHeight) };
							shoot[i].active = true;
							shoot[i].speed.x = SHOOT_SPEED * sin(player.rotation*DEG2RAD)*PLAYER_SPEED;
							shoot[i].speed.y = SHOOT_SPEED * cos(player.rotation*DEG2RAD)*PLAYER_SPEED;
							shoot[i].rotation = player.rotation;
							break;
						}
					}
				}
				//Shoot life timer
				for (int i = 0; i < PLAYER_MAX_SHOOTS; i++)
				{
					if (shoot[i].active)
						shoot[i].lifeSpawn = shoot[i].lifeSpawn + GetFrameTime()*100;
				}
				//Shot
				for (int i = 0; i < PLAYER_MAX_SHOOTS; i++)
				{
					if (shoot[i].active)
					{
						//Shoot move
						shoot[i].position.x += shoot[i].speed.x * GetFrameTime();
						shoot[i].position.y -= shoot[i].speed.y * GetFrameTime();

						//Collision shoot vs Walls
						if (shoot[i].position.x > SCREENWIDTH + INIT_SHOOT_RADIUS)
						{
							shoot[i].active = false;
							shoot[i].lifeSpawn = INIT_LIFE_SPAWN;
						}else if (shoot[i].position.x < INIT_LIFE_SPAWN - INIT_SHOOT_RADIUS) 
						{
							shoot[i].active = false;
							shoot[i].lifeSpawn = INIT_LIFE_SPAWN;
						}
						if (shoot[i].position.y > SCREENHEIGHT + INIT_SHOOT_RADIUS) 
						{
							shoot[i].active = false;
							shoot[i].lifeSpawn = INIT_LIFE_SPAWN;
						}else if (shoot[i].position.y < INIT_LIFE_SPAWN - INIT_SHOOT_RADIUS)
						{
							shoot[i].active = false;
							shoot[i].lifeSpawn = INIT_LIFE_SPAWN;
						}

						//LifeSpawn Shoot
						if (shoot[i].lifeSpawn >= SHOOT_MAX_LIFETIME)
						{
							shoot[i].position = INIT_POSITION;
							shoot[i].speed = INIT_SPEED;
							shoot[i].lifeSpawn = INIT_LIFE_SPAWN;
							shoot[i].active = false;
						}
					}
				}

				//Collision player vs meteor
				player.collider = { player.position.x + sin(player.rotation*DEG2RAD)*(shipHeight / SHIPHEIGHT_DIVIDER),player.position.y - cos(player.rotation*DEG2RAD)*(shipHeight / SHIPHEIGHT_DIVIDER),SHIP_COLLIDER_Z };
			
				for (int m = 0; m < MAX_BIG_METEORS; m++)
				{
					if (CheckCollisionCircles({ player.collider.x , player.collider.y }, player.collider.z, bigMeteor[m].position, bigMeteor[m].radius) && bigMeteor[m].active)
						gameover = true;
				}
				for (int m = 0; m < MAX_MEDIUM_METEORS; m++)
				{
					if (CheckCollisionCircles({ player.collider.x,player.collider.y }, player.collider.z, mediumMeteor[m].position, mediumMeteor[m].radius) && mediumMeteor[m].active)
						gameover = true;
				}
				for (int m = 0; m < MAX_SMALL_METEORS; m++)
				{
					if (CheckCollisionCircles({ player.collider.x,player.collider.y }, player.collider.z, smallMeteor[m].position, smallMeteor[m].radius) && smallMeteor[m].active)
						gameover = true;
				}

				//Meteors logic -Big Meteors
				for (int i = 0; i < MAX_BIG_METEORS; i++) 
				{
					if (bigMeteor[i].active)
					{
						//Movement 
						bigMeteor[i].position.x += bigMeteor[i].speed.x * GetFrameTime();
						bigMeteor[i].position.y += bigMeteor[i].speed.y * GetFrameTime();

						//Collision meteor vs wall
						if (bigMeteor[i].position.x > (SCREENWIDTH + bigMeteor[i].radius))
							bigMeteor[i].position.x = -(bigMeteor[i].radius);
						else if (bigMeteor[i].position.x < INIT_POSITION.x - bigMeteor[i].radius)
							bigMeteor[i].position.x = SCREENWIDTH + bigMeteor[i].radius;
						
						if (bigMeteor[i].position.y >(SCREENHEIGHT + bigMeteor[i].radius))
							bigMeteor[i].position.y = -(bigMeteor[i].radius);
						else if (bigMeteor[i].position.y < INIT_POSITION.y - bigMeteor[i].radius)
							bigMeteor[i].position.y = SCREENHEIGHT + bigMeteor[i].radius;	
					}
				}
				//Meteors logic -Medium Meteors
				for (int i = 0; i < MAX_MEDIUM_METEORS; i++)
				{
					if (mediumMeteor[i].active)
					{
						//Movement 
						mediumMeteor[i].position.x += mediumMeteor[i].speed.x * GetFrameTime();
						mediumMeteor[i].position.y += mediumMeteor[i].speed.y * GetFrameTime();

						//Collision meteor vs wall
						if (mediumMeteor[i].position.x >(SCREENWIDTH + mediumMeteor[i].radius))
							mediumMeteor[i].position.x = -(mediumMeteor[i].radius);
						else if (mediumMeteor[i].position.x < INIT_POSITION.x - mediumMeteor[i].radius)
							mediumMeteor[i].position.x = SCREENWIDTH + mediumMeteor[i].radius;

						if (mediumMeteor[i].position.y >(SCREENHEIGHT + mediumMeteor[i].radius))
							mediumMeteor[i].position.y = -(mediumMeteor[i].radius);
						else if (mediumMeteor[i].position.y < INIT_POSITION.y - mediumMeteor[i].radius)
							mediumMeteor[i].position.y = SCREENHEIGHT + mediumMeteor[i].radius;
					}
				}
				//Meteors logic -Small Meteors
				for (int i = 0; i < MAX_SMALL_METEORS; i++)
				{
					if (smallMeteor[i].active)
					{
						//Movement 
						smallMeteor[i].position.x += smallMeteor[i].speed.x *GetFrameTime();
						smallMeteor[i].position.y += smallMeteor[i].speed.y *GetFrameTime();

						//Collision meteor vs wall
						if (smallMeteor[i].position.x >(SCREENWIDTH + smallMeteor[i].radius))
							smallMeteor[i].position.x = -(smallMeteor[i].radius);
						else if (smallMeteor[i].position.x < INIT_POSITION.x - smallMeteor[i].radius)
							smallMeteor[i].position.x = SCREENWIDTH + smallMeteor[i].radius;

						if (smallMeteor[i].position.y >(SCREENHEIGHT + smallMeteor[i].radius))
							smallMeteor[i].position.y = -(smallMeteor[i].radius);
						else if (smallMeteor[i].position.y < INIT_POSITION.y - smallMeteor[i].radius)
							smallMeteor[i].position.y = SCREENHEIGHT + smallMeteor[i].radius;
					}
				}

				//Collision Player-shoots vs meteors
				for (int i = 0; i < PLAYER_MAX_SHOOTS; i++) 
				{
					if (shoot[i].active)
					{
						for (int a = 0; a < MAX_BIG_METEORS; a++) 
						{
							if (bigMeteor[a].active && CheckCollisionCircles(shoot[i].position, shoot[i].radius, bigMeteor[a].position, bigMeteor[a].radius))
							{
								shoot[i].active = false;
								shoot[i].lifeSpawn = INIT_LIFE_SPAWN;
								bigMeteor[a].active = false;
								destroyedMeteorsCount++;

								for (int j = 0; j < PAIR_DIVIDER; j++)
								{
									if (midMeteorsCount % PAIR_DIVIDER == INIT_COUNT)
									{
										mediumMeteor[midMeteorsCount].position = { bigMeteor[a].position.x , bigMeteor[a].position.y };
										mediumMeteor[midMeteorsCount].speed = { cos(shoot[i].rotation * DEG2RAD) * -(METEOR_SPEED),sin(shoot[i].rotation * DEG2RAD) * -(METEOR_SPEED) };
									}
									else
									{
										mediumMeteor[midMeteorsCount].position = { bigMeteor[a].position.x , bigMeteor[a].position.y };
										mediumMeteor[midMeteorsCount].speed = { cos(shoot[i].rotation * DEG2RAD) * -(METEOR_SPEED),sin(shoot[i].rotation * DEG2RAD) * METEOR_SPEED };
									}
									mediumMeteor[midMeteorsCount].active = true;
									midMeteorsCount++;
								}
								
								bigMeteor[a].color = RED;
								a = MAX_BIG_METEORS;
							}
						}
						
						for (int b = 0; b < MAX_MEDIUM_METEORS; b++)
						{
							if (mediumMeteor[b].active && CheckCollisionCircles(shoot[i].position, shoot[i].radius, mediumMeteor[b].position, mediumMeteor[b].radius))
							{
								shoot[i].active = false;
								shoot[i].lifeSpawn = INIT_LIFE_SPAWN;
								mediumMeteor[b].active = false;
								destroyedMeteorsCount++;

								for (int j = 0; j < PAIR_DIVIDER; j++)
								{
									if (smallMeteorsCount % PAIR_DIVIDER == 0)
									{
										smallMeteor[smallMeteorsCount].position = { mediumMeteor[b].position.x, mediumMeteor[b].position.y };
										smallMeteor[smallMeteorsCount].speed = { cos(shoot[i].rotation*DEG2RAD)*-(METEOR_SPEED) ,sin(shoot[i].rotation*DEG2RAD)*-(METEOR_SPEED)};
									}
									else
									{
										smallMeteor[smallMeteorsCount].position = { mediumMeteor[b].position.x, mediumMeteor[b].position.y };
										smallMeteor[smallMeteorsCount].speed = { cos(shoot[i].rotation*DEG2RAD)*METEOR_SPEED ,sin(shoot[i].rotation*DEG2RAD)*METEOR_SPEED};
									}
									smallMeteor[smallMeteorsCount].active = true;
									smallMeteorsCount++;
								}
								
								mediumMeteor[b].color = GREEN;
								b = MAX_MEDIUM_METEORS;
							}
						}

						for (int c = 0; c < MAX_SMALL_METEORS; c++)
						{
							if (smallMeteor[c].active && CheckCollisionCircles(shoot[i].position, shoot[i].radius, smallMeteor[c].position, smallMeteor[c].radius))
							{
								shoot[i].active = false;
								shoot[i].lifeSpawn = INIT_LIFE_SPAWN;
								smallMeteor[c].active = false;
								destroyedMeteorsCount++;
								smallMeteor[c].color = YELLOW;
								c = MAX_SMALL_METEORS;
							}
						}
					}
				}	
			}
			if (destroyedMeteorsCount == MAX_BIG_METEORS + MAX_MEDIUM_METEORS + MAX_SMALL_METEORS)
				victory = true;

		
		}
		
		void DrawGame()
		{
			//SpaceShip
			Vector2 v1 = { player.position.x + sinf(player.rotation*DEG2RAD)*shipHeight,player.position.y - cosf(player.rotation*DEG2RAD)*shipHeight };
			Vector2 v2 = { player.position.x - cosf(player.rotation*DEG2RAD)*(HALF_PLAYER_BASE_SIZE),player.position.y - sinf(player.rotation*DEG2RAD)*(HALF_PLAYER_BASE_SIZE) };
			Vector2 v3 = { player.position.x + cosf(player.rotation*DEG2RAD)*(HALF_PLAYER_BASE_SIZE),player.position.y + sinf(player.rotation*DEG2RAD)*(HALF_PLAYER_BASE_SIZE) };
		
			DrawTriangle(v1, v2, v3, RED);

			//Meteors
			for (int i = 0; i < MAX_BIG_METEORS; i++)
			{
				if (bigMeteor[i].active)
					DrawCircleV(bigMeteor[i].position, bigMeteor[i].radius, WHITE);
				else
					DrawCircleV(bigMeteor[i].position, bigMeteor[i].radius, Fade(BLANK, ALPHA_DEACTIVATE_METEOR));
			}
			for (int i = 0; i < MAX_MEDIUM_METEORS; i++)
			{
				if (mediumMeteor[i].active)
					DrawCircleV(mediumMeteor[i].position, mediumMeteor[i].radius, WHITE);
				else
					DrawCircleV(mediumMeteor[i].position, mediumMeteor[i].radius, Fade(BLANK, ALPHA_DEACTIVATE_METEOR));
			}
			for (int i = 0; i < MAX_SMALL_METEORS; i++)
			{
				if (smallMeteor[i].active)
					DrawCircleV(smallMeteor[i].position, smallMeteor[i].radius, WHITE);
				else
					DrawCircleV(smallMeteor[i].position, smallMeteor[i].radius, Fade(BLANK, ALPHA_DEACTIVATE_METEOR));
			}

			//Shoot
			for (int i = 0; i < PLAYER_MAX_SHOOTS; i++)
			{
				if (shoot[i].active)
					DrawCircleV(shoot[i].position, shoot[i].radius, WHITE);
			}


		}
	}
}