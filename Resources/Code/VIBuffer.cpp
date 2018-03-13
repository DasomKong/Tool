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

	// 1. 정점 버퍼의 사이즈(바이트 단위)
	// 2. 정점 사용 방식
	// 3. 사용하는 버퍼 스타일
	// 4. 메모리 풀 방식
	// 5. 생성된 버퍼를 저장할 포인터 객체
	// 6. 예약상태인 대게 NULL

	hr = m_pD3DDevice->CreateIndexBuffer(m_dwIdxSize * m_dwTriCnt, 0, m_IdxFmt, D3DPOOL_MANAGED, &m_pIB, NULL);
	FAILED_CHECK_MSG(hr, L"Index Buffer Create Failed");

	// 1. 인덱스 버퍼의 사이즈(바이트 단위)
	// 2. 정점 사용 방식
	// 3. 사용하는 버퍼 스타일
	// 4. 메모리 풀 방식
	// 5. 생성된 버퍼를 저장할 포인터 객체
	// 6. 예약상태인 대게 NULL

	return S_OK;
}

void CVIBuffer::Render(void)
{
	m_pD3DDevice->SetStreamSource(0, m_pVB, 0, m_dwVtxSize);
	// 디바이스 장치에게 현재 그리려는 버퍼를 연결해주는 함수
	// 디바이스 장치는 이 데이터를 보관하기 위한 슬롯을 가지고 있다.

	// 1. 몇 번 슬롯에 보관할 것인가
	// 2. 누구의 정보를 장치에게 넘겨줄 것인가
	// 3. 어디서부터 출력할 것인가(0인 경우 버퍼의 처음)
	// 4. 어떤 단위로 출력할 것인가

	m_pD3DDevice->SetFVF(m_dwVtxFVF);

	m_pD3DDevice->SetIndices(m_pIB);

	m_pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_dwVtxCnt, 0, m_dwTriCnt);
	// 2. 버텍스의 인덱스 시작 값
	// 3. 버텍스 버퍼에 들어가 있는 인덱스 중 몇 번부터 출력할 것인가
	// 4. 사용하고자하는 버텍스 개수
	// 5. 인덱스 버퍼에 들어가 있는 인덱스 중 몇 번부터 출력할 것인가
	// 6. 도형의 개수
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
