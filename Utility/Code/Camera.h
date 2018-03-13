#ifndef Camera_h__
#define Camera_h__

#include "GameObject.h"

BEGIN(Engine)

class ENGINE_DLL CCamera : public CGameObject
{
protected:
	explicit CCamera(LPDIRECT3DDEVICE9 pD3DDevice);
public:
	virtual ~CCamera(void);

public: // Getter
	D3DXMATRIX* GetViewMatrix(void) { return &m_matView; }
	D3DXMATRIX* GetProjMatrix(void) { return &m_matProj; }

public: // Setter
	void SetCameraTransform(const D3DXVECTOR3& vEve,
							const D3DXVECTOR3& vAt,
							const D3DXVECTOR3& vUp);

	void SetViewSpaceMatrix(const D3DXVECTOR3* pEye,
							const D3DXVECTOR3* pAt,
							const D3DXVECTOR3* pUp);
	
	void SetProjectionMatrixPerspective(const float& fFovy,
										const float& fAspect,
										const float& fNear,
										const float& fFar);

	void SetProjectionMatrixOrtho(	const float& fWidth,
									const float& fHeight,
									const float& fNear,
									const float& fFar);

protected:
	virtual HRESULT Initialize(CAMERA_TYPE eCameraType) PURE;

protected:
	D3DXMATRIX m_matView;
	D3DXMATRIX m_matProj;

	D3DXVECTOR3 m_vEve; // vPos
	D3DXVECTOR3 m_vAt;  // vDir을 구할때씀
	D3DXVECTOR3 m_vUp;  
	float m_fAngle[ANGLE_END]; // Pitch, Yaw, Roll 구현할때 쓸듯

	CAMERA_TYPE m_eCameraType;
};

END

#endif // Camera_h__
