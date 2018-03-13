#ifndef Texture_h__
#define Texture_h__

#include "Resources.h"

BEGIN(Engine)

class ENGINE_DLL CTexture : public CResources
{
private:
	explicit CTexture(LPDIRECT3DDEVICE9 pD3DDevice);
public:
	virtual ~CTexture(void) override;

public:
	virtual void Render(void) override {};
	void Render(const DWORD& iIndex);
	void Release(void);

	virtual CResources* CloneResource(void) override;

private:
	HRESULT LoadTexture(TEXTURE_TYPE eTextureType, const wstring& wstrFilePath, const WORD& wCnt);

private:
	typedef vector<IDirect3DBaseTexture9*>	VECTEXTURE;
	VECTEXTURE								m_TextureVec;
	DWORD									m_dwContainerSize = 0;

public:
	static CTexture* Create(LPDIRECT3DDEVICE9 pD3DDevice, TEXTURE_TYPE eTextureType, const wstring& wstrFilePath, const WORD& wCnt);
};

END

#endif // Texture_h__
