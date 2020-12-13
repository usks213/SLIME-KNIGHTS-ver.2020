//==================================================================
//									combo.h
//	�v���C���[�̃R���{
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//
//	2020/10/28	�R���{�N���X�쐬
//
//===================================================================

#pragma once

//====== �C���N���[�h�� ======
#include "../main.h"
#include "object.h"


//===== �}�N����` =====
#define MAX_COMBO	(5)


//===== �N���X��` =====
class CCombo : public CObject
{
public:
	CCombo();
	~CCombo();

	static CCombo* Create(Float3 pos);
	void Destroy();

	virtual void Update(){}
	virtual void LateUpdate();
	virtual void Draw();

	static void Init();
	static void Uninit();

	void SetLayer(LAYER::LAYER eLayer) { m_enLayer = eLayer; }

	void UpdateComboTexCoord();

	void AddCombo(int num);
	void ResetCombo();
	bool GetCritical() {
		// �����_���ŃN���e�B�J��
		int nCrt = rand() % 30;

		// �R���{�ŃN���e�B�J�����A�b�v
		nCrt += m_nComboCount;

		// �N���e�B�J������
		if (rand() % 100 < nCrt) return true;
		else return false;
	}

	struct SComboData
	{
		CSprite m_spr;
		int m_nAnimNo;
	};


private:
	static CTexture sm_texture;		// �}�X�^�[�e�N�X�`��
	static CTexture sm_comboTex;	// �R���{�e�N�X�`��
	static CTexture sm_comboUITex;	// �R���{�e�N�X�`��

	int m_nComboCount;
	SComboData m_data[MAX_COMBO];
	int m_nComboTime;
	int m_nMaxComboTime;
};

