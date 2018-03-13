#ifndef GameObject_h__
#define GameObject_h__

#include "Component.h"

BEGIN(Engine)

class CTransform;
class ENGINE_DLL CGameObject
{
protected:
	explicit CGameObject(LPDIRECT3DDEVICE9 pD3DDevice);
public:
	virtual ~CGameObject(void);

public: // Getter
	CTransform* Transform(void) const { return m_pTransform; }
	CComponent* GetComponent(const wstring& wstrComponentKey);

public: // Setter
	void SetTransform(	const D3DXVECTOR3& vPos,
						const D3DXVECTOR3& vDir = VEC3_FRONT,
						const D3DXVECTOR3& vScale = VEC3_ONE);
	void SetPosition(const D3DXVECTOR3& vPos);
	void SetRotation(const D3DXVECTOR3& vDir);
	void SetScale(const D3DXVECTOR3& vScale);
	void SetActive(const bool& bActive) { m_bActive = bActive; }

public:
	virtual HRESULT Initialize(void);
	virtual void Update(void);
	virtual void Render(void);

protected:
	virtual HRESULT AddComponent(void) { return S_OK; };
	//virtual HRESULT AddComponent(void* p);

private:
	virtual void Release(void);

protected:
	LPDIRECT3DDEVICE9					m_pD3DDevice = nullptr;
	typedef map<wstring, CComponent*>	MAPCOMPONENT;
	MAPCOMPONENT						m_ComponentMap;
	CTransform*							m_pTransform;
	bool								m_bActive = true;
};

END

#endif // GameObject_h__
