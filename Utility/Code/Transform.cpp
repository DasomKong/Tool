#include "Transform.h"

USING(Engine)

CTransform::CTransform(CGameObject* pGameObject)
	: CComponent(pGameObject)
	, m_vPos(VEC3_ZERO)
	, m_vDir(VEC3_FRONT)
	, m_vScale(VEC3_ONE)
{
	ZeroMemory(m_fAngle, sizeof(float) * ANGLE_END);
	Engine::MatIdentity(&m_matWorld);
}

CTransform::~CTransform(void)
{
}

void CTransform::Update(void)
{
	Engine::MatTransformWorld(&m_matWorld, &m_vPos, &m_vScale, m_fAngle);
}

D3DXVECTOR3 * CTransform::LookAt(const D3DXVECTOR3 & vTarget, const float & fRatio)
{
	return nullptr;
}

void CTransform::Translate(const D3DXVECTOR3 & vDir, SPACE eSpace)
{
}

CTransform * CTransform::Create(CGameObject* pGameObject)
{
	return new CTransform(pGameObject);
}
