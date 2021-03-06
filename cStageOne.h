#pragma once
#include "cScene.h"

class cScroolMap;
class cStageOne : public cScene
{
private:
	string m_nowBGM;
	cScroolMap* m_map;
	cTimer* m_timePlus;
	cTimer* m_createMeteor;
	cTimer* m_createRazer;
	cTimer* m_createStraight;
	cTimer* m_createRadial;
	cTimer* m_createRotate;

	FLOAT m_patternTime;

	int m_createMidBossTime = 100.f;
	int m_createBossTime = 200.f;
	int m_gameTime;
	int m_mapPattern;
	int m_totalPattern = 5;
public:
	cStageOne();
	virtual ~cStageOne();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	void DelayPattern();
	void MapPattern();
	void MapPattern1();
	void MapPattern2();
	void MapPattern3();
	void MapPattern4();
};

