//==================================================================
//								characterAction.h
//	 
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//
//	2020/08/02	キャラクターアクションクラスの追加
//
//
//===================================================================


//====== インクルード部 ======
#include "characterAction.h"
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
#include "damageText.h"
#include "stageManager.h"
#include "stageStartMap.h"
#include "resultUI.h"
#include "combo.h"
#include "../input.h"


#ifdef _WIN32
#include "../Sound.h"

#endif // _WIN32


//===== マクロ定義 =====
#define KNOCKBACK_FORCEX (18)
#define KNOCKBACK_FORCEY (12)
#define DEFAULT_ANIM_SPEED (12)

#define CRITICAL_HITSTOP_FRAME (12)
#define DEFAULT_HITSTOP_FRAME (6)

#define DAMAGE_SHAKE_FRAME (8)

#define DEFAULT_CAMERA_SHAKE_OFFSET (20)
#define CRITICAL_CAMERA_SHAKE_OFFSET (30)
#define DAMAGE_CAMERA_SHAKE_OFFSET (40)


//===== 静的関数 =====
List<CCharacterAction> CCharacterAction::m_list;


//===== グローバル変数 =====
static CSound g_SE_PlayerDamage;
static CSound g_SE_EnemyDamage;
static CSound g_SE_Destroy;
static CSound g_SE_CriticalHit;

static int g_nHitStopFrame = DEFAULT_HITSTOP_FRAME;
int GetHitStopFrame() { return g_nHitStopFrame; }


static bool g_bHitStop = true;
static bool g_bCameraShake = true;


//========================================
//
//	コンストラクタ
//
//========================================
CCharacterAction::CCharacterAction()
{
	m_pChara = nullptr;
	m_fMoveForce = 1.0f;
	m_fJumpForce = 1.0f;
	m_bRight = true;
	m_pAttackBase = nullptr;
	m_nAnimSpeed = 12;
	m_nFlashCnt = 0;
	m_eCurAction = WAIT;
	m_nHitStopCnt = -1;
	m_fAttackOffSetX = 0.0f;

	// リスト
	m_list.AddNode(this);
}


//========================================
//
//	デストラクタ
//
//========================================
CCharacterAction::~CCharacterAction()
{
	// リスト
	m_list.DestroyNode(this);

	// 攻撃エリアを消す
	if (m_pAttackBase != nullptr)
	{
		m_pAttackBase->Destroy();
		m_pAttackBase = nullptr;
	}
}


//========================================
//
//	初期化
//
//========================================
void CCharacterAction::Init()
{
	// サウンドのロード
	g_SE_Destroy.Load(FILE_PATH"sound/enemy/EnemyDestroy1.wav");
	g_SE_EnemyDamage.Load(FILE_PATH"sound/enemy/EnemyDamage2.wav");
	g_SE_PlayerDamage.Load(FILE_PATH"sound/player/PlayerNockBack.wav");
	g_SE_CriticalHit.Load(FILE_PATH"sound/player/CriticalHit.mp3");
}

//========================================
//
//	終了処理
//
//========================================
void CCharacterAction::Uninit()
{

}


//========================================
//
//	データセット
//
//========================================
void CCharacterAction::SetActionData(CCharacter *pChara, float fMoveForce, float fJumpForce, int nAnimSpeed)
{
	m_pChara = pChara;
	m_fMoveForce = fMoveForce;
	m_fJumpForce = fJumpForce;
	if(nAnimSpeed > 0)
		m_nAnimSpeed = nAnimSpeed;
}


