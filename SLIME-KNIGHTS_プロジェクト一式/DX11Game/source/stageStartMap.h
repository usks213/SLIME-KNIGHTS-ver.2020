//==================================================================
//								sceneStartMap.h
//	スタートマップ
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//
//	2020/09/05	スタートマップクラスの作成
//
//===================================================================
#pragma once


//====== インクルード部 ======
#include "../main.h"
#include "stage.h"


//===== クラス定義 =====
class CStageStartMap : public CStage
{
public:
	CStageStartMap();
	~CStageStartMap();

	// 四大処理
	virtual void Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();


private:

};


