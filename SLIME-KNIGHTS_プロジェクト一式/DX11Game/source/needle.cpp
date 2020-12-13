//==================================================================
//								needle.h
//	マップの針	
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//	
//	2020/09/06	ニードルクラスの作成
//
//===================================================================


//====== インクルード部 ======
#include "needle.h"
#include "collision.h"
#include "objectMgr.h"
#include "rigidbody.h"

#include "effect.h"

#include "../texture.h"
#include "../sprite.h"

#ifdef _WIN64
#include "../DirectX11.h"

#endif // _WIN64

//===== マクロ定義 =====


//===== 静的メンバ =====
CTexture CNeedl::sm_texture;


//===== 名前空間 =====


//========================================
//
//	コンストラクタ
//
//========================================
CNeedl::CNeedl()
{
	// リジッドボディ
	m_pRigidbody = CRigidbody::Create(&m_transform, true);

	// コリジョン
	m_pCollision = CCollision::Create(this, m_pRigidbody);

	// ポリゴンのパラメータの初期化
	m_transform;

	// スプライトデータ
	m_sprite;

	// レイヤー
	m_enLayer = LAYER::ENEMYBULLET;


}


//========================================
//
//	デストラクタ
//
//========================================
CNeedl::~CNeedl()
{
	// コリジョン
	m_pCollision->Destroy();
	m_pRigidbody->Destroy();
}


//========================================
//
//	初期化
//
//========================================
void CNeedl::Init()
{
	// テクスチャ
	sm_texture.LoadTexture(FILE_PATH"object/needle.tga");
}

//========================================
//
//	終了処理
//
//========================================
void CNeedl::Uninit()
{
	// テクスチャの解放
	sm_texture.UnloadTexture();
}

//========================================
//
//	更新処理
//
//========================================
void CNeedl::Update()
{

}

//========================================
//
//	描画処理
//
//========================================
void CNeedl::Draw()
{
	// 加算合成
//	glBlendFunc(GL_ONE, GL_ONE);
	//CDirectX11::SetBlendState(EBlendState::BS_ADDITIVE);


	// 四角形の描画
	m_sprite.Draw(&m_transform, &sm_texture);

	// アルファ合成
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//CDirectX11::SetBlendState(EBlendState::BS_ALPHABLEND);

	m_bStop = false;
}

//========================================
//
//	生成
//
//========================================
CNeedl* CNeedl::Create(Float3 pos)
{
	CNeedl *pBullet = CObjectManager::CreateObject<CNeedl>(pos);

	return pBullet;
}

//========================================
//
//	消去
//
//========================================
void CNeedl::Destroy()
{
	CObjectManager::DestroyObject(this);

}

//========================================
//
//	消去
//
//========================================
void CNeedl::OnCollision(CCollision *pCollision) 
{
	CObject* pObj = pCollision->GetObj();

	if (pObj->GetLayer() == LAYER::PLAYER)
	{
	}

	return;
}