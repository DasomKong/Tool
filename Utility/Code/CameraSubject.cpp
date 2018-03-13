#include "CameraSubject.h"

USING(Engine)
IMPLEMENT_SINGLETON(CCameraSubject)

CCameraSubject::CCameraSubject(void)
{
}

CCameraSubject::~CCameraSubject(void)
{
	Release();
}

void * CCameraSubject::GetData(int iMessage)
{
	return m_DataAry[iMessage];
}

void CCameraSubject::SetData(int iMessage, void * pData)
{
	if (nullptr == pData) return;

	m_DataAry[iMessage] = pData;
	Notify(iMessage);
}

void CCameraSubject::RemoveData(int iMessage, void * pData)
{
	m_DataAry[iMessage] = nullptr;
}

void CCameraSubject::Release(void)
{
	for (auto& pData : m_DataAry)
		pData = nullptr;
}
