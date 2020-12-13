//==================================================================
//									rigidbody.h
//	���W�b�h�{�f�B
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//
//	2020/07/12	���W�b�h�{�f�B�N���X�쐬
//
//===================================================================
#pragma once

//====== �C���N���[�h�� ======
#include "../main.h"
#include "List.h"

//===== �}�N����` =====

namespace DIRECTION
{
	enum EDIRECTION
	{
		RIGHT,
		LEFT,
		UP,
		DOWN,

		MAX_DIRECTION,
	};
}

//===== �N���X��` =====
class CTransform;

// �����F �ėp�^�ɂ���
class CRigidbody
{
public:
	CRigidbody();
	~CRigidbody();
	static void Init();
	static void Uninit();
	static void Update();

	// �����E����
	static CRigidbody* Create(CTransform *pTrans, bool bSolid = false, bool bUseGravity = true, bool bTrigger = false);
	void Destroy();

	// �����o��
	void Extrusion(CRigidbody *pOther);
	void ExtrusionCircleToCircle(CRigidbody *pOther);

	// �Q�b�g�֐�
	CTransform* GetObj() { return m_pTrans; }
	bool GetUseGravity() { return m_bUseGravity; }
	DIRECTION::EDIRECTION GetHitDir() { return m_enHitDir; }
	Float3 GetForce() { return m_force; }
	Float3 GetDir() { return m_dir; }

	// �Z�b�g�֐�
	void SetForce(Float3 force) { m_force = force; }
	void SetForceX(float forceX) { m_force.x = forceX; }
	void SetForceY(float forceY) { m_force.y = forceY; }
	void AddForceX(float forceX) { m_force.x += forceX; }
	void AddForceY(float forceY) { m_force.y += forceY; }
	void AddForce(Float3 force) 
	{ 
		m_force.x += force.x;
		m_force.y += force.y;
		m_force.z += force.z;
	}
	void SetDragX(float fDragX) { m_fDragX = fDragX; }
	void SetGravityForce(float fForce) { m_fGraviyForce = fForce; }
	void SetUseGravity(bool bUse) { m_bUseGravity = bUse; }
	void SetStop(bool bStop) { m_bStop = bStop; }
	void SetTrigger(bool bTrigger) { m_bTrigger = bTrigger; }
	void SetSolid(bool bSolid) { m_bSolid = bSolid; }
	void SetMass(float fMass) { m_fMass = fMass; }

private:
	static List<CRigidbody> m_list;
	CTransform *m_pTrans;

	// �p�����[�^
	Float3 m_velocity;
	Float3 m_force;
	float m_fMass;
	float m_fDragX;
	bool m_bSolid;		// �s���I�u�W�F�N�g
	Float3 m_dir;		// ����
	float m_fGraviyForce;

	DIRECTION::EDIRECTION m_enHitDir;

	bool m_bUseGravity;
	bool m_bTrigger;
	bool m_bStop;
};


