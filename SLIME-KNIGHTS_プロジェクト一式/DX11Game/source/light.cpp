//==================================================================
//								light.h
//	マップのライト	
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//	
//	2020/09/06	ライトクラスの作成
//
//===================================================================


//====== インクルード部 ======
#include "light.h"

#include "collision.h"
#include "objectMgr.h"


#include "../texture.h"
#include "../sprite.h"

#ifdef _WIN64
#include "../DirectX11.h"

#endif // _WIN64

//===== マクロ定義 =====



//===== 名前空間 =====


CTexture CLight::sm_texture;
bool CLight::m_bBoss = false;


//========================================
//
//	コンストラクタ
//
//========================================
CLight::CLight()
{
	// コリジョン
	m_pCollision = CCollision::Create(this, nullptr);

	// ポリゴンのパラメータの初期化
	m_transform.SetSize(Float2{ 500, 500 });

	// スプライトデータ
	m_sprite.SetColor(Float4{ 0.74f, 0.25f, 0.01f, 0.6f });
	if (m_bBoss)
	{
		m_sprite.SetColor(Float4{ 0.4f, 0.02f, 0.53f, 0.6f });
	}

	// レイヤー
	m_enLayer = LAYER::EFFECT;

	// 親
	m_pParent = nullptr;

}


//========================================
//
//	デストラクタ
//
//========================================
CLight::~CLight()
{
	// コリジョン
	m_pCollision->Destroy();
}

//========================================
//
//	初期化
//
//========================================
void CLight::Init()
{
	// テクスチャのロード
	sm_texture.LoadTexture(FILE_PATH"object/light.tga");

}

//========================================
//
//	終了処理
//
//========================================
void CLight::Uninit()
{
	// テクスチャの解放
	sm_texture.UnloadTexture();
}

//========================================
//
//	更新処理
//
//========================================
void CLight::Update()
{
	
}

//========================================
//
//	更新処理
//
//========================================
void CLight::LateUpdate()
{
	if (m_pParent == nullptr) return;
	Float3 pos = m_pParent->GetPos();

	m_transform.SetPos(pos);

	// 大きさを変える
	float size = m_transform.GetSizeX();
	if (m_fBaseSize * 1.07f < size)
	{
		m_bExpansion = false;
	}
	if (m_fBaseSize * 0.93f > size)
	{
		m_bExpansion = true;
	}

	if (m_bExpansion)
	{
		size *= 1.004f;
	}
	else
	{
		size *= 0.996f;
	}

	m_transform.SetSize(Float2{ size, size });
}

//========================================
//
//	描画処理
//
//========================================
void CLight::Draw()
{
	// 加算合成
//	glBlendFunc(GL_ONE, GL_ONE);
	CDirectX11::SetBlendState(EBlendState::BS_ADDITIVE);

	// 四角形の描画
	m_sprite.Draw(&m_transform, &sm_texture);

	// アルファ合成
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	CDirectX11::SetBlendState(EBlendState::BS_ALPHABLEND);

}

//========================================
//
//	生成
//
//========================================
CLight* CLight::Create(CTransform *pParent, float fScale)
{
	CLight *pLight = CObjectManager::CreateObject<CLight>();

	pLight->m_pParent = pParent;
	pLight->m_transform = *pParent;
	Float2 size = pLight->m_transform.GetSize();
	size.x *= fScale;
	size.y = size.x;
	pLight->m_fBaseSize = size.x;
	pLight->m_transform.SetSize(size);

	return pLight;
}

//========================================
//
//	消去
//
//========================================
void CLight::Destroy()
{
	CObjectManager::DestroyObject(this);

}

//========================================
//
//	当たり判定
//
//========================================
void CLight::OnCollision(CCollision *pCollision) 
{
	CObject* pObj = pCollision->GetObj();

	if (pObj->GetLayer() == LAYER::PLAYER)
	{
	}
}
