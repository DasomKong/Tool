#include "TriCol.h"

USING(Engine)

CTriCol::CTriCol(LPDIRECT3DDEVICE9 pD3DDevice)
	: CVIBuffer(pD3DDevice)
{
}

CTriCol::~CTriCol(void)
{
	Release();
}

HRESULT CTriCol::CreateBuffer(void)
{
	m_dwVtxFVF = VTXFVF_COL;
	m_dwTriCnt = 1;
	m_dwVtxCnt = 3;
	m_dwVtxSize = sizeof(VTXCOL);

	m_dwIdxSize = sizeof(VTXCOL);
	m_IdxFmt = D3DFMT_INDEX32;

	FAILED_CHECK(CVIBuffer::CreateBuffer());

	VTXCOL* pVtxCol = nullptr;

	m_pVB->Lock(0, 0, (void**)&pVtxCol, 0);

	pVtxCol[0].vPos = D3DXVECTOR3(0.f, 1.f, 0.f);
	pVtxCol[0].dwColor = D3DCOLOR_ARGB(255, 255, 0, 0);

	pVtxCol[1].vPos = D3DXVECTOR3(1.f, -1.f, 0.f);
	pVtxCol[1].dwColor = D3DCOLOR_ARGB(255, 0, 255, 0);

	pVtxCol[2].vPos = D3DXVECTOR3(-1.f, -1.f, 0.f);
	pVtxCol[2].dwColor = D3DCOLOR_ARGB(255, 0, 0, 255);

	m_pOriginVtx = new VTXCOL[m_dwVtxCnt];
	memcpy(m_pOriginVtx, pVtxCol, m_dwVtxCnt * m_dwVtxSize);

	m_pVB->Unlock();

	INDEX32* pIndex = nullptr;

	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	pIndex[0]._1 = 0;
	pIndex[0]._2 = 1;
	pIndex[0]._3 = 2;

	m_pIB->Unlock();

	return S_OK;
}

void CTriCol::Render(void)
{
	CVIBuffer::Render();
}

void CTriCol::Release(void)
{
}

CResources * CTriCol::CloneResource(void)
{
	++(*m_pwRefCnt);

	return new CTriCol(*this);
}

CTriCol * CTriCol::Create(LPDIRECT3DDEVICE9 pD3DDevice)
{
	CTriCol* pInstance = new CTriCol(pD3DDevice);

	if (FAILED(pInstance->CreateBuffer()))
		Safe_Delete(pInstance);

	return pInstance;
}
