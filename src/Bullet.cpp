#include "Bullet.h"
#include "TextureManager.h"

Bullet::Bullet() {
	TextureManager::Instance()->load("../Assets/textures/bullet.png", "Bullet");

	auto size = TextureManager::Instance()->getTextureSize("Bullet");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(700.0f, 300.0f);
	//setType(ENEMY);

	Reset();
}

Bullet::~Bullet()
= default;

void Bullet::draw() {
	// alias for x and y
	if (active) {
		const auto x = getTransform()->position.x;
		const auto y = getTransform()->position.y;

		TextureManager::Instance()->draw("Bullet", x, y, 0, 255, true);
	}
}

void Bullet::update() {
	if (active) {
		float deltaTime = 1.0f / 60.0f;

		
		getRigidBody()->velocity += getRigidBody()->acceleration * deltaTime;
		getTransform()->position += getRigidBody()->velocity * deltaTime;
	}

}

void Bullet::clean() {

}

void Bullet::Reset()
{
	
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 9.8f);
	getRigidBody()->isColliding = false;

}

/*void Bullet::despawn()
{
	m_pPool->Despawn(this);
}
*/