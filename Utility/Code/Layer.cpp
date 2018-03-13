#include "Layer.h"

USING(Engine)

CLayer::CLayer(LPDIRECT3DDEVICE9 pD3DDevice)
	: m_pD3DDevice(pD3DDevice)
{
}

CLayer::~CLayer(void)
{
	Release();
}

void CLayer::Update(void)
{
	for (auto& pairObjList : m_ObjListMap)
	{
		for (auto& pGameObj : pairObjList.second)
		{
			pGameObj->Update();
		}
	}
}

void CLayer::Render(void)
{
	for (auto& pairObjList : m_ObjListMap)
	{
		for (auto& pGameObj : pairObjList.second)
		{
			pGameObj->Render();
		}
	}
}

HRESULT CLayer::AddObject(const wstring & wstrObjKey, CGameObject * pGameObject)
{
	if (nullptr == pGameObject)
		return E_FAIL;

	auto iter = m_ObjListMap.find(wstrObjKey);

	if (iter == m_ObjListMap.end())
	{
		m_ObjListMap[wstrObjKey] = OBJLIST();
	}

	m_ObjListMap[wstrObjKey].push_back(pGameObject);

	return S_OK;
}

void CLayer::Release(void)
{
	for (auto& pairObjList : m_ObjListMap)
	{
		for (auto& pGameObj : pairObjList.second)
		{
			Safe_Delete(pGameObj);
		}
		pairObjList.second.clear();
	}
	m_ObjListMap.clear();
}

CLayer * CLayer::Create(LPDIRECT3DDEVICE9 pD3DDevice)
{
	return new CLayer(pD3DDevice);
}
