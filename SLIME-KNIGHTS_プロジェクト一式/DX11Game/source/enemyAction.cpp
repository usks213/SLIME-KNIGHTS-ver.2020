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


//====== �C���N���[�h�� ======
#include "enemyAction.h"
#include "collision.h"
#include "animator.h"
#include "rigidbody.h"
#include "animation.h"
#include "objectMgr.h"
#include "character.h"
#include "attackBase.h"
#include "effect.h"
#include "experience.h"
#include "camera.h"
#include "player.h"


//===== �}�N����` =====
#define KNOCKBACK_FORCEX (12)
#define KNOCKBACK_FORCEY (12)
#define DEFAULT_ANIM_SPEED (12)
#define ATTACK_OFFSET_X (96)

//===== �ÓI�֐� =====



//========================================
//
//	�R���X�g���N�^
//
//========================================
CEnemyAction::CEnemyAction()
{

}


//========================================
//
//	�f�X�g���N�^
//
//========================================
CEnemyAction::~CEnemyAction()
{

}



//========================================
//
//	�U��
//
//========================================
void CEnemyAction::Attack(int nAnimSpeed)
{
	
}


//========================================
//
//	�A�j���[�V�����I�����ɌĂяo��
//
//========================================
void CEnemyAction::OnAnimatorAction(CAnimator *pAnim)
{
	// �I�������A�j���[�V�����̖��O�ŕ���
	if (pAnim->GetCurrentAnimation()->GetName() == "RightAttack" || pAnim->GetCurrentAnimation()->GetName() == "LeftAttack")
	{

	}
}

