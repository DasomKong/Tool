#ifndef Engine_math_h__
#define Engine_math_h__

#include "d3d9.h"
#include "d3dx9.h"

namespace Engine
{

#define ToRadian( degree ) ((degree) * (D3DX_PI / 180.f))
#define ToDegree( radian ) ((radian) * (180.f / D3DX_PI))

#define VEC3_ZERO	D3DXVECTOR3{ 0.f, 0.f, 0.f }
#define VEC3_RIGHT	D3DXVECTOR3{ 1.f, 0.f, 0.f }
#define VEC3_UP		D3DXVECTOR3{ 0.f, 1.f, 0.f }
#define VEC3_FRONT	D3DXVECTOR3{ 0.f, 0.f, 1.f }
#define VEC3_ONE	D3DXVECTOR3{ 1.f, 1.f, 1.f }

#define MAT_IDENTITY D3DXMATRIX{ 1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f };

	// Vector3
	// inline
	__forceinline float Vec3Length(const D3DXVECTOR3 *pV)
	{
#ifdef _DEBUG
		if (!pV) return 0.f;
#endif
		return sqrtf(pV->x * pV->x + pV->y * pV->y + pV->z * pV->z);
	}

	__forceinline float Vec3Dot(const D3DXVECTOR3 * pV1, const D3DXVECTOR3 * pV2)
	{
#ifdef _DEBUG
		if (!pV1 || !pV2) return 0.f;
#endif
		return pV1->x * pV2->x + pV1->y * pV2->y + pV1->z * pV2->z;
	}

	__forceinline void Vec3Cross(D3DXVECTOR3 * pOut, const D3DXVECTOR3 * pV1, const D3DXVECTOR3 * pV2)
	{
#ifdef _DEBUG
		if (!pOut || !pV1 || !pV2) return;
#endif
		D3DXVECTOR3 vOut;

		vOut.x = pV1->y * pV2->z - pV1->z * pV2->y;
		vOut.y = pV1->z * pV2->x - pV1->x * pV2->z;
		vOut.z = pV1->x * pV2->y - pV1->y * pV2->x;

		memcpy(pOut, &vOut, sizeof(D3DXVECTOR3));
	}

	__forceinline void Vec3Lerp(D3DXVECTOR3 * pOut, const D3DXVECTOR3 * pV1, const D3DXVECTOR3 * pV2, float p)
	{
#ifdef _DEBUG
		if (!pOut || !pV1 || !pV2) return;
#endif
		D3DXVECTOR3 vOut = *pV1 * (1.f - p) + *pV2 * p;
		memcpy(pOut, &vOut, sizeof(D3DXVECTOR3));
	}

	// non_inline

	static void __stdcall Vec3Normalize(D3DXVECTOR3 * pOut, const D3DXVECTOR3 * pV)
	{
#ifdef _DEBUG
		if (!pOut || !pV) return;
#endif
		float length = sqrtf(pV->x * pV->x + pV->y * pV->y + pV->z * pV->z);

		if (0.f == length) return;

		memcpy(pOut, pV, sizeof(D3DXVECTOR3));

		*pOut /= length;
	}

	static void __stdcall Vec4Transform(D3DXVECTOR4 * pOut, const D3DXVECTOR4 * pV, const D3DXMATRIX * pM)
	{
#ifdef _DEBUG
		if (!pOut || !pV || !pM) return;
#endif
		D3DXVECTOR4 vOut;

		vOut.x = pV->x * pM->_11 + pV->y * pM->_21 + pV->z * pM->_31 + pV->w * pM->_41;
		vOut.y = pV->x * pM->_12 + pV->y * pM->_22 + pV->z * pM->_32 + pV->w * pM->_42;
		vOut.z = pV->x * pM->_13 + pV->y * pM->_23 + pV->z * pM->_33 + pV->w * pM->_43;
		vOut.w = pV->x * pM->_14 + pV->y * pM->_24 + pV->z * pM->_34 + pV->w * pM->_44;

		memcpy(pOut, &vOut, sizeof(D3DXVECTOR4));
	}

	static void __stdcall Vec3TransformCoord(D3DXVECTOR3 * pOut, const D3DXVECTOR3 * pV, const D3DXMATRIX * pM)
	{
#ifdef _DEBUG
		if (!pOut || !pV || !pM) return;
#endif
		D3DXVECTOR3 vOut;

		vOut.x = pV->x * pM->_11 + pV->y * pM->_21 + pV->z * pM->_31 + pM->_41;
		vOut.y = pV->x * pM->_12 + pV->y * pM->_22 + pV->z * pM->_32 + pM->_42;
		vOut.z = pV->x * pM->_13 + pV->y * pM->_23 + pV->z * pM->_33 + pM->_43;
		float fW = pV->x * pM->_14 + pV->y * pM->_24 + pV->z * pM->_34 + pM->_44;

		*pOut = vOut / fW;
	}

