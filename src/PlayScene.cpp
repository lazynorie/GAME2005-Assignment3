#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"
#include <cmath>
#include <math.h>
using namespace std;
// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"
#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"
const int mpp = 2;


PlayScene::PlayScene()
{
	PlayScene::start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	TextureManager::Instance()->draw("background", 500, 300, 0, 255, true);
	drawDisplayList();
}

void PlayScene::update()
{
	updateDisplayList();


	if (SDL_GetTicks() - bulletSpawnTimerStart >= bulletSpawnTimeDuration)
	{
		SpawnBullet();
	}
	vector<Bullet*>& activeBullets = m_pPool->all;
	for (vector<Bullet*>::iterator myiter = activeBullets.begin(); myiter != activeBullets.end(); myiter++)
	{
		Bullet* bullet = *myiter;
		if (bullet->active && bullet->getTransform()->position.y >= 650)
		{
			m_pPool->Despawn(*myiter);

			break;
		}
		else if (bullet->active && m_pPlayer->isColliding(bullet)) {
			m_pPool->Despawn(*myiter);
			SoundManager::Instance().playSound("explosion");
			break;
		}
	}
}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		TheGame::Instance()->changeSceneState(PLAY_SCENE_2);
	}


	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A))
	{
		m_pPlayer->moveLeft();
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
	{
		m_pPlayer->moveRight();
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_W)) {
		m_pPlayer->moveUp();
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_S)) {
		m_pPlayer->moveDown();
	}
	else {
		m_pPlayer->stopMoving();
	}


	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}
}

void PlayScene::start()
{
	// Player Sprite

	m_pPlayer = new Player();
	addChild(m_pPlayer);
	const SDL_Color blue = { 237, 244, 255, 255 };//light blue
	m_pStartLabel = new Label("Scene for part 1", "Consolas", 40, blue, glm::vec2(500.0f, 200.0f));
	m_pStartLabel->setParent(this);
	addChild(m_pStartLabel);

	TextureManager::Instance()->load("../Assets/textures/Background.jpg", "background");
	SoundManager::Instance().load("../Assets/audio/explosion.wav", "explosion", SOUND_SFX);
	// Back Button
	m_pBackButton = new Button("../Assets/textures/backButton.png", "backButton", BACK_BUTTON);
	m_pBackButton->getTransform()->position = glm::vec2(100.0f, 550.0f);
	m_pBackButton->addEventListener(CLICK, [&]()-> void
	{
		m_pBackButton->setActive(false);
		TheGame::Instance()->changeSceneState(PLAY_SCENE_2);
	});

	m_pBackButton->addEventListener(MOUSE_OVER, [&]()->void
	{
		m_pBackButton->setAlpha(128);
	});

	m_pBackButton->addEventListener(MOUSE_OUT, [&]()->void
	{
		m_pBackButton->setAlpha(255);
	});
	addChild(m_pBackButton);

	// Next Button
	m_pNextButton = new Button("../Assets/textures/nextButton.png", "nextButton", NEXT_BUTTON);
	m_pNextButton->getTransform()->position = glm::vec2(900.0f, 550.0f);
	m_pNextButton->addEventListener(CLICK, [&]()-> void
	{
		m_pNextButton->setActive(false);
		TheGame::Instance()->changeSceneState(END_SCENE);
	});

	m_pNextButton->addEventListener(MOUSE_OVER, [&]()->void
	{
		m_pNextButton->setAlpha(128);
	});

	m_pNextButton->addEventListener(MOUSE_OUT, [&]()->void
	{
		m_pNextButton->setAlpha(255);
	});

	addChild(m_pNextButton);


	m_pPool = new BulletPool(10);
	for (vector<Bullet*>::iterator myiter = m_pPool->all.begin(); myiter != m_pPool->all.end(); myiter++)
	{
		Bullet* bullet = *myiter;
		addChild(bullet);
	}
	bulletSpawnTimerStart = SDL_GetTicks();

}

void PlayScene::SpawnBullet()
{
	Bullet* bullet = m_pPool->spawn();
	if (bullet) {
		//addChild(bullet);
		bullet->getTransform()->position = glm::vec2(50 + rand() % 700, 0);
	}
	bulletSpawnTimerStart = SDL_GetTicks();
}

