#ifndef TerrainTex_h__
#define TerrainTex_h__

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CTerrainTex : public CVIBuffer
{
private:
	explicit CTerrainTex(LPDIRECT3DDEVICE9 pD3DDevice);
public:
	virtual ~CTerrainTex(void);

public: // Getter
	void GetTerrainInfo(WORD* wCntX, WORD* wCntZ, WORD* wItv);

public:
	virtual HRESULT CreateBuffer(const WORD& wCntX, const WORD& wCntZ, const WORD& wItv);
	virtual void Render(void) override;
	virtual void Release(void) override;

	void SetHeightMap(const wstring& wstrFilePath, const float& fHeight);

	virtual CResources* CloneResource(void) override;

private:
	DWORD* GetHeightMapPixel(const wstring wstrFilePath);

private:
	WORD m_wCntX = 0;
	WORD m_wCntZ = 0;
	WORD m_wItv = 0;

public:
	static CTerrainTex* Create(LPDIRECT3DDEVICE9 pD3DDevice, const WORD& wCntX, const WORD& wCntZ, const WORD& wItv);
};

END

#endif // TerrainTex_h__
