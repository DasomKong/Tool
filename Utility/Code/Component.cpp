#include "Component.h"

USING(Engine)

CComponent::CComponent(CGameObject* pGameObject)
	: m_pGameObject(pGameObject)
{
}

CComponent::~CComponent(void)
{
	m_pGameObject = nullptr;
}
