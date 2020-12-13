//==================================================================
//								character.h
//	GM21 
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//
//	2020/07/03	キャラクタークラス作成	
//
//
//===================================================================


//====== インクルード部 ======
#include "character.h"
#include "collision.h"
#include "animator.h"
#include "rigidbody.h"

//========================================
//
//	コンストラクタ
//
//========================================
CCharacter::CCharacter()
{
	// アニメーター
	m_pAnimator = CAnimator::Create(&m_sprite, this);

	m_pRigidbody = CRigidbody::Create(&m_transform);

	m_pCollision = CCollision::Create(this, m_pRigidbody);

	//m_charaAction.SetActionData(this, 5, 10);
	m_bFloorThrough = false;
}


//========================================
//
//	デストラクタ
//
//========================================
CCharacter::~CCharacter()
{
	m_pCollision->Destroy();
	m_pAnimator->Destroy();
	m_pRigidbody->Destroy();
}
