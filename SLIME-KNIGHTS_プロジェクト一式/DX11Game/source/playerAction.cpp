//==================================================================
//								playerAction.cpp
//	 
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//	
//	2020/08/13	プレイヤーアクションクラスの作成
//
//===================================================================


//====== インクルード部 ======
#include "playerAction.h"
#include "collision.h"
#include "animator.h"
#include "rigidbody.h"
#include "animation.h"
#include "objectMgr.h"
#include "character.h"
#include "attackBase.h"
#include "effect.h"
#include "experience.h"
#include "camera.h"
#include "player.h"

#ifdef _WIN32
#include "../Sound.h"

#endif // _WIN32


//===== マクロ定義 =====
#define KNOCKBACK_FORCEX (12)
#define KNOCKBACK_FORCEY (12)
#define DEFAULT_ANIM_SPEED (12)
#define ATTACK_OFFSET_X (96)

#define ATTACK_INTERVAL (12)

//===== 静的関数 =====


//===== グローバル変数 =====
static CSound g_SE_Attack;


//========================================
//
//	コンストラクタ
//
//========================================
CPlayerAction::CPlayerAction()
{
	m_bAttack = false;
	m_nAttackAnimSpeed = 10;
	m_pPlayer = nullptr;
	m_bDown = false;
	m_nAttackInterval = 0;
	m_nFlashCnt = 0;
}

//========================================
//
//	デストラクタ
//
//========================================
CPlayerAction::~CPlayerAction()
{

}


//========================================
//
//	初期化
//
//========================================
void CPlayerAction::Init()
{
	g_SE_Attack.Load(FILE_PATH"sound/player/Dagger woosh 5.wav");
	
}

//========================================
//
//	終了処理
//
//========================================
void CPlayerAction::Uninit()
{

}


//========================================
//
//	更新
//
//========================================
void CPlayerAction::Update()
{
	// プレイヤーの手の動き
	if (m_bRight)
	{
		// アニメーション
		if (m_bDown)
		{
			m_pPlayer->GetAttackAnimator()->SetAnimation("RightAttackUp", m_nAttackAnimSpeed);
		}
		else
		{
			m_pPlayer->GetAttackAnimator()->SetAnimation("RightAttackDown", m_nAttackAnimSpeed);
		}
		// アタックエリアの座標
		if(m_pAttackBase != nullptr)
			m_pAttackBase->SetOffSetX(ATTACK_OFFSET_X);
	}
	else
	{
		if (m_bDown)
		{
			m_pPlayer->GetAttackAnimator()->SetAnimation("LeftAttackUp", m_nAttackAnimSpeed);
		}
		else
		{
			m_pPlayer->GetAttackAnimator()->SetAnimation("LeftAttackDown", m_nAttackAnimSpeed);
		}
		// アタックエリアの座標
		if(m_pAttackBase != nullptr)
			m_pAttackBase->SetOffSetX(-ATTACK_OFFSET_X);
	}
	// ウェポンの位置
	m_pPlayer->GetMainWeapon()->SetPos(m_bRight, m_bDown);

	// ダメージ
	if (m_eCurAction == DAMAGE || m_pChara->GetStatus()->GetInvincible())
	{
		m_nFlashCnt++;
		if (m_nFlashCnt % 4 == 0)
		{
			m_pChara->GetSprite()->SetColor(Float4{1, 1, 1, 0});
		}
		else
		{
			m_pChara->GetSprite()->SetColor(Float4{ 1, 1, 1, 1 });
		}

		// 受け身の終了
		if (fabsf(m_pChara->GetRb()->GetForce().x) < 2.0f || !m_pChara->GetRb()->GetUseGravity())
		{
			// 状態遷移
			m_eCurAction = WAIT;
			m_pChara->GetRb()->SetDragX(1.0f);
		}
	}
	else
	{
		m_pChara->GetSprite()->SetColor(Float4{ 1, 1, 1, 1 });
		m_nFlashCnt = 0;
	}

	if (m_eCurAction == JUMP)
	{
		// ジャンプの最大点までいったら
		if (m_pChara->GetRb()->GetForce().y > 0.0f)
		{
			// 右か左か
			if (m_bRight)
			{
				// アニメーション
				m_pChara->GetAnim()->SetAnimation("RightFall", m_nAnimSpeed);
			}
			else
			{
				// アニメーション
				m_pChara->GetAnim()->SetAnimation("LeftFall", m_nAnimSpeed);
			}
		}

		// 地面に着いたら
		if(!m_pChara->GetRb()->GetUseGravity())
		{
			m_eCurAction = MOVE;
		}
	}


	// ヒットストップ
	if (m_pAttackBase)
	{
		if (m_pAttackBase->GetStop())
		{
			m_pChara->SetStop(true);
		}
	}

	if (m_pChara->GetStop())
	{
		m_pChara->GetAnim()->SetStop(true);
		m_pChara->GetRb()->SetStop(true);
		// プレイヤー
		m_pPlayer->GetAttackAnimator()->SetStop(true);
		m_pPlayer->GetMainWeapon()->SetStop(true);

		if (m_nHitStopCnt < 0)
			m_nHitStopCnt = HIT_STOP_FRAME;

		m_nHitStopCnt--;
		if (m_nHitStopCnt < 0)
		{
			m_pChara->SetStop(false);
			m_pChara->GetAnim()->SetStop(false);
			m_pChara->GetRb()->SetStop(false);
			m_pChara->GetStatus()->SetStop(false);
			// プレイヤー
			m_pPlayer->GetAttackAnimator()->SetStop(false);
			m_pPlayer->GetMainWeapon()->SetStop(false);
			m_bAttack = true;

			if(m_pAttackBase)
				m_pAttackBase->SetStop(false);
		}
	}


	// 攻撃間隔
	if (!m_bAttack)
	{
		if(m_nAttackInterval >= 0)
			m_nAttackInterval--;
	}

}


