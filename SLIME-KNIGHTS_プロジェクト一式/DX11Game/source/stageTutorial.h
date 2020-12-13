//==================================================================
//								sceneTutorial.h
//	チュートリアルマップ
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//
//	2020/09/05	チュートリアルマップクラスの作成
//
//===================================================================
#pragma once


//====== インクルード部 ======
#include "../main.h"
#include "stage.h"


//===== クラス定義 =====
class CStageTutorial : public CStage
{
public:
	CStageTutorial();
	~CStageTutorial();

	// 四大処理
	virtual void Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();


private:

};