//========================================
//
//	更新
//
//========================================
void CCharacterAction::Update()
{
	// 攻撃エリア
	if (m_pAttackBase)
	{
		if (m_bRight)
		{
			m_pAttackBase->SetOffSetX(m_fAttackOffSetX);
			m_pAttackBase->GetTransform()->SetDir(Float3{ 1.0f, 0.0f, 0.0f });
		}
		else
		{
			m_pAttackBase->SetOffSetX(-m_fAttackOffSetX);
			m_pAttackBase->GetTransform()->SetDir(Float3{ -1.0f, 0.0f, 0.0f });
		}
	}


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
		if (fabsf(m_pChara->GetRb()->GetForce().x) < 0.1f)
		{
			// 状態遷移
			m_eCurAction = WAIT;
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

		if (m_nHitStopCnt < 0)
			m_nHitStopCnt = HIT_STOP_FRAME;

		m_nHitStopCnt--;
		if (m_nHitStopCnt < 0)
		{
			m_pChara->SetStop(false);
			m_pChara->GetAnim()->SetStop(false);
			m_pChara->GetRb()->SetStop(false);
			m_pChara->GetStatus()->SetStop(false);

			if (m_pAttackBase)
				m_pAttackBase->SetStop(false);
		}
	}


}


//========================================
//
//	右移動
//
//========================================
void CCharacterAction::Right(int nAnimSpeed)
{
	if (m_eCurAction != DAMAGE)
	{
		// 移動
		float speed = 1.0f + m_pChara->GetStatus()->GetMoveSpeed() / 100.0f;
		m_pChara->GetRb()->SetForceX(m_fMoveForce * speed);
	}

	if (m_eCurAction == WAIT || m_eCurAction == MOVE)
	{
		// アニメーション
		if(nAnimSpeed > 0)	m_pChara->GetAnim()->SetAnimation("RightMove", nAnimSpeed);
		else				m_pChara->GetAnim()->SetAnimation("RightMove", m_nAnimSpeed);
		// フラグ
		m_bRight = true;
		// 状態
		m_eCurAction = MOVE;
	}
	else if (m_eCurAction == JUMP)
	{
		// ジャンプの最大点までいったら
		if (m_pChara->GetRb()->GetForce().y <= 0.0f)
		{
			// アニメーション
			if (nAnimSpeed > 0)	m_pChara->GetAnim()->SetAnimation("RightJump", nAnimSpeed);
			else				m_pChara->GetAnim()->SetAnimation("RightJump", m_nAnimSpeed);
		}
		else
		{
			// アニメーション
			if (nAnimSpeed > 0)	m_pChara->GetAnim()->SetAnimation("RightFall", nAnimSpeed);
			else				m_pChara->GetAnim()->SetAnimation("RightFall", m_nAnimSpeed);
		}
		// フラグ
		m_bRight = true;
	}
}

//========================================
//
//	左移動
//
//========================================
void CCharacterAction::Left(int nAnimSpeed)
{
	if (m_eCurAction != DAMAGE)
	{
		// 移動
		float speed = 1.0f + m_pChara->GetStatus()->GetMoveSpeed() / 100.0f;
		m_pChara->GetRb()->SetForceX(-m_fMoveForce * speed);
	}

	if (m_eCurAction == WAIT || m_eCurAction == MOVE)
	{
		// アニメーション
		if (nAnimSpeed > 0)	m_pChara->GetAnim()->SetAnimation("LeftMove", nAnimSpeed);
		else				m_pChara->GetAnim()->SetAnimation("LeftMove", m_nAnimSpeed);
		// フラグ
		m_bRight = false;
		// 状態
		m_eCurAction = MOVE;
	}
	else if (m_eCurAction == JUMP)
	{
		// ジャンプの最大点までいったら
		if (m_pChara->GetRb()->GetForce().y <= 0.0f)
		{
			// アニメーション
			if (nAnimSpeed > 0)	m_pChara->GetAnim()->SetAnimation("LeftJump", nAnimSpeed);
			else				m_pChara->GetAnim()->SetAnimation("LeftJump", m_nAnimSpeed);
		}
		else
		{
			// アニメーション
			if (nAnimSpeed > 0)	m_pChara->GetAnim()->SetAnimation("LeftFall", nAnimSpeed);
			else				m_pChara->GetAnim()->SetAnimation("LeftFall", m_nAnimSpeed);
		}
		// フラグ
		m_bRight = false;
	}
}