	static void __stdcall Vec3TransformNormal(D3DXVECTOR3 * pOut, const D3DXVECTOR3 * pV, const D3DXMATRIX * pM)
	{
#ifdef _DEBUG
		if (!pOut || !pV || !pM) return;
#endif
		D3DXVECTOR4 v(*pV, 0.f);
		Vec4Transform(&v, &v, pM);

		if (0.f == v.w)
			*pOut = D3DXVECTOR3{ v.x, v.y, v.z };
		else
			*pOut = D3DXVECTOR3{ v.x / v.w, v.y / v.w, v.z / v.w };
	}

	// Matrix
	// inline

	__forceinline void MatIdentity(D3DXMATRIX * pOut)
	{
#ifdef _DEBUG
		if (!pOut) return;
#endif
		ZeroMemory(pOut, sizeof(D3DXMATRIX));
		pOut->_11 = pOut->_22 = pOut->_33 = pOut->_44 = 1.0f;
	}

	// non_inline

	static void __stdcall MatScaling(D3DXMATRIX * pOut, float sx, float sy, float sz)
	{
#ifdef _DEBUG
		if (!pOut) return;
#endif
		MatIdentity(pOut);

		pOut->_11 = sx;
		pOut->_22 = sy;
		pOut->_33 = sz;
	}

	static void __stdcall MatTranslation(D3DXMATRIX * pOut, float x, float y, float z)
	{
#ifdef _DEBUG
		if (!pOut) return;
#endif
		MatIdentity(pOut);

		pOut->_41 = x;
		pOut->_42 = y;
		pOut->_43 = z;
	}

	static void __stdcall MatRotationX(D3DXMATRIX * pOut, float Angle)
	{
#ifdef _DEBUG
		if (!pOut) return;
#endif
		MatIdentity(pOut);
		
		pOut->_23 = sinf(Angle);
		pOut->_32 = -pOut->_23;
		pOut->_33 = pOut->_22 = cosf(Angle);
	}

	static void __stdcall MatRotationY(D3DXMATRIX * pOut, float Angle)
	{
#ifdef _DEBUG
		if (!pOut) return;
#endif
		MatIdentity(pOut);
		
		pOut->_31 = sinf(Angle);
		pOut->_13 = -pOut->_31;
		pOut->_33 = pOut->_11 = cosf(Angle);
	}

	static void __stdcall MatRotationZ(D3DXMATRIX * pOut, float Angle)
	{
#ifdef _DEBUG
		if (!pOut) return;
#endif
		MatIdentity(pOut);
		
		pOut->_12 = sinf(Angle);
		pOut->_21 = -pOut->_12;
		pOut->_22 = pOut->_11 = cosf(Angle);
	}

	// Pipeline
	// inline

	// Vector X Rotation Result
	__forceinline void Vec3RotationX(D3DXVECTOR3 * pOut, const D3DXVECTOR3 * pV, float Angle)
	{
		float fcos = cosf(Angle);
		float fsin = sinf(Angle);

		pOut->x = pV->x;
		pOut->y = pV->y * fcos - pV->z * fsin;
		pOut->z = pV->y * fsin + pV->z * fcos;
	}

	// Vector Y Rotation Result
	__forceinline void Vec3RotationY(D3DXVECTOR3 * pOut, const D3DXVECTOR3 * pV, float Angle)
	{
		float fcos = cosf(Angle);
		float fsin = sinf(Angle);

		pOut->x = pV->x * fcos + pV->z * fsin;
		pOut->y = pV->y;
		pOut->z = -pV->x * fsin + pV->z * fcos;
	}

	// Vector Z Rotation Result
	__forceinline void Vec3RotationZ(D3DXVECTOR3 * pOut, const D3DXVECTOR3 * pV, float Angle)
	{
		float fcos = cosf(Angle);
		float fsin = sinf(Angle);

		pOut->x = pV->x * fcos - pV->y * fsin;
		pOut->y = pV->x * fsin + pV->y * fcos;
		pOut->z = pV->z;
	}

	__forceinline void MatTransform(D3DXMATRIX * pOut, const D3DXVECTOR3 * pRight, const D3DXVECTOR3 * pUp, const D3DXVECTOR3 * pFront, const D3DXVECTOR3 * pPosition)
	{
		memcpy(&pOut->_11, pRight, sizeof(float) * 3);
		memcpy(&pOut->_21, pUp, sizeof(float) * 3);
		memcpy(&pOut->_31, pFront, sizeof(float) * 3);
		memcpy(&pOut->_41, pPosition, sizeof(float) * 3);
	}

	// non-inline

