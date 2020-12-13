//==================================================================
//											stageChageStartArea.cpp
//	ステージチェンジエリアのスタートマップ版
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//	
//	2020/09/04	ステージチェンジスタートエリアクラスの作成
//
//===================================================================


//====== インクルード部 ======
#include "stageChangeStartArea.h"

#include "collision.h"
#include "objectMgr.h"
#include "stageManager.h"
#include "stageMaker.h"
#include "fade.h"
#include "stageStartMap.h"

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
CStageChangeStartArea::CStageChangeStartArea()
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
CStageChangeStartArea::~CStageChangeStartArea()
{
	// コリジョン
	m_pCollision->Destroy();
}


//========================================
//
//	更新処理
//
//========================================
void CStageChangeStartArea::Update()
{
	
}

//========================================
//
//	更新処理
//
//========================================
void CStageChangeStartArea::LateUpdate()
{

}

//========================================
//
//	描画処理
//
//========================================
void CStageChangeStartArea::Draw()
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
CStageChangeStartArea* CStageChangeStartArea::Create(Float3 pos)
{
	CStageChangeStartArea *pStageChangeArea = CObjectManager::CreateObject<CStageChangeStartArea>(pos);
	pStageChangeArea->GetTransform()->SetSize(Float2{ 80, 800 });

	return pStageChangeArea;
}

//========================================
//
//	消去
//
//========================================
void CStageChangeStartArea::Destroy()
{
	CObjectManager::DestroyObject(this);

}

//========================================
//
//	当たり判定
//
//========================================
void CStageChangeStartArea::OnCollision(CCollision *pCollision) 
{
	CObject* pObj = pCollision->GetObj();

	if (pObj->GetLayer() == LAYER::PLAYER)
	{
		if (FADE::GetNowFade()) return;
		if (m_Hit) return;


		CStageManager::SetNextStage(new CStageStartMap());
		CStageManager::SetTutorialClear(true);

		m_Hit = true;
	}
}
