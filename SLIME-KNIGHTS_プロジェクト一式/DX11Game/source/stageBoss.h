//==================================================================
//								sceneBoss.h
//	ボスステージ
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//
//	2020/09/04	ボスステージクラスの作成
//
//===================================================================
#pragma once


//====== インクルード部 ======
#include "../main.h"
#include "stage.h"


//===== クラス定義 =====
class CStageBoss : public CStage
{
public:
	CStageBoss();
	~CStageBoss();

	// 四大処理
	virtual void Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();


private:

};


