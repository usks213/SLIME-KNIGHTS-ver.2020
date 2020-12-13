//==================================================================
//								levelupText.h
//	���x���A�b�v�\��
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//	
//	2020/07/09/05	���x���A�b�v�e�L�X�g�N���X
//
//===================================================================

#pragma once

//====== �C���N���[�h�� ======
#include "../main.h"
#include "object.h"
#include "string.h"


//===== �萔��` =====


//===== �N���X��` =====

class CLevelUpText : public CObject
{
public:
	// �ʏ�֐�
	CLevelUpText();
	~CLevelUpText();
	void Destroy();

	// �ÓI�֐�
	static CLevelUpText* Create(Float3 pos);
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
	CAnimator* GetAnim() { return m_pAnimator; }
	CRigidbody* GetRb()  { return m_pRigidbody; }

protected:
	CCollision* m_pCollision;	// �R���|�[�l���g
	CAnimator* m_pAnimator;		// �R���|�[�l���g
	CRigidbody* m_pRigidbody;	// �R���|�[�l���g

	STRING::CString *m_pString;
	float m_fForceY;
	char m_szText[30];
private:
	int m_nExistTime;
};



//===== �v���g�^�C�v�錾 =====