//========================================
//
//	上移動
//
//========================================
void CCharacterAction::Up(int nAnimSpeed)
{
	// 移動
	//if (m_eCurAction != DAMAGE)
	{
		float speed = 1.0f + m_pChara->GetStatus()->GetMoveSpeed() / 100.0f;
		m_pChara->GetRb()->SetForceY(-m_fMoveForce * speed);
	}

	if (m_eCurAction == WAIT || m_eCurAction == MOVE)
	{
		// 状態
		m_eCurAction = MOVE;
	}
}

//========================================
//
//	下移動
//
//========================================
void CCharacterAction::Down(int nAnimSpeed)
{
	// 移動
	//if (m_eCurAction != DAMAGE)
	{
		float speed = 1.0f + m_pChara->GetStatus()->GetMoveSpeed() / 100.0f;
		m_pChara->GetRb()->SetForceY(m_fMoveForce * speed);
	}

	if (m_eCurAction == WAIT || m_eCurAction == MOVE)
	{
		// 状態
		m_eCurAction = MOVE;
	}
}

//========================================
//
//	ジャンプ
//
//========================================
void CCharacterAction::Jump(int nAnimSpeed)
{
	if (m_eCurAction == WAIT || m_eCurAction == MOVE || m_eCurAction == JUMP)
	{
		// 移動
		m_pChara->GetRb()->SetForceY(-m_fJumpForce);
		// 右か左か
		if (m_bRight)
		{
			// アニメーション
			if (nAnimSpeed > 0)	m_pChara->GetAnim()->SetAnimation("RightJump", nAnimSpeed);
			else				m_pChara->GetAnim()->SetAnimation("RightJump", m_nAnimSpeed);
		}
		else
		{
			// アニメーション
			if (nAnimSpeed > 0)	m_pChara->GetAnim()->SetAnimation("LeftJump", nAnimSpeed);
			else				m_pChara->GetAnim()->SetAnimation("LeftJump", m_nAnimSpeed);
		}
		// 状態
		m_eCurAction = JUMP;
	}
}

//========================================
//
//	ウェイト
//
//========================================
void CCharacterAction::Wait(int nAnimSpeed)
{
	if (m_eCurAction != ATTACK && m_eCurAction != DAMAGE && m_eCurAction != JUMP)
	{
		// 右か左か
		if (m_bRight)
		{
			// アニメーション
			if (nAnimSpeed > 0)	m_pChara->GetAnim()->SetAnimation("RightWait", nAnimSpeed);
			else				m_pChara->GetAnim()->SetAnimation("RightWait", m_nAnimSpeed);
		}
		else
		{
			// アニメーション
			if (nAnimSpeed > 0)	m_pChara->GetAnim()->SetAnimation("LeftWait", nAnimSpeed);
			else				m_pChara->GetAnim()->SetAnimation("LeftWait", m_nAnimSpeed);
		}
		// 状態
		m_eCurAction = WAIT;
	}
}

