#ifndef ResourcesMgr_h__
#define ResourcesMgr_h__

#include "Texture.h"

#include "TriCol.h"
#include "RcCol.h"
#include "RcTex.h"
#include "TerrainCol.h"
#include "TerrainTex.h"
#include "CubeCol.h"
#include "CubeTex.h"

BEGIN(Engine)

class ENGINE_DLL CResourcesMgr
{
public:
	DECLARE_SINGLETON(CResourcesMgr)
private:
	CResourcesMgr(void);
	~CResourcesMgr(void);

public: 
	HRESULT InitResourcesMgr(LPDIRECT3DDEVICE9 pD3DDevice);
	HRESULT AddBuffer(	RESOURCE_TYPE eResourceType,
						CVIBuffer::BUFFER_TYPE eBufferType,
						const wstring& wstrResourceKey,
						const WORD& wCntX = 0,
						const WORD& wCntZ = 0,
						const WORD& wItv = 1,
						const wstring& wstrHeightMapPath = L"",
						const float& fHeight = 100.f);

	HRESULT AddTexture(	RESOURCE_TYPE eResourceType,
						TEXTURE_TYPE eTexType,
						const wstring& wstrResourceKey,
						const wstring& wstrResourcePath,
						const WORD& wCnt);

	CResources* CloneResource(RESOURCE_TYPE eResourceType, const wstring& wstrResourceKey);

public:
	void GetVtxInfo(RESOURCE_TYPE eResourceType, const wstring& wstrResourceKey, void* pVertex);
	void SetVtxInfo(RESOURCE_TYPE eResourceType, const wstring& wstrResourceKey, void* pVertex);

public:
	void Render(const wstring& wstrResourceKey);
	void ReleaseDynamic(void);

private:
	void Release(void);

private:
	LPDIRECT3DDEVICE9 m_pD3DDevice = nullptr;

	CResources* m_pResouces = nullptr;

	typedef map<std::wstring, CResources*> MAPRESOURCES;
	MAPRESOURCES m_ResourcesMap[RESOURCE_END];
};

END

#endif // ResourcesMgr_h__
