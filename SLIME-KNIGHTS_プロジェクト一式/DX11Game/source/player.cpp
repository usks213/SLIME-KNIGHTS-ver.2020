//==================================================================
//								player.cpp
//	GM21 プレイヤー関連
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//
//	2020/06/05	プレイヤー描画
//
//	2020/06/10	コントローラー入力
//
//	2020/06/12	センサー入力
//
//===================================================================


//====== インクルード部 ======
#include "player.h"
#include "../sprite.h"
#include "../texture.h"
#include "objectMgr.h"
#include "collision.h"
#include "animator.h"
#include "animation.h"
#include "rigidbody.h"
#include "bullet.h"
#include "camera.h"
#include "levelupText.h"

#include "weapon.h"
#include "string.h"
#include "effect.h"


#ifdef _WIN32
#include "../input.h"
#include "../Sound.h"
#else
#include "../controller.h"
#endif // _WIN32

//===== マクロ定義 =====
#define MAX_PLAYER	(1)
#define MAX_PLAYER_TEX_X (4)
#define MAX_PLAYER_TEX_Y (32)
#define PLAYER_SPEED (12.0f)
#define THROUGH_TIME (20)
#define ANIM_SPEED (6)

//===== プロトタイプ宣言 =====


//===== グローバル変数 =====
// 加速度センサー用変数
Float3 g_accPlayer;			// 現在の加速度を保存
Float3 g_accPlayerPrev;		// 直前フレームの加速度センサー
// ジャイロセンサー用変数
Float3 g_gyroPlayer;		// (x,y,z)が各(0.0～1.0)の間の角度
Float3 g_gyroReset;			// ジャイロセンサーの角度リセット用


//===== 静的メンバ =====
CTexture CPlayer::sm_texture;
CTexture CPlayer::sm_attackTexture;
CStatus CPlayer::sm_backupStatus;

//===== グローバル変数 =====
static CSound g_SE_Move;
static CSound g_SE_Jump;


//========================================
//
//	コンストラクタ
//
//========================================
CPlayer::CPlayer()
{
	// ポリゴンのパラメータの初期化
	//m_transform.SetPos(Float3{ 96 * 4, 96 * 11, 0 });

	// スプライトデータ
	m_sprite;
	
	// レイヤー
	m_enLayer = LAYER::PLAYER;

	// スルー
	m_nThrouTime = 0;

	// アニメーションの再生
	// 停止
	CAnimation::Create(m_pAnimator, "LeftWait",  6, 0, 1, 2, 3,  4,  5);
	CAnimation::Create(m_pAnimator, "RightWait", 6, 6, 7, 8, 9, 10, 11);
	// 歩行
	CAnimation::Create(m_pAnimator, "LeftMove",  4, 12, 13, 14, 15);
	CAnimation::Create(m_pAnimator, "RightMove", 4, 18, 19, 20, 21);
	// ジャンプ
	CAnimation::Create(m_pAnimator, "LeftJump", 2, 24, 25);
	CAnimation::Create(m_pAnimator, "RightJump", 2, 33, 32);
	// 落下
	CAnimation::Create(m_pAnimator, "LeftFall", 2, 26, 27);
	CAnimation::Create(m_pAnimator, "RightFall", 2, 31, 30);


	// 攻撃用アニメーターの生成
	m_pAttackAnimator = CAnimator::Create(&m_attackSprite, this);
	// 攻撃アニメーション
	CAnimation::Create(m_pAttackAnimator, "LeftAttackDown", 3, 0, 1, 2);
	CAnimation::Create(m_pAttackAnimator, "RightAttackDown", 3, 3, 4, 5);
	CAnimation::Create(m_pAttackAnimator, "LeftAttackUp", 3, 6, 7, 8);
	CAnimation::Create(m_pAttackAnimator, "RightAttackUp", 3, 9, 10, 11);
	m_pAttackAnimator->SetAnimation("LeftAttack", 10, 3, 4);
	m_pAttackAnimator->SetStop(true);

	// アニメーションのセット
	m_pAnimator->SetAnimation("LeftWait", 18, 6, 8);


	// サウンド
	g_SE_Move.Load(FILE_PATH"sound/player/Concrete footsteps 5.wav");
	g_SE_Jump.Load(FILE_PATH"sound/player/PlayerJump.mp3");

	// 移動SEフラグ
	m_bMoveSE = false;
	m_nMoveSECnt = 0;

	// キャラクターアクションのセット
	m_charaAction.SetActionData(this, PLAYER_SPEED, PLAYER_SPEED * 2.0f, ANIM_SPEED);
	m_charaAction.SetPlayerAttackData(this, 4);

	// ウェポン
	m_pMainWeapon = CWeapon::Create(&m_transform, WEAPON::SWORD);
	//m_pMainWeapon = CObjectManager::CreateObject<CBoomerang>();

	// コンボ
	m_pCombo = CCombo::Create(Float3{ SCREEN_CENTER_X - 96, SCREEN_CENTER_Y - 88, 0 });

	// ステータス
	m_status.SetLevel(0);
	m_status.AddLevel(1);
	m_status.SetExperience(0);
	m_status.SetInvincibleTime(90);
	m_status;

	// フラグ
	m_bPlayerStop = false;
	m_bInputStop = false;
}


