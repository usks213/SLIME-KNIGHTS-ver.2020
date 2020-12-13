//==================================================================
//								Fire.h
//	マップの灯り
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//	
//	2020/07/09/06	ファイヤクラスの作成	
//
//===================================================================


//====== インクルード部 ======
#include "Fire.h"
#include "collision.h"
#include "animator.h"
#include "../DirectX11.h"
#include "objectMgr.h"
#include "animation.h"
#include "light.h"


#ifdef _WIN32
#include "../Sound.h"
#endif // _WIN32

//===== マクロ定義 =====
#define FIRE_SIZE_X		(41 * 0.65f)
#define FIRE_SIZE_Y		(52 * 0.65f)

//===== 静的メンバ =====
CTexture CFire::sm_textureFire;
CTexture CFire::sm_textureBottom;


//===== グローバル変数 =====



//========================================
//
//	コンストラクタ
//
//========================================
CFire::CFire()
{
	m_pCollision = CCollision::Create(this);
	m_pAnimator = CAnimator::Create(&m_sprite, this);

	// ポリゴンのパラメータの初期化
	m_transform.SetSize(Float2{ FIRE_SIZE_X * 4, FIRE_SIZE_Y * 4 });

	// スプライトデータ
	m_sprite.SetColorW(0.95f);

	// レイヤー
	m_enLayer = LAYER::MAP_OBJ;

	// アニメーション
	CAnimation::Create(m_pAnimator, "fire", (unsigned int)15);
	m_pAnimator->SetAnimation("fire", 6, 17, 1);

	m_pAnimator->SetCurAnimNo(rand() % 17);
}


//========================================
//
//	デストラクタ
//
//========================================
CFire::~CFire()
{
	m_pCollision->Destroy();
	m_pAnimator->Destroy();
}


//========================================
//
//	初期化
//
//========================================
void CFire::Init()
{

	// テクスチャのロード
	sm_textureFire.LoadTexture(FILE_PATH"object/fire4.tga");

}

//========================================
//
//	終了処理
//
//========================================
void CFire::Uninit()
{
	// テクスチャの解放
	sm_textureFire.UnloadTexture();
}

//========================================
//
//	更新処理
//
//========================================
void CFire::Update()
{


}

//========================================
//
//	描画処理
//
//========================================
void CFire::Draw()
{
	// 四角形の描画
	m_sprite.Draw(&m_transform, &sm_textureFire);

}

//========================================
//
//	生成
//
//========================================
void CFire::Create(Float3 pos)
{
	CFire* pFire = CObjectManager::CreateObject<CFire>(pos);

	CLight::Create(&pFire->m_transform, 4.7f);
}

//========================================
//
//	初期化
//
//========================================
void CFire::Destroy()
{
	CObjectManager::DestroyObject(this);
}


//========================================
//
//	コリジョン
//
//========================================
void CFire::OnCollision(CCollision *pCollision)
{
	CObject* pObj = pCollision->GetObj();
	
}


//========================================
//
//	アニメーター
//
//========================================
void CFire::OnAnimator(CAnimator *pAnimator)
{

}
