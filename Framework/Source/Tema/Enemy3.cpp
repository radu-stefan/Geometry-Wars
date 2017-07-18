#include "Enemy3.h"
#include "Enemy1.h"

Enemy3::Enemy3()
{
	speed = rand() % 6 + 3;
	pos = GameObject::GenEnemyPos();
	scale = vec2(1, 1);
	lives = 1;
	color = vec3(1.0, 0.0, 0.0);
	model = mat3(1.0f);
}

void Enemy3::GameObject_update() {

	vec2 direction = normalize(vec2(player.x - pos.x, player.y - pos.y));
	pos.x += direction.x * speed * deltaT;
	pos.y += direction.y * speed * deltaT;
	
	if (lives == 0) {
		GameObject *obj = new Enemy1();
		obj->pos = vec2(pos.x - direction.y * 5, pos.y + direction.x * 5);
		enemyQueue.push(obj);
		obj = new Enemy1();
		obj->pos = vec2(pos.x + direction.y * 5, pos.y - direction.x * 5);
		enemyQueue.push(obj);
	}

	float ang = Transform2D::Angle(player, vec2(pos.x, pos.y));
	model = visMatrix * Transform2D::Translate(pos.x, pos.y) * Transform2D::Rotate(ang) * Transform2D::Scale(scale.x, scale.y);
}

Enemy3::~Enemy3()
{
}