//========================================
//
//	デストラクタ
//
//========================================
CPlayer::~CPlayer()
{
	m_pMainWeapon->Destroy();
	m_pAttackAnimator->Destroy();
	m_pCombo->Destroy();
}

//========================================
//
//	初期化
//
//========================================
void CPlayer::Init()
{
	// テクスチャのロード
	//sm_texture.LoadTexture(FILE_PATH"Chara.tga");
	sm_texture.LoadTexture(FILE_PATH"player/player_anim_2.tga");
	sm_attackTexture.LoadTexture(FILE_PATH"player/player_attack.tga");

	// ウェポン
	CWeapon::Init();


	// ここでステータスデータの読み込み


}

//========================================
//
//	終了処理
//
//========================================
void CPlayer::Uninit()
{
	// テクスチャの解放
	sm_texture.UnloadTexture();
	sm_attackTexture.UnloadTexture();


	// ウェポン
	CWeapon::Uninit();

	// ここでステータスデータの書き込み


}

//========================================
//
//	更新
//
//========================================
void CPlayer::Update()
{
	if (m_bPlayerStop || m_bInputStop) return;

#ifdef _WIN32
	static bool bRight;
	// input
	// ボタン：プレス
	if (GetKeyPress(VK_D) || GetKeyPress(VK_RIGHT))
	{
		bRight = true;
		m_charaAction.Right();
		// サウンド 
		if (m_nMoveSECnt < 0 && !m_pRigidbody->GetUseGravity())
		{
			g_SE_Move.Play();
			m_bMoveSE = false;
			m_nMoveSECnt = ANIM_SPEED * 2;
			// エフェクト
			Float3 pos = m_transform.GetPos();
			pos.x -= m_transform.GetSizeX() / 4;
			pos.y += m_transform.GetSize().y / 3;
			CEffect::Create(EFFECT::DUST_R, pos);
		}
	}
	else if (GetKeyPress(VK_A) || GetKeyPress(VK_LEFT))
	{
		bRight = false;
		m_charaAction.Left();
		// サウンド 
		if (m_nMoveSECnt < 0 && !m_pRigidbody->GetUseGravity())
		{
			g_SE_Move.Play();
			m_bMoveSE = false;
			m_nMoveSECnt = ANIM_SPEED * 2;
			// エフェクト
			Float3 pos = m_transform.GetPos();
			pos.x += m_transform.GetSizeX() / 4;
			pos.y += m_transform.GetSize().y / 3;
			CEffect::Create(EFFECT::DUST_L, pos);
		}
	}
	else
	{
		// ウェイト
		m_charaAction.Wait();

		m_nMoveSECnt = 0;
	}
	// 下りる
	if (GetKeyPress(VK_S) || GetKeyPress(VK_DOWN))
	{
		m_bFloorThrough = true;
	}
	// ジャンプ
	if ((GetKeyPress(VK_SPACE) || GetKeyPress(VK_W) || GetKeyPress(VK_UP)
		|| GetKeyPress(VK_X) || GetKeyPress(VK_K))
		&& !m_pRigidbody->GetUseGravity())
	{
		m_charaAction.Jump();
		// サウンド
		g_SE_Jump.Play(0.6f);
	}
	// 攻撃
	if (GetKeyPress(VK_Z) || GetKeyPress(VK_L))
	{
		if (bRight)
		{
			//CBullet::Create(Float3{m_transform.GetPos().x + 96, m_transform.GetPos().y, 0}, 50, &m_status);
			//m_charaAction.Attack(3);
		}
		else
		{
			//CBullet::Create(Float3{ m_transform.GetPos().x - 96, m_transform.GetPos().y, 0 }, -50, &m_status);
			//m_charaAction.Attack(3);
		}

		m_charaAction.Attack(3, m_pMainWeapon->GetTransform());

	}

	// デバッグ
	/*if (GetKeyPress(VK_C))
	{
		CLevelUpText::Create(m_transform.GetPos());
	}*/

#else
	static bool bRight;
	// input
	// ボタン：プレス
	if (GetControllerPress(NpadButton::Right::Index))
	{
		bRight = true;
		m_charaAction.Right();
	}
	else if (GetControllerPress(NpadButton::Left::Index))
	{
		bRight = false;
		m_charaAction.Left();
	}
	else if (GetControllerPress(NpadButton::Down::Index))
	{
		m_bFloorThrough = true;
	}
	else
	{
		m_charaAction.Wait();
	}
	// ジャンプ
	if (GetControllerPress(NpadButton::B::Index))
	{
		//m_pRigidbody->SetForceY(-PLAYER_SPEED * 1.2f);
		m_charaAction.Jump();
	}
	// 攻撃
	if (GetControllerPress(NpadButton::Y::Index))
	{
		if (bRight)
		{
			//CBullet::Create(Float3{m_transform.GetPos().x + 96, m_transform.GetPos().y, 0}, 50, &m_status);
			m_charaAction.Attack(4);
		}
		else
		{
			//CBullet::Create(Float3{ m_transform.GetPos().x - 96, m_transform.GetPos().y, 0 }, -50, &m_status);
			m_charaAction.Attack(4);
		}
	}


#endif // _WIN32

	// スルーフラグの管理
	if (m_bFloorThrough)
	{
		m_nThrouTime++;
		if (m_nThrouTime > THROUGH_TIME)
		{
			m_bFloorThrough = false;
			m_nThrouTime = 0;
		}
	}

	// 移動SE
	m_nMoveSECnt--;

	// ステータスのバックアップを取る
	sm_backupStatus = m_status;

	// カメラ
	CCamera::SetCameraTarget(this->GetTransform());

}

