//==================================================================
//								enemy.h
//	GM21 エネミー
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//
//	2020/06/05	プレイヤー描画
//	2020/06/14	オブジェクトの派生クラスに
//
//===================================================================

#pragma once

//====== インクルード部 ======
#include "../main.h"
#include "object.h"
#include "character.h"
#include "viewArea.h"
#include "attackArea.h"
#include "enemyUI.h"
#include "experience.h"
#include "../Sound.h"


//===== 定数定義 =====
namespace ENEMY
{
	enum ETYPE
	{
		SLIM,
		WING,
		WING_GREEN,
		LANCE,
		BOW,
		KNIGHT,
		BOSS,

		MAX_TYPE
	};

	enum EENEMY_SOUND
	{
		SE_SLIME,
		SE_ONE_SHOT,
		SE_MUL_SHOT,
		SE_BOSS_SHOT,
		SE_BOSS_DESTROY,

		MAX_ENEMY_SOUND,
	};

}



//===== クラス定義 =====
class CEnemy : public CCharacter
{
public:
	CEnemy();
	~CEnemy();
	// 仮想関数
	virtual void Update();
	virtual void LateUpdate() {};
	virtual void Draw();
	virtual void Destroy() { 
		// 経験値
		CExperience::Create(GetStatus()->GetExperience(), GetTransform()->GetPos());
		CObjectManager::DestroyObject(this);
	}

	static void Init();
	static void Uninit();

	virtual void OnCollision(CCollision *pCollision);
	virtual void OnAnimator(CAnimator *pAnimator) { m_charaAction.OnAnimatorAction(pAnimator); };

	// セット関数
	void SetTarget(CTransform *pTarget) { m_pTargetPlayer = pTarget; }
	void SetAttack(bool bFlag) { m_bAttack = bFlag; }

	// ゲット関数
	CEnemyUI* GetUI() { return m_pUI; }

protected:
	static CTexture sm_texture[ENEMY::MAX_TYPE];		// マスターテクスチャ
	static CSound sm_SE[ENEMY::MAX_ENEMY_SOUND];			// サウンド
	ENEMY::ETYPE m_eType;

	int m_nMoveCnt;
	int m_nMoveInterval;
	int m_nMoveType;
	int m_nJumpInterval;

	CCharacterAction m_charaAction;
	CViewArea *m_pViewArea;
	CAttackArea *m_pAttackArea;

	// ターゲット
	CTransform* m_pTargetPlayer;
	bool m_bAttack;

	// UI
	CEnemyUI* m_pUI;
};


//===== プロトタイプ宣言 =====
