#ifndef Layer_h__
#define Layer_h__

#include "GameObject.h"

BEGIN(Engine)

class ENGINE_DLL CLayer
{
private:
	explicit CLayer(LPDIRECT3DDEVICE9 pD3DDevice);
public:
	~CLayer(void);

public:
	void Update(void);
	void Render(void);

	HRESULT AddObject(const wstring& wstrObjKey, CGameObject* pGameObject);

private:
	void Release(void);

private:
	LPDIRECT3DDEVICE9					m_pD3DDevice = nullptr;

	typedef list<CGameObject*>			OBJLIST;
	typedef map<wstring, OBJLIST>		MAPOBJLIST;
	MAPOBJLIST							m_ObjListMap;

public:
	static CLayer* Create(LPDIRECT3DDEVICE9 pD3DDevice);
};

END

#endif // Layer_h__
