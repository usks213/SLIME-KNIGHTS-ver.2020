//==================================================================
//								attackBase.h
//	攻撃	
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//	
//	2020/08/03	攻撃のクラス
//
//===================================================================


//====== インクルード部 ======
#include "attackBase.h"

#include "collision.h"
#include "objectMgr.h"
#include "rigidbody.h"
#include "animation.h"
#include "animator.h"

#include "effect.h"

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
CAttackBase::CAttackBase()
{
	// コリジョン
	m_pCollision = CCollision::Create(this, nullptr);
	// アニメーター
	m_pAnimator = CAnimator::Create(&m_sprite, this);

	// ポリゴンのパラメータの初期化
	m_transform.SetSize(Float2{ 100, 100 });

	// スプライトデータ
	m_sprite.SetColor(Float4{ 1.0f, 0.0f, 0.0f, 0.1f });

	// レイヤー
	m_enLayer = LAYER::PLAYERATTACK;

	// 座標更新データ
	m_fOffSetX = 0.0f;
	m_pParentStatus = nullptr;
	m_pParentTrans = nullptr;
}


//========================================
//
//	デストラクタ
//
//========================================
CAttackBase::~CAttackBase()
{
	// コリジョン
	m_pCollision->Destroy();
	m_pAnimator->Destroy();
}


//========================================
//
//	更新処理
//
//========================================
void CAttackBase::Update()
{
	if (m_pParentTrans == nullptr) return;
	Float3 pos = m_pParentTrans->GetPos();
	pos.x += m_fOffSetX;

	m_transform.SetPos(pos);
}

//========================================
//
//	更新処理
//
//========================================
void CAttackBase::LateUpdate()
{
	if (m_pParentTrans == nullptr) return;
	Float3 pos = m_pParentTrans->GetPos();
	pos.x += m_fOffSetX;

	m_transform.SetPos(pos);
}

//========================================
//
//	描画処理
//
//========================================
void CAttackBase::Draw()
{
	// 加算合成
//	glBlendFunc(GL_ONE, GL_ONE);
	//CDirectX11::SetBlendState(EBlendState::BS_ADDITIVE);

	// 四角形の描画
	if(GetDebugFlag())
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
CAttackBase* CAttackBase::Create(CStatus *pStatus, CTransform *pParent, float fOffSet)
{
	CAttackBase *pAttackBase = CObjectManager::CreateObject<CAttackBase>();

	pAttackBase->m_pParentTrans = pParent;

	pAttackBase->m_pParentStatus = pStatus;

	pAttackBase->m_fOffSetX = fOffSet;

	return pAttackBase;
}

//========================================
//
//	消去
//
//========================================
void CAttackBase::Destroy()
{
	CObjectManager::DestroyObject(this);

}

//========================================
//
//	当たり判定
//
//========================================
void CAttackBase::OnCollision(CCollision *pCollision) 
{
	CObject* pObj = pCollision->GetObj();

	if (pObj->GetLayer() == LAYER::ENEMY)
	{
		//CEffect::Create(EFFECT::EXPLOSION, m_pos);
		//CObjectManager::DestroyObject(this);
	}
	
}

//========================================
//
//	当たり判定
//
//========================================
void CAttackBase::OnAnimator(CAnimator *pAnim)
{
	CAnimation *pAn = pAnim->GetCurrentAnimation();
	if (pAn == nullptr) return;

	if (pAn->GetName() == "a")
	{

	}
}