//========================================
//
//	更新
//
//========================================
void CPlayer::LateUpdate()
{
	// ステータスのバックアップを取る
	sm_backupStatus = m_status;

	if (m_bPlayerStop)
	{
		m_pRigidbody->SetStop(true);
	}
}

//========================================
//
//	描画
//
//========================================
void CPlayer::Draw()
{
	//if (m_bPlayerStop) return;

	m_sprite.Draw(&m_transform, &sm_texture);
	m_attackSprite.Draw(&m_transform, &sm_attackTexture);
	
}


//========================================
//
//	当たり判定
//
//========================================
void CPlayer::OnCollision(CCollision *pCol)
{
	if (m_bPlayerStop) return;

	CObject *pObj = pCol->GetObj();

	// キャラクターがあった時の処理
	m_charaAction.OnCollisionAction(pCol);

	// ステータスのバックアップを取る
	sm_backupStatus = m_status;
}


//========================================
//
//	アニメーション終了時に呼び出す
//
//========================================
void CPlayer::OnAnimator(CAnimator *pAnim)
{
	if (m_bPlayerStop) return;

	// プレイヤーアクション
	m_charaAction.OnAnimatorAction(pAnim); 

	// 終了したアニメーションの名前で分岐
	if (pAnim->GetCurrentAnimation()->GetName() == "RightMove" || 
		pAnim->GetCurrentAnimation()->GetName() == "LeftMove")
	{
		//m_bMoveSE = true;
	}
};