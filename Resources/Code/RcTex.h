#ifndef RcTex_h__
#define RcTex_h__

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CRcTex : public CVIBuffer
{
private:
	explicit CRcTex(LPDIRECT3DDEVICE9 pD3DDevice);
public:
	virtual ~CRcTex(void) override;

public:
	virtual HRESULT CreateBuffer(void) override;
	virtual void Render(void) override;
	virtual void Release(void) override;

	virtual CResources* CloneResource(void) override;

public:
	static CRcTex* Create(LPDIRECT3DDEVICE9 pD3DDevice);
};

END

#endif // RcTex_h__
