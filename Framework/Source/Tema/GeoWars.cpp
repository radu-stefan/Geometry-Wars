#include "GeoWars.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include "Transform2D.h"
#include "Object2D.h"


GeoWars::GeoWars()
{
}

GeoWars::~GeoWars()
{
}

void GeoWars::Init()
{
	auto camera = GetSceneCamera();
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	logicSpace.x = 0;		// logic x
	logicSpace.y = 0;		// logic y
	logicSpace.width = 60;	// logic width
	logicSpace.height = 60;	// logic height

	enemy_Counter = 0;
	mouse.x = 0;
	mouse.y = 0;
	player = new Player();
	en_freq = 2.0f;
	last = (float)Engine::GetElapsedTime();
	anim = false;
	animInit = false;
	animColor = 0.0f;

	boss = new Boss();

	Mesh* ship = Object2D::CreateShip("ship", glm::vec3(0, 0, 1));
	AddMeshToList(ship);

	Mesh* life = Object2D::CreateLife("life", glm::vec3(1, 0, 0));
	AddMeshToList(life);

	Mesh* projectile = Object2D::CreateProjectile("projectile", glm::vec3(0.54, 0.17, 0.88));
	AddMeshToList(projectile);
}


// uniform 2D visualization matrix (same scale factor on x and y axes)
glm::mat3 GeoWars::VisualizationTransf2DUnif(const LogicSpace & logicSpace, const ViewportSpace & viewSpace)
{
	float sx, sy, tx, ty, smin;
	sx = viewSpace.width / logicSpace.width;
	sy = viewSpace.height / logicSpace.height;
	if (sx < sy)
		smin = sx;
	else
		smin = sy;
	tx = viewSpace.x - smin * logicSpace.x + (viewSpace.width - smin * logicSpace.width) / 2;
	ty = viewSpace.y - smin * logicSpace.y + (viewSpace.height - smin * logicSpace.height) / 2;

	return glm::transpose(glm::mat3(
		smin, 0.0f, tx,
		0.0f, smin, ty,
		0.0f, 0.0f, 1.0f));
}

