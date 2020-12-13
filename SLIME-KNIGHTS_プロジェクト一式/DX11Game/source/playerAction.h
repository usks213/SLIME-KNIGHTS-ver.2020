//==================================================================
//								playerAction.h
//	 
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//	
//	2020/08/13	�v���C���[�A�N�V�����N���X�̍쐬
//
//===================================================================

#pragma once

//====== �C���N���[�h�� ======
#include "characterAction.h"


//===== �N���X��` =====

class CPlayer;

class CPlayerAction : public CCharacterAction
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CPlayerAction();
	~CPlayerAction();

	// �������E�I������
	static void Init();
	static void Uninit();

	// �X�V
	virtual void Update();

	// �s���p�^�[��
	virtual void Attack(int nAnimSpeed = 0);
	virtual void Attack(int nAnimSpeed, CTransform* pTrans);


	// OnCollision�ɃZ�b�g
	//virtual void OnCollisionAction(CCollision *pCol);
	// OnAnimator�ɃZ�b�g
	virtual void OnAnimatorAction(CAnimator *pAnim);

	void SetPlayerAttackData(CPlayer *pPlayer, int nAttackAnimSpeed)
	{ 
		m_pPlayer = pPlayer; 
		m_nAttackAnimSpeed = nAttackAnimSpeed;
	}
	void SetAttackAnimSpeed(int nAttackAnimSpeed) { m_nAttackAnimSpeed = nAttackAnimSpeed; }

protected:
	CPlayer *m_pPlayer;

	int m_nAttackAnimSpeed;
	bool m_bAttack;
	bool m_bDown;
	int m_nAttackInterval;
};

