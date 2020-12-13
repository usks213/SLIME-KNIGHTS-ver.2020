//==================================================================
//									status.h
//	ステータス
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//
//	2020/08/02	ステータスクラスの作成
//
//===================================================================

//====== インクルード部 ======
#include "status.h"
#include <stdlib.h>
#include "stageManager.h"


//===== マクロ定義 =====


//===== クラス定義 =====



//===== プロトタイプ宣言 =====


//===== 静的メンバ =====
static List<CStatus> m_list;
//List<CStatus> CStatus::m_list;



//========================================
//
//	コンストラクタ
//
//========================================
CStatus::CStatus()
{
	// 基本ステータス
	m_nLevel = 1;			// レベル
	m_nMaxHp = m_nHp = 5;				// 体力
	m_nDamage = 1;			// 攻撃力
	m_nAttackSpeed = 1;		// 攻撃速度
	m_nMoveSpeed = 1;		// 移動速度

	m_nMoney = 10;			// お金
	m_nExperience = 1;		// 経験値
	m_nRequiredExperience = 10;// 必要経験値

	// 状態
	m_bInvincible = false;		// 無敵フラグ
	m_nInvincibleCnt = 0;	// 無敵カウント
	m_nInvincibleTime = 15;	// 無敵時間

	// 状態異常
	m_nPoisonResis = 10;		// 毒耐性
	m_nPoisonCnt = 0;
	m_nPoisonTime = 120;
	m_nParalysisResis = 10;	// 麻痺耐性
	m_nParalysisCnt = 0;
	m_nParalysisTime = 120;

	m_bStop = false;

	// リストに格納
	m_list.AddNode(this);


	// レベルをセット
	// 階層を参照して
	SetLevel(CStageManager::GetStageLevel() * 10 + (rand() %(5 * (CStageManager::GetStageLevel() + 1))) + 1);
}


//========================================
//
//	デストラクタ
//
//========================================
CStatus::~CStatus()
{
	// リストの消去
	m_list.DestroyNode(this);
}


//========================================
//
//	更新処理
//
//========================================
void CStatus::Update()
{
	if (m_bStop) return;

	// 無敵カウント
	if(m_bInvincible)
		m_nInvincibleCnt--;
	if (m_nInvincibleCnt < 0)
	{
		m_bInvincible = false;
	}

	// 状態異常

	// バフ

	// デバフ

}


//========================================
//
//	描画処理
//
//========================================
void CStatus::Draw()
{
	// ダメージ・無敵

	// 状態異常

	// バフ

	// デバフ

}


//========================================
//
//	ダメージ計算関数 戻り値：残りHP
//
//========================================
int CStatus::AttackDamage(CStatus *pStatus, bool bCritical)
{
	// クリティカル発生
	if (bCritical)
	{
		// 発生時はダメージアップ
		m_nHp -= pStatus->m_nDamage * 2;
	}
	else
	{
		// ステータスの計算
		m_nHp -= pStatus->m_nDamage;
	}

	// ゼロ以下なら
	if (m_nHp < 0) m_nHp = 0;

	// 無敵
	m_bInvincible = true;
	m_nInvincibleCnt = m_nInvincibleTime;


	return m_nHp;
}




//========================================
//
//	リストの更新
//
//========================================
void CStatus::ListUpdate()
{
	// 先頭リストの取得
	List<CStatus>* pHead = m_list.GetHead();

	// ノード無し
	if (pHead == nullptr) return;

	// リスト内の一斉更新
	List<CStatus> *pNode = nullptr;
	for (pNode = pHead; pNode != nullptr; pNode = pNode->GetNext())
	{
		pNode->GetThis()->Update();

	}
}

//========================================
//
//	レベルのセット
//
//========================================
void CStatus::SetLevel(int nSet)
{
	m_nLevel = nSet;

	// 以下のステータスをレベルをもとに自動算出
	m_nMaxHp = m_nHp = (int)(5 + nSet * 2.45f + rand() % (nSet / 2 + 1)) + 10;
	m_nDamage = (int)(nSet * 1.45f + rand() % (nSet / 4 + 1)) + 1 + 2;
	m_nMoney = (int)(nSet * 3.3f + rand() % (nSet + 1));
	m_nExperience = (int)(nSet * 3.66f + rand() % (nSet / 2 + 1)) + 3;

	m_nMoveSpeed = m_nLevel;
	m_nAttackSpeed = m_nLevel;
}