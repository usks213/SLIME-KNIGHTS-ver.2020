//==================================================================
//								weapon.h
//	����	
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//	
//	2020/08/14	�E�F�|���̃N���X
//
//===================================================================

#pragma once

//====== �C���N���[�h�� ======
#include "../main.h"
#include "object.h"


//===== �N���X��` =====

namespace WEAPON
{
	enum EWEAPON_TYPE
	{
		SWORD,
		LANCE,
		BOW,
		STICK,

		MAX_WEAPON_TYPE,
	};
}

class CWeapon : public CObject
{
public:
	CWeapon();
	~CWeapon();

	// �ÓI�֐�
	static void Init();
	static void Uninit();
	static CWeapon* Create(CTransform *pParent, WEAPON::EWEAPON_TYPE eType = WEAPON::SWORD);

	// ���z�֐�
	virtual void Update();
	virtual void LateUpdate();
	virtual void Draw();
	virtual void Destroy();

	// �����蔻��p�̊֐�
	virtual void OnAnimator(CAnimator  *pAnimator);

	// �Q�b�g�֐�

	// �Z�b�g�֐�
	void SetOffSetX(float fOffSetX) { m_fOffSetX = fOffSetX; }
	void SetOffSetY(float fOffSetY) { m_fOffSetY = fOffSetY; }

	virtual void StartMove(int nFrame, bool bRight, bool bDown);
	virtual void SetPos(bool bRight, bool bDown);
	virtual void SetPos(Float3 pos) {}

	void SetRight() {
		m_transform.SetAngle(45 + 180);
		m_bRight = true;
		m_transform.SetDir(Float3{ 1.0f, 0.0f, 0.0f });
	}
	void SetLeft() {
		m_transform.SetAngle(45);
		m_bRight = false;
		m_transform.SetDir(Float3{ -1.0f, 0.0f, 0.0f });
	}

	void SetTargetAngle(Float3 targetPos);

protected:
	// �R���|�[�l���g
	CAnimator*  m_pAnimator;	// �A�j���[�^�[

	// ���W�n�X�V�p
	CTransform* m_pParentTrans;
	float m_fOffSetX;
	float m_fOffSetY;
	int m_nMoveFrame;
	int m_nMoveCnt;
	bool m_bRight;
	bool m_bDown;

 	static CTexture sm_texture[WEAPON::MAX_WEAPON_TYPE];
	WEAPON::EWEAPON_TYPE m_eWeaponType;
private:

};

class CBoomerang : public CWeapon
{
public:
	// ���z�֐�
	virtual void Update() 
	{
		// ���W�X�V
		Float3 pos = m_transform.GetPos();
		pos.x += m_force.x;
		pos.y += m_force.y;
		pos.z += m_force.z;

		m_transform.SetPos(pos);

		static float angle;
		angle += 0.1f;
		m_transform.SetAngle(angle);

	}
	virtual void LateUpdate()
	{
		// ���W�X�V
		Float3 pos = m_transform.GetPos();
		pos.x += m_force.x;
		pos.y += m_force.y;
		pos.z += m_force.z;

		m_transform.SetPos(pos);

		static float angle;
		angle += 0.1f;
		m_transform.SetAngle(angle);
		
	}

	virtual void StartMove(int nFrame, bool bRight, bool bDown)
	{ 
		if (bRight) m_force = Float3{ 20, 0, 0 };
		else m_force = Float3{ -20, 0, 0 };

		m_transform.SetPos(m_pos);
	}

	virtual void SetPos(Float3 pos) { m_pos = pos; }


private:
	Float3 m_force;
	Float3 m_pos;
};
