#include "Camera.h"

USING(Engine)

CCamera::CCamera(LPDIRECT3DDEVICE9 pD3DDevice)
	: CGameObject(pD3DDevice)
	, m_vEve(VEC3_ZERO)
	, m_vAt(VEC3_ZERO)
	, m_vUp(VEC3_UP)
{
}

CCamera::~CCamera(void)
{
}

void CCamera::SetCameraTransform(const D3DXVECTOR3 & vEve, const D3DXVECTOR3 & vAt, const D3DXVECTOR3 & vUp)
{
	memcpy(&m_vEve, &vEve, sizeof(D3DXVECTOR3));
	memcpy(&m_vAt, &vAt, sizeof(D3DXVECTOR3));
	memcpy(&m_vUp, &vUp, sizeof(D3DXVECTOR3));

	SetViewSpaceMatrix(&m_vEve, &m_vAt, &m_vUp);
}

void CCamera::SetViewSpaceMatrix(const D3DXVECTOR3 * pEye, const D3DXVECTOR3 * pAt, const D3DXVECTOR3 * pUp)
{
	MatLookAtLH(&m_matView, pEye, pAt, pUp);
}

void CCamera::SetProjectionMatrixPerspective(const float & fFovy, const float & fAspect, const float & fNear, const float & fFar)
{
	MatPerspectiveFovLH(&m_matProj, fFovy, fAspect, fNear, fFar);
}

void CCamera::SetProjectionMatrixOrtho(const float & fWidth, const float & fHeight, const float & fNear, const float & fFar)
{
	MatOrthoLH(&m_matProj, fWidth, fHeight, fNear, fFar);
}
