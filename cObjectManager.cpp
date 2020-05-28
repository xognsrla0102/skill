#include "DXUT.h"
#include "cObject.h"
#include "cObjectManager.h"

cObjectManager::cObjectManager()
{
}

cObjectManager::~cObjectManager()
{
	for (auto iter : m_objs)
		SAFE_DELETE(iter);
}

void cObjectManager::Update()
{
	for (int i = 0; i < TAG_END; ++i) {
		if(OBJFIND(i) != nullptr)
			OBJFIND(i)->Update();
	}
}

void cObjectManager::Render()
{
	//������Ʈ �Ŵ��� ����

	//�÷��̾� �±�

	//���׹� �±� -> ���� ��, ���Ÿ� �� ���� ������Ʈ
	//�±׸��� ������ ����
	//���׹� �±׿��� ������ �ϸ� ���׹� �Ŵ��� �ӿ� ����
	//�� ���� �����Լ��� ȣ����
	//���׹� �Ŵ����� �������� ��� ������� �������� �ϵ��� ó��
	for (int i = 0; i < TAG_END; ++i) {
		if (OBJFIND(i) != nullptr)
			OBJFIND(i)->Render();
	}
}

void cObjectManager::AddOBJ(cObject* obj, int tagNum)
{
	if (m_objs[tagNum] == nullptr) m_objs[tagNum] = obj;
	else DEBUG_LOG("�̹� ���� �̸��� �±װ� �־���...\n");
}

cObject* cObjectManager::FindOBJ(int tagNum)
{
	if (m_objs[tagNum] == nullptr) return nullptr;
	return m_objs[tagNum];
}
