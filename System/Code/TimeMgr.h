#ifndef TimeMgr_h__
#define TimeMgr_h__

#include "Engine_Include.h"

BEGIN(Engine)

class ENGINE_DLL CTimeMgr
{
public:
	DECLARE_SINGLETON(CTimeMgr)

private:
	CTimeMgr(void);
	~CTimeMgr(void);

public:
	// Getter

	float GetTime(void) { return m_fDeltaTime; }

public:
	HRESULT InitTime(void);
	void SetTime(void);


private:
	LARGE_INTEGER m_CurrentFrameTime;
	LARGE_INTEGER m_LastFrameTime;
	LARGE_INTEGER m_FixTime;
	LARGE_INTEGER m_CpuTick;

	float m_fDeltaTime = 0.f;
};

END

#endif // TimeMgr_h__
