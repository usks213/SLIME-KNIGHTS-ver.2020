//==================================================================
//								characterAction.h
//	 
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//	
//	2020/08/02	�L�����N�^�[�A�N�V�����N���X�̒ǉ�
//
//===================================================================

#pragma once

//====== �C���N���[�h�� ======
#include "../main.h"
#include "object.h"
#include "attackBase.h"
#include "List.h"


//===== �}�N����` =====

int GetHitStopFrame();
#define HIT_STOP_FRAME GetHitStopFrame()

//===== �N���X��` =====

class CCharacter;

class CCharacterAction
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CCharacterAction();
	~CCharacterAction();

	static void Init();
	static void Uninit();

	// �K�v�f�[�^�̃Z�b�g
	void SetActionData(CCharacter *pChara, float fMoveForce, float fJumpForce, int nAnimSpeed = 0);

	// ���X�g�X�V
	static void ListUpdate();
	// �X�V
	virtual void Update();

	// �s���p�^�[��
	virtual void Right(int nAnimSpeed = 0);
	virtual void Left(int nAnimSpeed = 0);
	virtual void Up(int nAnimSpeed = 0);
	virtual void Down(int nAnimSpeed = 0);
	virtual void Jump(int nAnimSpeed = 0);
	virtual void Wait(int nAnimSpeed = 0);
	virtual void Attack(int nAnimSpeed = 0);
	virtual void Damage(CStatus *pStatus, int nAnimSpeed = 0);

	virtual void CreateAttackBase(LAYER::LAYER eLayer, float fOffSetX);

	// OnCollision�ɃZ�b�g
	virtual void OnCollisionAction(CCollision *pCol);
	// OnAnimator�ɃZ�b�g
	virtual void OnAnimatorAction(CAnimator *pAnim);

	// �Q�b�g�֐�
	bool GetRight() { return m_bRight; }
	CAttackBase* GetAttackBase() { return m_pAttackBase; }

	void SetWait()
	{
		m_eCurAction = WAIT;
		Wait();
	}

protected:
	// ���X�g
	static List<CCharacterAction> m_list;

	// �L�����N�^�[�f�[�^
	CCharacter *m_pChara;

	// �A�N�V�����֘A
	float m_fMoveForce;
	float m_fJumpForce;
	bool m_bRight;
	int m_nAnimSpeed;
	int m_nFlashCnt;

	int m_nHitStopCnt;

	// ��������铖���蔻��f�[�^
	CAttackBase *m_pAttackBase;
	float m_fAttackOffSetX;

	// �s���p�^�[��
	enum EAction
	{
		WAIT,
		MOVE,
		JUMP,
		ATTACK,
		DAMAGE,

		MAX_ACTION,
	};
	// ���݂̃A�N�V����
	EAction m_eCurAction;

};

