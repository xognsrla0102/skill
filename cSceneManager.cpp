#include "DXUT.h"
#include "cScene.h"
#include "cSceneManager.h"

cSceneManager::cSceneManager()
{
	IMAGE->AddTexture("ChangeSceneEffect", "resources/image/scenechange/white.png");
	IMAGE->AddTexture("ChangeScenePlaneEffect", "resources/image/scenechange/plane.png");

	m_white = new cImage;
	m_white->m_text = IMAGE->FindTexture("ChangeSceneEffect");
	m_white->m_a = 0.f;
	m_white->SetNowRGB();

	m_plane = new cImage;
	m_plane->m_text = IMAGE->FindTexture("ChangeScenePlaneEffect");
	m_plane->m_pos = VEC2(WINSIZEX + m_plane->m_text->m_info.Width, -300);
}

cSceneManager::~cSceneManager()
{
	SAFE_DELETE(m_white);
	SAFE_DELETE(m_plane);

	for (auto iter : m_scenes)
		SAFE_DELETE(iter.second);
	m_scenes.clear();
}

void cSceneManager::AddScene(const string& key, cScene* scenePtr)
{
	if (!scenePtr) {
		DEBUG_LOG("씬 포인터가 없습니다.\n");
		return;
	}
	if (m_scenes.find(key) != m_scenes.end()) {
		DEBUG_LOG("%s 씬이 있습니다.\n", key.c_str());
		return;
	}
	m_scenes[key] = scenePtr;
	DEBUG_LOG("%s 씬 생성완료.\n", key.c_str());
}

void cSceneManager::ChangeScene(const string& key, string changeName, FLOAT changeSpeed)
{
	if (m_scenes.find(key) == m_scenes.end()) {
		DEBUG_LOG("%s 씬이 없습니다.", key.c_str());
		return;
	}
	m_next = m_scenes.find(key)->second;

	m_changeSpeed = changeSpeed;

	if (changeName == "Fade") {
		m_isFadeChange = true;
		m_isFadeOut = true;
	}
	else if (changeName == "Plane")
		m_isPlaneChange = true;

	if (changeName != "None") m_isSceneChange = true;
	else m_isSceneChange = false;
}

void cSceneManager::Update()
{
	if ((!m_isSceneChange && m_next) ||
		(m_next && m_isFadeIn && m_white->m_a > 240.f) ||
		(m_next && m_plane->m_pos.x < -(int)m_plane->m_text->m_info.Width)
		) {
		SAFE_RELEASE(m_now);
		m_now = m_next;
		m_next = nullptr;
		m_now->Init();
	}

	if (m_isFadeChange) FadeSceneChange();
	else if (m_isPlaneChange) PlaneSceneChange();

	if (m_now) m_now->Update();
}

void cSceneManager::Render()
{
	if (m_now) m_now->Render();

	if (m_isFadeChange)
		IMAGE->Render(m_white->m_text, VEC2(0, 0), VEC2(1, 1), 0.f, FALSE, m_white->m_color);
	else if (m_isPlaneChange)
		IMAGE->Render(m_plane->m_text, m_plane->m_pos);
}

//점점 나타남
bool cSceneManager::FadeIn()
{
	if (m_white->m_a < m_changeSpeed) {
		m_white->m_a = 0;
		m_white->SetNowRGB();
		return true;
	}
	else {
		m_white->m_a -= m_changeSpeed;
		m_white->SetNowRGB();
		return false;
	}
}

//점점 어두워짐
bool cSceneManager::FadeOut()
{
	if (m_white->m_a > 255 - m_changeSpeed) {
		m_white->m_a = 255;
		m_white->SetNowRGB();
		return true;
	}
	else {
		m_white->m_a += m_changeSpeed;
		m_white->SetNowRGB();
		return false;
	}
}

void cSceneManager::FadeSceneChange()
{
	//페이드 아웃 먼저 하고 페이드 인을 해야 한다.
	if (m_isFadeOut) {
		if (FadeOut()) {
			m_isFadeOut = false;
			m_isFadeIn = true;
		}
		return;
	}

	if (m_isFadeIn) {
		if (FadeIn()) {
			m_isFadeIn = false;
			m_isFadeChange = false;
			m_isSceneChange = false;
		}
	}
}

void cSceneManager::PlaneSceneChange()
{
	m_plane->m_pos.x -= m_changeSpeed * D_TIME;
	if (m_plane->m_pos.x < -(int)m_plane->m_text->m_info.Width) {
		m_plane->m_pos = VEC2(WINSIZEX + m_plane->m_text->m_info.Width, -300);
		m_isPlaneChange = false;
		m_isSceneChange = false;
	}
}

string cSceneManager::GetNowSceneKey()
{
	for (auto iter : m_scenes) {
		if (m_now == iter.second)
			return iter.first;
	}
	return "현재 씬을 찾을 수 없습니다.\n";
}