void GeoWars::SetViewportArea(const ViewportSpace & viewSpace, glm::vec3 colorColor, bool clear)
{
	glViewport(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

	glEnable(GL_SCISSOR_TEST);
	glScissor(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

	// Clears the color buffer (using the previously set color) and depth buffer
	glClearColor(colorColor.r, colorColor.g, colorColor.b, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_SCISSOR_TEST);

	GetSceneCamera()->SetOrthographic((float)viewSpace.x, (float)(viewSpace.x + viewSpace.width), (float)viewSpace.y, (float)(viewSpace.y + viewSpace.height), 0.1f, 400);
	GetSceneCamera()->Update();
}

void GeoWars::FrameStart()
{
	// Clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void GeoWars::Update(float deltaTimeSeconds)
{
	{
		glm::ivec2 resolution = window->GetResolution();

		viewSpace = ViewportSpace(0, 0, resolution.x, resolution.y);
		SetViewportArea(viewSpace, glm::vec3(animColor, 0.0f, 0.0f), false);

		// Compute uniform 2D visualization matrix
		visMatrix = glm::mat3(1);
		visMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);

		GameObject::visMatrix = visMatrix;
		GameObject::deltaT = deltaTimeSeconds;
		GameObject::elasedTime = Engine::GetElapsedTime();
	}

	if (player->lives > 0) {

		std::vector<GameObject*>::iterator it1, it2;
		bool collision = false;

		if (enemy_Counter <= 50) {
		
		}


		if (enemy_Counter <= 50) {
			//add enemies
			if ((float)Engine::GetElapsedTime() - last > en_freq) {
				if (en_freq > 0.5f)
					en_freq -= 0.05f;
				last = (float)Engine::GetElapsedTime();

				switch (rand() % 3)
				{
				case 0:
					GameObject::enemies.push_back(new Enemy1());
					break;
				case 1:
					GameObject::enemies.push_back(new Enemy2());
					break;
				case 2:
					GameObject::enemies.push_back(new Enemy3());
					break;
				default:
					break;
				}
			}
		}
		else {
			//update boss
			boss->GameObject_update();
			//check collision with player
			if (GameObject::Collision(boss->pos, player->pos, boss->scale.x * 2)) {
				player->lives = 0;
			}


			//check collision with player projectiles
			for (it1 = GameObject::projectiles.begin(); it1 != GameObject::projectiles.end(); ) {
				if (GameObject::Collision(boss->pos, (*it1)->pos, boss->scale.x * 2)) {
					boss->lives--;
					//erase projectile
					delete *it1;
					it1 = GameObject::projectiles.erase(it1);
					//if boss == dead then reset enemy_Counter and boss
					if (boss->lives <= 0) {
						enemy_Counter = 0;
						boss = new Boss();
						break;
					}
				}
				else
					it1++;
			}
		}

		while (!GameObject::enemyQueue.empty()) {
			GameObject::enemies.push_back(GameObject::enemyQueue.front());
			GameObject::enemyQueue.pop();
		}

		//update boss projectiles
		for (it1 = GameObject::boss_projs.begin(); it1 != GameObject::boss_projs.end(); it1++)
			(*it1)->GameObject_update();
		//check collision boss projectilesa
		for (it1 = GameObject::boss_projs.begin(); it1 != GameObject::boss_projs.end(); ) {
			if (GameObject::Collision(player->pos, (*it1)->pos, player->scale.x * 2)) {
				player->lives--;
				delete *it1;
				it1 = GameObject::boss_projs.erase(it1);
			}
			else
				it1++;
		}


		// update player
		player->GameObject_update();

		//update projectiles
		for (it1 = GameObject::projectiles.begin(); it1 != GameObject::projectiles.end(); ) {
			(*it1)->GameObject_update();
			if ((*it1)->pos.x > logicSpace.width || (*it1)->pos.y > logicSpace.height || 
					(*it1)->pos.x < logicSpace.x || (*it1)->pos.y < logicSpace.y) {
				delete *it1;
				it1 = GameObject::projectiles.erase(it1);
			}
			else
				it1++;
		}

		//update enemies & detect enemy-projectile-player collision
		for (it1 = GameObject::enemies.begin(); it1 != GameObject::enemies.end(); ) {
			(*it1)->GameObject_update();

			//check player collision
			if (GameObject::Collision((*it1)->pos, player->pos, (*it1)->scale.x*2)) {
				delete *it1;
				it1 = GameObject::enemies.erase(it1);
				enemy_Counter++;
				player->lives--;
				continue;
			}
			//check projectile collison
			for (it2 = GameObject::projectiles.begin(); it2 != GameObject::projectiles.end(); it2++) {
				if (GameObject::Collision( (*it1)->pos, (*it2)->pos, (*it1)->scale.x * 2)) {
					(*it1)->lives--;
					(*it1)->GameObject_update();
					if ((*it1)->lives == 0) {
						delete *it1;
						it1 = GameObject::enemies.erase(it1);
						enemy_Counter++;
						collision = true;
					}
					delete *it2;
					it2 = GameObject::projectiles.erase(it2);
					break;
				}
			}
			if (collision)
				collision = false;
			else
				it1++;
		}
	}
	//ending animation
	else {
		if (!animInit) {
			animStart = Engine::GetElapsedTime();
			animInit = true;
		}
		if (!anim) {
			animColor = (Engine::GetElapsedTime() - animStart) / 2.0f;
			if (Engine::GetElapsedTime() - animStart >= 2)
				anim = true;
		}
	}

	//render objects
	DrawScene();
}

void GeoWars::FrameEnd()
{

}

void GeoWars::DrawScene()
{
	int i;
	std::vector<GameObject*>::iterator it1, it2;

	if (enemy_Counter > 50) {
		//render boss
		RenderMesh2D(meshes["ship"], boss->model, boss->color);
	}
	//render boss projectiles
	for (it1 = GameObject::boss_projs.begin(); it1 != GameObject::boss_projs.end(); it1++)
		RenderMesh2D(meshes["projectile"], (*it1)->model, (*it1)->color);

	//render player
	RenderMesh2D(meshes["ship"], player->model, player->color);
	//render player lives
	for (i = 0; i < player->lives; i++) {
		modelMatrix = visMatrix * Transform2D::Translate(logicSpace.width - 1 - i, logicSpace.height - 2);
		RenderMesh2D(meshes["life"], shaders["VertexColor"], modelMatrix);
	}
	//render player projectiles
	for (it1 = GameObject::projectiles.begin(); it1 != GameObject::projectiles.end(); it1++) {
		RenderMesh2D(meshes["projectile"], (*it1)->model, (*it1)->color);
	}
	//render enemies
	for (it1 = GameObject::enemies.begin(); it1 != GameObject::enemies.end(); it1++) {
		RenderMesh2D(meshes["ship"], (*it1)->model, (*it1)->color);
	}
}

void GeoWars::OnInputUpdate(float deltaTime, int mods)
{
	if (window->KeyHold(GLFW_KEY_W)) {
		if(player->pos.y < logicSpace.height)
			player->pos.y += player->speed*deltaTime;
	}
	if (window->KeyHold(GLFW_KEY_S)) {
		if (player->pos.y > logicSpace.y)
			player->pos.y -= player->speed*deltaTime;
	}
	if (window->KeyHold(GLFW_KEY_A)) {
		if (player->pos.x > logicSpace.x)
			player->pos.x -= player->speed*deltaTime;
	}
	if (window->KeyHold(GLFW_KEY_D)) {
		if (player->pos.x < logicSpace.width)
			player->pos.x += player->speed*deltaTime;
	}

}

void GeoWars::OnKeyPress(int key, int mods)
{

}

void GeoWars::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void GeoWars::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	mouse.x = (logicSpace.width / viewSpace.width) * mouseX;
	mouse.y = logicSpace.height - (logicSpace.height / viewSpace.height) * mouseY;

	GameObject::mouse = mouse;
}

void GeoWars::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	if( player->lives > 0 )
		if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT)) {
			GameObject::projectiles.push_back(new Projectile());
		}
	// add mouse button press event
}

void GeoWars::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void GeoWars::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

