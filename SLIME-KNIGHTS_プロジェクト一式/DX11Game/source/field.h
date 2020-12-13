//==================================================================
//								field.h
//	GM21 �t�B�[���h����	
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//	
//	2020/07/14	�t�B�[���h�N���X�쐬
//
//===================================================================

#pragma once

//====== �C���N���[�h�� ======
#include "../main.h"
#include "../texture.h"


//===== �N���X��` =====

class CField
{
public:
	CField();
	~CField();
	void Destroy();

	// �ÓI�֐�
	static void Init();
	static void Uninit();
	static void Create(const char *pszCSV, CTexture* pTex, int nSplitX, int nSplitY);
	static void CreateBg(const char *pszCSV, CTexture* pTex, int nSplitX, int nSplitY);
	static void SetObject(const char *pszCSV, bool bBoss = false);
	static void SetEnemy(const char *pszCSV);
	static void SetPlayer(const char *pszCSV, int nPosType);
	static void SetChangeArea(const char *pszCSV);

	static int GetWidth() { return m_nWidth; }
	static int GetHieght() { return m_nHeight; }

private:

	static int m_nHeight;
	static int m_nWidth;
};

