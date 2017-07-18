#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>
#include "Player.h"
#include "Projectile.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "Enemy3.h"
#include "Boss.h"
#include <vector>

class GeoWars : public SimpleScene
{
public:
	struct ViewportSpace
	{
		ViewportSpace() : x(0), y(0), width(1), height(1) {}
		ViewportSpace(int x, int y, int width, int height)
			: x(x), y(y), width(width), height(height) {}
		int x;
		int y;
		int width;
		int height;
	};

	struct LogicSpace
	{
		LogicSpace() : x(0), y(0), width(1), height(1) {}
		LogicSpace(float x, float y, float width, float height)
			: x(x), y(y), width(width), height(height) {}
		float x;
		float y;
		float width;
		float height;
	};

public:
	GeoWars();
	~GeoWars();

	void Init() override;

private:
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;

	void DrawScene();

	void Render();

	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;

	// Sets the logic space and view space
	// logicSpace: { x, y, width, height }
	// viewSpace: { x, y, width, height }
	glm::mat3 VisualizationTransf2DUnif(const LogicSpace &logicSpace, const ViewportSpace &viewSpace);

	void SetViewportArea(const ViewportSpace &viewSpace, glm::vec3 colorColor = glm::vec3(0), bool clear = true);

protected:
	ViewportSpace viewSpace;
	LogicSpace logicSpace;
	glm::mat3 modelMatrix, visMatrix;
	float en_freq, last;
	vec2 mouse;

	float animStart;
	bool anim;
	bool animInit;
	float animColor;
	int enemy_Counter;

	GameObject* player;
	GameObject* boss;
};


