#ifndef Component_h__
#define Component_h__

#include "Engine_Include.h"

BEGIN(Engine)

class CGameObject;
class ENGINE_DLL CComponent
{
protected:
	explicit CComponent(CGameObject* pGameObject);
public:
	virtual ~CComponent(void) PURE;

public: // Getter
	virtual CGameObject* GameObject(void) const { return m_pGameObject; }

public:
	virtual void Update(void) {};

protected:
	CGameObject* m_pGameObject = nullptr;
};

END

#endif // Component_h__