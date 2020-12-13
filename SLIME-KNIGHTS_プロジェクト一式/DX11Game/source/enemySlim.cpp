//==================================================================
//								enemySlim.cpp
//	スライム
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//
//	2020/08/19	スライムクラスの作成
//
//===================================================================


//====== インクルード部 ======
#include "enemySlim.h"
#include "../sprite.h"
#include "../texture.h"
#include "objectMgr.h"
#include "collision.h"
#include "rigidbody.h"
#include "animation.h"
#include "animator.h"
#include "effect.h"


#ifdef _WIN32
#include "../input.h"
#include "../Sound.h"
#else
#include "../controller.h"
#endif // _WIN32

//===== マクロ定義 =====
#define MAX_ENEMY_TEX_X (8)
#define MAX_ENEMY_TEX_Y (4)
#define ENEMYSPEED (10.0f)

//===== プロトタイプ宣言 =====

//===== グローバル変数 =====


//===== 静的メンバ =====


//========================================
//
//	コンストラクタ
//
//========================================
CEnemySlim::CEnemySlim()
{
	// エリアのサイズ
	m_pViewArea->GetTransform()->SetSize(Float2{ 500, 100 });
	m_pAttackArea->GetTransform()->SetSize(Float2{ 300, 100 });

	// アニメーション
	// 停止
	CAnimation::Create(m_pAnimator, "LeftWait",  4, 0, 1, 2, 3);
	CAnimation::Create(m_pAnimator, "RightWait", 4, 8, 9, 10, 11);
	// 歩行
	CAnimation::Create(m_pAnimator, "LeftMove",  4, 0, 1, 2, 3);
	CAnimation::Create(m_pAnimator, "RightMove", 4, 8, 9, 10, 11);
	//攻撃
	CAnimation::Create(m_pAnimator, "LeftAttack", 8, 16, 17, 18, 19, 20, 21, 22, 23);
	CAnimation::Create(m_pAnimator, "RightAttack",  8, 24, 25, 26, 27, 28, 29, 30, 31);

	// アニメーションのセット
	m_pAnimator->SetAnimation("RightWait", 15, MAX_ENEMY_TEX_X, MAX_ENEMY_TEX_Y);

	// キャラクターアクションデータ
	m_charaAction.SetActionData(this, 2, 16);

	// タイプ
	m_eType = ENEMY::SLIM;

}


//========================================
//
//	デストラクタ
//
//========================================
CEnemySlim::~CEnemySlim()
{

}


//========================================
//
//	更新
//
//========================================
void CEnemySlim::Update()
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
		if (x < 0)
		{
			m_charaAction.Left();
		}
		else
		{
			m_charaAction.Right();
		}

		m_nJumpInterval--;
		if (m_bAttack)
		{
			if (!m_pRigidbody->GetUseGravity())
			{
				if (m_nJumpInterval < 0)
				{
					m_charaAction.Jump();
					m_charaAction.Attack(4);
					m_nJumpInterval = 180;
					// サウンド
					CEnemy::sm_SE[ENEMY::SE_SLIME].Play(0.4f);
				}
			}
		}
	}
	else
	{
		switch (m_nMoveType)
		{
		case 0:
			m_charaAction.Right();
			break;
		case 1:
			m_charaAction.Left();
			break;
		case 2:
			// サウンド
			CEnemy::sm_SE[ENEMY::SE_SLIME].Play(0.4f);
			m_charaAction.Jump();
			m_charaAction.Attack(4);
			if (m_charaAction.GetRight())
			{
				m_nMoveType = 0;
			}
			else
			{
				m_nMoveType = 1;
			}
			break;
		default:
			break;
		}
	}

	// ターゲット
	m_pTargetPlayer = nullptr;
	m_bAttack = false;
}

