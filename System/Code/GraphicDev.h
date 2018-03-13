#ifndef GraphicDev_h__
#define GraphicDev_h__

#include "Engine_Include.h"

BEGIN(Engine)

class ENGINE_DLL CGraphicDev
{
public:
	DECLARE_SINGLETON(CGraphicDev)

public:
	enum WINMODE { MODE_FUUL, MODE_WIN };

private:
	CGraphicDev(void);
public:
	~CGraphicDev(void);

public: // Getter
	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pDevice; }

public:// Setter
	void SetRenderState(_D3DRENDERSTATETYPE RSType, const DWORD& dwFlag) 
	{
		m_pDevice->SetRenderState(RSType, dwFlag);
	}
	void SetSamplerState(_D3DSAMPLERSTATETYPE SSType, const DWORD& dwFlag)
	{
		m_pDevice->SetSamplerState(0, SSType, dwFlag);
	}

public:
	HRESULT InitGraphicDev(WINMODE Mode, HWND hWnd, const WORD& wSizeX, const WORD& wSizeY);

private:
	void SetParameters(D3DPRESENT_PARAMETERS& d3dpp, WINMODE Mode, HWND hWnd, const WORD& wSizeX, const WORD& wSizeY);
	void Release(void);

private:
	LPDIRECT3D9				m_pSDK;
	LPDIRECT3DDEVICE9		m_pDevice;
};

END

#endif // GraphicDev_h__
