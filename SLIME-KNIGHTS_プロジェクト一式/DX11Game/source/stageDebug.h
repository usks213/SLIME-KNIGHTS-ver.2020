//==================================================================
//								sceneDebug.h
//	デバッグステージ
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//
//	2020/08/23	デバッグステージクラスの作成
//
//===================================================================
#pragma once


//====== インクルード部 ======
#include "../main.h"
#include "stage.h"


//===== クラス定義 =====
class CStageDebug : public CStage
{
public:
	CStageDebug();
	~CStageDebug();

	// 四大処理
	virtual void Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();


private:

};


