//==================================================================
//								stageChageArea.h
//	ステージチェンジエリア	
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//	
//	2020/08/23	ステージチェンジエリア
//
//===================================================================


//====== インクルード部 ======
#include "stageChangeArea.h"

#include "collision.h"
#include "rigidbody.h"
#include "objectMgr.h"
#include "stageManager.h"
#include "stageDebug.h"
#include "stageMaker.h"
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
int CStageChangeArea::m_nGotoChangeArea = 1;



//========================================
//
//	コンストラクタ
//
//========================================
CStageChangeArea::CStageChangeArea()
{
	// リジッドボディ
	//m_pRb = CRigidbody::Create(&m_transform, false, false, true);
	// コリジョン
	m_pCollision = CCollision::Create(this);

	// ポリゴンのパラメータの初期化
	m_transform.SetSize(Float2{ 150, 150 });

	// スプライトデータ
	m_sprite.SetColor(Float4{ 0.0f, 0.0f, 1.0f, 0.3f });

	// レイヤー
	m_enLayer = LAYER::FIELD;

	m_nChangeAreaType = 0;

	m_Hit = false;
}


//========================================
//
//	デストラクタ
//
//========================================
CStageChangeArea::~CStageChangeArea()
{
	// コリジョン
	m_pCollision->Destroy();
	//m_pRb->Destroy();
}


//========================================
//
//	更新処理
//
//========================================
void CStageChangeArea::Update()
{
	
}

//========================================
//
//	更新処理
//
//========================================
void CStageChangeArea::LateUpdate()
{

}

//========================================
//
//	描画処理
//
//========================================
void CStageChangeArea::Draw()
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
CStageChangeArea* CStageChangeArea::Create(Float3 pos, int nAreaType)
{
	CStageChangeArea *pStageChangeArea = CObjectManager::CreateObject<CStageChangeArea>(pos);
	pStageChangeArea->m_nChangeAreaType = nAreaType;
	if (nAreaType <= R)
	{
		pStageChangeArea->GetTransform()->SetSize(Float2{ 80, 800 });
	}
	else
	{
		pStageChangeArea->GetTransform()->SetSize(Float2{ 800, 80 });
	}

	return pStageChangeArea;
}

//========================================
//
//	消去
//
//========================================
void CStageChangeArea::Destroy()
{
	CObjectManager::DestroyObject(this);

}

//========================================
//
//	当たり判定
//
//========================================
void CStageChangeArea::OnCollision(CCollision *pCollision) 
{
	CObject* pObj = pCollision->GetObj();

	if (pObj->GetLayer() == LAYER::PLAYER)
	{
		if (FADE::GetNowFade()) return;
		if (m_Hit) return;

		switch (m_nChangeAreaType)
		{
		case L:
			m_nGotoChangeArea = R;
			CStageMaker::SubCurMapPosX();
			break;
		case R:
			m_nGotoChangeArea = L;
			CStageMaker::AddCurMapPosX();
			break;
		case T:
			m_nGotoChangeArea = B;
			CStageMaker::SubCurMapPosY();
			break;
		case B:
			m_nGotoChangeArea = T;
			CStageMaker::AddCurMapPosY();
			break;
		default:
			break;
		}

		CStageManager::SetNextStage(new CStageDebug());

		m_Hit = true;
	}
}
