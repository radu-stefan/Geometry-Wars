#include "Projectile.h"



Projectile::Projectile()
{
	speed = 30.0f;
	pos = player;
	scale = vec2(1, 1);
	color = vec3(1.0, 1.0, 1.0);
	model = mat3(1.0f);
	rot = Transform2D::Angle(mouse, pos);
	direction = normalize(vec2(mouse.x - pos.x, mouse.y - pos.y));

}

void Projectile::GameObject_update() {

	pos.x += direction.x * speed * deltaT;
	pos.y += direction.y * speed * deltaT;

	model = visMatrix * Transform2D::Translate(pos.x, pos.y) * Transform2D::Rotate(rot) * Transform2D::Scale(scale.x, scale.y);
}

Projectile::~Projectile()
{
}
