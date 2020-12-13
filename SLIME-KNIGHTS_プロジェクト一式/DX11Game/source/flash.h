//==================================================================
//									flash.h
//	�t���b�V��
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//
//	2020/09/05	�t���b�V���N���X�̍쐬
//
//===================================================================

#pragma once

//====== �C���N���[�h�� ======
#include "../main.h"
#include "object.h"


//===== �}�N����` =====


//===== �N���X��` =====
class CEnemySlimBoss;

class CFlash : public CObject
{
public:
	CFlash();
	~CFlash();
	// �t���b�V���A�E�g�̊J�n
	void StartFlash(void(*pSetEvent)(CEnemySlimBoss*), CEnemySlimBoss* pBoss);
	// ���z�֐�
	virtual void Update();
	virtual void Draw();

	static bool GetNowFlash() { return m_bNowFlash; }

private:
	int m_nAlpha;	// �t���b�V���p�|���S���̃A���t�@�l(0�`255)
	int m_nFrame;	// �t���b�V���ɂ�����t���[����

	CTexture m_texture;
	void(*m_pSetEvent)(CEnemySlimBoss*) = nullptr;
	CEnemySlimBoss* m_pBoss;

	static bool m_bNowFlash;
};
