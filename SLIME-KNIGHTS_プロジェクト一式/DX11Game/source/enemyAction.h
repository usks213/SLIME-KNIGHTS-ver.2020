//==================================================================
//								enemyAction.h
//	 
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//	
//	2020/08/16	�G�l�~�[�A�N�V�����N���X�̍쐬
//
//===================================================================

#pragma once

//====== �C���N���[�h�� ======
#include "characterAction.h"


//===== �N���X��` =====

class CEnemyAction : public CCharacterAction
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CEnemyAction();
	~CEnemyAction();

	// �s���p�^�[��
	virtual void Attack(int nAnimSpeed = 0);

	// OnCollision�ɃZ�b�g
	//virtual void OnCollisionAction(CCollision *pCol);
	// OnAnimator�ɃZ�b�g
	virtual void OnAnimatorAction(CAnimator *pAnim);


protected:
};

