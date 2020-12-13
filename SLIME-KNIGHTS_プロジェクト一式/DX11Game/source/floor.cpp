//==================================================================
//								floor.cpp
//	フィールド用床	
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//	
//	2020/08/29	フロアクラスの作成
//
//===================================================================


//====== インクルード部 ======
#include "floor.h"
#include "collision.h"
#include "objectMgr.h"
#include "animation.h"
#include "rigidbody.h"
#include "character.h"

#include "../texture.h"

//===== マクロ定義 =====

//===== 静的メンバ =====
CTexture CFloor::sm_texture;


//===== 名前空間 =====


//========================================
//
//	コンストラクタ
//
//========================================
CFloor::CFloor()
{
	// コリジョン
	m_pRigidBody = CRigidbody::Create(&m_transform, true, false, true);
	m_pCollision = CCollision::Create(this, m_pRigidBody);


	// ポリゴンのパラメータの初期化
	m_transform.SetSize(Float2{ DEFAULT_OBJECT_SIZE, DEFAULT_OBJECT_SIZE / 2 });

	// スプライトデータ
	m_sprite;

	// レイヤー
	m_enLayer = LAYER::FLOOR;


}


//========================================
//
//	デストラクタ
//
//========================================
CFloor::~CFloor()
{
	// コリジョン
	if (m_pCollision != nullptr)
		m_pCollision->Destroy();

	if (m_pRigidBody != nullptr)
		m_pRigidBody->Destroy();
}


//========================================
//
//	初期化
//
//========================================
void CFloor::Init()
{
	// テクスチャのロード
	sm_texture.LoadTexture(FILE_PATH"map/floor.tga");
}

//========================================
//
//	終了処理
//
//========================================
void CFloor::Uninit()
{
	// テクスチャの解放
	sm_texture.UnloadTexture();
}

//========================================
//
//	更新処理
//
//========================================
void CFloor::Update()
{

}

//========================================
//
//	描画処理
//
//========================================
void CFloor::Draw()
{
	m_sprite.Draw(&m_transform, &sm_texture);
}


//========================================
//
//	生成
//
//========================================
CFloor* CFloor::Create(Float3 pos)
{
	pos.y -= 24;
	CFloor *pBlock = CObjectManager::CreateObject<CFloor>(pos);

	return pBlock;
}

//========================================
//
//	消去
//
//========================================
void CFloor::Destroy()
{
	CObjectManager::DestroyObject(this);

}

//========================================
//
//	当たり判定
//
//========================================
void CFloor::OnCollision(CCollision *pCollision)
{
	CObject *pObj = pCollision->GetObj();

	// キャラクターのとき
	if (pObj->GetLayer() == LAYER::PLAYER || pObj->GetLayer() == LAYER::ENEMY)
	{
		CCharacter *pChara = static_cast<CCharacter*>(pObj);

		// スルー
		if (pChara->GetFloorThrough()) return;

		// 上からぶつかってきたとき
		if (m_pRigidBody->GetHitDir() == DIRECTION::DOWN)
		{
			if (pChara->GetRb()->GetForce().y >= 0)
			{
				Float3 pos = m_transform.GetPos();
				pos.x = pObj->GetTransform()->GetPos().x;
				pos.y -= m_transform.GetSize().y / 2 + pObj->GetTransform()->GetSize().y / 2;
				pObj->GetTransform()->SetPos(pos);

				pChara->GetRb()->SetUseGravity(false);
				pChara->GetRb()->SetForceY(0);
			}
		}
	}
}