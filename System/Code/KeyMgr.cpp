#include "KeyMgr.h"

USING(Engine)
IMPLEMENT_SINGLETON(CKeyMgr)

CKeyMgr::CKeyMgr(void)
{
}

CKeyMgr::~CKeyMgr(void)
{
}

HRESULT CKeyMgr::InitKeyMgr(void)
{
	return S_OK;
}

void CKeyMgr::CheckKey(void)
{
	m_dwPreKey = m_dwKey;
	m_dwKey = EMPTY_KEY;

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		m_dwKey |= KEY_LEFT;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		m_dwKey |= KEY_RIGHT;
	if (GetAsyncKeyState(VK_UP) & 0x8000)
		m_dwKey |= KEY_UP;
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		m_dwKey |= KEY_DOWN;

	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		m_dwKey |= KEY_ENTER;
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		m_dwKey |= KEY_SPACE;
	if (GetAsyncKeyState(VK_TAB) & 0x8000)
		m_dwKey |= KEY_TAB;
	if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
		m_dwKey |= KEY_SHIFT;

	if (GetAsyncKeyState('A') & 0x8000)
		m_dwKey |= KEY_A;
	if (GetAsyncKeyState('D') & 0x8000)
		m_dwKey |= KEY_D;
	if (GetAsyncKeyState('W') & 0x8000)
		m_dwKey |= KEY_W;
	if (GetAsyncKeyState('S') & 0x8000)
		m_dwKey |= KEY_S;

	if (GetAsyncKeyState('1') & 0x8000)
		m_dwKey |= KEY_1;
	if (GetAsyncKeyState('2') & 0x8000)
		m_dwKey |= KEY_2;
	if (GetAsyncKeyState('3') & 0x8000)
		m_dwKey |= KEY_3;
	if (GetAsyncKeyState('4') & 0x8000)
		m_dwKey |= KEY_4;
}

const bool CKeyMgr::IsKeyDown(DWORD dwKey)
{
	if (m_dwKey & dwKey)
	{
		if (!(m_dwPreKey & dwKey))
			return true;
	}

	return false;
}

const bool CKeyMgr::IsKeyUp(DWORD dwKey)
{
	if (m_dwPreKey & dwKey)
	{
		if (!(m_dwKey & dwKey))
			return true;
	}

	return false;
}

const bool CKeyMgr::IsCombineKey(DWORD dwKey1, DWORD dwKey2)
{
	if (m_dwKey & dwKey1)
	{
		if (m_dwKey & dwKey2)
			return true;
	}

	return false;
}
