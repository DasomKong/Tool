#include "Management.h"

USING(Engine)
IMPLEMENT_SINGLETON(CManagement)

Engine::CManagement::CManagement(void)
{
}

CManagement::~CManagement(void)
{
	Release();
}

HRESULT CManagement::InitManagement(LPDIRECT3DDEVICE9 pD3DDevice)
{
	m_pD3DDevice = pD3DDevice;

	m_pRenderer = CRenderer::Create(pD3DDevice);
	NULL_CHECK_RETURN_MSG(m_pRenderer, E_FAIL, L"Renderer Create Failed");

	return S_OK;
}

void CManagement::Update(void)
{
	if (nullptr != m_pScene)
		m_pScene->Update();
}

void CManagement::Render(float fTime)
{
	if (nullptr != m_pRenderer)
		m_pRenderer->Render(fTime);
}

void CManagement::Release(void)
{
	Safe_Delete(m_pScene);
	Safe_Delete(m_pRenderer);
}