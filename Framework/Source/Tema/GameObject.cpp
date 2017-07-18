#include "GameObject.h"

std::queue<GameObject*> GameObject::enemyQueue;
std::vector<GameObject*> GameObject::projectiles;
std::vector<GameObject*> GameObject::enemies;
std::vector<GameObject*> GameObject::boss_projs;
float GameObject::elasedTime = 0;
float GameObject::deltaT = 0.0f;
vec2 GameObject::player = vec2(0.0f);
vec2 GameObject::mouse = vec2(0.0f);
mat3 GameObject::visMatrix = mat3(1.0f);
vec2 GameObject::boss = vec2(30 + 30 * sin(GameObject::elasedTime*0.7),55);

bool GameObject::Collision(vec2 o1, vec2 o2, float radius) {
	if (length(vec2(o1.x - o2.x, o1.y - o2.y)) < radius)
		return true;
	return false;
}

vec2 GameObject::GenEnemyPos() {
	int a = (int)MIN(60 - player.x, 60 - player.y);
	int b = (int)MIN(player.x, player.y);
	int radius = (int)MIN(a,b);
	if (radius < 15)
		radius = 15;
	int random = rand();

	return vec2(player.x + radius*cos(random), player.y + radius*sin(random) );
}


GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}
