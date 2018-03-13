#ifndef Transform_h__
#define Transform_h__

#include "Component.h"
#include "Engine_enum.h"

BEGIN(Engine)

class ENGINE_DLL CTransform : public CComponent
{
private:
	explicit CTransform(CGameObject* pGameObject);
public:
	virtual ~CTransform(void) override;

public:
	virtual void Update(void) override;

	// Target방향으로 현재 Transform의 회전 방향을 변경
	// fRatio : 회전 값을 선형 보간으로 설정, 기본 값은 1.f (바로 해당 위치로 회전)
	D3DXVECTOR3* LookAt(const D3DXVECTOR3& vTarget, const float& fRatio = 1.f);

	// 해당 방향으로 물체를 이동
	// SPACE를 이용해 상대적인 방향으로 이동 가능
	void Translate(const D3DXVECTOR3& vDir, SPACE eSpace = WORLD_SPACE);

public:
	D3DXVECTOR3		m_vPos; // 중심 위치 벡터
	D3DXVECTOR3		m_vDir; // 바라보는 방향 벡터 (물체의 정면)
	float			m_fAngle[ANGLE_END]; // 정면 방향 벡터에 대한 오일러 각도 값, VEC3_FRONT 기준
	D3DXVECTOR3		m_vScale; // 축에 대한 비율 값
	D3DXMATRIX		m_matWorld; // 로컬 좌표를 월드 좌표로 변환시켜주기 위한 값

public:
	static CTransform* Create(CGameObject* pGameObject);
};

END

#endif // Transform_h__
