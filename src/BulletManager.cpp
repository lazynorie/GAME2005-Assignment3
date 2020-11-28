#include "BulletManager.h"
BulletManager::BulletManager(PlayScene* scene)
{
	m_pScene = scene;
}
void BulletManager::update()
{
	if (timer >= spawnTime)
	{
		spawnBullet();
	}
}

void BulletManager::spawnBullet()
{
	Bullet* bullet = m_pPool->spawn();
	if (bullet) {
		m_pScene->addChild(bullet);
		bullet->getTransform()->position = glm::vec2(50 + rand() % 700, rand() % 100 - 1);
	}
}


