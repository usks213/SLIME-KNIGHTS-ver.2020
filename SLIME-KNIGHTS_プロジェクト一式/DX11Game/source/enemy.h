//==================================================================
//								enemy.h
//	GM21 �G�l�~�[
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//
//	2020/06/05	�v���C���[�`��
//	2020/06/14	�I�u�W�F�N�g�̔h���N���X��
//
//===================================================================

#pragma once

//====== �C���N���[�h�� ======
#include "../main.h"
#include "object.h"
#include "character.h"
#include "viewArea.h"
#include "attackArea.h"
#include "enemyUI.h"
#include "experience.h"
#include "../Sound.h"


//===== �萔��` =====
namespace ENEMY
{
	enum ETYPE
	{
		SLIM,
		WING,
		WING_GREEN,
		LANCE,
		BOW,
		KNIGHT,
		BOSS,

		MAX_TYPE
	};

	enum EENEMY_SOUND
	{
		SE_SLIME,
		SE_ONE_SHOT,
		SE_MUL_SHOT,
		SE_BOSS_SHOT,
		SE_BOSS_DESTROY,

		MAX_ENEMY_SOUND,
	};

}



//===== �N���X��` =====
class CEnemy : public CCharacter
{
public:
	CEnemy();
	~CEnemy();
	// ���z�֐�
	virtual void Update();
	virtual void LateUpdate() {};
	virtual void Draw();
	virtual void Destroy() { 
		// �o���l
		CExperience::Create(GetStatus()->GetExperience(), GetTransform()->GetPos());
		CObjectManager::DestroyObject(this);
	}

	static void Init();
	static void Uninit();

	virtual void OnCollision(CCollision *pCollision);
	virtual void OnAnimator(CAnimator *pAnimator) { m_charaAction.OnAnimatorAction(pAnimator); };

	// �Z�b�g�֐�
	void SetTarget(CTransform *pTarget) { m_pTargetPlayer = pTarget; }
	void SetAttack(bool bFlag) { m_bAttack = bFlag; }

	// �Q�b�g�֐�
	CEnemyUI* GetUI() { return m_pUI; }

protected:
	static CTexture sm_texture[ENEMY::MAX_TYPE];		// �}�X�^�[�e�N�X�`��
	static CSound sm_SE[ENEMY::MAX_ENEMY_SOUND];			// �T�E���h
	ENEMY::ETYPE m_eType;

	int m_nMoveCnt;
	int m_nMoveInterval;
	int m_nMoveType;
	int m_nJumpInterval;

	CCharacterAction m_charaAction;
	CViewArea *m_pViewArea;
	CAttackArea *m_pAttackArea;

	// �^�[�Q�b�g
	CTransform* m_pTargetPlayer;
	bool m_bAttack;

	// UI
	CEnemyUI* m_pUI;
};


//===== �v���g�^�C�v�錾 =====
