//==================================================================
//									resultUI.h
//	���U���g���
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//
//	2020/09/07	���U���gUI�N���X�̍쐬
//
//===================================================================

#pragma once

//====== �C���N���[�h�� ======
#include "../main.h"
#include "object.h"
#include "string.h"


//===== �}�N����` =====
#define MAX_RESULT_BAR (5)

//===== �N���X��` =====
class CResultUI : public CObject
{
public:
	CResultUI();
	~CResultUI();

	static CResultUI* Create(Float3 pos = Float3{0,0,0});
	void Destroy();

	virtual void Update();
	virtual void Draw();

	static void Init();
	static void Uninit();

	static void Reset(int nPrevLevel) {
		m_nEnemy = 0;
		m_nExperience = 0;
		m_nPrevLevel = nPrevLevel;
		m_nCurLevel = 0;
	}

	static void AddEnemy() { m_nEnemy++; }
	static void AddExperience(int nEx) { m_nExperience += nEx; }
	static void SetCurLevel(int nLevel) { m_nCurLevel = nLevel; }

private:
	// ���
	int m_nState;

	// BG
	Float4 m_colorBG;
	float m_fBgAlpha;


	// GAME OVER
	static CTexture sm_textureGameOver;		// �}�X�^�[�e�N�X�`��
	float m_fGameOverAlpha;

	// BAR
	static CTexture sm_textureBar;				// �}�X�^�[�e�N�X�`��
	float m_fBarPosY[MAX_RESULT_BAR];
	int m_nBarCnt;

	// �X�g�����O
	STRING::CString* m_pString;


	// ���U���gUI�̃f�[�^
	static int m_nExperience;
	static int m_nEnemy;
	static int m_nPrevLevel;
	static int m_nCurLevel;
	static int m_nDrawLevel;
	int m_nTime;
};
