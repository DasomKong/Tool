#include "CubeCol.h"

USING(Engine)

CCubeCol::CCubeCol(LPDIRECT3DDEVICE9 pD3DDevice)
	: CVIBuffer(pD3DDevice)
{
}

CCubeCol::~CCubeCol(void)
{
	Release();
}

HRESULT CCubeCol::CreateBuffer(const WORD & wItv)
{
	m_dwVtxFVF = VTXFVF_COL;
	m_dwTriCnt = 12;
	m_dwVtxCnt = 8;
	m_dwVtxSize = sizeof(VTXCOL);

	m_dwIdxSize = sizeof(INDEX32);
	m_IdxFmt = D3DFMT_INDEX32;

	FAILED_CHECK(CVIBuffer::CreateBuffer());

	m_wItv = wItv;

	VTXCOL* pVtxCol = nullptr;

	m_pVB->Lock(0, 0, (void**)&pVtxCol, 0);

	pVtxCol[0].vPos = D3DXVECTOR3(-1.f, 1.f, -1.f);
	pVtxCol[0].dwColor = D3DCOLOR_ARGB(255, 255, 0, 0);

	pVtxCol[1].vPos = D3DXVECTOR3(1.f, 1.f, -1.f);
	pVtxCol[1].dwColor = D3DCOLOR_ARGB(255, 0, 255, 0);

	pVtxCol[2].vPos = D3DXVECTOR3(1.f, -1.f, -1.f);
	pVtxCol[2].dwColor = D3DCOLOR_ARGB(255, 0, 0, 255);

	pVtxCol[3].vPos = D3DXVECTOR3(-1.f, -1.f, -1.f);
	pVtxCol[3].dwColor = D3DCOLOR_ARGB(255, 0, 0, 0);

	// µÞ ¸é
	pVtxCol[4].vPos = D3DXVECTOR3(-1.f, 1.f, 1.f);
	pVtxCol[4].dwColor = D3DCOLOR_ARGB(255, 255, 0, 0);

	pVtxCol[5].vPos = D3DXVECTOR3(1.f, 1.f, 1.f);
	pVtxCol[5].dwColor = D3DCOLOR_ARGB(255, 0, 255, 0);

	pVtxCol[6].vPos = D3DXVECTOR3(1.f, -1.f, 1.f);
	pVtxCol[6].dwColor = D3DCOLOR_ARGB(255, 0, 0, 255);

	pVtxCol[7].vPos = D3DXVECTOR3(-1.f, -1.f, 1.f);
	pVtxCol[7].dwColor = D3DCOLOR_ARGB(255, 255, 255, 255);

	m_pOriginVtx = new VTXCOL[m_dwVtxCnt];
	memcpy(m_pOriginVtx, pVtxCol, m_dwVtxCnt * m_dwVtxSize);

	m_pVB->Unlock();

	INDEX32* pIndex = nullptr;

	m_pIB->Lock(0, 0, (void**)&pIndex, 0);
	// x+
	pIndex[0]._1 = 1;
	pIndex[0]._2 = 5;
	pIndex[0]._3 = 6;

	pIndex[1]._1 = 1;
	pIndex[1]._2 = 6;
	pIndex[1]._3 = 2;

	// x-
	pIndex[2]._1 = 4;
	pIndex[2]._2 = 0;
	pIndex[2]._3 = 3;

	pIndex[3]._1 = 4;
	pIndex[3]._2 = 3;
	pIndex[3]._3 = 7;

	// y+
	pIndex[4]._1 = 4;
	pIndex[4]._2 = 5;
	pIndex[4]._3 = 1;

	pIndex[5]._1 = 4;
	pIndex[5]._2 = 1;
	pIndex[5]._3 = 0;

	// y-
	pIndex[6]._1 = 3;
	pIndex[6]._2 = 2;
	pIndex[6]._3 = 6;

	pIndex[7]._1 = 3;
	pIndex[7]._2 = 6;
	pIndex[7]._3 = 7;

	// Z+
	pIndex[8]._1 = 7;
	pIndex[8]._2 = 6;
	pIndex[8]._3 = 5;

	pIndex[9]._1 = 7;
	pIndex[9]._2 = 5;
	pIndex[9]._3 = 4;

	// Z-
	pIndex[10]._1 = 0;
	pIndex[10]._2 = 1;
	pIndex[10]._3 = 2;

	pIndex[11]._1 = 0;
	pIndex[11]._2 = 2;
	pIndex[11]._3 = 3;
	m_pIB->Unlock();

	return S_OK;
}

void CCubeCol::Render(void)
{
	CVIBuffer::Render();
}

void CCubeCol::Release(void)
{
}

CResources * CCubeCol::CloneResource(void)
{
	++(*m_pwRefCnt);

	return new CCubeCol(*this);
}

CCubeCol * CCubeCol::Create(LPDIRECT3DDEVICE9 pD3DDevice, const WORD & wItv)
{
	CCubeCol* pInstance = new CCubeCol(pD3DDevice);

	if (FAILED(pInstance->CreateBuffer(wItv)))
		Safe_Delete(pInstance);
	
	return pInstance;
}
