#include "RcTex.h"

USING(Engine)

CRcTex::CRcTex(LPDIRECT3DDEVICE9 pD3DDevice)
	: CVIBuffer(pD3DDevice)
{
}

CRcTex::~CRcTex(void)
{
	Release();
}

HRESULT CRcTex::CreateBuffer(void)
{
	m_dwVtxFVF = VTXFVF_TEX;
	m_dwTriCnt = 2;
	m_dwVtxCnt = 4;
	m_dwVtxSize = sizeof(VTXTEX);

	m_dwIdxSize = sizeof(INDEX32);
	m_IdxFmt = D3DFMT_INDEX32;

	FAILED_CHECK(CVIBuffer::CreateBuffer());

	VTXTEX* pVtxTex = nullptr;

	m_pVB->Lock(0, 0, (void**)&pVtxTex, 0);

	pVtxTex[0].vPos = D3DXVECTOR3(-1.f, 1.f, 0.f);
	pVtxTex[0].vTex = D3DXVECTOR2(0.f, 0.f);

	pVtxTex[1].vPos = D3DXVECTOR3(1.f, 1.f, 0.f);
	pVtxTex[1].vTex = D3DXVECTOR2(1.f, 0.f);

	pVtxTex[2].vPos = D3DXVECTOR3(1.f, -1.f, 0.f);
	pVtxTex[2].vTex = D3DXVECTOR2(1.f, 1.f);

	pVtxTex[3].vPos = D3DXVECTOR3(-1.f, -1.f, 0.f);
	pVtxTex[3].vTex = D3DXVECTOR2(0.f, 1.f);

	m_pOriginVtx = new VTXTEX[m_dwVtxCnt];
	memcpy(m_pOriginVtx, pVtxTex, m_dwVtxCnt * m_dwVtxSize);

	m_pVB->Unlock();

	INDEX32* pIndex = nullptr;

	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	pIndex[0]._1 = 0;
	pIndex[0]._2 = 1;
	pIndex[0]._3 = 2;

	pIndex[1]._1 = 0;
	pIndex[1]._2 = 2;
	pIndex[1]._3 = 3;

	m_pIB->Unlock();

	return S_OK;
}

void CRcTex::Render(void)
{
	CVIBuffer::Render();
}

void CRcTex::Release(void)
{
}

CResources * CRcTex::CloneResource(void)
{
	++(*m_pwRefCnt);

	return new CRcTex(*this);
}

CRcTex * CRcTex::Create(LPDIRECT3DDEVICE9 pD3DDevice)
{
	CRcTex* pInstance = new CRcTex(pD3DDevice);

	if (FAILED(pInstance->CreateBuffer()))
		Safe_Delete(pInstance);

	return pInstance;
}
