//==================================================================
//									fade.h
//	GM21 �t�F�[�h�C���E�t�F�[�h�A�E�g
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//
//	2020/06/17	�t�F�[�h�̕`��
//
//===================================================================

#pragma once

//====== �C���N���[�h�� ======
#include "../main.h"
#include "object.h"


//===== �}�N����` =====


//===== �N���X��` =====
class FADE : public CObject
{
public:
	FADE(void(*pSetChange)());
	~FADE();
	// �t�F�[�h�A�E�g�̊J�n
	void StartFadeOut();
	// ���z�֐�
	virtual void Update();
	virtual void Draw();

	static bool GetNowFade() { return m_bNowFade; }
	void SetChangeEvent(void(*pSetChange)()) { m_pSetChange = pSetChange; }

private:
	int m_nAlpha;	// �t�F�[�h�p�|���S���̃A���t�@�l(0�`255)
	int m_nState;	// ���
	int m_nFrame;	// �t�F�[�h�ɂ�����t���[����

	CTexture m_texture;
	void(*m_pSetChange)() = nullptr;

	static bool m_bNowFade;
};
