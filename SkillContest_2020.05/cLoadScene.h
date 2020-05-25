#pragma once
#include "cScene.h"

class cLoadScene : public cScene
{
private:
	cTexture* m_bg = nullptr;
private:
	void LoadImg(string key, string path, INT amount = 0);
	void LoadSnd(string key, wstring path);
public:
	cLoadScene();
	virtual ~cLoadScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

