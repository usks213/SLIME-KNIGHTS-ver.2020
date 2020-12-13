//==================================================================
//								bullet.h
//	GM21 バレット	
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//	
//	2020/07/17	バレットクラス作成
//
//===================================================================


//====== インクルード部 ======
#include "bullet.h"
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
CTexture CBullet::sm_texture[BULLET::MAX_BULLET_TYPE];


//===== 名前空間 =====


//========================================
//
//	コンストラクタ
//
//========================================
CBullet::CBullet()
{
	// リジッドボディ
	m_pRigidbody = CRigidbody::Create(&m_transform, false, false);
	m_pRigidbody->SetDragX(0);
	m_pRigidbody->SetGravityForce(0.0f);
	m_pRigidbody->SetTrigger(true);

	// コリジョン
	m_pCollision = CCollision::Create(this, m_pRigidbody);

	// ポリゴンのパラメータの初期化
	m_transform.SetSize(Float2{20, 20});

	// スプライトデータ
	m_sprite;

	// レイヤー
	m_enLayer = LAYER::ENEMYBULLET;

	// タイプ
	m_eType = BULLET::BLUE;
}


//========================================
//
//	デストラクタ
//
//========================================
CBullet::~CBullet()
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
void CBullet::Init()
{
	// テクスチャ
	sm_texture[BULLET::BLUE].LoadTexture(FILE_PATH"bullet/bullet_blue.tga");
	sm_texture[BULLET::GREEN].LoadTexture(FILE_PATH"bullet/bullet_green.tga");
	sm_texture[BULLET::PURPLE].LoadTexture(FILE_PATH"bullet/bullet_purple.tga");
	sm_texture[BULLET::ARROW].LoadTexture(FILE_PATH"bullet/arrow.tga");
}

//========================================
//
//	終了処理
//
//========================================
void CBullet::Uninit()
{
	// テクスチャの解放
	for (int i = 0; i < BULLET::MAX_BULLET_TYPE; i++)
	{
		sm_texture[i].UnloadTexture();
	}
}

//========================================
//
//	更新処理
//
//========================================
void CBullet::Update()
{

}

//========================================
//
//	描画処理
//
//========================================
void CBullet::Draw()
{
	// 加算合成
//	glBlendFunc(GL_ONE, GL_ONE);
	//if(m_eType != BULLET::ARROW)
	CDirectX11::SetBlendState(EBlendState::BS_ADDITIVE);

	// 四角形の描画
	CTransform trans = m_transform;
	trans.SetSize(Float2{ 40, 40 });
	m_sprite.Draw(&trans, &sm_texture[m_eType]);

	// アルファ合成
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	CDirectX11::SetBlendState(EBlendState::BS_ALPHABLEND);

}

//========================================
//
//	生成
//
//========================================
CBullet* CBullet::Create(Float3 pos, Float3 force, CStatus *pStatus, BULLET::EBULLET_TYPE eType)
{
	CBullet *pBullet = CObjectManager::CreateObject<CBullet>(pos);

	pBullet->m_pRigidbody->SetForce(force);

	Float3 vec = Normalize(force);
	Float3 right = Float3{ 1.0f, 0.0f, 0.0f };
	float rad = acosf(Dot(right, vec));
	float angle = rad / 3.1415f * 180.0f;
	float cross = Cross2D(right, vec);

	// ０～１８０
	if (cross >= 0)
	{
		pBullet->m_transform.SetAngle(-(angle + 90.0f + 45.0f));
	}
	// １８０～３６０
	else
	{
		pBullet->m_transform.SetAngle(angle - 90 - 45.0f);
	}

	pBullet->m_pParentStatus = *pStatus;
	pBullet->m_eType = eType;

	switch (eType)
	{
	case BULLET::BLUE:
		break;
	case BULLET::GREEN:
		break;
	case BULLET::PURPLE:
		break;
	case BULLET::ARROW:
		break;
	default:
		break;
	}

	return pBullet;
}

//========================================
//
//	消去
//
//========================================
void CBullet::Destroy()
{
	CObjectManager::DestroyObject(this);

}

//========================================
//
//	消去
//
//========================================
void CBullet::OnCollision(CCollision *pCollision) 
{
	CObject* pObj = pCollision->GetObj();

	if (pObj->GetLayer() == LAYER::PLAYER)
	{
		//CEffect::Create(EFFECT::EXPLOSION, m_pos);
		CObjectManager::DestroyObject(this);
	}
	else if(pObj->GetLayer() == LAYER::FIELD)
	{
		this->Destroy();
	}

	return;
}