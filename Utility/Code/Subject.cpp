#include "Subject.h"

USING(Engine)

CSubject::CSubject(void)
{
}

CSubject::~CSubject(void)
{
	Release();
}

void CSubject::Subscribe(CObserver * pObserver)
{
	NULL_CHECK(pObserver);

	m_ObserverList.push_back(pObserver);
}

void CSubject::UnSubscribe(CObserver * pObserver)
{
	auto iter = m_ObserverList.begin();
	auto iter_end = m_ObserverList.end();

	for (; iter != iter_end;)
	{
		if ((*iter) == pObserver)
		{
			m_ObserverList.erase(iter);
			return;
		}
		else
			++iter;
	}
}

void CSubject::Notify(int iMessage)
{
	for (auto& iter : m_ObserverList)
		iter->Update(iMessage);
}

void CSubject::Release(void)
{
	// Observer의 삭제는 Observer 객체를 가진 Object에서 직접 해제
	m_ObserverList.clear();
}
