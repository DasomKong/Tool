#ifndef VIBuffer_h__
#define VIBuffer_h__

#include "Resources.h"

BEGIN(Engine)

class ENGINE_DLL CVIBuffer : public CResources
{
public:
	enum BUFFER_TYPE 
	{ 
		BUFFER_TRICOL, 
		BUFFER_RCCOL, 
		BUFFER_RCTEX,
		BUFFER_TERRAINCOL, 
		BUFFER_TERRAINTEX,
		BUFFER_CUBECOL,
		BUFFER_CUBETEX,
		BUFFER_END 
	};

protected:
	explicit CVIBuffer(LPDIRECT3DDEVICE9 pD3DDevice);
public:
	virtual ~CVIBuffer(void) override;

public: // Getter
	void GetOriginVtxInfo(void* pVertex);
	void GetVtxInfo(void* pVertex);
public: // Setter
	void SetVtxInfo(void* pVertex);

public:
	virtual HRESULT CreateBuffer(void);
	virtual void Render(void);
	virtual void Release(void);

	virtual CResources* CloneResource(void) PURE;

protected:
	LPDIRECT3DVERTEXBUFFER9		m_pVB			= nullptr;
	LPDIRECT3DINDEXBUFFER9		m_pIB			= nullptr;

	DWORD						m_dwVtxSize		= 0;
	DWORD						m_dwVtxCnt		= 0;
	DWORD						m_dwVtxFVF		= 0;
	DWORD						m_dwTriCnt		= 0;

	DWORD						m_dwIdxSize		= 0;
	D3DFORMAT					m_IdxFmt;

	void*						m_pOriginVtx = nullptr;
};

END

#endif // VIBuffer_h__
