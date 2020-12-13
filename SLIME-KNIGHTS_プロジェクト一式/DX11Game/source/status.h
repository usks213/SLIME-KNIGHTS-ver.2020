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
#pragma once

//====== インクルード部 ======
#include "List.h"
#include <stdlib.h>
#include "levelupText.h"

//===== マクロ定義 =====


//===== クラス定義 =====

class CStatus
{
public:
	CStatus();
	~CStatus();
	// ステータスの更新
	void Update();
	// ステータス系エフェクトと描画
	void Draw();

	// ダメージを与える
	int AttackDamage(CStatus *pStatus, bool bCritical = false);

	// 加算関数
	void AddLevel(int nAdd)
	{
		m_nLevel += nAdd;
		if (m_nLevel > 9999999) m_nLevel = 9999999;
		// ステータスを上げる
		m_nMaxHp = m_nHp = (int)(5 + m_nLevel * 6.45f + m_nLevel / 2 * 1.3f + 50);
		m_nDamage = (int)(m_nLevel * 1.45f + m_nLevel / 5 + 1) + 5;
		m_nMoveSpeed = m_nLevel;
		m_nAttackSpeed = m_nLevel;
	}
	void AddHp(int nAdd) { m_nHp += nAdd; };
	void AddDamage(int nAdd) { m_nDamage += nAdd; };
	void AddAttackSpeed(int nAdd) { m_nAttackSpeed += nAdd; };
	void AddMoveSpeed(int nAdd) { m_nMoveSpeed += nAdd; };
	void AddMoney(int nAdd) { m_nMoney += nAdd; };
	void AddExperience(int nAdd, Float3 pos)
	{
		m_nExperience += nAdd;
		// 経験値が溜まった
		while (m_nExperience >= m_nRequiredExperience)
		{
			// レベルアップ
			AddLevel(1);
			// テキスト生成
			CLevelUpText::Create(pos);
			// 経験値のリセット
			m_nExperience -= m_nRequiredExperience;
			// 必要経験値を設定
			//m_nRequiredExperience = m_nLevel * (m_nLevel / 4 + rand() % (m_nLevel / 4 + 1));
			m_nRequiredExperience = (int)(m_nLevel * 9.531f);
		}
	}

	// セット関数
	void SetLevel(int nSet);
	void SetHp(int nSet) { m_nHp = nSet; }
	void SetMaxHp(int nSet) { m_nMaxHp = nSet; }
	void SetDamage(int nSet) { m_nDamage = nSet; }
	void SetAttackSpeed(int nSet) { m_nAttackSpeed = nSet; }
	void SetMoveSpeed(int nSet) { m_nMoveSpeed = nSet; }
	void SetMoney(int nSet) { m_nMoney = nSet; }
	void SetExperience(int nSet) { m_nExperience = nSet;}
	void SetStop(bool bStop) { m_bStop = bStop; }
	void SetInvincibleTime(int nFrame) { m_nInvincibleTime = nFrame; }
	void SetInvincibleCnt(int nFrame) { m_nInvincibleCnt = nFrame; }
	void SetInvincible(bool bFlag) { m_bInvincible = bFlag; }

	// ゲット関数
	int GetLevel() { return m_nLevel; }
	int GetHp() { return m_nHp; }
	int GetMaxHp() { return m_nMaxHp; }
	int GetDamage() { return m_nDamage; }
	int GetAttackSpeed() { return m_nAttackSpeed; }
	int GetMoveSpeed() { return m_nMoveSpeed; }
	int GetMoney() { return m_nMoney; }
	int GetExperience() { return m_nExperience; }
	int GetRequiredExperience() { return m_nRequiredExperience; }
	bool GetInvincible() { return m_bInvincible; }

	// リスト
	static void ListUpdate();

private:
	// ステータス管理リスト
	//static List<CStatus> m_list;

	// キャラクター


	// 基本ステータス
	int m_nLevel;			// レベル
	int m_nMaxHp;			// 最大体力
	int m_nHp;				// 体力
	int m_nDamage;			// 攻撃力
	int m_nAttackSpeed;		// 攻撃速度
	int m_nMoveSpeed;		// 移動速度

	int m_nMoney;			// お金
	int m_nExperience;		// 経験値
	int m_nRequiredExperience;// 必要経験値

	// 状態
	bool m_bInvincible;		// 無敵フラグ
	int m_nInvincibleCnt;	// 無敵カウント
	int m_nInvincibleTime;	// 無敵時間

	// 状態異常
	int m_nPoisonResis;		// 毒耐性
	int m_nPoisonCnt;
	int m_nPoisonTime;
	int m_nParalysisResis;	// 麻痺耐性
	int m_nParalysisCnt;
	int m_nParalysisTime;

	// バフ
	// HPリジェネ
	// ステータスUP系

	// デバフ
	// 移動速度DOWN
	// ステータスDOWN系


	// ストップフラグ
	bool m_bStop;
};

