//==================================================================
//								playerUI.h
//	�v���C���[��UI
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//	
//	2020/07/09/05	�v���C���[UI�N���X�̍쐬
//
//===================================================================

#pragma once

//====== �C���N���[�h�� ======
#include "../main.h"
#include "object.h"
#include "string.h"


//===== �萔��` =====


//===== �N���X��` =====

class CPlayerUI : public CObject
{
public:
	// �ʏ�֐�
	CPlayerUI();
	~CPlayerUI();
	void Destroy();

	// �ÓI�֐�
	static CPlayerUI* Create(Float3 pos);
	static void Init();
	static void Uninit();

	// ���z�֐�
	virtual void Update();
	virtual void LateUpdate();
	virtual void Draw();


protected:
	// BG
	Float4 m_colorBG;
	// UI
	Float4 m_colorUI;
	// HP
	Float4 m_colorHP;
	Float2 m_sizeHP;
	// EX
	Float4 m_colorEX;
	Float2 m_sizeEX;

	// �e�N�X�`���f�[�^
	static CTexture sm_UiTexture;

	// �e�L�X�g
	STRING::CString *m_pLevel;
	STRING::CString *m_pHP;
	STRING::CString *m_pExperience;
private:
};


