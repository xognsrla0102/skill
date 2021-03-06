#pragma once
#include "cObject.h"

class cEnemy;
class cBoss;
class cMidBoss;
class cEnemyManager : public cObject
{
private:
	vector<cEnemy*> m_meteor;
	vector<cEnemy*> m_enemy;
public:
	cMidBoss* m_mBoss = nullptr;
	cBoss* m_boss = nullptr;
public:
	cEnemyManager();
	~cEnemyManager();
	
	virtual void Update() override;
	virtual void Render() override;
	void Release();

	vector<cEnemy*>& GetMeteor() { return m_meteor; }
	vector<cEnemy*>& GetEnemy() { return m_enemy; }
	cMidBoss* GetMidBoss() { return m_mBoss; }
	cBoss* GetBoss() { return m_boss; }
};

