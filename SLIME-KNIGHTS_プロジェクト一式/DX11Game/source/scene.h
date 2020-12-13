//==================================================================
//								scene.h
//	GM21 シーン
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//
//	2020/07/16	シーンクラス作成
//
//===================================================================

#pragma once

//====== インクルード部 ======
#include "../main.h"


//===== クラス定義 =====
class CScene
{
public:
	CScene();
	~CScene();

	// 四大処理
	virtual void Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();

private:

};


