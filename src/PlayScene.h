#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Plane.h"
#include "Player.h"
#include "Button.h"
#include "Label.h"
#include "Target.h"
#include "Bullet.h"
#include "BulletPool.h"


class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;
private:
	const float bulletSpawnTimeDuration = 1000.0f;
	float bulletSpawnTimerStart;
	glm::vec2 m_mousePosition;



	BulletPool* m_pPool;

	Plane* m_pPlaneSprite;
	Player* m_pPlayer;
	//Bullet* m_pBullet;
	Label* m_pStartLabel{};


	Button* m_pBackButton;
	Button* m_pNextButton;

	void SpawnBullet();
};
//class PlayScene : public Scene
//{
//public:
//	PlayScene();
//	~PlayScene();
//
//	// Scene LifeCycle Functions
//	virtual void draw() override;
//	virtual void update() override;
//	virtual void clean() override;
//	virtual void handleEvents() override;
//	virtual void start() override;
//
//	
//private:
//	// IMGUI Function
//	void GUI_Function() const;
//	std::string m_guiTitle;
//	
//	glm::vec2 m_mousePosition;
//
//	Target* m_pBall;
//	Player* m_pEnemy;
//	Player* m_pPlayer;
//	bool m_playerFacingRight;
//
//	// UI Items
//	Button* m_pBackButton;
//	Button* m_pNextButton;
//	Label* m_pInstructionsLabel_1;
//
//	Label* m_pInstructionsLabel_2;
//
//};

#endif /* defined (__PLAY_SCENE__) */