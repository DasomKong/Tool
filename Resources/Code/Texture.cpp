#include "Texture.h"

USING(Engine)

CTexture::CTexture(LPDIRECT3DDEVICE9 pD3DDevice)
	: CResources(pD3DDevice)
{
}

CTexture::~CTexture(void)
{
	Release();
}

void CTexture::Render(const DWORD & iIndex)
{
	if (iIndex >= m_dwContainerSize)
		return;

	m_pD3DDevice->SetTexture(0, m_TextureVec[iIndex]);
}

void CTexture::Release(void)
{
	if (0 == (*m_pwRefCnt))
	{
		for (size_t i = 0; i < m_TextureVec.size(); ++i)
		{
			Safe_Release(m_TextureVec[i]);
		}
		m_TextureVec.clear();
		VECTEXTURE().swap(m_TextureVec);

		CResources::Release();
	}
	else
	{
		--(*m_pwRefCnt);
	}
}

CResources * CTexture::CloneResource(void)
{
	++(*m_pwRefCnt);

	return new CTexture(*this);
}

HRESULT CTexture::LoadTexture(TEXTURE_TYPE eTextureType, const wstring & wstrFilePath, const WORD & wCnt)
{
	m_TextureVec.reserve(wCnt);

	IDirect3DBaseTexture9* pTexture = nullptr;

	TCHAR szFullPath[MAX_PATH] = L"";

	for (size_t i = 0; i < wCnt; ++i)
	{
		wsprintf(szFullPath, wstrFilePath.c_str(), i);

		HRESULT hr = NULL;

		switch (eTextureType)
		{
		case Engine::TEX_NORMAL:
			hr = D3DXCreateTextureFromFile(m_pD3DDevice, szFullPath, (LPDIRECT3DTEXTURE9*)&pTexture);
			break;
		case Engine::TEX_CUBE:
			hr = D3DXCreateCubeTextureFromFile(m_pD3DDevice, szFullPath, (LPDIRECT3DCUBETEXTURE9*)&pTexture);
			break;
		}
		FAILED_CHECK_MSG(hr, szFullPath);

		m_TextureVec.push_back(pTexture);
	}

	m_dwContainerSize = m_TextureVec.size();
	return S_OK;
}

CTexture * CTexture::Create(LPDIRECT3DDEVICE9 pD3DDevice, TEXTURE_TYPE eTextureType, const wstring & wstrFilePath, const WORD & wCnt)
{
	CTexture* pTexture = new CTexture(pD3DDevice);

	if (FAILED(pTexture->LoadTexture(eTextureType, wstrFilePath, wCnt)))
		Safe_Delete(pTexture);

	return pTexture;
}
