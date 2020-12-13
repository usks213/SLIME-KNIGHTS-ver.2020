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


//====== インクルード部 ======
#include "stageChangeBossArea.h"

#include "collision.h"
#include "objectMgr.h"
#include "stageManager.h"
#include "stageMaker.h"
#include "stageBoss.h"
#include "fade.h"

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
CTexture CStageChangeBossArea::sm_texture;


//========================================
//
//	コンストラクタ
//
//========================================
CStageChangeBossArea::CStageChangeBossArea()
{
	// コリジョン
	m_pCollision = CCollision::Create(this, nullptr);

	// ポリゴンのパラメータの初期化
	m_transform.SetSize(Float2{ 150, 150 });

	// スプライトデータ
	m_sprite.SetColor(Float4{ 0.8f, 0.8f, 0.8f, 1 });
	// レイヤー
	m_enLayer = LAYER::FIELD;

	m_Hit = false;
}


//========================================
//
//	デストラクタ
//
//========================================
CStageChangeBossArea::~CStageChangeBossArea()
{
	// コリジョン
	m_pCollision->Destroy();
}

//========================================
//
//	初期化
//
//========================================
void CStageChangeBossArea::Init()
{
	sm_texture.LoadTexture(FILE_PATH"object/boss_gate.tga");
}

//========================================
//
//	終了処理
//
//========================================
void CStageChangeBossArea::Uninit()
{
	sm_texture.UnloadTexture();
}


//========================================
//
//	更新処理
//
//========================================
void CStageChangeBossArea::Update()
{
	
}

//========================================
//
//	更新処理
//
//========================================
void CStageChangeBossArea::LateUpdate()
{

}

//========================================
//
//	描画処理
//
//========================================
void CStageChangeBossArea::Draw()
{
	// 加算合成
//	glBlendFunc(GL_ONE, GL_ONE);
	//CDirectX11::SetBlendState(EBlendState::BS_ADDITIVE);

	// 四角形の描画
	//if (GetDebugFlag())
	m_sprite.Draw(&m_transform, &sm_texture);

	// アルファ合成
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//CDirectX11::SetBlendState(EBlendState::BS_ALPHABLEND);

}

//========================================
//
//	生成
//
//========================================
CStageChangeBossArea* CStageChangeBossArea::Create(Float3 pos)
{
	pos.y -= 96 + 48;
	CStageChangeBossArea *pStageChangeArea = CObjectManager::CreateObject<CStageChangeBossArea>(pos);
	pStageChangeArea->GetTransform()->SetSize(Float2{ 96*3, 96*4 });

	return pStageChangeArea;
}

//========================================
//
//	消去
//
//========================================
void CStageChangeBossArea::Destroy()
{
	CObjectManager::DestroyObject(this);

}

//========================================
//
//	当たり判定
//
//========================================
void CStageChangeBossArea::OnCollision(CCollision *pCollision) 
{
	CObject* pObj = pCollision->GetObj();

	if (pObj->GetLayer() == LAYER::PLAYER)
	{
		if (FADE::GetNowFade()) return;
		if (m_Hit) return;


		CStageManager::SetNextStage(new CStageBoss());

		m_Hit = true;
	}
}
