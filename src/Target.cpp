#include "Target.h"
#include "TextureManager.h"
#include <iostream>
using namespace std;
const int mpp = 2;

Target::Target()
{
	TextureManager::Instance()->load("../Assets/textures/Circle.png", "circle");

	const auto size = TextureManager::Instance()->getTextureSize("circle");


	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position = glm::vec2(100.0f, 500.0f);
	getRigidBody()->velocity = glm::vec2(0, 0);
	getRigidBody()->isColliding = false;

	setType(TARGET);
}

Target::~Target()
= default;

void Target::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the target
	TextureManager::Instance()->draw("circle", x, y, 0, 255, true);
}

void Target::update()
{
	m_move();
	m_checkBounds();
}

void Target::clean()
{
}

void Target::m_move()
{
	float deltaTime = 1.0f / 60.0f;
	glm::vec2 gravity = glm::vec2(0, 9.8f);
	cout << getRigidBody()->velocity.x << endl;

	getRigidBody()->velocity += getRigidBody()->acceleration * (deltaTime * mpp);
	getTransform()->position += getRigidBody()->velocity * (deltaTime * mpp);
	velocity += acc * (deltaTime * mpp);

}

void Target::m_checkBounds()
{
}

void Target::m_reset()
{
}

void Target::doThrow()
{
	getTransform()->position = throwposition;
	getRigidBody()->velocity = throwspeed;
}

void Target::doFallen()
{
	ifLanded = true;
	getTransform()->position = fallenposition;
	getRigidBody()->velocity = fallenspeed;
	velocity = 0;
}