//========================================
//
//	攻撃
//
//========================================
void CCharacterAction::Attack(int nAnimSpeed)
{
	if (m_eCurAction == WAIT || m_eCurAction == MOVE || m_eCurAction == JUMP)
	{
		// サイズ
		Float2 size = m_pChara->GetTransform()->GetSize();
		size.x *= 1.2f;
		size.y *= 1.2f;
		// 右か左か
		if (m_bRight)
		{
			// 攻撃エリア生成
			if (m_pAttackBase == nullptr)
			{
				m_pAttackBase = CAttackBase::Create(m_pChara->GetStatus(), m_pChara->GetTransform(), 0);
				m_pAttackBase->GetTransform()->SetDir(Float3{ 1.0f, 0.0f, 0.0f });
				m_pAttackBase->SetLayer(LAYER::ENEMYATTACK);
				m_pAttackBase->GetTransform()->SetSize(size);
			}
			// アニメーション
			if (nAnimSpeed > 0)	m_pChara->GetAnim()->SetAnimation("RightAttack", nAnimSpeed);
			else				m_pChara->GetAnim()->SetAnimation("RightAttack", m_nAnimSpeed);
		}
		else
		{
			// 攻撃エリア生成
			if (m_pAttackBase == nullptr)
			{
				m_pAttackBase = CAttackBase::Create(m_pChara->GetStatus(), m_pChara->GetTransform(), 0);
				m_pAttackBase->GetTransform()->SetDir(Float3{ -1.0f, 0.0f, 0.0f });
				m_pAttackBase->SetLayer(LAYER::ENEMYATTACK);
				m_pAttackBase->GetTransform()->SetSize(size);
			}
			// アニメーション
			if (nAnimSpeed > 0)	m_pChara->GetAnim()->SetAnimation("LeftAttack", nAnimSpeed);
			else				m_pChara->GetAnim()->SetAnimation("LeftAttack", m_nAnimSpeed);
		}
		// 状態
		m_eCurAction = ATTACK;
	}
}

//========================================
//
//	攻撃を受ける
//
//========================================
void CCharacterAction::Damage(CStatus *pStatus, int nAnimSpeed)
{
	if (m_eCurAction != DAMAGE)
	{
		// ステータス
		int nHp = m_pChara->GetStatus()->AttackDamage(pStatus);
		// 死んだら
		if (nHp <= 0)
		{
			// 死亡エフェクト

			// お金の生成

			// 消去
			CObjectManager::DestroyObject(m_pChara);
		}

		// 右か左か
		if (m_bRight)
		{
			// ノックバック
			m_pChara->GetRb();

			// 点滅

			// アニメーション
			if (nAnimSpeed > 0)	m_pChara->GetAnim()->SetAnimation("RightDamage", nAnimSpeed);
			else				m_pChara->GetAnim()->SetAnimation("RightDamage", m_nAnimSpeed);
		}
		else
		{
			// ノックバック
			m_pChara->GetRb();

			// 点滅

			// アニメーション
			if (nAnimSpeed > 0)	m_pChara->GetAnim()->SetAnimation("LeftDamage", nAnimSpeed);
			else				m_pChara->GetAnim()->SetAnimation("LeftDamage", m_nAnimSpeed);
		}
		// 状態
		m_eCurAction = DAMAGE;
	}
}

