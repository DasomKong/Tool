#ifndef CubeCol_h__
#define CubeCol_h__

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CCubeCol : public CVIBuffer
{
private:
	explicit CCubeCol(LPDIRECT3DDEVICE9 pD3DDevice);
public:
	virtual ~CCubeCol(void);

public:
	virtual HRESULT CreateBuffer(const WORD& wItv);
	virtual void Render(void) override;
	virtual void Release(void) override;

	virtual CResources* CloneResource(void) override;

private:
	WORD m_wItv = 0;

public:
	static CCubeCol* Create(LPDIRECT3DDEVICE9 pD3DDevice, const WORD& wItv);
};

END

#endif // CubeCol_h__
