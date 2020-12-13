//==================================================================
//								stageMaker.h
//	ランダムステージメイカー
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//
//	2020/08/25	ステージメイカークラスの作成
//
//===================================================================

#pragma once

//====== インクルード部 ======
#include "../main.h"
#include "../texture.h"
#include "List.h"
#include "miniMap.h"

#define MAP_WIDTH	(7)
#define MAP_HEIGHT	(5)

//===== クラス定義 =====
class CStageMaker
{
public:
	CStageMaker();
	~CStageMaker();

	// 四大処理
	static void Init();
	static void Uninit();
	virtual void Update();
	virtual void Draw();

	static void CreateRendomMap();
	static void CreateStage();
	//static void CreateMiniMap();
	//static void DestroyMiniMap();
	static void MiniMapDraw();
	static void SetMiniMapDraw(bool bFalg) { m_bMiniMapDraw = bFalg; }
	static bool GetMiniMapDraw() { return m_bMiniMapDraw; }

	struct SMAP_DATA
	{
		int		nMapType;
		bool	bClearFlag;
	};

	static void AddCurMapPosX() { m_nCurrentMapPosX++; }
	static void AddCurMapPosY() { m_nCurrentMapPosY++; }

	static void SubCurMapPosX() { m_nCurrentMapPosX--; }
	static void SubCurMapPosY() { m_nCurrentMapPosY--; }

	static bool GetStartFlag() { return m_bStart; }
	static void SetStartFlag(bool bFlag) { m_bStart = bFlag; }
private:
	
	//static SMAP_DATA* m_pMapData;
	static SMAP_DATA m_pMapData[MAP_HEIGHT * MAP_WIDTH];
	static CTexture sm_minimapTexture;
	static CTexture sm_minimapUITexture;
	static CTexture sm_minimapTextTexture;
	static int m_nCurrentMapPosX;
	static int m_nCurrentMapPosY;
	static bool m_bStart;
	static bool m_bMiniMapDraw;

	static List<CMiniMap> m_miniMapList;

};


