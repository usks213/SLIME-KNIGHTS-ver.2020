//==================================================================
//								camera.h
//	GM21 カメラ生成	
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//	
//	2020/07/14	カメラクラス作成
//
//===================================================================

#pragma once

//====== インクルード部 ======
#include "../main.h"
#include "transform.h"


//===== クラス定義 =====

class CCamera
{
public:
	CCamera();
	~CCamera();
	void Destroy();

	// 静的関数
	static void Init();
	static void Uninit();
	static void Update();
	static void Create();

	static void SetCameraTarget(CTransform *pTarget);

	// セット関数
	static void SetCameraShake(int nFrame, int nShakeOffSet) 
	{
		m_bShake = true;
		m_nShakeFrame = nFrame;
		m_nShakeOffSet = nShakeOffSet;
	}

	static void SetCameraLimit(float fWidth, float fHeight) {
		m_fFieldWidth = fWidth;
		m_fFieldHeight = fHeight;
	}

	// ゲット関数
	static XMVECTOR GetEyePos() { return m_eyePos; }
	static XMVECTOR GetFocusPos() { return m_focusPos; }
	static XMVECTOR GetUpVec() { return m_upVec; }
	static XMVECTOR GetDir() { return m_dir; }
	static float GetScale() { return m_fScale; }
	static Float3 GetCameraPos() { return m_pos; }

	// 仮想関数
protected:

private:
	// 静的メンバ
	static float m_elevation;		// 縦回転
	static float m_azimuth;			// 横回転
	static float m_distance;		// カメラの距離

	static XMVECTOR m_focusPos;		// 注視点
	static XMVECTOR m_eyePos;		// カメラぞ座標
	static XMVECTOR m_upVec;		// カメラの上ベクトル

	static XMVECTOR m_dir;			// カメラの向き
	static float m_fScale;			// スケール
	static Float3 m_pos;			// カメラ座標
	static bool m_bShake;			// 振動フラグ
	static int m_nShakeFrame;		// 振動フレーム数
	static int m_nShakeOffSet;		// 振動幅

	// カメラ座標のリミット (マップの大きさ)
	static float m_fFieldWidth;
	static float m_fFieldHeight;

	// ターゲット
	static CTransform* m_pTarget;
};

