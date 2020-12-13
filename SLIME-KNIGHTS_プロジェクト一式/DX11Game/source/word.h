//==================================================================
//									word.h
//	������\��
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//
//	2020/08/08	������\���N���X�̍쐬
//
//===================================================================

#pragma once

//====== �C���N���[�h�� ======
#include "../main.h"
#include "object.h"


//===== �}�N����` =====


//===== �N���X��` =====
class CWord
{
public:
	CWord();
	~CWord();

	void Update();
	void Draw(bool bCamera);

	static CWord* Create(Float3 pos, Float2 size, Float2 texPos, Float2 texSize, Float4 color, CTexture *pTexture);
	static CWord* Create();
	void Destroy();

	// �Q�b�g�֐�
	CTransform* GetTrans() { return &m_trans; }
	CSprite* GetSprite() { return &m_sprite; }
	// �Z�b�g�֐�
	void SetTexture(CTexture *pTexture) { m_pTexture = pTexture; }

private:
	CTransform m_trans;
	CSprite m_sprite;
	CTexture *m_pTexture;
};

