#include "BulletPool.h"
#include<iostream>
#include<vector>
using namespace std;
BulletPool::BulletPool(int size)
{
	for (int i = 0; i < size; i++)
	{
		Bullet* bullet = new Bullet();
		inactive.push_back(bullet);
		all.push_back(bullet);

	}
	cout << "Bullet Pool created with size " << size << endl;

}

Bullet* BulletPool::spawn()
{
	Bullet* bullet = NULL;
	if (inactive.size()>0)
	{
		bullet = inactive.back();
		bullet->Reset();
		bullet->active = true;
		inactive.pop_back();
		active.push_back(bullet);
	}
	else
	{
		cout << "ERROR: Max Bullets Spawned."<< endl;
	}
	return bullet;
}

void BulletPool::Despawn(Bullet*bullet)
{
	bullet->active= false ;
	inactive.push_back(bullet);

	for (vector<Bullet*>::iterator myiter = active.begin(); myiter != active.end(); myiter++)
	{
		if (*myiter == bullet) 
		
		{
			active.erase(myiter);
			return;
		}
	}

}




