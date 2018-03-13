#ifndef Renderer_h__
#define Renderer_h__

#include "Engine_Include.h"

BEGIN(Engine)

class CScene;
class ENGINE_DLL CRenderer
{
private:
	CRenderer(LPDIRECT3DDEVICE9 pD3DDevcie);
public:
	~CRenderer(void);

public: // Setter
	void SetScene(CScene* pScene);

public:
	HRESULT InitRenderer(void);
	void Render(float fTime);

private:
	LPDIRECT3DDEVICE9		m_pD3DDevice = nullptr;
	CScene*					m_pScene = nullptr;

	ID3DXFont*				m_pD3DXFont = nullptr;
	float					m_fTime = 0.f;
	WORD					m_wFrameCnt = 0;
	TCHAR					m_szFPS[128] = L"";

public:
	static CRenderer* Create(LPDIRECT3DDEVICE9 pD3DDevice);
};

END

#endif // Renderer_h__