//PlayScene::PlayScene()
//{
//	PlayScene::start();
//}
//
//PlayScene::~PlayScene()
//= default;
//
//void PlayScene::draw()
//{
//	TextureManager::Instance()->draw("background", 500, 300, 0, 255, true);
//
//	drawDisplayList();
//	SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);
//
//	if (EventManager::Instance().isIMGUIActive())
//	{
//		GUI_Function();
//	}
//}
//
//void PlayScene::update()
//{
//	updateDisplayList();
//}
//
//void PlayScene::clean()
//{
//	removeAllChildren();
//}
//
//void PlayScene::handleEvents()
//{
//	EventManager::Instance().update();
//
//	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
//	{
//		TheGame::Instance()->quit();
//	}
//
//	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
//	{
//		TheGame::Instance()->changeSceneState(START_SCENE);
//	}
//
//	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
//	{
//		TheGame::Instance()->changeSceneState(END_SCENE);
//	}
//}
//
//void PlayScene::start()
//{
//	//Loads the background textrue from the disk into RAM
//	TextureManager::Instance()->load("../Assets/textures/Background.jpg", "background");
//
//	// Set GUI Title
//	m_guiTitle = "Play Scene";
//
//	//Ball
//	m_pBall = new Target();
//	addChild(m_pBall);
//
//	// Back Button
//	m_pBackButton = new Button("../Assets/textures/backButton.png", "backButton", BACK_BUTTON);
//	m_pBackButton->getTransform()->position = glm::vec2(100.0f, 550.0f);
//	m_pBackButton->addEventListener(CLICK, [&]()-> void
//	{
//		m_pBackButton->setActive(false);
//		TheGame::Instance()->changeSceneState(START_SCENE);
//	});
//
//	m_pBackButton->addEventListener(MOUSE_OVER, [&]()->void
//	{
//		m_pBackButton->setAlpha(128);
//	});
//
//	m_pBackButton->addEventListener(MOUSE_OUT, [&]()->void
//	{
//		m_pBackButton->setAlpha(255);
//	});
//	addChild(m_pBackButton);
//
//	// Next Button
//	m_pNextButton = new Button("../Assets/textures/nextButton.png", "nextButton", NEXT_BUTTON);
//	m_pNextButton->getTransform()->position = glm::vec2(900.0f, 550.0f);
//	m_pNextButton->addEventListener(CLICK, [&]()-> void
//	{
//		m_pNextButton->setActive(false);
//		TheGame::Instance()->changeSceneState(END_SCENE);
//	});
//
//	m_pNextButton->addEventListener(MOUSE_OVER, [&]()->void
//	{
//		m_pNextButton->setAlpha(128);
//	});
//
//	m_pNextButton->addEventListener(MOUSE_OUT, [&]()->void
//	{
//		m_pNextButton->setAlpha(255);
//	});
//
//	addChild(m_pNextButton);
//
//
//	const SDL_Color blue = { 237, 244, 255, 255 };//light blue
//
//	/* Instructions Label */
//	m_pInstructionsLabel_1 = new Label("Press the backtick (`) to access the physics control.", "Consolas", 15, blue);
//	m_pInstructionsLabel_1->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.6f, 530.0f);
//
//	addChild(m_pInstructionsLabel_1);
//
//	m_pInstructionsLabel_2 = new Label("Set ALL(IMPORTANT!) the values before click on 'Fallen' button.", "Consolas", 15, blue);
//	m_pInstructionsLabel_2->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.6f, 570.0f);
//
//	addChild(m_pInstructionsLabel_2);
//}
//
//void PlayScene::GUI_Function() const
//{
//	// Always open with a NewFrame
//	ImGui::NewFrame();
//
//	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
//	//ImGui::ShowDemoWindow();
//
//	ImGui::Begin("Physics Controll", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);
//
//	ImGui::Value("The scale is 1", mpp);
//
//	if (ImGui::Button("Fallen"))
//	{
//		m_pBall->doFallen();
//	}
//	/*if (buttonPressed)
//	{
//		std::cout << "Throw button pressed" << std:: endl;
//	}*/
//	ImGui::Separator();
//
//	static float rampHeight = 300;
//	static float rampWidth = 400;
//
//	//lab5 content
//	ImGui::SliderFloat("Ramp height(cm)", &rampHeight, 0, 500);
//	ImGui::SliderFloat("Ramp width(cm)", &rampWidth, 0, 700);
//	int originX = 100;
//	int originY = 500;
//	SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, SDL_ALPHA_OPAQUE);
//	SDL_RenderDrawLine(Renderer::Instance()->getRenderer(), originX, originY, originX, -rampHeight + originY);
//	SDL_RenderDrawLine(Renderer::Instance()->getRenderer(), originX, originY, rampWidth + originX, originY);
//	SDL_RenderDrawLine(Renderer::Instance()->getRenderer(), originX, -rampHeight + originY, rampWidth + originX, originY);
//
//	m_pBall->fallenposition = glm::vec2(originX, -rampHeight + originY);
//
//	glm::vec2 speed = m_pBall->getRigidBody()->velocity;
//
//	static float mass = 12.8;
//	ImGui::SliderFloat("Object mass(kg)", &mass, 0, 1000);
//
//	static float fricCoefficient = 0.42;
//	ImGui::SliderFloat("Coefficient of Friction", &fricCoefficient, 0, 1);
//
//	float rampLength;
//	rampLength = sqrt( (rampHeight * rampHeight) + (rampWidth * rampWidth) );
//	ImGui::Value("The length(cm) of the ramp is", rampLength);
//
//
//	//Net Force
//	float netForce;
//	netForce = mass * 9.8 * (rampHeight / rampLength);
//	ImGui::Value("The netforce(N) of the object is", netForce);
//
//	m_pBall->acc = netForce / mass;
//	ImGui::Value("The acceleration(m/s^2) of the object is", m_pBall->acc);
//	ImGui::Value("The x-axis velocity(m/s) of the object is", m_pBall->getRigidBody()->velocity.x);
//	ImGui::Value("The y-axis velocity(m/s) of the object is", m_pBall->getRigidBody()->velocity.y);
//	if (m_pBall->getTransform()->position.y >= 500) {
//		ImGui::Value("Distance(cm) travelled after ramp", m_pBall->getTransform()->position.x - rampWidth - originX);
//	}
//	else {
//		ImGui::Value("Distance(cm) travelled after ramp", 0);
//	}
//	m_pBall->getRigidBody()->acceleration.x = m_pBall->acc * (rampWidth / rampLength);
//	m_pBall->getRigidBody()->acceleration.y = m_pBall->acc * (rampHeight / rampLength);
//
//	float surfaceFriction;
//	surfaceFriction = mass * 9.8 * fricCoefficient;
//	ImGui::Value("The surface frection(N) is", surfaceFriction);
//	
//	m_pBall->fricAcc = surfaceFriction / mass;
//
//	ImGui::End();
//	ImGui::EndFrame();
//
//	// Don't Remove this
//	ImGui::Render();
//	ImGuiSDL::Render(ImGui::GetDrawData());
//	ImGui::StyleColorsDark();
//}
//
//
