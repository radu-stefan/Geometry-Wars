#include "Player.h"


Player::Player()
{
	speed = 10.0f;
	pos = vec2(30, 30);
	scale = vec2(1, 1);
	color = vec3(0.0, 1.0, 0.0);
	lives = 3;
	model = mat3(1.0f);
}

void Player::GameObject_update() {
	GameObject::player = pos;
	float ang = Transform2D::Angle(mouse, vec2(pos.x, pos.y));
	model = visMatrix * Transform2D::Translate( pos.x, pos.y) * Transform2D::Rotate( ang) * Transform2D::Scale( scale.x, scale.y);
}


Player::~Player()
{
}
