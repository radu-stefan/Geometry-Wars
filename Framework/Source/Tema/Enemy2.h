#pragma once
#include "GameObject.h"
class Enemy2 :
	public GameObject
{
public:

	float animStart;
	bool animInit;
	bool anim;

	Enemy2();
	void GameObject_update();
	~Enemy2();
};

