//==================================================================
//								field.h
//	GM21 フィールド生成	
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//	
//	2020/07/14	フィールドクラス作成
//
//===================================================================

#pragma once

//====== インクルード部 ======
#include "../main.h"
#include "../texture.h"


//===== クラス定義 =====

class CField
{
public:
	CField();
	~CField();
	void Destroy();

	// 静的関数
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

