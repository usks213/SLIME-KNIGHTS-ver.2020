//==================================================================
//								transform.cpp
//	トランスフォーム
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//
//	2020/07/22	トランスフォームクラスの作成
//
//===================================================================


//====== インクルード部 ======
#include "transform.h"


//===== マクロ定義 =====



//========================================
//
//	コンストラクタ
//
//========================================
CTransform::CTransform()
{
	m_pos = Float3{ 0.0f, 0.0f, 0.0f };
	m_size = Float2{ DEFAULT_OBJECT_SIZE, DEFAULT_OBJECT_SIZE };
	m_fAngle = 0.0f;
	m_dir = Float3{ 0.0f, 0.0f, 0.0f };
}

//========================================
//
//	デストラクタ
//
//========================================
CTransform::~CTransform()
{

}