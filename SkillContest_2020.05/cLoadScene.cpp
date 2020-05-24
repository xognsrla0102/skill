#include "DXUT.h"
#include "cLoadScene.h"

cLoadScene::cLoadScene()
{
}

cLoadScene::~cLoadScene()
{
}

void cLoadScene::Init()
{
	SOUND->AddSound("Title", L"resources/bgm/title.wav");
}

void cLoadScene::Update()
{
	if (GetAsyncKeyState(VK_SPACE) & 0x0001) {
		SOUND->Copy("Title");
	}
}

void cLoadScene::Render()
{
}

void cLoadScene::Release()
{
}