//========================================
//
//	ソード攻撃
//
//========================================
void CPlayerAction::Attack(int nAnimSpeed)
{
	if (m_bAttack || m_nAttackInterval > 0) return;

	if (m_eCurAction == WAIT || m_eCurAction == MOVE || m_eCurAction == JUMP)
	{
		// 攻撃スピード
		m_nAttackAnimSpeed = nAnimSpeed;

		// 右か左か
		if (m_bRight)
		{
			// 攻撃エリア生成
			m_pAttackBase = CAttackBase::Create(m_pChara->GetStatus(), m_pChara->GetTransform(), ATTACK_OFFSET_X);
			m_pAttackBase->GetTransform()->SetDir(Float3{ 1.0f, 0.0f, 0.0f });
			m_pAttackBase->GetTransform()->SetSize(Float2{ 150, 150 });
			m_pAttackBase->SetLayer(LAYER::PLAYERATTACK);
			// エフェクト
			Float3 pos = m_pChara->GetTransform()->GetPos();
			pos.x += ATTACK_OFFSET_X;
			CEffect::Create(EFFECT::SWORD_R, pos);
		}
		else
		{
			// 攻撃エリア生成
			m_pAttackBase = CAttackBase::Create(m_pChara->GetStatus(), m_pChara->GetTransform(), -ATTACK_OFFSET_X);
			m_pAttackBase->GetTransform()->SetDir(Float3{ -1.0f, 0.0f, 0.0f });
			m_pAttackBase->GetTransform()->SetSize(Float2{150, 150});
			m_pAttackBase->SetLayer(LAYER::PLAYERATTACK);
			// エフェクト
			Float3 pos = m_pChara->GetTransform()->GetPos();
			pos.x -= ATTACK_OFFSET_X;
			CEffect::Create(EFFECT::SWORD_L, pos);
		}

		// ウェポン
		m_pPlayer->GetMainWeapon()->StartMove(m_nAttackAnimSpeed * 3, m_bRight, m_bDown);

		// 状態
		m_bAttack = true;
		// アニメーション再生
		m_pPlayer->GetAttackAnimator()->SetStop(false);
		// 画面揺れ
		//CCamera::SetCameraShake(1);
		// サウンド
		g_SE_Attack.Play();

	}
}

