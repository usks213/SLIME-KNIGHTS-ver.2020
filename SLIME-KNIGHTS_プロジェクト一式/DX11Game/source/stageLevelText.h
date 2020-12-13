//==================================================================
//								stageLevelText.h
//	�X�e�[�W���x���̕\��
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//	
//	2020/07/09/07	�X�e�[�W���x���N���X�̍쐬
//
//===================================================================

#pragma once

//====== �C���N���[�h�� ======
#include "../main.h"
#include "object.h"
#include "string.h"


//===== �萔��` =====


//===== �N���X��` =====

class CStageLevelText : public CObject
{
public:
	// �ʏ�֐�
	CStageLevelText();
	~CStageLevelText();
	void Destroy();

	// �ÓI�֐�
	static CStageLevelText* Create(Float3 pos, int nLevel);
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
	CAnimator* GetAnim() { return m_pAnimator; }

protected:
	CAnimator* m_pAnimator;		// �R���|�[�l���g

	STRING::CString *m_pString;
	char m_szText[30];
private:
	float m_fAlpha;
	bool m_bAlpha;
};



//===== �v���g�^�C�v�錾 =====
