//==================================================================
//								Fire.h
//	�}�b�v�̓���
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//	
//	2020/07/09/06	�t�@�C���N���X�̍쐬	
//
//===================================================================

#pragma once

//====== �C���N���[�h�� ======
#include "../main.h"
#include "object.h"


//===== �萔��` =====

//===== �N���X��` =====

class CFire : public CObject
{
public:
	// �ʏ�֐�
	CFire();
	~CFire();
	void Destroy();

	// �ÓI�֐�
	static void Create(Float3 pos);
	static void Init();
	static void Uninit();

	// ���z�֐�
	virtual void Update();
	virtual void Draw();
	// �����蔻��p�̊֐�
	virtual void OnCollision(CCollision *pCollision);
	// �A�j���[�V�����I�����ɌĂяo�����֐�
	virtual void OnAnimator(CAnimator *pAnimator);

	// �R���|�[�l���g
	CCollision* GetCol() { return m_pCollision; }

protected:
	CCollision* m_pCollision;	// �R���|�[�l���g
	CAnimator*  m_pAnimator;	// �R���|�[�l���g

	// ���C�g
	static CTexture sm_textureFire;
	static CTexture sm_textureBottom;
	CSprite m_spriteDefault;
private:

};



//===== �v���g�^�C�v�錾 =====
