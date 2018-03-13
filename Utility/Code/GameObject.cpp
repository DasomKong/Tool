#include "GameObject.h"

#include "Transform.h"

USING(Engine)

CGameObject::CGameObject(LPDIRECT3DDEVICE9 pD3DDevice)
	: m_pD3DDevice(pD3DDevice)
{
}

CGameObject::~CGameObject(void)
{
	Release();
}

CComponent * CGameObject::GetComponent(const wstring & wstrComponentKey)
{
	auto iter = m_ComponentMap.find(wstrComponentKey);

	if (iter == m_ComponentMap.end())
		return nullptr;

	return iter->second;
}

void CGameObject::SetTransform(const D3DXVECTOR3 & vPos, const D3DXVECTOR3 & vDir, const D3DXVECTOR3 & vScale)
{
	m_pTransform->m_vPos = vPos;
	m_pTransform->m_vDir = vDir;
	m_pTransform->m_vScale = vScale;
}

void CGameObject::SetPosition(const D3DXVECTOR3 & vPos)
{
	m_pTransform->m_vPos = vPos;
}

void CGameObject::SetRotation(const D3DXVECTOR3 & vDir)
{
	m_pTransform->m_vDir = vDir;
}

void CGameObject::SetScale(const D3DXVECTOR3 & vScale)
{
	m_pTransform->m_vScale = vScale;
}

HRESULT CGameObject::Initialize(void)
{
	return S_OK;
}

void CGameObject::Update(void)
{
	for (auto& pairCom : m_ComponentMap)
		pairCom.second->Update();
}

void CGameObject::Render(void)
{
}

void CGameObject::Release(void)
{
	m_pTransform = nullptr;

	for_each(m_ComponentMap.begin(), m_ComponentMap.end(), CDeleteMap());
	m_ComponentMap.clear();
}
