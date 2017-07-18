#include "Boss.h"

static std::vector<GameObject*> projectiles;


Boss::Boss()
{
	last_shot = GameObject::elasedTime;
	speed = 15.0f;
	pos = GameObject::boss;
	scale = vec2(1.5f, 1.5f);
	lives = 50;
	color = vec3(1.0, 1.0, 1.0);
	model = mat3(1.0f);
}

void Boss::GameObject_update() {

	if (GameObject::elasedTime - last_shot > 1) {
		GameObject::boss_projs.push_back(new Boss_Proj());
		last_shot = GameObject::elasedTime;
	}
	pos.x = 30 + 30 * sin( GameObject::elasedTime*0.7 );
	GameObject::boss = pos;

	float ang = Transform2D::Angle(player, vec2(pos.x, pos.y));
	model = visMatrix * Transform2D::Translate(pos.x, pos.y) * Transform2D::Rotate(ang) * Transform2D::Scale(scale.x, scale.y);
}


Boss::~Boss()
{
}
