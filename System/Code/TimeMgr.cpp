#include "TimeMgr.h"

USING(Engine)
IMPLEMENT_SINGLETON(CTimeMgr)

Engine::CTimeMgr::CTimeMgr(void)
{
}

CTimeMgr::~CTimeMgr(void)
{
}

HRESULT CTimeMgr::InitTime(void)
{
	QueryPerformanceCounter(&m_LastFrameTime);
	QueryPerformanceCounter(&m_CurrentFrameTime);
	QueryPerformanceCounter(&m_FixTime);
	QueryPerformanceFrequency(&m_CpuTick);

	return S_OK;
}

void CTimeMgr::SetTime(void)
{
	QueryPerformanceCounter(&m_CurrentFrameTime);

	if (m_CurrentFrameTime.QuadPart - m_FixTime.QuadPart > m_CpuTick.QuadPart)
	{
		QueryPerformanceFrequency(&m_CpuTick);
		m_FixTime.QuadPart = m_CurrentFrameTime.QuadPart;
	}

	m_fDeltaTime = float(m_CurrentFrameTime.QuadPart - m_LastFrameTime.QuadPart) / m_CpuTick.QuadPart;

	m_LastFrameTime = m_CurrentFrameTime;
}
