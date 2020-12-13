//==================================================================
//								transform.h
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

#pragma once

//====== インクルード部 ======
#include "../main.h"

//===== マクロ定義 =====


//===== クラス定義 =====
class CTransform
{
public:
	CTransform();
	~CTransform();

	// ゲット関数
	float GetAngle() { return m_fAngle; }
	Float3 GetPos() { return m_pos; }
	float GetSizeX() { return m_size.x; }
	Float2 GetSize() { return m_size; }
	Float3 GetDir() { return m_dir; }
	// セット関数
	void SetPos(Float3 pos) { m_pos = pos; }
	void SetPosZ(float z) { m_pos.z = z; }
	void SetAngle(float fAngle) { m_fAngle = fAngle; }
	void SetSize(Float2 size) { m_size = size; }
	void SetDir(Float3 dir) { m_dir = dir; }
private:
	Float3 m_pos;				// 中心座標
	Float2 m_size;				// 縦横サイズ
	float m_fAngle;				// オブジェクトの回転角度
	Float3 m_dir;				// 向き
};