	// World Matrix
	static void __stdcall MatTransformWorld(D3DXMATRIX* pOut, const D3DXVECTOR3* pPosition, const D3DXVECTOR3 * pScale, const float * pAngle)
	{
		D3DXVECTOR3		vRight{VEC3_RIGHT};
		D3DXVECTOR3		vUp{VEC3_UP};
		D3DXVECTOR3		vFront{VEC3_FRONT};

		// 크기 변환
		vRight.x = pScale->x;
		vUp.y = pScale->y;
		vFront.z = pScale->z;

		// 회전
		Vec3RotationX(&vRight, &vRight, pAngle[ANGLE_X]);
		Vec3RotationX(&vUp, &vUp, pAngle[ANGLE_X]);
		Vec3RotationX(&vFront, &vFront, pAngle[ANGLE_X]);

		Vec3RotationY(&vRight, &vRight, pAngle[ANGLE_Y]);
		Vec3RotationY(&vUp, &vUp, pAngle[ANGLE_Y]);
		Vec3RotationY(&vFront, &vFront, pAngle[ANGLE_Y]);

		Vec3RotationZ(&vRight, &vRight, pAngle[ANGLE_Z]);
		Vec3RotationZ(&vUp, &vUp, pAngle[ANGLE_Z]);
		Vec3RotationZ(&vFront, &vFront, pAngle[ANGLE_Z]);

		// 위치 변환
		//MatIdentity(pOut);
		//MatTransform(pOut, &vRight, &vUp, &vFront, pPosition);

		ZeroMemory(pOut, sizeof(D3DXMATRIX));
		pOut->_44 = 1.0f;
		memcpy(&pOut->_11, &vRight, sizeof(float) * 3);
		memcpy(&pOut->_21, &vUp, sizeof(float) * 3);
		memcpy(&pOut->_31, &vFront, sizeof(float) * 3);
		memcpy(&pOut->_41, pPosition, sizeof(float) * 3);
	}

	// ViewSpace Matrix
	static void __stdcall MatLookAtLH(D3DXMATRIX * pOut, const D3DXVECTOR3 * pEye, const D3DXVECTOR3 * pAt, const D3DXVECTOR3 * pUp)
	{
#ifdef _DEBUG
		if (!pOut || !pEye || !pAt || !pUp) return;
#endif
		D3DXVECTOR3	vRight;
		D3DXVECTOR3	vUp;
		D3DXVECTOR3	vFront{ *pAt - *pEye };

		Vec3Normalize(&vFront, &vFront);

		Vec3Cross(&vRight, pUp, &vFront);
		Vec3Normalize(&vRight, &vRight);

		Vec3Cross(&vUp, &vFront, &vRight);
		Vec3Normalize(&vUp, &vUp);

		//MatIdentity(pOut);
		//MatTransform(pOut, &vRight, &vUp, &vFront, pEye);

		ZeroMemory(pOut, sizeof(D3DXMATRIX));
		pOut->_44 = 1.0f;
		memcpy(&pOut->_11, &vRight, sizeof(float) * 3);
		memcpy(&pOut->_21, &vUp, sizeof(float) * 3);
		memcpy(&pOut->_31, &vFront, sizeof(float) * 3);
		memcpy(&pOut->_41, pEye, sizeof(float) * 3);

		D3DXMatrixInverse(pOut, 0, pOut);

		/*D3DXVECTOR3 vPos{ -D3DXVec3Dot(&vRight, pEye),-D3DXVec3Dot(&vUp, pEye),-D3DXVec3Dot(&vFront, pEye) };
		MatTransform(pOut,
			&D3DXVECTOR3{ vRight.x, vUp.x, vFront.x },
			&D3DXVECTOR3{ vRight.y, vUp.y, vFront.y },
			&D3DXVECTOR3{ vRight.z, vUp.z, vFront.z },
			&vPos);*/
	}

	// Projection Matrix - Perspective
	static void __stdcall MatPerspectiveFovLH(D3DXMATRIX * pOut, float fovy, float Aspect, float zn, float zf)
	{
#ifdef _DEBUG
		if (!pOut) return;
#endif
		ZeroMemory(pOut, sizeof(D3DXMATRIX));

		pOut->_22 = 1.f / tanf(fovy / 2.f);
		pOut->_11 = pOut->_22 / Aspect;

		pOut->_33 = zf / (zf - zn);
		pOut->_34 = 1.f;

		pOut->_43 = -zn * pOut->_33;
	}

	// Projection Matrix - Orthograph
	static void __stdcall MatOrthoLH(D3DXMATRIX * pOut, float w, float h, float zn, float zf)
	{
#ifdef _DEBUG
		if (!pOut) return;
#endif
		ZeroMemory(pOut, sizeof(D3DXMATRIX));

		pOut->_11 = 2.f / w;
		pOut->_22 = 2.f / h;

		pOut->_33 = zf / (zf - zn);
		pOut->_34 = 1.f;

		pOut->_43 = -zn * pOut->_33;
	}
}

#endif // Engine_math_h__
