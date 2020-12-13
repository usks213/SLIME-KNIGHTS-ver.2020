//==================================================================
//									movieUI.h
//	���[�r�[���̍�����
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//
//	2020/09/08	���[�r�[UI�N���X�̍쐬
//
//===================================================================

#pragma once

//====== �C���N���[�h�� ======
#include "../main.h"
#include "object.h"


//===== �}�N����` =====


//===== �N���X��` =====
class CMovieUI : public CObject
{
public:
	CMovieUI();
	~CMovieUI();

	static CMovieUI* Create(Float3 pos = Float3{0,0,0});
	void Destroy();

	virtual void Update();
	virtual void Draw();

	static void Init();
	static void Uninit();
	static void SetDraw(bool bFlag) { m_bDraw = bFlag; }

private:
	static CTexture sm_texture;		// �}�X�^�[�e�N�X�`��
	static bool m_bDraw;

};