//========================================
//
//	ブーメラン攻撃
//
//========================================
void CPlayerAction::Attack(int nAnimSpeed, CTransform* pTrans)
{
	if (m_bAttack || m_nAttackInterval > 0) return;

	if (m_eCurAction == WAIT || m_eCurAction == MOVE || m_eCurAction == JUMP)
	{
		// 攻撃スピード
		m_nAttackAnimSpeed = nAnimSpeed;

		// 右か左か
		if (m_bRight)
		{
			// 攻撃エリア生成
			m_pAttackBase = CAttackBase::Create(m_pChara->GetStatus(), pTrans, ATTACK_OFFSET_X);
			m_pAttackBase->GetTransform()->SetDir(Float3{ 1.0f, 0.0f, 0.0f });
			m_pAttackBase->GetTransform()->SetSize(Float2{ 150, 150 });
			m_pAttackBase->SetLayer(LAYER::PLAYERATTACK);
			// エフェクト
			Float3 pos = m_pChara->GetTransform()->GetPos();
			pos.x += ATTACK_OFFSET_X;
			CEffect::Create(EFFECT::SWORD_R, pos);
		}
		else
		{
			// 攻撃エリア生成
			m_pAttackBase = CAttackBase::Create(m_pChara->GetStatus(), pTrans, -ATTACK_OFFSET_X);
			m_pAttackBase->GetTransform()->SetDir(Float3{ -1.0f, 0.0f, 0.0f });
			m_pAttackBase->GetTransform()->SetSize(Float2{ 150, 150 });
			m_pAttackBase->SetLayer(LAYER::PLAYERATTACK);
			// エフェクト
			Float3 pos = m_pChara->GetTransform()->GetPos();
			pos.x -= ATTACK_OFFSET_X;
			CEffect::Create(EFFECT::SWORD_L, pos);
		}

		// ウェポン
		m_pPlayer->GetMainWeapon()->SetPos(m_pPlayer->GetTransform()->GetPos());
		m_pPlayer->GetMainWeapon()->StartMove(m_nAttackAnimSpeed * 3, m_bRight, m_bDown);

		// 状態
		m_bAttack = true;
		// アニメーション再生
		m_pPlayer->GetAttackAnimator()->SetStop(false);
		// 画面揺れ
		//CCamera::SetCameraShake(1);
		// サウンド
		g_SE_Attack.Play();

	}
}



//========================================
//
//	アニメーション終了時に呼び出す
//
//========================================
void CPlayerAction::OnAnimatorAction(CAnimator *pAnim)
{
	// 終了したアニメーションの名前で分岐
	if (pAnim->GetCurrentAnimation()->GetName() == "RightAttackDown" || pAnim->GetCurrentAnimation()->GetName() == "LeftAttackDown" ||
		pAnim->GetCurrentAnimation()->GetName() == "RightAttackUp"   || pAnim->GetCurrentAnimation()->GetName() == "LeftAttackUp")
	{
		if (m_bAttack)
		{
			// 攻撃エリアを消す
			if (m_pAttackBase != nullptr)
			{
				m_pAttackBase->Destroy();
				m_pAttackBase = nullptr;
			}
			// 状態遷移
			m_bAttack = false;
			m_bDown ^= 1;

			// 攻撃速度のインターバル
			float speed = (m_pChara->GetStatus()->GetAttackSpeed() / 100.0f);
			m_nAttackInterval = ATTACK_INTERVAL - ATTACK_INTERVAL * speed;

			// アニメーションストップ
			pAnim->SetStop(true);

			// サウンドストップ
			g_SE_Attack.Stop();
		}
	}
}

