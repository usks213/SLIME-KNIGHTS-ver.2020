//==================================================================
//								block.h
//	GM21 フィールド用ブロック	
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//	
//	2020/07/12	ブロッククラス作成
//
//===================================================================


//====== インクルード部 ======
#include "block.h"
#include "collision.h"
#include "objectMgr.h"
#include "animation.h"
#include "rigidbody.h"

#include "../texture.h"

//===== マクロ定義 =====

//===== 静的メンバ =====


//===== 名前空間 =====


//========================================
//
//	コンストラクタ
//
//========================================
CBlock::CBlock()
{
	// コリジョン
	m_pRigidBody = CRigidbody::Create(&m_transform, true, false);
	m_pCollision = CCollision::Create(this, m_pRigidBody);


	// ポリゴンのパラメータの初期化
	m_transform;
	
	// スプライトデータ
	m_sprite;

	// レイヤー
	m_enLayer = LAYER::FIELD;


}


//========================================
//
//	デストラクタ
//
//========================================
CBlock::~CBlock()
{
	// コリジョン
	if(m_pCollision != nullptr)
		m_pCollision->Destroy();

	if (m_pRigidBody != nullptr)
		m_pRigidBody->Destroy();
}


//========================================
//
//	初期化
//
//========================================
void CBlock::Init()
{

}

//========================================
//
//	終了処理
//
//========================================
void CBlock::Uninit()
{

}

//========================================
//
//	更新処理
//
//========================================
void CBlock::Update()
{

}

//========================================
//
//	描画処理
//
//========================================
void CBlock::Draw()
{
	m_sprite.Draw(&m_transform, m_pTexture);
}


//========================================
//
//	生成
//
//========================================
CBlock* CBlock::Create(Float3 pos, CTexture* nTex, int nTexPos, int nSplitX, int nSplitY)
{
	CBlock *pBlock = CObjectManager::CreateObject<CBlock>(pos);

	// テクスチャ
	pBlock->m_pTexture = nTex;

	// テクスチャサイズ
	pBlock->m_sprite.SetTexSize(Float2{ 1.0f / nSplitX, 1.0f / nSplitY });

	// テクスチャ座標
	pBlock->m_sprite.SetTexPos(Float2{ nTexPos % nSplitX * pBlock->m_sprite.GetTexSize().x,
										nTexPos / nSplitX * pBlock->m_sprite.GetTexSize().y });

	return pBlock;
}

//========================================
//
//	消去
//
//========================================
void CBlock::Destroy()
{
	CObjectManager::DestroyObject(this);

}