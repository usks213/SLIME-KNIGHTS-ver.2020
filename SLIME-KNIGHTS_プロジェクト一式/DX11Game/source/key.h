//==================================================================
//									key.h
//	�L�[�{�[�h�̉摜
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//
//	2020/09/06	�L�[�N���X�̍쐬
//
//===================================================================

#pragma once

//====== �C���N���[�h�� ======
#include "../main.h"
#include "object.h"


//===== �}�N����` =====

namespace KEY
{
	enum EKEY_TYPE
	{
		W,
		A,
		S,
		D,
		R,
		Z,
		X,
		C,
		J,
		K,
		L,
		RIGHT,
		LEFT,
		UP,
		DOWN,
		TAB,
		SPACE,

		MAX_KEY_TYPE,
	};
}

//===== �N���X��` =====
class CKey : public CObject
{
public:
	CKey();
	~CKey();

	static CKey* Create(KEY::EKEY_TYPE eType, Float3 pos = Float3{0,0,0}, bool bCamera = true);
	void Destroy();

	virtual void Update();
	virtual void Draw();

	static void Init();
	static void Uninit();

	void SetLayer(LAYER::LAYER eLayer) { m_enLayer = eLayer; }

private:
	static CTexture sm_texture[KEY::MAX_KEY_TYPE];		// �}�X�^�[�e�N�X�`��
	CTexture* m_pTexture;
	bool m_bCamera;
};
