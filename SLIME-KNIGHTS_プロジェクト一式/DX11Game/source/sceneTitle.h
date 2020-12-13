//==================================================================
//								sceneGame.h
//	GM21 ゲームシーン
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//
//	2020/07/18	ゲームクラス作成
//
//===================================================================
#pragma once


//====== インクルード部 ======
#include "../main.h"
#include "scene.h"


//===== クラス定義 =====
class CSceneTitle : public CScene
{
public:
	CSceneTitle();
	~CSceneTitle();

	// 四大処理
	virtual void Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();

private:

};


