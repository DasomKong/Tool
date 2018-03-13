#include "Scene.h"

USING(Engine)

CScene::CScene(LPDIRECT3DDEVICE9 pD3DDevcie)
	: m_pD3DDevice(pD3DDevcie)
{
}

CScene::~CScene(void)
{
	Release();
}

HRESULT CScene::InitScene(void)
{
	return S_OK;
}

void CScene::Update(void)
{
	for (auto& pLayer : m_LayerMap)
		pLayer.second->Update();
}

void CScene::Render(void)
{
	for (auto& pLayer : m_LayerMap)
		pLayer.second->Render();
}

void CScene::Release(void)
{
	for_each(m_LayerMap.begin(), m_LayerMap.end(), CDeleteMap());
	m_LayerMap.clear();
}
