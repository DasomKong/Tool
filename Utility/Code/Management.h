#ifndef Management_h__
#define Management_h__

#include "Engine_Include.h"

#include "Renderer.h"
#include "Scene.h"

BEGIN(Engine)

class ENGINE_DLL CManagement
{
public:
	DECLARE_SINGLETON(CManagement)

private:
	CManagement(void);
	~CManagement(void);

public:
	HRESULT InitManagement(LPDIRECT3DDEVICE9 pD3DDevice);
	void Update(void);
	void Render(float fTime);

public:
	template<typename T>
	HRESULT SceneChange(T& Functor);

private:
	void Release(void);

private:
	LPDIRECT3DDEVICE9		m_pD3DDevice = nullptr;
	CRenderer*				m_pRenderer = nullptr;
	CScene*					m_pScene = nullptr;
};

template<typename T>
HRESULT CManagement::SceneChange(T & Functor)
{
	if (nullptr != m_pScene)
		Engine::Safe_Delete(m_pScene);

	FAILED_CHECK(Functor(&m_pScene, m_pD3DDevice));

	m_pRenderer->SetScene(m_pScene);

	return S_OK;
}

END

#endif // Management_h__
