#ifndef RcCol_h__
#define RcCol_h__

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CRcCol : public CVIBuffer
{
private:
	explicit CRcCol(LPDIRECT3DDEVICE9 pD3DDevice);
public:
	virtual ~CRcCol(void) override;

public:
	virtual HRESULT CreateBuffer(void) override;
	virtual void Render(void) override;
	virtual void Release(void) override;

	virtual CResources* CloneResource(void) override;

public:
	static CRcCol* Create(LPDIRECT3DDEVICE9 pD3DDevice);
};

END

#endif // RcCol_h__
