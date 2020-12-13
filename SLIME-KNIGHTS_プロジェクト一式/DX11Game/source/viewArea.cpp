//==================================================================
//								viewArea.h
//	視野エリア	
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//	
//	2020/08/18	視野エリアクラスの作成
//
//===================================================================


//====== インクルード部 ======
#include "viewArea.h"

#include "collision.h"
#include "objectMgr.h"
#include "enemy.h"

#include "../texture.h"
#include "../sprite.h"

#ifdef _WIN64
#include "../DirectX11.h"

#endif // _WIN64

//===== マクロ定義 =====



//===== 名前空間 =====


//========================================
//
//	コンストラクタ
//
//========================================
CViewArea::CViewArea()
{
	// コリジョン
	m_pCollision = CCollision::Create(this, nullptr);

	// ポリゴンのパラメータの初期化
	m_transform.SetSize(Float2{ 500, 500 });

	// スプライトデータ
	m_sprite.SetColor(Float4{ 0.0f, 1.0f, 0.0f, 0.08f });

	// レイヤー
	m_enLayer = LAYER::MAX_LAYER;

	// エネミーデータ
	m_pParentEnemy = nullptr;

}


//========================================
//
//	デストラクタ
//
//========================================
CViewArea::~CViewArea()
{
	// コリジョン
	m_pCollision->Destroy();
}


//========================================
//
//	更新処理
//
//========================================
void CViewArea::Update()
{
	
}

//========================================
//
//	更新処理
//
//========================================
void CViewArea::LateUpdate()
{
	if (m_pParentEnemy == nullptr) return;
	Float3 pos = m_pParentEnemy->GetTransform()->GetPos();

	m_transform.SetPos(pos);
}

//========================================
//
//	描画処理
//
//========================================
void CViewArea::Draw()
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
CViewArea* CViewArea::Create(CEnemy *pParent)
{
	CViewArea *pViewArea = CObjectManager::CreateObject<CViewArea>();

	pViewArea->m_pParentEnemy = pParent;

	return pViewArea;
}

//========================================
//
//	消去
//
//========================================
void CViewArea::Destroy()
{
	CObjectManager::DestroyObject(this);

}

//========================================
//
//	当たり判定
//
//========================================
void CViewArea::OnCollision(CCollision *pCollision) 
{
	CObject* pObj = pCollision->GetObj();

	if (pObj->GetLayer() == LAYER::PLAYER)
	{
		m_pParentEnemy->SetTarget(pObj->GetTransform());
	}
}
