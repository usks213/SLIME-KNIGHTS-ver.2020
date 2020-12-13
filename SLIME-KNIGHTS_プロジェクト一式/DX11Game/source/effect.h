//==================================================================
//								effect.h
//	GM21 �G�t�F�N�g
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//	
//	2020/07/11	�G�t�F�N�g�N���X�̍쐬	
//
//===================================================================

#pragma once

//====== �C���N���[�h�� ======
#include "../main.h"
#include "object.h"


//===== �N���X��` =====

namespace EFFECT
{
	enum EEFFECT_NAME
	{
		PLAYER_DAMAGE,
		ENEMY_DAMAGE,
		DUST_L,
		DUST_R,
		SWORD_L,
		SWORD_R,

		MAX_EFFECT_NAME,
	};
}

class CEffect : public CObject
{
public:
	CEffect();
	~CEffect();
	void Destroy();

	// �ÓI�֐�
	static void Init();
	static void Uninit();
	static void Create(EFFECT::EEFFECT_NAME enName, Float3 pos);

	// ���z�֐�
	virtual void Update();
	virtual void Draw();
	// �����蔻��p�̊֐�
	virtual void OnCollision(CCollision *pCollision) { return; }		// �L�����N�^�[�Ɏ�������
	// �A�j���[�V�����I�����ɌĂяo�����֐�
	virtual void OnAnimator(CAnimator *pAnimator);
protected:
	CCollision* m_pCollision;	// �R���|�[�l���g
	CAnimator* m_pAnimator;		// �R���|�[�l���g
	static CTexture sm_aTexture[EFFECT::MAX_EFFECT_NAME];
	CTexture *m_pTexture;
private:

};


//===== �v���g�^�C�v�錾 =====
