#include "VIBuffer.h"

USING(Engine)

CVIBuffer::CVIBuffer(LPDIRECT3DDEVICE9 pD3DDevice)
	: CResources(pD3DDevice)
{
}

CVIBuffer::~CVIBuffer(void)
{
	Release();
}

void CVIBuffer::GetOriginVtxInfo(void * pVertex)
{
	memcpy(pVertex, m_pOriginVtx, m_dwVtxCnt* m_dwVtxSize);
}

void CVIBuffer::GetVtxInfo(void * pVertex)
{
	void* pOriginVertex = nullptr;

	m_pVB->Lock(0, 0, &pOriginVertex, 0);
	memcpy(pVertex, pOriginVertex, m_dwVtxCnt * m_dwVtxSize);
	m_pVB->Unlock();
}

void CVIBuffer::SetVtxInfo(void * pVertex)
{
	void* pOriginVertex = nullptr;

	m_pVB->Lock(0, 0, &pOriginVertex, 0);
	memcpy(pOriginVertex, pVertex, m_dwVtxCnt * m_dwVtxSize);
	m_pVB->Unlock();
}

HRESULT CVIBuffer::CreateBuffer(void)
{
	HRESULT hr = NULL;

	hr = m_pD3DDevice->CreateVertexBuffer(m_dwVtxCnt * m_dwVtxSize, 0, m_dwVtxFVF, D3DPOOL_MANAGED, &m_pVB, NULL);
	FAILED_CHECK_MSG(hr, L"Vertex Buffer Create Failed");

	// 1. ���� ������ ������(����Ʈ ����)
	// 2. ���� ��� ���
	// 3. ����ϴ� ���� ��Ÿ��
	// 4. �޸� Ǯ ���
	// 5. ������ ���۸� ������ ������ ��ü
	// 6. ��������� ��� NULL

	hr = m_pD3DDevice->CreateIndexBuffer(m_dwIdxSize * m_dwTriCnt, 0, m_IdxFmt, D3DPOOL_MANAGED, &m_pIB, NULL);
	FAILED_CHECK_MSG(hr, L"Index Buffer Create Failed");

	// 1. �ε��� ������ ������(����Ʈ ����)
	// 2. ���� ��� ���
	// 3. ����ϴ� ���� ��Ÿ��
	// 4. �޸� Ǯ ���
	// 5. ������ ���۸� ������ ������ ��ü
	// 6. ��������� ��� NULL

	return S_OK;
}

void CVIBuffer::Render(void)
{
	m_pD3DDevice->SetStreamSource(0, m_pVB, 0, m_dwVtxSize);
	// ����̽� ��ġ���� ���� �׸����� ���۸� �������ִ� �Լ�
	// ����̽� ��ġ�� �� �����͸� �����ϱ� ���� ������ ������ �ִ�.

	// 1. �� �� ���Կ� ������ ���ΰ�
	// 2. ������ ������ ��ġ���� �Ѱ��� ���ΰ�
	// 3. ��𼭺��� ����� ���ΰ�(0�� ��� ������ ó��)
	// 4. � ������ ����� ���ΰ�

	m_pD3DDevice->SetFVF(m_dwVtxFVF);

	m_pD3DDevice->SetIndices(m_pIB);

	m_pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_dwVtxCnt, 0, m_dwTriCnt);
	// 2. ���ؽ��� �ε��� ���� ��
	// 3. ���ؽ� ���ۿ� �� �ִ� �ε��� �� �� ������ ����� ���ΰ�
	// 4. ����ϰ����ϴ� ���ؽ� ����
	// 5. �ε��� ���ۿ� �� �ִ� �ε��� �� �� ������ ����� ���ΰ�
	// 6. ������ ����
}

void CVIBuffer::Release(void)
{
	if (0 == (*m_pwRefCnt))
	{
		Safe_Release(m_pVB);
		Safe_Release(m_pIB);
		Safe_Delete_Array(m_pOriginVtx);

		CResources::Release();
	}
	else
	{
		--(*m_pwRefCnt);
	}
}
