//==================================================================
//								camera.cpp
//	GM21 カメラ
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//	
//	2020/07/14	カメラクラス作成
//
//===================================================================


//====== インクルード部 ======
#include "camera.h"
#include "../input.h"

//===== マクロ定義 =====
#define AngleToRadian(a) (a / 180.0f * 3.1415f)

//===== マクロ定義 =====


//===== 静的メンバ =====
CTransform* CCamera::m_pTarget = nullptr;

float CCamera::m_elevation;		// 縦回転
float CCamera::m_azimuth;		// 横回転
float CCamera::m_distance = -5.0f;		// カメラの距離

XMVECTOR CCamera::m_focusPos;	// 注視点
XMVECTOR CCamera::m_eyePos;		// カメラぞ座標
XMVECTOR CCamera::m_upVec;		// カメラの上ベクトル
XMVECTOR CCamera::m_dir;		// カメラの向き

float CCamera::m_fScale = 1.5f;	// スケール
Float3 CCamera::m_pos;					// カメラ座標
bool CCamera::m_bShake;					// 振動フラグ
int CCamera::m_nShakeFrame;				// 振動フレーム数
int CCamera::m_nShakeOffSet = 20;		// 振動幅

float CCamera::m_fFieldWidth  = 0;
float CCamera::m_fFieldHeight = 0;


//========================================
//
//	コンストラクタ
//
//========================================
CCamera::CCamera()
{
	m_elevation = 0.0f;		// 縦回転
	m_azimuth	= 0.0f;		// 横回転
	m_distance	= 1.5f;		// 距離

	m_fScale = 1.5f;

	m_pos = Float3{ 0, 0, 0 };

}


//========================================
//
//	デストラクタ
//
//========================================
CCamera::~CCamera()
{
	
}


//========================================
//
//	初期化
//
//========================================
void CCamera::Init()
{
	m_pos = Float3{ 0, 0, 0 };
	m_fFieldHeight = 0;
	m_fFieldWidth  = 0;

}

//========================================
//
//	終了処理
//
//========================================
void CCamera::Uninit()
{
	m_pos = Float3{ 0, 0, 0 };
	m_fFieldHeight = 0;
	m_fFieldWidth = 0;
}


//========================================
//
//	更新処理
//
//========================================
void CCamera::Update()
{
	//// カメラ操作
	//if (GetKeyPress(VK_Q))
	//	m_distance += 0.1f;

	//if (GetKeyPress(VK_E))
	//	m_distance -= 0.1f;

	// スケール
	m_fScale = powf(1.1f, m_distance);

	// カメラ座標
	if (m_pTarget)
	{
		m_pos = m_pTarget->GetPos();
	}
	
	// カメラ座標の限界
	if (m_pos.x > m_fFieldWidth - SCREEN_CENTER_X / m_fScale)  m_pos.x = m_fFieldWidth - SCREEN_CENTER_X / m_fScale;
	if (m_pos.y > m_fFieldHeight - SCREEN_CENTER_Y / m_fScale) m_pos.y = m_fFieldHeight - SCREEN_CENTER_Y / m_fScale;
	if (m_pos.x < SCREEN_CENTER_X / m_fScale) m_pos.x = SCREEN_CENTER_X / m_fScale;
	if (m_pos.y < SCREEN_CENTER_Y / m_fScale) m_pos.y = SCREEN_CENTER_Y / m_fScale;


	// カメラ振動
	m_nShakeFrame--;
	if (m_nShakeFrame < 0)
	{
		m_bShake = false;
	}
	if (m_bShake)
	{
		m_pos.x += -m_nShakeOffSet + rand() % (m_nShakeOffSet * 2);
		m_pos.y += -m_nShakeOffSet + rand() % (m_nShakeOffSet * 2);
	}
	

	//distance -= detail.input->getMouseState().lZ / 10;

	//Float3 *pPos = &m_pTarget->GetPos();

	//// ここにプレイヤーの座標を
	//m_focusPos = XMVectorSet(pPos->x, pPos->y, pPos->z, 1);

	//m_eyePos = XMVectorSet(
	//	m_distance * sinf(AngleToRadian(m_elevation)) * cosf(AngleToRadian(m_azimuth)),
	//	m_distance * cosf(AngleToRadian(m_elevation)),
	//	m_distance * sinf(AngleToRadian(m_azimuth)) * sinf(AngleToRadian(m_elevation)),
	//	1.0f);
	//m_eyePos += m_focusPos;

	//m_upVec = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);			// 視点の上ベクトル

	//// カメラの向きを計算
	//m_dir = m_focusPos - m_eyePos;
	//// ベクトルの正規化
	//m_dir = XMVector4Normalize(m_dir);
}


//========================================
//
//	ターゲットのセット
//
//========================================
void CCamera::SetCameraTarget(CTransform *pTarget)
{
	m_pTarget = pTarget;
}



//========================================
//
//	生成
//
//========================================
void CCamera::Create()
{
	
}

//========================================
//
//	初期化
//
//========================================
void CCamera::Destroy()
{

}