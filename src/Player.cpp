#include "Player.h"
#include "TextureManager.h"

Player::Player()
{
	TextureManager::Instance()->load("../Assets/textures/brick.png", "circle");

	auto size = TextureManager::Instance()->getTextureSize("circle");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(400.0f, 300.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(PLAYER);
}

Player::~Player()
= default;

void Player::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	TextureManager::Instance()->draw("circle", x, y, 0, 255, true);
}

void Player::update()
{
	const float deltaTime = 1.0f / 60.f;

	glm::vec2 pos = getTransform()->position;
	pos.x += getRigidBody()->velocity.x * deltaTime;
	pos.y += getRigidBody()->velocity.y * deltaTime;

	getTransform()->position = pos;
}

void Player::clean()
{

}

void Player::moveLeft() {
	getRigidBody()->velocity = glm::vec2(-SPEED, 0.0f);
}

void Player::moveRight() {
	getRigidBody()->velocity = glm::vec2(SPEED, 0.0f);
}

void Player::moveUp() {
	getRigidBody()->velocity = glm::vec2(0.0f, -SPEED);
}

void Player::moveDown() {
	getRigidBody()->velocity = glm::vec2(0.0f, SPEED);
}

void Player::stopMoving() {
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
}

bool Player::isColliding(GameObject * pOther) {
	// Works for square sprites only
	float myRadius = getWidth() * 0.5f;
	float otherRadius = pOther->getWidth() * 0.5f;

	return (getDistance(pOther) <= myRadius + otherRadius);
}

float Player::getDistance(GameObject * pOther) {
	glm::vec2 myPos = getTransform()->position;
	glm::vec2 otherPos = pOther->getTransform()->position;

	// Use pythagorean to calculate distance c = sqrt(a^2 + b^2)
	float a = myPos.x - otherPos.x;
	float b = myPos.y - otherPos.y;
	return sqrt(a * a + b * b);
}

//
//Player::Player(): m_currentAnimationState(PLAYER_IDLE_RIGHT)
//{
//	TextureManager::Instance()->loadSpriteSheet(
//		"../Assets/sprites/atlas.txt",
//		"../Assets/sprites/atlas.png", 
//		"spritesheet");
//
//	setSpriteSheet(TextureManager::Instance()->getSpriteSheet("spritesheet"));
//	
//	// set frame width
//	setWidth(53);
//
//	// set frame height
//	setHeight(58);
//
//	getTransform()->position = glm::vec2(100.0f, 400.0f);
//	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
//	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
//	getRigidBody()->isColliding = false;
//	setType(PLAYER);
//
//	m_buildAnimations();
//}
//
//Player::~Player()
//= default;
//
//void Player::draw()
//{
//	// alias for x and y
//	const auto x = getTransform()->position.x;
//	const auto y = getTransform()->position.y;
//
//	// draw the player according to animation state
//	switch(m_currentAnimationState)
//	{
//	case PLAYER_IDLE_RIGHT:
//		TextureManager::Instance()->playAnimation("spritesheet", getAnimation("idle"),
//			x, y, 0.12f, 0, 255, true);
//		break;
//	case PLAYER_IDLE_LEFT:
//		TextureManager::Instance()->playAnimation("spritesheet", getAnimation("idle"),
//			x, y, 0.12f, 0, 255, true, SDL_FLIP_HORIZONTAL);
//		break;
//	case PLAYER_RUN_RIGHT:
//		TextureManager::Instance()->playAnimation("spritesheet", getAnimation("run"),
//			x, y, 0.25f, 0, 255, true);
//		break;
//	case PLAYER_RUN_LEFT:
//		TextureManager::Instance()->playAnimation("spritesheet", getAnimation("run"),
//			x, y, 0.25f, 0, 255, true, SDL_FLIP_HORIZONTAL);
//		break;
//	default:
//		break;
//	}
//	
//}
//
//void Player::update()
//{
//}
//
//void Player::clean()
//{
//}
//
//void Player::setAnimationState(const PlayerAnimationState new_state)
//{
//	m_currentAnimationState = new_state;
//}
//
//void Player::m_buildAnimations()
//{
//	Animation idleAnimation = Animation();
//
//	idleAnimation.name = "idle";
//	idleAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-idle-0"));
//	idleAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-idle-1"));
//	idleAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-idle-2"));
//	idleAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-idle-3"));
//
//	setAnimation(idleAnimation);
//
//	Animation runAnimation = Animation();
//
//	runAnimation.name = "run";
//	runAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-run-0"));
//	runAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-run-1"));
//	runAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-run-2"));
//	runAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-run-3"));
//
//	setAnimation(runAnimation);
//}
