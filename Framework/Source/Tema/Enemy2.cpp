#include "Enemy2.h"


Enemy2::Enemy2()
{
	animStart = 0;
	anim = false;
	animInit = false;
	speed = rand() % 6 + 3;
	pos = GameObject::GenEnemyPos();
	scale = vec2(1, 1);
	lives = 2;
	color = vec3(1.0, 1.0, 0.0);
	model = mat3(1.0f);
}

void Enemy2::GameObject_update() {
	if (lives == 1 ) {
		if (!animInit) {
			color = vec3(0.8f, 0.0f, 0.8f);
			speed *= 2;
			animStart = GameObject::elasedTime;
			animInit = true;
		}
		if ( !anim ) {
			float s = 1 - (GameObject::elasedTime - animStart)*2;
			scale = vec2( s, s);
			if ( s <= 0.5 )
				anim = true;
		}
	}

	vec2 direction = normalize(vec2(player.x - pos.x, player.y - pos.y));
	pos.x += direction.x * speed * deltaT;
	pos.y += direction.y * speed * deltaT;

	float ang = Transform2D::Angle(player, vec2(pos.x, pos.y));
	model = visMatrix * Transform2D::Translate(pos.x, pos.y) * Transform2D::Rotate(ang) * Transform2D::Scale(scale.x, scale.y);
}

Enemy2::~Enemy2()
{
}
