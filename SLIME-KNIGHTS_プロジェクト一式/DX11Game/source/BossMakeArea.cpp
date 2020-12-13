//==================================================================
//											BossMakeArea.cpp
//	ボス生成エリア
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//	
//	2020/09/04	ボス生成エリアクラスの作成
//
//===================================================================


//====== インクルード部 ======
#include "BossMakeArea.h"

#include "collision.h"
#include "objectMgr.h"
#include "stageManager.h"
#include "stageMaker.h"
#include "stageBoss.h"
#include "fade.h"
#include "enemySlimBoss.h"

#include "../texture.h"
#include "../sprite.h"

#ifdef _WIN64
#include "../DirectX11.h"

#endif // _WIN64

//===== マクロ定義 =====

enum EMAP_AREA_TYPE
{
	L,
	R,
	T,
	B,
};

//===== 名前空間 =====


//===== 静的メンバ =====



//========================================
//
//	コンストラクタ
//
//========================================
CBossMakeArea::CBossMakeArea()
{
	// コリジョン
	m_pCollision = CCollision::Create(this, nullptr);

	// ポリゴンのパラメータの初期化
	m_transform.SetSize(Float2{ 150, 150 });

	// スプライトデータ
	m_sprite.SetColor(Float4{ 0.0f, 0.0f, 1.0f, 0.3f });

	// レイヤー
	m_enLayer = LAYER::FIELD;

	m_Hit = false;
}


//========================================
//
//	デストラクタ
//
//========================================
CBossMakeArea::~CBossMakeArea()
{
	// コリジョン
	m_pCollision->Destroy();
}


//========================================
//
//	更新処理
//
//========================================
void CBossMakeArea::Update()
{
	
}

//========================================
//
//	更新処理
//
//========================================
void CBossMakeArea::LateUpdate()
{

}

//========================================
//
//	描画処理
//
//========================================
void CBossMakeArea::Draw()
{
	// 加算合成
//	glBlendFunc(GL_ONE, GL_ONE);
	//CDirectX11::SetBlendState(EBlendState::BS_ADDITIVE);

	// 四角形の描画
	if (GetDebugFlag())
		m_sprite.Draw(&m_transform, nullptr);

	// アルファ合成
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//CDirectX11::SetBlendState(EBlendState::BS_ALPHABLEND);

}

//========================================
//
//	生成
//
//========================================
CBossMakeArea* CBossMakeArea::Create(Float3 pos)
{
	CBossMakeArea *pStageChangeArea = CObjectManager::CreateObject<CBossMakeArea>(pos);
	pStageChangeArea->GetTransform()->SetSize(Float2{ 200, 2000 });

	return pStageChangeArea;
}

//========================================
//
//	消去
//
//========================================
void CBossMakeArea::Destroy()
{
	CObjectManager::DestroyObject(this);

}

//========================================
//
//	当たり判定
//
//========================================
void CBossMakeArea::OnCollision(CCollision *pCollision) 
{
	CObject* pObj = pCollision->GetObj();

	if (pObj->GetLayer() == LAYER::PLAYER)
	{
		if (m_Hit) return;

		// ボスの生成
		CObjectManager::CreateObject<CEnemySlimBoss>(m_transform.GetPos());

		this->Destroy();
	}
}
