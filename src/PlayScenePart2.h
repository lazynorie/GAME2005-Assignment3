#pragma once
#ifndef __PLAY_SCENE_2__
#define __PLAY_SCENE_2__

#include "Scene.h"
#include "Plane.h"
#include "Player.h"
#include "Button.h"
#include "Label.h"
#include "Target.h"

class PlayScenePart2 : public Scene
{
public:
	PlayScenePart2();
	~PlayScenePart2();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;
	void m_collisionCheck();
	
private:
	// IMGUI Function
	void GUI_Function() const;
	std::string m_guiTitle;
	
	glm::vec2 m_mousePosition;

	Target* m_pBall;
	Player* m_pEnemy;
	Player* m_pPlayer;
	bool m_playerFacingRight;

	Label* m_pStartLabel{};
	// UI Items
	Button* m_pBackButton;
	Button* m_pNextButton;
	Label* m_pInstructionsLabel_1;

	Label* m_pInstructionsLabel_2;

};
#endif /* defined (__PLAY_SCENE_2__) */