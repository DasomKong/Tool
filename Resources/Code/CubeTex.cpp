#include "CubeTex.h"

USING(Engine)

CCubeTex::CCubeTex(LPDIRECT3DDEVICE9 pD3DDevice)
	: CVIBuffer(pD3DDevice)
{
}

CCubeTex::~CCubeTex(void)
{
	Release();
}

HRESULT CCubeTex::CreateBuffer(const WORD& wItv)
{
	m_dwVtxFVF = VTXFVF_CUBE;
	m_dwTriCnt = 12;
	m_dwVtxCnt = 8;
	m_dwVtxSize = sizeof(VTXCUBE);

	m_dwIdxSize = sizeof(INDEX32);
	m_IdxFmt = D3DFMT_INDEX32;

	FAILED_CHECK(CVIBuffer::CreateBuffer());

	m_wItv = wItv;

	VTXCUBE* pVtxCube = nullptr;

	m_pVB->Lock(0, 0, (void**)&pVtxCube, 0);

	// �� ��
	pVtxCube[0].vPos = D3DXVECTOR3(-1.f, 1.f, -1.f);
	pVtxCube[0].vTex = pVtxCube[0].vPos;

	pVtxCube[1].vPos = D3DXVECTOR3(1.f, 1.f, -1.f);
	pVtxCube[1].vTex = pVtxCube[1].vPos;

	pVtxCube[2].vPos = D3DXVECTOR3(1.f, -1.f, -1.f);
	pVtxCube[2].vTex = pVtxCube[2].vPos;

	pVtxCube[3].vPos = D3DXVECTOR3(-1.f, -1.f, -1.f);
	pVtxCube[3].vTex = pVtxCube[3].vPos;

	// �� ��
	pVtxCube[4].vPos = D3DXVECTOR3(-1.f, 1.f, 1.f);
	pVtxCube[4].vTex = pVtxCube[4].vPos;

	pVtxCube[5].vPos = D3DXVECTOR3(1.f, 1.f, 1.f);
	pVtxCube[5].vTex = pVtxCube[5].vPos;

	pVtxCube[6].vPos = D3DXVECTOR3(1.f, -1.f, 1.f);
	pVtxCube[6].vTex = pVtxCube[6].vPos;

	pVtxCube[7].vPos = D3DXVECTOR3(-1.f, -1.f, 1.f);
	pVtxCube[7].vTex = pVtxCube[7].vPos;

	m_pOriginVtx = new VTXCUBE[m_dwVtxCnt];
	memcpy(m_pOriginVtx, pVtxCube, m_dwVtxCnt * m_dwVtxSize);

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

void CCubeTex::Render(void)
{
	CVIBuffer::Render();
}

void CCubeTex::Release(void)
{
}

CResources * CCubeTex::CloneResource(void)
{
	++(*m_pwRefCnt);

	return new CCubeTex(*this);
}

CCubeTex * CCubeTex::Create(LPDIRECT3DDEVICE9 pD3DDevice, const WORD& wItv)
{
	CCubeTex*	pInstance = new CCubeTex(pD3DDevice);

	if (FAILED(pInstance->CreateBuffer(wItv)))
		Engine::Safe_Delete(pInstance);

	return pInstance;
}
