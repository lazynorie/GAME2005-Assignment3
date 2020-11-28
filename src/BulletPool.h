#pragma once
#ifndef __BulletPool__
#define __BulletPool__
#include"Bullet.h"
#include<iostream>
using namespace std;
class BulletPool
{
public:
	BulletPool(int);
	~BulletPool();

	Bullet* spawn();
	void Despawn(Bullet*);
	vector<Bullet*> all;
private:
	
	vector<Bullet*> inactive;
	vector<Bullet*>active;
};
#endif

