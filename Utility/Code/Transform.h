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

	// Target�������� ���� Transform�� ȸ�� ������ ����
	// fRatio : ȸ�� ���� ���� �������� ����, �⺻ ���� 1.f (�ٷ� �ش� ��ġ�� ȸ��)
	D3DXVECTOR3* LookAt(const D3DXVECTOR3& vTarget, const float& fRatio = 1.f);

	// �ش� �������� ��ü�� �̵�
	// SPACE�� �̿��� ������� �������� �̵� ����
	void Translate(const D3DXVECTOR3& vDir, SPACE eSpace = WORLD_SPACE);

public:
	D3DXVECTOR3		m_vPos; // �߽� ��ġ ����
	D3DXVECTOR3		m_vDir; // �ٶ󺸴� ���� ���� (��ü�� ����)
	float			m_fAngle[ANGLE_END]; // ���� ���� ���Ϳ� ���� ���Ϸ� ���� ��, VEC3_FRONT ����
	D3DXVECTOR3		m_vScale; // �࿡ ���� ���� ��
	D3DXMATRIX		m_matWorld; // ���� ��ǥ�� ���� ��ǥ�� ��ȯ�����ֱ� ���� ��

public:
	static CTransform* Create(CGameObject* pGameObject);
};

END

#endif // Transform_h__
