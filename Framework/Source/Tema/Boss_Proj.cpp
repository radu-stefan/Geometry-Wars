#include "Boss_Proj.h"



Boss_Proj::Boss_Proj()
{
	speed = 10.0f;
	pos = boss;
	scale = vec2(1.5, 1.5);
	color = vec3(0.8, 0.52, 0.25);
	model = mat3(1.0f);
	rot = Transform2D::Angle(player, pos);
	direction = normalize(vec2(player.x - pos.x, player.y - pos.y));
}

void Boss_Proj::GameObject_update() {

	pos.x += direction.x * speed * deltaT;
	pos.y += direction.y * speed * deltaT;

	model = visMatrix * Transform2D::Translate(pos.x, pos.y) * Transform2D::Rotate(rot) * Transform2D::Scale(scale.x, scale.y);
}

Boss_Proj::~Boss_Proj()
{
}
