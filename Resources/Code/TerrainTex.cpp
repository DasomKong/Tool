#include "TerrainTex.h"

USING(Engine)

CTerrainTex::CTerrainTex(LPDIRECT3DDEVICE9 pD3DDevice)
	: CVIBuffer(pD3DDevice)
{
}

CTerrainTex::~CTerrainTex(void)
{
	Release();
}

void CTerrainTex::GetTerrainInfo(WORD * wCntX, WORD * wCntZ, WORD * wItv)
{
	*wCntX = m_wCntX;
	*wCntZ = m_wCntZ;
	*wItv = m_wItv;
}

HRESULT CTerrainTex::CreateBuffer(const WORD & wCntX, const WORD & wCntZ, const WORD & wItv)
{
	m_dwVtxFVF = VTXFVF_TEX;
	m_dwTriCnt = (wCntX - 1) * (wCntZ - 1) * 2;
	m_dwVtxCnt = wCntX * wCntZ;
	m_dwVtxSize = sizeof(VTXTEX);

	m_dwIdxSize = sizeof(INDEX32);
	m_IdxFmt = D3DFMT_INDEX32;

	FAILED_CHECK(CVIBuffer::CreateBuffer());

	m_wCntX = wCntX;
	m_wCntZ = wCntZ;
	m_wItv = wItv;

	VTXTEX* pVtxTex = nullptr;

	m_pVB->Lock(0, 0, (void**)&pVtxTex, 0);

	int iIndex = 0;

	for (int z = 0; z < wCntZ; ++z)
	{
		for (int x = 0; x < wCntX; ++x)
		{
			iIndex = z * wCntX + x;

			pVtxTex[iIndex].vPos = D3DXVECTOR3(float(x) * wItv, 0.f, float(z) * wItv);
			pVtxTex[iIndex].vTex = D3DXVECTOR2(x / (wCntX - 1.f), z / (wCntZ - 1.f));
		}
	}

	m_pOriginVtx = new VTXTEX[m_dwVtxCnt];
	memcpy(m_pOriginVtx, pVtxTex, m_dwVtxCnt * m_dwVtxSize);

	m_pVB->Unlock();

	INDEX32 * pIndex = nullptr;

	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	int iTriCnt = 0;

	for (int z = 0; z < wCntZ - 1; ++z)
	{
		for (int x = 0; x < wCntX - 1; ++x)
		{
			iIndex = z * wCntX + x;

			pIndex[iTriCnt]._1 = iIndex + wCntX;
			pIndex[iTriCnt]._2 = iIndex + wCntX + 1;
			pIndex[iTriCnt]._3 = iIndex + 1;

			++iTriCnt;

			pIndex[iTriCnt]._1 = iIndex + wCntX;
			pIndex[iTriCnt]._2 = iIndex + 1;
			pIndex[iTriCnt]._3 = iIndex;

			++iTriCnt;
		}
	}

	m_pIB->Unlock();

	return S_OK;
}

void CTerrainTex::Render(void)
{
	CVIBuffer::Render();
}

void CTerrainTex::Release(void)
{
}

void CTerrainTex::SetHeightMap(const wstring & wstrFilePath, const float & fHeight)
{
	DWORD* pdwPixel = GetHeightMapPixel(wstrFilePath);
	NULL_CHECK(pdwPixel);

	VTXTEX* pVtxTex = nullptr;

	m_pVB->Lock(0, 0, (void**)&pVtxTex, 0);

	int iIndex = 0;

	for (int z = 0; z < m_wCntZ; ++z)
	{
		for (int x = 0; x < m_wCntX; ++x)
		{
			iIndex = z * m_wCntX + x;
			pVtxTex[iIndex].vPos.y = (pdwPixel[iIndex] & 0x000000ff) / fHeight;
		}
	}
	memcpy(m_pOriginVtx, pVtxTex, m_dwVtxCnt * m_dwVtxSize);

	m_pVB->Unlock();

	Safe_Delete_Array(pdwPixel);
}

CResources * CTerrainTex::CloneResource(void)
{
	++(*m_pwRefCnt);

	return new CTerrainTex(*this);
}

DWORD * CTerrainTex::GetHeightMapPixel(const wstring wstrFilePath)
{
	HANDLE hFile = nullptr;

	DWORD dwByte = 0;

	hFile = CreateFile(wstrFilePath.c_str(),
		GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	BITMAPFILEHEADER fH;
	BITMAPINFOHEADER iH;

	ReadFile(hFile, &fH, sizeof(fH), &dwByte, NULL);
	ReadFile(hFile, &iH, sizeof(iH), &dwByte, NULL);

	DWORD* pdwPixel = new DWORD[iH.biWidth * iH.biHeight];
	ReadFile(hFile, pdwPixel, sizeof(DWORD) * iH.biWidth * iH.biHeight, &dwByte, NULL);

	CloseHandle(hFile);

	return pdwPixel;
}

CTerrainTex * CTerrainTex::Create(LPDIRECT3DDEVICE9 pD3DDevice, const WORD & wCntX, const WORD & wCntZ, const WORD & wItv)
{
	CTerrainTex* pInstance = new CTerrainTex(pD3DDevice);

	if (FAILED(pInstance->CreateBuffer(wCntX, wCntZ, wItv)))
		Safe_Delete(pInstance);

	return pInstance;
}
