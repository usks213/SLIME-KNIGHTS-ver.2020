//==================================================================
//								enemyUI.h
//	�G�l�~�[��UI
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//	
//	2020/07/09/07	�G�l�~�[UI�N���X�̍쐬
//
//===================================================================

#pragma once

//====== �C���N���[�h�� ======
#include "../main.h"
#include "object.h"


//===== �萔��` =====


//===== �N���X��` =====
class CEnemy;

class CEnemyUI : public CObject
{
public:
	// �ʏ�֐�
	CEnemyUI();
	~CEnemyUI();
	void Destroy();

	// �ÓI�֐�
	static CEnemyUI* Create(CEnemy* pParent);
	static void Init();
	static void Uninit();

	// ���z�֐�
	virtual void Update();
	virtual void LateUpdate();
	virtual void Draw();

	void SetDraw(bool bFlag) { m_bDraw = bFlag; }

protected:
	// BG
	Float4 m_colorBG;
	// UI
	Float4 m_colorUI;
	// HP
	Float4 m_colorHP;
	Float2 m_sizeHP;

	// �e�N�X�`���f�[�^
	static CTexture sm_UiTexture;

	CEnemy* m_pParent;

	bool m_bDraw;
private:
};


