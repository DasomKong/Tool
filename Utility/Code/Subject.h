#ifndef Subject_h__
#define Subject_h__

#include "Observer.h"

BEGIN(Engine)

class ENGINE_DLL CSubject
{
protected:
	CSubject(void);
public:
	virtual ~CSubject(void);

public:
	void Subscribe(CObserver* pObserver);
	void UnSubscribe(CObserver* pObserver);
	void Notify(int iMessage);

private:
	void Release(void);

protected:
	typedef list<CObserver*>	LISTOBSERVER;
	LISTOBSERVER				m_ObserverList;
};

END

#endif // Subject_h__
