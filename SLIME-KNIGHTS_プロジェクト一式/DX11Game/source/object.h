//==================================================================
//								object.h
//	GM21 オブジェクト関連
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//
//	2020/06/03	ファイル分割してオブジェクト単位でソースにする
//	2020/06/14	オブジェクトを基底クラスに
//	2020/06/18	フレンド関数をスタティックの関数に変更
//	2020/08/15	ヒットストップを実装する
//
//===================================================================

#pragma once

//====== インクルード部 ======
#include "../main.h"
#include "transform.h"
#include "../sprite.h"
#include "../texture.h"


//===== マクロ定義 =====

// レイヤー
namespace LAYER
{
	enum LAYER
	{
		BG,
		FIELD,
		FLOOR,
		MAP_OBJ,
		ENEMY,
		WEAPON,
		PLAYER,
		ENEMYBULLET,
		PLAYERBULLET,
		ENEMYATTACK,
		PLAYERATTACK,
		EXPERIENCE,
		EFFECT,
		UI,
		STRING,
		RESULT_UI,
		FADE,
		MAX_LAYER,
	};
}


//===== クラス定義 =====

// 前定義
class CCollision;
class CAnimator;
class CRigidbody;
class CStatus;

class CObject
{
public:
	// コンストラクタ・デストラクタ
	 CObject();
	virtual ~CObject();
	// 仮想関数
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void LateUpdate() { return; }

	// 他のオブジェクトに当たった時に呼ばれる関数
	virtual void OnCollision(CCollision *pCollision) { return; }		// キャラクターに持たせる
	// アニメーション終了時に呼び出される関数
	virtual void OnAnimator(CAnimator *pAnimator) { return; }

	// 静的関数

	// ゲット関数
	int GetLayer() { return m_enLayer; }
	//CTexture* GetTexture() { return m_pTexture; }
	CTransform* GetTransform() { return &m_transform; }
	CSprite* GetSprite() { return &m_sprite; }
	// セット関数
	//void SetTexture(CTexture* tex) { m_pTexture = tex; }
	virtual CStatus* GetStatus() { return nullptr; }
	bool GetStop() { return m_bStop; }
	void SetStop(bool bFlag) { m_bStop = bFlag;; }

protected:

	// 形状データ
	CTransform m_transform;
	// スプライトデータ
	CSprite m_sprite;

	// レイヤー
	LAYER::LAYER m_enLayer;		// レイヤー番号
	bool m_bStop;
private:
	friend class CObjectManager;
	bool m_bDestroy;
};

