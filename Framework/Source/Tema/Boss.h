#pragma once
#include "GameObject.h"
#include "Boss_Proj.h"
class Boss :
	public GameObject
{
public:

	float last_shot;
	Boss();
	void GameObject_update();
	~Boss();
};

