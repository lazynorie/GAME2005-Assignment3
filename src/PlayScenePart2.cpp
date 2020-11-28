#include "PlayScenePart2.h"
#include "Game.h"
#include "EventManager.h"
#include <cmath>
#include <math.h>

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"

const int mpp = 2;

PlayScenePart2::PlayScenePart2()
{
	PlayScenePart2::start();
}

PlayScenePart2::~PlayScenePart2()
= default;

void PlayScenePart2::draw()
{
	TextureManager::Instance()->draw("background", 500, 300, 0, 255, true);

	drawDisplayList();
	SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);

	if (EventManager::Instance().isIMGUIActive())
	{
		GUI_Function();
	}
}

void PlayScenePart2::update()
{
	updateDisplayList();
	m_collisionCheck();
}

void PlayScenePart2::clean()
{
	removeAllChildren();
}

void PlayScenePart2::handleEvents()
{
	EventManager::Instance().update();

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
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
}

void PlayScenePart2::start()
{
	//Loads the background textrue from the disk into RAM
	TextureManager::Instance()->load("../Assets/textures/Background.jpg", "background");

	// Set GUI Title
	m_guiTitle = "Play Scene";


	m_pPlayer = new Player();
	addChild(m_pPlayer);

	//Ball
	m_pBall = new Target();
	addChild(m_pBall);

	const SDL_Color blue = { 237, 244, 255, 255 };//light blue
	m_pStartLabel = new Label("Scene for part 2", "Consolas", 40, blue, glm::vec2(500.0f, 200.0f));
	m_pStartLabel->setParent(this);
	addChild(m_pStartLabel);
	// Back Button
	m_pBackButton = new Button("../Assets/textures/backButton.png", "backButton", BACK_BUTTON);
	m_pBackButton->getTransform()->position = glm::vec2(100.0f, 550.0f);
	m_pBackButton->addEventListener(CLICK, [&]()-> void
	{
		m_pBackButton->setActive(false);
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
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



	/* Instructions Label */
	m_pInstructionsLabel_1 = new Label("Press the backtick (`) to access the physics control.", "Consolas", 15, blue);
	m_pInstructionsLabel_1->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.6f, 530.0f);

	addChild(m_pInstructionsLabel_1);

	m_pInstructionsLabel_2 = new Label("Set ALL(IMPORTANT!) the values before click on 'Fallen' button.", "Consolas", 15, blue);
	m_pInstructionsLabel_2->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.6f, 570.0f);

	addChild(m_pInstructionsLabel_2);
}

void PlayScenePart2::GUI_Function() const
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();

	ImGui::Begin("Physics Controll", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	ImGui::Value("The scale is 1", mpp);

	if (ImGui::Button("Fallen"))
	{
		m_pBall->doFallen();
	}

	ImGui::Separator();

	static float rampHeight = 300;
	static float rampWidth = 400;

	int originX = 100;
	int originY = 500;
	SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, SDL_ALPHA_OPAQUE);

	m_pBall->fallenposition = glm::vec2(originX, -rampHeight + originY);

	glm::vec2 speed = m_pBall->getRigidBody()->velocity;

	static float mass = 12.8;
	ImGui::SliderFloat("Object mass(kg)", &mass, 0, 1000);

	static float fricCoefficient = 0.42;
	ImGui::SliderFloat("Coefficient of Friction", &fricCoefficient, 0, 1);

	float rampLength;
	rampLength = sqrt( (rampHeight * rampHeight) + (rampWidth * rampWidth) );
	ImGui::Value("The length(cm) of the ramp is", rampLength);


	//Net Force
	float netForce;
	netForce = mass * 9.8 * (rampHeight / rampLength);
	ImGui::Value("The netforce(N) of the object is", netForce);

	m_pBall->acc = netForce / mass;
	ImGui::Value("The acceleration(m/s^2) of the object is", m_pBall->acc);
	ImGui::Value("The x-axis velocity(m/s) of the object is", m_pBall->getRigidBody()->velocity.x);
	ImGui::Value("The y-axis velocity(m/s) of the object is", m_pBall->getRigidBody()->velocity.y);
	if (m_pBall->getTransform()->position.y >= 500) {
		ImGui::Value("Distance(cm) travelled after ramp", m_pBall->getTransform()->position.x - rampWidth - originX);
	}
	else {
		ImGui::Value("Distance(cm) travelled after ramp", 0);
	}
	m_pBall->getRigidBody()->acceleration.x = m_pBall->acc * (rampWidth / rampLength);
	m_pBall->getRigidBody()->acceleration.y = m_pBall->acc * (rampHeight / rampLength);

	float surfaceFriction;
	surfaceFriction = mass * 9.8 * fricCoefficient;
	ImGui::Value("The surface frection(N) is", surfaceFriction);
	
	m_pBall->fricAcc = surfaceFriction / mass;

	ImGui::End();
	ImGui::EndFrame();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}

void PlayScenePart2::m_collisionCheck() {
	if (m_pBall->getTransform()->position.y <= 50 || m_pBall->getTransform()->position.y >= 550) {
		m_pBall->getRigidBody()->velocity.y = -m_pBall->getRigidBody()->velocity.y;
	}
	if (m_pBall->getTransform()->position.x <= 50 || m_pBall->getTransform()->position.x >= 950) {
		m_pBall->getRigidBody()->velocity.x = -m_pBall->getRigidBody()->velocity.x;
	}
	if (m_pBall->getTransform()->position.x <= m_pPlayer->getTransform()->position.x + 100 && m_pBall->getTransform()->position.x >= m_pPlayer->getTransform()->position.x - 100) {
		m_pBall->getRigidBody()->velocity.x = -m_pBall->getRigidBody()->velocity.x;
	}
	if (m_pBall->getTransform()->position.y <= m_pPlayer->getTransform()->position.y + 100 && m_pBall->getTransform()->position.y >= m_pPlayer->getTransform()->position.y - 100) {
		m_pBall->getRigidBody()->velocity.y = -m_pBall->getRigidBody()->velocity.y;
	}
}


