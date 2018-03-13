#ifndef Resources_h__
#define Resources_h__

#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CResources : public CComponent
{
protected:
	explicit CResources(LPDIRECT3DDEVICE9 pD3DDevice);
public:
	virtual ~CResources(void);

public:
	virtual void Render(void) PURE;
	virtual void Release(void);

	virtual CResources* CloneResource(void) PURE;

protected:
	LPDIRECT3DDEVICE9	m_pD3DDevice	= nullptr;
	WORD*				m_pwRefCnt		= nullptr;
};

END

#endif // Resources_h__
