//==================================================================
//											stageChageBossArea.h
//	ステージチェンジエリアのボス部屋版
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//	
//	2020/09/04	ステージチェンジボスエリアクラスの作成
//
//===================================================================

#pragma once

//====== インクルード部 ======
#include "../main.h"
#include "object.h"


//===== クラス定義 =====

class CStageChangeBossArea : public CObject
{
public:
	CStageChangeBossArea();
	~CStageChangeBossArea();

	// 静的関数
	static CStageChangeBossArea* Create(Float3 pos);
	static void Init();
	static void Uninit();

	// 仮想関数
	virtual void Update();
	virtual void LateUpdate();
	virtual void Draw();
	virtual void Destroy();

	// 当たり判定用の関数
	virtual void OnCollision(CCollision *pCollision);

	// ゲット関数
	CCollision* GetCol() { return m_pCollision; }

protected:
	// コンポーネント
	CCollision* m_pCollision;	// コリジョン
	static CTexture sm_texture;

	bool m_Hit;
private:

};

