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
//===================================================================

#pragma once

//====== インクルード部 ======
#include "../main.h"
#include "object.h"
#include "attackBase.h"
#include "List.h"


//===== マクロ定義 =====

int GetHitStopFrame();
#define HIT_STOP_FRAME GetHitStopFrame()

//===== クラス定義 =====

class CCharacter;

class CCharacterAction
{
public:
	// コンストラクタ・デストラクタ
	CCharacterAction();
	~CCharacterAction();

	static void Init();
	static void Uninit();

	// 必要データのセット
	void SetActionData(CCharacter *pChara, float fMoveForce, float fJumpForce, int nAnimSpeed = 0);

	// リスト更新
	static void ListUpdate();
	// 更新
	virtual void Update();

	// 行動パターン
	virtual void Right(int nAnimSpeed = 0);
	virtual void Left(int nAnimSpeed = 0);
	virtual void Up(int nAnimSpeed = 0);
	virtual void Down(int nAnimSpeed = 0);
	virtual void Jump(int nAnimSpeed = 0);
	virtual void Wait(int nAnimSpeed = 0);
	virtual void Attack(int nAnimSpeed = 0);
	virtual void Damage(CStatus *pStatus, int nAnimSpeed = 0);

	virtual void CreateAttackBase(LAYER::LAYER eLayer, float fOffSetX);

	// OnCollisionにセット
	virtual void OnCollisionAction(CCollision *pCol);
	// OnAnimatorにセット
	virtual void OnAnimatorAction(CAnimator *pAnim);

	// ゲット関数
	bool GetRight() { return m_bRight; }
	CAttackBase* GetAttackBase() { return m_pAttackBase; }

	void SetWait()
	{
		m_eCurAction = WAIT;
		Wait();
	}

protected:
	// リスト
	static List<CCharacterAction> m_list;

	// キャラクターデータ
	CCharacter *m_pChara;

	// アクション関連
	float m_fMoveForce;
	float m_fJumpForce;
	bool m_bRight;
	int m_nAnimSpeed;
	int m_nFlashCnt;

	int m_nHitStopCnt;

	// 生成される当たり判定データ
	CAttackBase *m_pAttackBase;
	float m_fAttackOffSetX;

	// 行動パターン
	enum EAction
	{
		WAIT,
		MOVE,
		JUMP,
		ATTACK,
		DAMAGE,

		MAX_ACTION,
	};
	// 現在のアクション
	EAction m_eCurAction;

};

