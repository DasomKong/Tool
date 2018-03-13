#ifndef CScene_h__
#define CScene_h__

#include "Layer.h"

BEGIN(Engine)

class ENGINE_DLL CScene
{
public:
	enum LAYER_ID { LAYER_ENVIRONMENT, LAYER_OBJECT, LAYER_EFFECT, LAYER_UI };

protected:
	explicit CScene(LPDIRECT3DDEVICE9 pD3DDevcie);
public:
	virtual ~CScene(void);

public:
	virtual HRESULT InitScene(void);
	virtual void Update(void);
	virtual void Render(void);

private:
	void Release(void);

protected: // Need override
	virtual HRESULT LoadBuffer(void) { return S_OK; }
	virtual HRESULT LoadTexture(void) { return S_OK; }
	virtual HRESULT LoadSound(void) { return S_OK; }

	virtual HRESULT Add_Environment_Layer(void) { return S_OK; }
	virtual HRESULT Add_Object_Layer(void) { return S_OK; }
	virtual HRESULT Add_Effect_Layer(void) { return S_OK; }
	virtual HRESULT Add_UI_Layer(void) { return S_OK; }

protected:
	LPDIRECT3DDEVICE9				m_pD3DDevice = nullptr;

	typedef map<WORD, CLayer*>		MAPLAYER;
	MAPLAYER						m_LayerMap;
};

END

#endif // CScene_h__
