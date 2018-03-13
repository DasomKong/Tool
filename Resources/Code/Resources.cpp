#include "Resources.h"

USING(Engine)

CResources::CResources(LPDIRECT3DDEVICE9 pD3DDevice)
	: CComponent(nullptr)
	, m_pD3DDevice(pD3DDevice)
	, m_pwRefCnt(new WORD(0))
{
}

CResources::~CResources(void)
{
}

void CResources::Release(void)
{
	Safe_Delete(m_pwRefCnt);
}
