//==================================================================
//									bg.h
//	GM21 �w�i
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//
//	2020/06/05	�w�i�`��
//	2020/06/17	�I�u�W�F�N�g�w����
//
//===================================================================

#pragma once

//====== �C���N���[�h�� ======
#include "../main.h"
#include "object.h"


//===== �}�N����` =====

namespace BG
{
	enum EBG_TYPE
	{
		TITLE,
		GAME,
		RESALT,
		BOSS_MOVIE,

		MAX_BG_TYPE,
	};
}

//===== �N���X��` =====
class CBG : public CObject
{
public:
	CBG();
	~CBG();

	static CBG* Create(BG::EBG_TYPE eType, Float3 pos = Float3{0,0,0});
	void Destroy();

	virtual void Update();
	virtual void Draw();

	static void Init();
	static void Uninit();

	void SetLayer(LAYER::LAYER eLayer) { m_enLayer = eLayer; }

private:
	static CTexture sm_texture[BG::MAX_BG_TYPE];		// �}�X�^�[�e�N�X�`��
	CTexture* m_pTexture;
};
