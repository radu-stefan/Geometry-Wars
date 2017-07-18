#pragma once
#include "Transform2D.h"
#include <vector>
#include <queue>
class GameObject
{
public:
	vec2 pos;
	vec2 scale;
	vec3 color;
	int lives;
	mat3 model;
	float speed;
	float rot;
	vec2 direction;

	static float elasedTime;
	static float deltaT;
	static vec2 player;
	static vec2 boss;
	static vec2 mouse;
	static mat3 visMatrix;
	static int enemy_Counter;

	static std::vector<GameObject*> projectiles;
	static std::vector<GameObject*> enemies;
	static std::queue<GameObject*> enemyQueue;
	static std::vector<GameObject*> boss_projs;


	virtual void GameObject_update() = 0;


	static bool Collision(vec2 o1, vec2 o2, float radius);

	static vec2 GenEnemyPos();

	GameObject();
	virtual ~GameObject();
};