//========================================
//
//	当たり判定後に呼び出す
//
//========================================
void CCharacterAction::OnCollisionAction(CCollision *pCol)
{
	// エネミー
	if (m_pChara->GetLayer() == LAYER::ENEMY)
	{
		// 当たったオブジェクトで分岐
		if (pCol->GetObj()->GetLayer() == LAYER::PLAYERATTACK || pCol->GetObj()->GetLayer() == LAYER::PLAYERBULLET)
		{
			CStatus *pStatus = pCol->GetObj()->GetStatus();
			if (pStatus != nullptr)
			{
				// 無敵じゃないなら
				if (m_pChara->GetStatus()->GetInvincible() == false)
				{
					// 状態遷移
					m_eCurAction = DAMAGE;

					// エフェクト
					CEffect::Create(EFFECT::ENEMY_DAMAGE, m_pChara->GetTransform()->GetPos());

					// ノックバック
					CRigidbody *pRb = m_pChara->GetRb();
					if (pCol->GetObj()->GetTransform()->GetDir().x < 0.0f)
					{
						pRb->SetForceX(-KNOCKBACK_FORCEX);
					}
					else
					{
						pRb->SetForceX(KNOCKBACK_FORCEX);
					}
					pRb->SetForceY(-KNOCKBACK_FORCEY);

					// ヒットストップ
					if (g_bHitStop)
					{
						m_pChara->SetStop(true);
						m_pChara->GetStatus()->SetStop(true);
						pCol->GetObj()->SetStop(true);
					}

					//コンボ加算
					CStageManager::GetMainPlayer()->GetCombo()->AddCombo(1);

					// クリティカル計算
					bool isCrt = CStageManager::GetMainPlayer()->GetCombo()->GetCritical();
					int nHp = 0;

					// クリティカル発生
					if (isCrt)
					{
						// ダメージ表記
						CDamageText::Create(pStatus->GetDamage() * 2, m_pChara->GetTransform()->GetPos(), {1,1,0,1}, true);

						// ダメージ計算
						nHp = m_pChara->GetStatus()->AttackDamage(pStatus, true);

						// ヒットストップフレーム
						g_nHitStopFrame = CRITICAL_HITSTOP_FRAME;

						// 画面揺れ
						if(g_bCameraShake)
							CCamera::SetCameraShake(CRITICAL_HITSTOP_FRAME, CRITICAL_CAMERA_SHAKE_OFFSET);

						// サウンド
						g_SE_CriticalHit.Play();
					}
					else // 発生してない
					{
						// ダメージ表記
						CDamageText::Create(pStatus->GetDamage(), m_pChara->GetTransform()->GetPos());

						// ダメージ計算
						nHp = m_pChara->GetStatus()->AttackDamage(pStatus);

						// ヒットストップフレーム
						g_nHitStopFrame = DEFAULT_HITSTOP_FRAME;

						// 画面揺れ
						CCamera::SetCameraShake(DEFAULT_HITSTOP_FRAME, DEFAULT_CAMERA_SHAKE_OFFSET);

						
					}
					// サウンド
					g_SE_EnemyDamage.Play();

					// 死んだら
					if (nHp <= 0)
					{
						// α値を戻す
						m_pChara->GetSprite()->SetColorW(1.0f);

						// 死亡エフェクト

						// サウンド
						g_SE_Destroy.Play();

						// カウンター
						CResultUI::AddEnemy();


						// 経験値の生成
						//CExperience::Create(m_pChara->GetStatus()->GetExperience(), m_pChara->GetTransform()->GetPos());

						// 経験値
						//pStatus->AddExperience(m_pChara->GetStatus()->GetExperience());

						// 消去
						//CObjectManager::DestroyObject(m_pChara);
						m_pChara->Destroy();
					}
				}
			}
		}

	}
	// プレイヤー
	else if (m_pChara->GetLayer() == LAYER::PLAYER)
	{
		// 当たったオブジェクトで分岐
		if (pCol->GetObj()->GetLayer() == LAYER::ENEMYATTACK || pCol->GetObj()->GetLayer() == LAYER::ENEMYBULLET)
		{
			CStatus *pStatus = pCol->GetObj()->GetStatus();
			if (pStatus != nullptr)
			{
				// 無敵じゃないなら
				if (m_pChara->GetStatus()->GetInvincible() == false)
				{
					// 状態遷移
					m_eCurAction = DAMAGE;

					// 画面揺れ
					CCamera::SetCameraShake(DAMAGE_SHAKE_FRAME, DAMAGE_CAMERA_SHAKE_OFFSET);

					// エフェクト
					CEffect::Create(EFFECT::PLAYER_DAMAGE, m_pChara->GetTransform()->GetPos());

					// ノックバック
					CRigidbody *pRb = m_pChara->GetRb();
					if (pCol->GetObj()->GetTransform()->GetDir().x < 0.0f)
					{
						pRb->SetForceX(-KNOCKBACK_FORCEX);
					}
					else
					{
						pRb->SetForceX(KNOCKBACK_FORCEX);
					}
					pRb->SetForceY(-KNOCKBACK_FORCEY);
					pRb->SetDragX(0.08f);

					// ヒットストップ
					m_pChara->SetStop(true);
					m_pChara->GetStatus()->SetStop(true);
					pCol->GetObj()->SetStop(true);
					// ヒットストップフレーム
					g_nHitStopFrame = DEFAULT_HITSTOP_FRAME;

					// サウンド
					g_SE_EnemyDamage.Play(1.0f);

					// コンボ減算
					CStageManager::GetMainPlayer()->GetCombo()->ResetCombo();

					// ダメージ表記
					CDamageText::Create(pStatus->GetDamage(), m_pChara->GetTransform()->GetPos(), {1, 0, 0, 1});

					// ダメージ計算
					int nHp = m_pChara->GetStatus()->AttackDamage(pStatus);
					// 死んだら
					if (nHp <= 0)
					{
						// 死亡エフェクト

						// サウンド
						g_SE_Destroy.Play();

						//// お金の生成
						//for (int i = 0; i < m_pChara->GetStatus()->GetMoney(); i++)
						//	CExperience::Create(EXPERIENCE::ONE, m_pChara->GetTransform()->GetPos());
						// 経験値の生成
						CExperience::Create(m_pChara->GetStatus()->GetExperience(), m_pChara->GetTransform()->GetPos());

						// HPと経験値を０に
						m_pChara->GetStatus()->SetHp(0);
						m_pChara->GetStatus()->SetExperience(0);

						// 消去
						//CObjectManager::DestroyObject(m_pChara);
						// α値０でストップをかける
						m_pChara->GetTransform()->SetPos(Float3{ -1000, -1000, 0 });
						m_pChara->GetRb()->SetStop(true);
						static_cast<CPlayer*>(m_pChara)->SetPlayerStop(true);
						CCamera::SetCameraTarget(nullptr);

						// リザルド
						CResultUI::SetCurLevel(m_pChara->GetStatus()->GetLevel());

						// リスタート
						//CStageManager::SetTimerNextStage(new CStageStartMap(), 300, CStageManager::SetRestart);
						// ここをリザルト表示に！
						//CResultUI::Create();
						CStageManager::CreateResult();

						CStageManager::SetBGM(BGM::RENGA_BOSS);
						CStageManager::StopBGM();
					}
				}
			}
		}
	}
}

