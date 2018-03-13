#ifndef KeyMgr_h__
#define KeyMgr_h__

#include "Engine_Include.h"

BEGIN(Engine)

class ENGINE_DLL CKeyMgr
{
public:
#pragma region KEY TABLE
	static const DWORD EMPTY_KEY	= 0x00000000;

	static const DWORD KEY_LEFT		= 0x00000001;
	static const DWORD KEY_RIGHT	= 0x00000002;
	static const DWORD KEY_UP		= 0x00000004;
	static const DWORD KEY_DOWN		= 0x00000008;

	static const DWORD KEY_ENTER	= 0x00000010;
	static const DWORD KEY_SPACE	= 0x00000020;
	static const DWORD KEY_TAB		= 0x00000040;
	static const DWORD KEY_SHIFT	= 0x00000080;

	static const DWORD KEY_A		= 0x00000100;
	static const DWORD KEY_D		= 0x00000200;
	static const DWORD KEY_W		= 0x00000400;
	static const DWORD KEY_S		= 0x00000800;

	static const DWORD KEY_1		= 0x00001000;
	static const DWORD KEY_2		= 0x00002000;
	static const DWORD KEY_3		= 0x00004000;
	static const DWORD KEY_4		= 0x00008000;
#pragma endregion

public:
	DECLARE_SINGLETON(CKeyMgr)
private:
	CKeyMgr(void);
	~CKeyMgr(void);

public: // Getter
	DWORD GetKey(void) const { return m_dwKey; }

public: 
	HRESULT InitKeyMgr(void);
	void CheckKey(void);
	const bool IsKeyDown(DWORD dwKey);
	const bool IsKeyUp(DWORD dwKey);
	const bool IsCombineKey(DWORD dwKey1, DWORD dwKey2);

private:
	DWORD		m_dwKey		= 0;
	DWORD		m_dwPreKey	= 0;
};

END

#endif // KeyMgr_h__
