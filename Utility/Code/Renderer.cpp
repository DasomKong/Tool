#include "Renderer.h"

#include "Scene.h"

USING(Engine)

CRenderer::CRenderer(LPDIRECT3DDEVICE9 pD3DDevcie)
	: m_pD3DDevice(pD3DDevcie)
{
}

CRenderer::~CRenderer(void)
{
}

void CRenderer::SetScene(CScene * pScene)
{
	m_pScene = pScene;
}

HRESULT CRenderer::InitRenderer(void)
{
	D3DXFONT_DESC		hFont;
	ZeroMemory(&hFont, sizeof(D3DXFONT_DESC));

	hFont.Width = 10;
	hFont.Height = 15;
	hFont.Weight = FW_NORMAL;
	lstrcpy(hFont.FaceName, L"πŸ≈¡");
	hFont.CharSet = HANGUL_CHARSET;

	FAILED_CHECK(D3DXCreateFontIndirect(m_pD3DDevice, &hFont, &m_pD3DXFont));

	return S_OK;
}

void CRenderer::Render(float fTime)
{
#ifdef _DEBUG
	RECT rc{ 0, 0, 800, 600 };
	++m_wFrameCnt;
	m_fTime += fTime;

	if (1.f < m_fTime)
	{
		wsprintf(m_szFPS, L"FPS : %d", m_wFrameCnt);
		m_wFrameCnt = 0;
		m_fTime = 0.f;
	}
#endif // _DEBUG

	m_pD3DDevice->Clear(0, nullptr, D3DCLEAR_STENCIL | D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(255, 181, 219, 146), 1.f, 0);
	m_pD3DDevice->BeginScene();

#ifdef _DEBUG
	m_pD3DXFont->DrawText(nullptr, m_szFPS, lstrlen(m_szFPS), &rc, DT_NOCLIP, D3DCOLOR_ARGB(255, 0, 255, 0));
#endif // _DEBUG

	if (nullptr != m_pScene)
		m_pScene->Render();

	m_pD3DDevice->EndScene();
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

CRenderer * CRenderer::Create(LPDIRECT3DDEVICE9 pD3DDevice)
{
	CRenderer* pInstance = new CRenderer(pD3DDevice);

	if (FAILED(pInstance->InitRenderer()))
		Safe_Delete(pInstance);

	return pInstance;
}
