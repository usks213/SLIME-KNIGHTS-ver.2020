//==================================================================
//								enemyBow.h
//	弓エネミー
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//
//	2020/09/06	弓エネミー
//
//===================================================================


//====== インクルード部 ======
#include "enemyBow.h"
#include "../sprite.h"
#include "../texture.h"
#include "objectMgr.h"
#include "collision.h"
#include "rigidbody.h"
#include "animation.h"
#include "animator.h"
#include "effect.h"
#include "attackBase.h"
#include "bullet.h"

#ifdef _WIN32
#include "../input.h"
#include "../Sound.h"
#else
#include "../controller.h"
#endif // _WIN32

//===== マクロ定義 =====
#define MAX_ENEMY_TEX_X (2)
#define MAX_ENEMY_TEX_Y (2)
#define ENEMYSPEED (10.0f)

#define SHOT_INTERVAL (300)
#define SHOT_FORCE	(8)


//===== プロトタイプ宣言 =====


//===== グローバル変数 =====


//===== 静的メンバ =====


//========================================
//
//	コンストラクタ
//
//========================================
CEnemyBow::CEnemyBow()
{
	// オブジェクトのサイズ
	m_transform.SetSize(Float2{ 96, 72 });

	//m_pRigidbody->SetMass(1.0f);
	m_pRigidbody->SetSolid(true);

	// エリアのサイズ
	m_pViewArea->GetTransform()->SetSize(Float2{ 3000, 3000 });
	m_pAttackArea->GetTransform()->SetSize(Float2{ 2500, 2500 });

	// アニメーション
	// 停止
	CAnimation::Create(m_pAnimator, "LeftWait",  2, 0, 1);
	CAnimation::Create(m_pAnimator, "RightWait", 2, 2, 3);
	// 歩行
	CAnimation::Create(m_pAnimator, "LeftMove", 2, 0, 1);
	CAnimation::Create(m_pAnimator, "RightMove", 2, 2, 3);

	// アニメーションのセット
	m_pAnimator->SetAnimation("RightWait", 15, MAX_ENEMY_TEX_X, MAX_ENEMY_TEX_Y);

	// キャラクターアクションデータ
	m_charaAction.SetActionData(this, 0, 0);

	// タイプ
	m_eType = ENEMY::BOW;

	// ウェポン
	m_pWeapon = CWeapon::Create(&m_transform, WEAPON::BOW);
	m_pWeapon->SetOffSetX(0);
}


//========================================
//
//	デストラクタ
//
//========================================
CEnemyBow::~CEnemyBow()
{
	// ウェポン
	m_pWeapon->Destroy();
}


//========================================
//
//	更新
//
//========================================
void CEnemyBow::Update()
{
	m_nMoveCnt--;
	if (m_nMoveCnt < 0)
	{
		m_nMoveType = rand() % 3;
		m_nMoveCnt = 240 + rand() % 120;
	}

	// ターゲットがいる時
	if (m_pTargetPlayer)
	{
		float x = m_pTargetPlayer->GetPos().x - m_transform.GetPos().x;
		float y = m_pTargetPlayer->GetPos().y - m_transform.GetPos().y;

		if (x < 0)
		{
			m_charaAction.Left();
			m_pWeapon->SetLeft();
			m_transform.SetDir(Float3{ -1.0f, 0.0f, 0.0f});
		}
		else
		{
			m_charaAction.Right();
			m_pWeapon->SetRight();
			m_transform.SetDir(Float3{ 1.0f, 0.0f, 0.0f });
		}

		m_nMoveInterval--;

		// 攻撃
		//if (m_bAttack)
		{
			if (m_nMoveInterval < 0)
			{
				//弾の生成
				Float3 force = Normalize(Float3{ x, y, 0 });
				force.x *= SHOT_FORCE;
				force.y *= SHOT_FORCE;
				CBullet::Create(m_transform.GetPos(), force, &m_status, BULLET::ARROW);
				m_nMoveInterval = SHOT_INTERVAL;
				// サウンド
				CEnemy::sm_SE[ENEMY::SE_ONE_SHOT].Play(0.2f);
			}
		}

		m_pWeapon->SetTargetAngle(m_pTargetPlayer->GetPos());
	}
	else
	{
		switch (m_nMoveType)
		{
		case 0:
			m_charaAction.Right();
			m_pWeapon->SetRight();
			break;
		case 1:
			m_charaAction.Left();
			m_pWeapon->SetLeft();
			break;
		}
	}

	// ターゲット
	m_pTargetPlayer = nullptr;
	m_bAttack = false;

}

