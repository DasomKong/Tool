#ifndef TriCol_h__
#define TriCol_h__

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CTriCol : public CVIBuffer
{
private:
	explicit CTriCol(LPDIRECT3DDEVICE9 pD3DDevice);
public:
	virtual ~CTriCol(void) override;

public:
	virtual HRESULT CreateBuffer(void) override;
	virtual void Render(void) override;
	virtual void Release(void) override;

	virtual CResources* CloneResource(void) override;

public:
	static CTriCol* Create(LPDIRECT3DDEVICE9 pD3DDevice);
};

END
#endif // TriCol_h__
