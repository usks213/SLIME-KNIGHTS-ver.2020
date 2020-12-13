//==================================================================
//								experience.h
//	�h���b�v����o���l
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//	
//	2020/07/09/05	�G�N�X�y���G���X�N���X�̍쐬	
//
//===================================================================

#pragma once

//====== �C���N���[�h�� ======
#include "../main.h"
#include "object.h"


//===== �萔��` =====

//===== �N���X��` =====

class CExperience : public CObject
{
public:
	// �ʏ�֐�
	CExperience();
	~CExperience();
	void Destroy();

	// �ÓI�֐�
	static void Create(int nNum, Float3 pos);
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
	CRigidbody* GetRb()  { return m_pRigidbody; }

protected:
	CCollision* m_pCollision;	// �R���|�[�l���g
	CRigidbody* m_pRigidbody;	// �R���|�[�l���g

	// �o���l
	static CTexture sm_texture;
	static CTexture sm_textureLight;
	float m_fForceY;
	Float2 m_size;
	int m_nExperience;
private:

};



//===== �v���g�^�C�v�錾 =====
