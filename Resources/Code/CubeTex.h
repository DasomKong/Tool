#ifndef CubeTex_h__
#define CubeTex_h__

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CCubeTex : public CVIBuffer
{
private:
	explicit CCubeTex(LPDIRECT3DDEVICE9 pD3DDevice);
public:
	virtual ~CCubeTex(void);

public:
	virtual HRESULT CreateBuffer(const WORD& wItv);
	virtual void Render(void) override;
	virtual void Release(void) override;

	virtual CResources* CloneResource(void) override;

private:
	WORD	m_wItv = 0;

public:
	static CCubeTex* Create(LPDIRECT3DDEVICE9 pD3DDevice, const WORD& wItv);
};
END

#endif // CubeTex_h__
