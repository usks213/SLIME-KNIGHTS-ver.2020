//==================================================================
//								enemyAction.h
//	 
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//	
//	2020/08/16	エネミーアクションクラスの作成
//
//===================================================================


//====== インクルード部 ======
#include "enemyAction.h"
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


//===== マクロ定義 =====
#define KNOCKBACK_FORCEX (12)
#define KNOCKBACK_FORCEY (12)
#define DEFAULT_ANIM_SPEED (12)
#define ATTACK_OFFSET_X (96)

//===== 静的関数 =====



//========================================
//
//	コンストラクタ
//
//========================================
CEnemyAction::CEnemyAction()
{

}


//========================================
//
//	デストラクタ
//
//========================================
CEnemyAction::~CEnemyAction()
{

}



//========================================
//
//	攻撃
//
//========================================
void CEnemyAction::Attack(int nAnimSpeed)
{
	
}


//========================================
//
//	アニメーション終了時に呼び出す
//
//========================================
void CEnemyAction::OnAnimatorAction(CAnimator *pAnim)
{
	// 終了したアニメーションの名前で分岐
	if (pAnim->GetCurrentAnimation()->GetName() == "RightAttack" || pAnim->GetCurrentAnimation()->GetName() == "LeftAttack")
	{

	}
}