//========================================
//
//	アニメーション終了時に呼び出す
//
//========================================
void CCharacterAction::OnAnimatorAction(CAnimator *pAnim)
{
	// 終了したアニメーションの名前で分岐
	if (pAnim->GetCurrentAnimation()->GetName() == "RightAttack" || pAnim->GetCurrentAnimation()->GetName() == "LeftAttack")
	{
		// 攻撃エリアを消す
		if (m_pAttackBase != nullptr)
		{
			m_pAttackBase->Destroy();
			m_pAttackBase = nullptr;
		}

		// 状態遷移
		m_eCurAction = WAIT;
	}
}


//========================================
//
//	リスト更新
//
//========================================
void CCharacterAction::ListUpdate()
{
	// 演出オンオフ
	if (GetKeyTrigger(VK_7))
	{
		g_bCameraShake ^= 1;
		g_bHitStop ^= 1;
	}


	// 先頭リストの取得
	List<CCharacterAction>* pHead = m_list.GetHead();

	// ノード無し
	if (pHead == nullptr) return;

	// リスト内の一斉更新
	List<CCharacterAction> *pNode = nullptr;
	List<CCharacterAction> *pNextBack = nullptr;
	for (pNode = pHead; pNode != nullptr; pNode = pNextBack)
	{
		// 次のポインタのバックアップを取る
		pNextBack = pNode->GetNext();

		// 一斉更新
		pNode->GetThis()->Update();
	}
}


//========================================
//
//	リスト更新
//
//========================================
void CCharacterAction::CreateAttackBase(LAYER::LAYER eLayer, float fOffSetX)
{
	if (m_pAttackBase == nullptr)
	{
		m_pAttackBase = CAttackBase::Create(m_pChara->GetStatus(), m_pChara->GetTransform(), fOffSetX);
		m_pAttackBase->SetLayer(eLayer);
		m_fAttackOffSetX = fOffSetX;
	}

}