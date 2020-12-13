//==================================================================
//								player.h
//	GM21 プレイヤー関連
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
#include "playerAction.h"
#include "weapon.h"
#include "combo.h"


//===== クラス定義 =====
class CPlayer : public CCharacter
{
public:
	CPlayer();
	~CPlayer();
	// 仮想関数
	virtual void Update();
	virtual void LateUpdate();
	virtual void Draw();

	static void Init();
	static void Uninit();

	virtual void OnCollision(CCollision *pCollision);
	virtual void OnAnimator(CAnimator *pAnimator);

	// ゲット関数
	CSprite* GetAttackSprite() { return &m_attackSprite; }
	CAnimator* GetAttackAnimator() { return m_pAttackAnimator; }
	CWeapon* GetMainWeapon() { return m_pMainWeapon; }
	static CStatus GetBackUpStatus() { return sm_backupStatus; }

	void SetBackUpStatus() { m_status = sm_backupStatus; }
	void SetPlayerStop(bool bFlag) { 
		m_bPlayerStop = bFlag; 
		m_charaAction.Wait();
	}
	void SetInputStop(bool bFlag) {
		m_bInputStop = bFlag;
		m_charaAction.SetWait();
	}

	void SetReStartPos(Float3 pos)
	{
		m_transform.SetPos(pos);
		if (m_pMainWeapon)
		{
			m_pMainWeapon->GetTransform()->SetPos(pos);
		}
		if (m_charaAction.GetAttackBase())
		{
			m_charaAction.GetAttackBase()->GetTransform()->SetPos(pos);
		}

	}

	CCombo* GetCombo() { return m_pCombo; }

private:
	static CTexture sm_texture;		// マスターテクスチャ

	static CTexture sm_attackTexture;		// マスターテクスチャ
	CSprite m_attackSprite;
	CAnimator* m_pAttackAnimator;		// コンポーネント
	CPlayerAction m_charaAction;

	static CStatus sm_backupStatus;
	CWeapon *m_pMainWeapon;				// メインウェポン
	CCombo* m_pCombo;

	int m_nThrouTime;
	bool m_bMoveSE;
	int m_nMoveSECnt;

	bool m_bPlayerStop;
	bool m_bInputStop;

};

