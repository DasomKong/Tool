#include "ResourcesMgr.h"

USING(Engine)
IMPLEMENT_SINGLETON(CResourcesMgr)

CResourcesMgr::CResourcesMgr(void)
{
}

CResourcesMgr::~CResourcesMgr(void)
{
	Release();
}

HRESULT CResourcesMgr::InitResourcesMgr(LPDIRECT3DDEVICE9 pD3DDevice)
{
	m_pD3DDevice = pD3DDevice;
	NULL_CHECK_RETURN(m_pD3DDevice, E_FAIL);

	return S_OK;
}

HRESULT CResourcesMgr::AddBuffer(RESOURCE_TYPE eResourceType, 
	CVIBuffer::BUFFER_TYPE eBufferType, const wstring & wstrResourceKey, 
	const WORD & wCntX, const WORD & wCntZ, const WORD & wItv,
	const wstring& wstrHeightMapPath, const float& fHeight)
{
	auto iter = m_ResourcesMap[eResourceType].find(wstrResourceKey);

	if (iter != m_ResourcesMap[eResourceType].end())
	{
		TAGMSG_BOX(wstrResourceKey.c_str(), L"중복된 버퍼");
		return E_FAIL;
	}

	CResources* pResources = nullptr;

	switch (eBufferType)
	{
	case Engine::CVIBuffer::BUFFER_TRICOL:
		pResources = CTriCol::Create(m_pD3DDevice);
		break;
	case Engine::CVIBuffer::BUFFER_RCCOL:
		pResources = CRcCol::Create(m_pD3DDevice);
		break;
	case Engine::CVIBuffer::BUFFER_RCTEX:
		pResources = CRcTex::Create(m_pD3DDevice);
		break;
	case Engine::CVIBuffer::BUFFER_TERRAINCOL:
		pResources = CTerrainCol::Create(m_pD3DDevice, wCntX, wCntZ, wItv);
		dynamic_cast<CTerrainCol*>(pResources)->SetHeightMap(wstrHeightMapPath, fHeight);
		break;
	case Engine::CVIBuffer::BUFFER_TERRAINTEX:
		pResources = CTerrainTex::Create(m_pD3DDevice, wCntX, wCntZ, wItv);
		dynamic_cast<CTerrainTex*>(pResources)->SetHeightMap(wstrHeightMapPath, fHeight);
		break;
	case Engine::CVIBuffer::BUFFER_CUBECOL:
		pResources = CCubeCol::Create(m_pD3DDevice, wItv);
		break;
	case Engine::CVIBuffer::BUFFER_CUBETEX:
		pResources = CCubeTex::Create(m_pD3DDevice, wItv);
		break;
	}

	NULL_CHECK_RETURN(pResources, E_FAIL);

	m_ResourcesMap[eResourceType].insert(MAPRESOURCES::value_type(wstrResourceKey, pResources));

	return S_OK;
}

HRESULT CResourcesMgr::AddTexture(RESOURCE_TYPE eResourceType, TEXTURE_TYPE eTexType, const wstring & wstrResourceKey, const wstring & wstrResourcePath, const WORD & wCnt)
{
	auto iter = m_ResourcesMap[eResourceType].find(wstrResourceKey);

	if (iter != m_ResourcesMap[eResourceType].end())
	{
		TAGMSG_BOX(wstrResourceKey.c_str(), L"중복된 텍스쳐");
		return E_FAIL;
	}

	CResources* pResources = CTexture::Create(m_pD3DDevice, eTexType, wstrResourcePath, wCnt);
	NULL_CHECK_RETURN(pResources, E_FAIL);

	m_ResourcesMap[eResourceType].insert(MAPRESOURCES::value_type(wstrResourceKey, pResources));

	return S_OK;
}

CResources * CResourcesMgr::CloneResource(RESOURCE_TYPE eResourceType, const wstring & wstrResourceKey)
{
	auto iter = m_ResourcesMap[eResourceType].find(wstrResourceKey);

	if (iter == m_ResourcesMap[eResourceType].end())
	{
		TAGMSG_BOX(wstrResourceKey.c_str(), L"Clone Failed");
		return nullptr;
	}

	return iter->second->CloneResource();
}

void CResourcesMgr::GetVtxInfo(RESOURCE_TYPE eResourceType, const wstring & wstrResourceKey, void * pVertex)
{
	auto iter = m_ResourcesMap[eResourceType].find(wstrResourceKey);

	if (iter == m_ResourcesMap[eResourceType].end())
	{
		MSG_BOX(wstrResourceKey.c_str());
		return;
	}

	dynamic_cast<CVIBuffer*>(iter->second)->GetVtxInfo(pVertex);
}

void CResourcesMgr::SetVtxInfo(RESOURCE_TYPE eResourceType, const wstring & wstrResourceKey, void * pVertex)
{
	auto iter = m_ResourcesMap[eResourceType].find(wstrResourceKey);

	if (iter == m_ResourcesMap[eResourceType].end())
	{
		MSG_BOX(wstrResourceKey.c_str());
		return;
	}

	dynamic_cast<CVIBuffer*>(iter->second)->SetVtxInfo(pVertex);
}

void CResourcesMgr::Render(const wstring & wstrResourceKey)
{

}

void CResourcesMgr::ReleaseDynamic(void)
{
	for_each(m_ResourcesMap[RESOURCE_DYNAMIC].begin(), m_ResourcesMap[RESOURCE_DYNAMIC].end(), CDeleteMap());
	m_ResourcesMap[RESOURCE_DYNAMIC].clear();
}

void CResourcesMgr::Release(void)
{
	for (size_t i = 0; i < RESOURCE_END; ++i)
	{
		for_each(m_ResourcesMap[i].begin(), m_ResourcesMap[i].end(), CDeleteMap());
		m_ResourcesMap[i].clear();
	}
}
