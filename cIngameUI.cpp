#include "DXUT.h"
#include "cPlayer.h"
#include "cImage.h"
#include "cIngameUI.h"

cIngameUI::cIngameUI()
{
	m_bg = new cImage;
	m_nowWeapon = new cImage;
	m_gameName = new cImage;
	m_level = new cImage;
	m_expBar = new cImage;
	m_backWhite = new cImage;
	m_player = new cImage;
	m_damaged = new cImage;
}

cIngameUI::~cIngameUI()
{
	SAFE_DELETE(m_bg);
	SAFE_DELETE(m_nowWeapon);
	SAFE_DELETE(m_gameName);
	SAFE_DELETE(m_level);
	SAFE_DELETE(m_expBar);
	SAFE_DELETE(m_backWhite);
	SAFE_DELETE(m_player);
	SAFE_DELETE(m_damaged);
}

void cIngameUI::Init()
{
	m_bg->m_text = IMAGE->FindTexture("IngameBGUI");
	m_nowWeapon->m_text = IMAGE->FindTexture("IngameWeaponUI");
	m_gameName->m_text = IMAGE->FindTexture("IngameStarUI");
	m_level->m_text = IMAGE->FindTexture("IngameLevelUI");
	m_expBar->m_text = IMAGE->FindTexture("IngameExpUI");
	m_backWhite->m_text = IMAGE->FindTexture("IngameBackWhiteUI");
	m_damaged->m_text = IMAGE->FindTexture("IngameDamagedUI");
}

void cIngameUI::Render()
{
	P_STATUS status = ((cPlayer*)OBJFIND(PLAYER))->m_status;
	cAnimation* ani = OBJFIND(PLAYER)->GetAni();

	if (status == P_IDLE)
		m_player->m_text = IMAGE->FindTexture("PlayerIdle");
	else if (status == P_LEFT)
		m_player->m_text = IMAGE->FindTexture("PlayerLeft", ani->m_nowFrame);
	else if (status == P_RIGHT)
		m_player->m_text = IMAGE->FindTexture("PlayerRight", ani->m_nowFrame);

	IMAGE->Render(m_backWhite->m_text, VEC2(680, 100));
	IMAGE->Render(m_player->m_text, VEC2(710, 420), VEC2(1.8, 1.8));

	IMAGE->Render(m_bg->m_text, VEC2(0, 0));

	int weapon = ((cPlayer*)OBJFIND(PLAYER))->m_nowWeapon;
	IMAGE->Render(m_nowWeapon->m_text, VEC2(190 + 76 * weapon, 642), VEC2(1, 1), 0.f, true);
	IMAGE->Render(m_gameName->m_text, VEC2(785, 200), VEC2(1, 1), 0.f, true);
	for (size_t i = 0; i < GAME->m_level; ++i)
		IMAGE->Render(m_level->m_text, VEC2(710 + 40 * i, 370), VEC2(1, 1), 0.f, true);

	char str[256];
	int score = GAME->m_totalExp;
	sprintf(str, "%09d", score);
	DRAW_NUM(string(str), VEC2(830, 30), 40);

	float result = GAME->m_nowExp / (float)GAME->m_expMax;
	RECT rt = {
		0, 0,
		m_expBar->m_text->m_info.Width * result,
		m_expBar->m_text->m_info.Height
	};
	IMAGE->CropRender(m_expBar->m_text, VEC2(685, 606), VEC2(1, 1), rt, false);

	result *= 100;
	if (GAME->m_level == 5) result = 0;
	DRAW_FLOAT_SIZE(to_string(result), VEC2(690, 630), 5, 16, 15, VEC2(0.3, 0.3));
}

void cIngameUI::Release()
{
}
