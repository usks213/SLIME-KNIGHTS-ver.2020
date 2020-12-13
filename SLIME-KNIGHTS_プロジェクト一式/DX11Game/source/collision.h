//==================================================================
//									collision.h
//	コリジョン
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//
//	2020/06/24	コリジョン
//	2020/07/03	CCollisionクラスの作成
//
//===================================================================
#pragma once

//====== インクルード部 ======
#include "../main.h"
#include "List.h"

//===== マクロ定義 =====

enum ECOLLISION_TYPE
{
	RECTANGLE,
	CIRCLE,

	MAX_COLLISION_TYPE,
};

//===== クラス定義 =====
class CObject;
class CRigidbody;

// メモ： 汎用型にして
class CCollision
{
public:
	CCollision();
	~CCollision();
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	static void Collision(List<CCollision> *pMain);
	static void Collision(List<CCollision> *pMain, List<CCollision> *pSubHead);

	// 生成・消去
	static CCollision* Create(CObject *pObj, CRigidbody *pRb = nullptr, ECOLLISION_TYPE enColType = RECTANGLE);
	void Destroy();

	// ゲット関数
	CObject* GetObj() { return m_pObj; }
	CRigidbody* GetRb() { return m_pRb; }

private:
	static List<CCollision> m_list;
	CObject *m_pObj;
	CRigidbody *m_pRb;

	ECOLLISION_TYPE m_enColType;
};

// 四分木空間
class CCell
{
public:
	CCell()
	{

	}
	~CCell()
	{
		List<CCollision> *pHead = m_list.GetHead();

		if (pHead == nullptr) return;

		List<CCollision> *pNode = nullptr;
		List<CCollision> *pNextBack = nullptr;

		for (pNode = pHead; pNode != nullptr; pNode = pNextBack)
		{
			pNextBack = pNode->GetNext();

			m_list.DestroyNode(pNode);
		}
	}

	void ClearList()
	{
		List<CCollision> *pHead = m_list.GetHead();

		if (pHead == nullptr) return;

		List<CCollision> *pNode = nullptr;
		List<CCollision> *pNextBack = nullptr;

		for (pNode = pHead; pNode != nullptr; pNode = pNextBack)
		{
			pNextBack = pNode->GetNext();

			m_list.DestroyNode(pNode);
		}
	}

	List<CCollision>* GetList() { return &m_list; }

	static void SetMapSize(float width, float height)
	{
		m_fUnit_W = width  / (float)(1 << (m_uiLevel - 1));
		m_fUnit_H = height / (float)(1 << (m_uiLevel - 1));
	}

	static float GetUnitW() { return m_fUnit_W; }
	static float GetUnitH() { return m_fUnit_H; }
	static unsigned int GetUnitLevel() { return m_uiLevel; }

private:
	List<CCollision> m_list;
	static float m_fUnit_W;		// 最小レベル空間の幅単位
	static float m_fUnit_H;		// 最小レベル空間の高単位
	static const unsigned int m_uiLevel = 3;			// 最下位レベル
};


//===== プロトタイプ宣言 =====
float Dot(Float3 vec1, Float3 vec2);
float Cross2D(Float3 vec1, Float3 vec2);
float Length(Float3 vec);
Float3 Normalize(Float3 vec);

// 線分同士の当たり判定 正規化なし? (頂点は0から左上時計回り)
//bool CheckLineToLine(Float3 pos1, Float3 pos2, Float3 pos3, Float3 pos4, Float3 *pCrossPos);

// 線分同士の当たり判定 正規化なし? (頂点は0から左上時計回り)
bool CheckCollisionLine(Float3 pos1, Float3 pos2, Float3 pos3, Float3 pos4, Float3* outPos = nullptr, float *outT1 = nullptr);

//*******************************
//
//	矩形と矩形の当たり判定
//	
//	引数:
//		矩形１の中心座標
//		矩形２の中心座標
//		矩形１のサイズ
//		矩形２のサイズ
//
//	戻り値
//		false：接触していない
//		true：接触している
//
//*******************************
bool CheckCollisionRectToRect(Float3 centerPos1, Float3 centerPos2, Float2 size1, Float2 size2);

//*******************************
//
//	円と円の当たり判定
//	
//	引数:
//		円１の中心座標
//		円２の中心座標
//		円１の半径
//		円２の半径
//
//	戻り値
//		false：接触していない
//		true：接触している
//
//*******************************
bool CheckCollisionCircleToCircle(Float3 centerPos1, Float3 centerPos2, float radius1, float radius2);

//*******************************
//
//	円と矩形の当たり判定
//	
//	引数:
//		円１の中心座標
//		矩形２の中心座標
//		円１の半径
//		矩形２の大きさ
//
//	戻り値
//		false：接触していない
//		true：接触している
//
//*******************************
bool CheckCollisionCircleToRect(Float3 centerPos1, Float3 centerPos2, float radius1, Float2 size2);

