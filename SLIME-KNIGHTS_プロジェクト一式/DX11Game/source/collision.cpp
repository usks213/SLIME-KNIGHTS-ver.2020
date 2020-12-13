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
//
//===================================================================

//====== インクルード部 ======
#include "collision.h"
#include "object.h"
#include "rigidbody.h"

//===== マクロ定義 =====
#define MAX_CELL (1+4+16+64)

//===== クラス定義 =====



//===== プロトタイプ宣言 =====


// 静的メンバの初期化
List<CCollision> CCollision::m_list;

float CCell::m_fUnit_W = 0.0f;		// 最小レベル空間の幅単位
float CCell::m_fUnit_H = 0.0f;		// 最小レベル空間の高単位


//========================================
//
//	コンストラクタ
//
//========================================
CCollision::CCollision()
{
	m_pObj = nullptr;
	m_pRb = nullptr;
	m_enColType = RECTANGLE;
}


//========================================
//
//	デストラクタ
//
//========================================
CCollision::~CCollision()
{

}


//========================================
//
//	初期化
//
//========================================
void CCollision::Init()
{
	

}

//========================================
//
//	終了処理
//
//========================================
void CCollision::Uninit()
{
	// 先頭リストの取得
	List<CCollision>* pHead = m_list.GetHead();

	// ノード無し
	if (pHead == nullptr) return;

	// キャラクターワーク
	CCollision *pCol = nullptr;

	// リスト内の一斉更新
	List<CCollision> *pNode = nullptr;
	List<CCollision> *pNextBack = nullptr;
	for (pNode = pHead; pNode != nullptr; pNode = pNextBack)
	{
		pNextBack = pNode->GetNext();

		pNode->DestroyNode(pNode);
	}
}

// ビット分割関数
DWORD BitSeparate32(DWORD n)
{
	n = (n | (n << 8)) & 0x00ff00ff;
	n = (n | (n << 4)) & 0x0f0f0f0f;
	n = (n | (n << 2)) & 0x33333333;
	return (n | (n << 1)) & 0x55555555;
}

// 2Dモートン空間番号算出関数
WORD Get2DMortonNumber(WORD x, WORD y)
{
	return (WORD)(BitSeparate32(x) | (BitSeparate32(y) << 1));
}

// 座標→線形4分木要素番号変換関数
DWORD GetPointElem(float pos_x, float pos_y)
{
	// 本当はフィールドの大きさとか
	return Get2DMortonNumber((WORD)(pos_x / CCell::GetUnitW()), (WORD)(pos_y / CCell::GetUnitH()));
}

// 当たり判定
void CCollision::Collision(List<CCollision> *pMain, List<CCollision> *pSubHead)
{
	// 先頭リストの取得
	List<CCollision>* pHead = pSubHead;

	// ノード無し
	if (pHead == nullptr) return;

	// キャラクターワーク
	CObject *pMainObj = pMain->GetThis()->m_pObj;
	CObject *pCol = nullptr;

	CTransform *pMainTrans = pMainObj->GetTransform();
	CTransform *pColTrans = nullptr;

	// リスト内の一斉更新
	List<CCollision> *pNode = nullptr;
	List<CCollision> *pNextBack = nullptr;
	for (pNode = pHead; pNode != nullptr; pNode = pNextBack)
	{
		// 次のポインタのバックアップを取る
		pNextBack = pNode->GetNext();
		// 相手側のデータ
		pCol = pNode->GetThis()->m_pObj;
		pColTrans = pCol->GetTransform();

		//===== ここでプリミティブの種類で当たり判定を分ける =====

		// 矩形と矩形
		if (pMain->GetThis()->m_enColType == RECTANGLE && pNode->GetThis()->m_enColType == RECTANGLE)
		{
			if (CheckCollisionRectToRect(pMainTrans->GetPos(), pColTrans->GetPos(),
				pMainTrans->GetSize(), pColTrans->GetSize()))
			{
				// 押し出し
				if (pMain->GetThis()->m_pRb != nullptr && pNode->GetThis()->m_pRb != nullptr)
				{
					// 押し出し処理
					pMain->GetThis()->m_pRb->Extrusion(pNode->GetThis()->m_pRb);
					// 相手側の押し出し処理
					pNode->GetThis()->m_pRb->Extrusion(pMain->GetThis()->m_pRb);
				}
				// 当たってたら判定後の関数を呼ぶ
				pMainObj->OnCollision(pNode->GetThis());
				// 相手側も呼ぶ
				pCol->OnCollision(pMain->GetThis());
			}
		}
		// 円と円
		else if (pMain->GetThis()->m_enColType == CIRCLE && pNode->GetThis()->m_enColType == CIRCLE)
		{
			if (CheckCollisionCircleToCircle(pMainTrans->GetPos(), pColTrans->GetPos(), pMainTrans->GetSize().x, pColTrans->GetSize().x))
			{
				// 押し出し
				if (pMain->GetThis()->m_pRb != nullptr && pNode->GetThis()->m_pRb != nullptr)
				{
					pMain->GetThis()->m_pRb->ExtrusionCircleToCircle(pNode->GetThis()->m_pRb);
				}

				// 当たってたら判定後の関数を呼ぶ
				pMainObj->OnCollision(pNode->GetThis());
				// 相手側も呼ぶ
				pCol->OnCollision(pMain->GetThis());
			}
		}
		// 円と矩形
		else if (pMain->GetThis()->m_enColType == CIRCLE && pNode->GetThis()->m_enColType == RECTANGLE)
		{
			if (CheckCollisionCircleToRect(pMainTrans->GetPos(), pColTrans->GetPos(), pMainTrans->GetSize().x, pColTrans->GetSize()))
			{
				// 押し出し
				if (pMain->GetThis()->m_pRb != nullptr && pNode->GetThis()->m_pRb != nullptr)
				{
					// 押し出し処理
					pMain->GetThis()->m_pRb->Extrusion(pNode->GetThis()->m_pRb);
					// 相手側の押し出し処理
					pNode->GetThis()->m_pRb->Extrusion(pMain->GetThis()->m_pRb);
				}

				// 当たってたら判定後の関数を呼ぶ
				pMainObj->OnCollision(pNode->GetThis());
				// 相手側も呼ぶ
				pCol->OnCollision(pMain->GetThis());
			}

		}
		// 矩形と円
		else if (pMain->GetThis()->m_enColType == RECTANGLE && pNode->GetThis()->m_enColType == CIRCLE)
		{
			if (CheckCollisionCircleToRect(pColTrans->GetPos(), pMainTrans->GetPos(), pColTrans->GetSize().x, pMainTrans->GetSize()))
			{
				// 押し出し
				if (pMain->GetThis()->m_pRb != nullptr && pNode->GetThis()->m_pRb != nullptr)
				{
					// 押し出し処理
					pMain->GetThis()->m_pRb->Extrusion(pNode->GetThis()->m_pRb);
					// 相手側の押し出し処理
					pNode->GetThis()->m_pRb->Extrusion(pMain->GetThis()->m_pRb);
				}

				// 当たってたら判定後の関数を呼ぶ
				pMainObj->OnCollision(pNode->GetThis());
				// 相手側も呼ぶ
				pCol->OnCollision(pMain->GetThis());
			}
		}

		// 点と線

		// 線と線

		// 三角

		//=========================================================

	}

}

//========================================
//
//	更新
//
//========================================
void CCollision::Update()
{
	// 先頭リストの取得
	List<CCollision>* pHead = m_list.GetHead();

	// ノード無し
	if (pHead == nullptr) return;

	// 空間レベルの数
	const unsigned int uiLevel = CCell::GetUnitLevel();
	const unsigned int nMaxCell = MAX_CELL;

	// 空間の作成
	CCell mainCell[MAX_CELL];
	CCell subCell[MAX_CELL];
	// モートン番号
	DWORD Def = 0;
	DWORD wLeftTop = 0;
	DWORD wRightDown = 0;
	CTransform *pTrans;

	// リスト内の一斉更新
	List<CCollision> *pNode = nullptr;
	List<CCollision> *pNextBack = nullptr;
	for (pNode = pHead; pNode != nullptr; pNode = pNode->GetNext())
	{
		// 次のポインタのバックアップを取る
		//pNextBack = pNode->GetNext();

		// ここでカメラ外ならAABBではじく
		
		// ヒットストップ
		if (pNode->GetThis()->GetObj()->GetStop()) continue;

		pTrans = pNode->GetThis()->GetObj()->GetTransform();

		// ここで空間の登録をする
		// 左上と右下を出す
		wLeftTop = GetPointElem(pTrans->GetPos().x - pTrans->GetSize().x / 2,
								pTrans->GetPos().y - pTrans->GetSize().y / 2);
		wRightDown = GetPointElem(	pTrans->GetPos().x + pTrans->GetSize().x / 2,
									pTrans->GetPos().y + pTrans->GetSize().y / 2);
		// XORをとる	
		Def = wLeftTop ^ wRightDown;
		unsigned int HiLevel = 0;
		unsigned int i;
		for (i = 0; i < uiLevel; i++)
		{
			DWORD Check = (Def >> (i * 2)) & 0x3;
			if (Check != 0)
				HiLevel = i + 1;
		}
		DWORD SpaceNum = wRightDown >> (HiLevel * 2);
		int nPow4 = 1;
		for (i = 0; i < uiLevel - HiLevel; i++) nPow4 *= 4;
		DWORD AddNum = (nPow4 - 1) / 3;
		SpaceNum += AddNum;	// これが今いる空間

		// 空間外ははじく
		if (SpaceNum > nMaxCell - 1) continue;

		// 今いる空間のメインリストに格納
		mainCell[SpaceNum].GetList()->AddNode(pNode->GetThis());

		// 今いる空間の親のサブに格納
		while (SpaceNum > 0)
		{
			SpaceNum--;
			SpaceNum /= 4;

			subCell[SpaceNum].GetList()->AddNode(pNode->GetThis());
		}

		// ここでダブルループで、他のキャラと総当たりで当たり判定を取る
		//pNode->GetThis()->Collision(pNode);
	}

	// ここでそれぞれの空間内でのに当たり判定を取る
	for (int i = 0; i < nMaxCell; i++)
	{
		pHead = mainCell[i].GetList()->GetHead();
		if (pHead == nullptr) continue;

		for (pNode = pHead; pNode != nullptr; pNode = pNextBack)
		{
			pNextBack = pNode->GetNext();

			// 当たり判定を取る
			pNode->GetThis()->Collision(pNode, pNextBack);
		}
	}

	// 次に親から子への当たり判定を取る
	for (int i = 0; i < nMaxCell; i++)
	{
		pHead = mainCell[i].GetList()->GetHead();
		if (pHead == nullptr) continue;

		for (pNode = pHead; pNode != nullptr; pNode = pNextBack)
		{
			pNextBack = pNode->GetNext();

			// 当たり判定を取る
			pNode->GetThis()->Collision(pNode, subCell[i].GetList()->GetHead());
		}
	}

	/*for (int i = 0; i < 85; i++)
	{
		mainCell[i].ClearList();
		subCell[i].ClearList();
	}*/

}

//========================================
//
//	当たり判定
//
//========================================
void CCollision::Collision(List<CCollision> *pMain)
{
	// 先頭リストの取得
	List<CCollision>* pHead = m_list.GetHead();
	List<CCollision>* pTail = m_list.GetTail();

	// ノード無し
	if (pHead == nullptr) return;

	// キャラクターワーク
	CObject *pMainObj = pMain->GetThis()->m_pObj;
	CObject *pCol = nullptr;

	CTransform *pMainTrans = pMainObj->GetTransform();
	CTransform *pColTrans  = nullptr;

	// リスト内の一斉更新
	List<CCollision> *pNode = nullptr;
	List<CCollision> *pNextBack = nullptr;
	for (pNode = pMain->GetNext(); pNode != nullptr; pNode = pNextBack)
	{
		// 次のポインタのバックアップを取る
		pNextBack = pNode->GetNext();
		// 相手側のデータ
		pCol = pNode->GetThis()->m_pObj;
		pColTrans = pCol->GetTransform();

		//===== ここでプリミティブの種類で当たり判定を分ける =====

		// 矩形と矩形
		if (pMain->GetThis()->m_enColType == RECTANGLE && pNode->GetThis()->m_enColType == RECTANGLE)
		{
			if (CheckCollisionRectToRect(pMainTrans->GetPos(), pColTrans->GetPos(),
				pMainTrans->GetSize(), pColTrans->GetSize()))
			{
				// 押し出し
				if (pMain->GetThis()->m_pRb != nullptr && pNode->GetThis()->m_pRb != nullptr)
				{
					// 押し出し処理
					pMain->GetThis()->m_pRb->Extrusion(pNode->GetThis()->m_pRb);
					// 相手側の押し出し処理
					pNode->GetThis()->m_pRb->Extrusion(pMain->GetThis()->m_pRb);
				}
				// 当たってたら判定後の関数を呼ぶ
				pMainObj->OnCollision(pNode->GetThis());
				// 相手側も呼ぶ
				pCol->OnCollision(pMain->GetThis());
			}
		}
		// 円と円
		else if(pMain->GetThis()->m_enColType == CIRCLE && pNode->GetThis()->m_enColType == CIRCLE)
		{
			if (CheckCollisionCircleToCircle(pMainTrans->GetPos(), pColTrans->GetPos(), pMainTrans->GetSize().x, pColTrans->GetSize().x))
			{
				// 押し出し
				if (pMain->GetThis()->m_pRb != nullptr && pNode->GetThis()->m_pRb != nullptr)
				{
					pMain->GetThis()->m_pRb->ExtrusionCircleToCircle(pNode->GetThis()->m_pRb);
				}

				// 当たってたら判定後の関数を呼ぶ
				pMainObj->OnCollision(pNode->GetThis());
				// 相手側も呼ぶ
				pCol->OnCollision(pMain->GetThis());
			}
		}
		// 円と矩形
		else if (pMain->GetThis()->m_enColType == CIRCLE && pNode->GetThis()->m_enColType == RECTANGLE)
		{
			if (CheckCollisionCircleToRect(pMainTrans->GetPos(), pColTrans->GetPos(), pMainTrans->GetSize().x, pColTrans->GetSize()))
			{
				// 押し出し
				if (pMain->GetThis()->m_pRb != nullptr && pNode->GetThis()->m_pRb != nullptr)
				{
					// 押し出し処理
					pMain->GetThis()->m_pRb->Extrusion(pNode->GetThis()->m_pRb);
					// 相手側の押し出し処理
					pNode->GetThis()->m_pRb->Extrusion(pMain->GetThis()->m_pRb);
				}

				// 当たってたら判定後の関数を呼ぶ
				pMainObj->OnCollision(pNode->GetThis());
				// 相手側も呼ぶ
				pCol->OnCollision(pMain->GetThis());
			}

		}
		// 矩形と円
		else if(pMain->GetThis()->m_enColType == RECTANGLE && pNode->GetThis()->m_enColType == CIRCLE)
		{
			if (CheckCollisionCircleToRect(pColTrans->GetPos(), pMainTrans->GetPos(), pColTrans->GetSize().x, pMainTrans->GetSize()))
			{
				// 押し出し
				if (pMain->GetThis()->m_pRb != nullptr && pNode->GetThis()->m_pRb != nullptr)
				{
					// 押し出し処理
					pMain->GetThis()->m_pRb->Extrusion(pNode->GetThis()->m_pRb);
					// 相手側の押し出し処理
					pNode->GetThis()->m_pRb->Extrusion(pMain->GetThis()->m_pRb);
				}

				// 当たってたら判定後の関数を呼ぶ
				pMainObj->OnCollision(pNode->GetThis());
				// 相手側も呼ぶ
				pCol->OnCollision(pMain->GetThis());
			}
		}
		
		// 点と線

		// 線と線

		// 三角

		//=========================================================

	}

}


//=====================================================
//
//	描画	// 当たり判定の大きさを描画してあげる
//
//=====================================================
void CCollision::Draw()
{
	CSprite sprite;
	sprite.SetColor(Float4{ 1.0f, 1.0f, 0.0f, 0.1f });

	// 先頭リストの取得
	List<CCollision>* pHead = m_list.GetHead();

	// ノード無し
	if (pHead == nullptr) return;

	// キャラクターワーク
	CCollision *pCol = nullptr;

	// リスト内の一斉更新
	List<CCollision> *pNode = nullptr;
	List<CCollision> *pNextBack = nullptr;
	for (pNode = pHead; pNode != nullptr; pNode = pNextBack)
	{
		pNextBack = pNode->GetNext();

		if (pNode->GetThis()->GetObj()->GetLayer() == LAYER::MAX_LAYER) continue;
		if (pNode->GetThis()->GetObj()->GetLayer() == LAYER::PLAYERATTACK) continue;
		sprite.Draw(pNode->GetThis()->GetObj()->GetTransform());
	}
}


//========================================
//
//	生成
//
//========================================
CCollision* CCollision::Create(CObject *pObj, CRigidbody *pRb, ECOLLISION_TYPE enColType)
{
	CCollision *pCol = new CCollision;

	m_list.AddNode(pCol);

	pCol->m_pObj = pObj;
	pCol->m_pRb = pRb;
	pCol->m_enColType = enColType;

	return pCol;
}


//========================================
//
//	消去
//
//========================================
void CCollision::Destroy()
{
	if (m_list.DestroyNode(this))
	{
		delete this;
	}
}



// 内積
float Dot(Float3 vec1, Float3 vec2)
{
	float dot;

	dot = vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;

	return dot;
}

// 外積
float Cross2D(Float3 vec1, Float3 vec2)
{
	return vec1.x * vec2.y - vec1.y * vec2.x;
}

// ベクトルの長さ
float Length(Float3 vec)
{
	return sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

// ベクトルの正規化
Float3 Normalize(Float3 vec)
{
	float mag = Length(vec);
	vec.x /= mag;
	vec.y /= mag;
	vec.z /= mag;

	return vec;
}


// 線分の衝突
bool CheckCollisionLine(Float3 pos1, Float3 pos2, Float3 pos3, Float3 pos4, Float3* outPos, float *outT1) 
{

	Float3 v = { pos3.x - pos1.x, pos3.y - pos1.y, 0.0f };
	// ベクトル
	Float3 vec1 = { pos2.x - pos1.x, pos2.y - pos1.y, 0.0f };
	Float3 vec2 = { pos4.x - pos3.x, pos4.y - pos3.y, 0.0f };

	float Crs_v1_v2 = Cross2D(vec1, vec2);
	if (Crs_v1_v2 == 0.0f) {
		// 平行状態
		return false;
	}

	float Crs_v_v1 = Cross2D(v, vec1);
	float Crs_v_v2 = Cross2D(v, vec2);

	float t1 = Crs_v_v2 / Crs_v1_v2;
	float t2 = Crs_v_v1 / Crs_v1_v2;

	if(outT1)
		*outT1 = t2;

	const float eps = 0.00001f;
	if (t1 + eps < 0 || t1 - eps > 1 || t2 + eps < 0 || t2 - eps > 1) {
		// 交差していない
		return false;
	}

	if (outPos)
	{
		//*outPos = seg1.s + seg1.v * t1;
		outPos->x = pos1.x + vec1.x * t1;
		outPos->y = pos1.y + vec1.y * t1;
		outPos->z = 0;
	}
	return true;
}



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
bool CheckCollisionRectToRect(Float3 centerPos1, Float3 centerPos2, Float2 size1, Float2 size2)
{
	Float2 halfSize1 = Float2{ size1.x / 2.0f, size1.y / 2.0f };
	Float2 halfSize2 = Float2{ size2.x / 2.0f, size2.y / 2.0f };

	if ((centerPos2.x - halfSize2.x < centerPos1.x + halfSize1.x) &&		// 2の左端 < 1の右端
		(centerPos1.x - halfSize1.x < centerPos2.x + halfSize2.x ))		// 1の左端 < 2の右端
	{
		if ((centerPos2.y - halfSize2.y < centerPos1.y + halfSize1.y) &&		// 2の上端 < 1の下端
			(centerPos1.y - halfSize1.y < centerPos2.y + halfSize2.y))		// 1の上端 < 2の下端
		{
			return true;
		}
	}



	return false;
}




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
bool CheckCollisionCircleToCircle(Float3 centerPos1, Float3 centerPos2, float radius1, float radius2)
{
	float fX = centerPos1.x - centerPos2.x;
	float fY = centerPos1.y - centerPos2.y;
	float fR = radius1 + radius2;

	if (fX * fX + fY * fY		// (円1の中心座標X - 円2の中心座標X)の2乗 + (円1の中心座標Y - 円2の中心座標Y)の2乗
		<= fR * fR)				// (円1の半径+円2の半径)の2乗
	{
		return true;
	}

	return false;
}


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
bool CheckCollisionCircleToRect(Float3 centerPos1, Float3 centerPos2, float radius1, Float2 size2)
{
	// 円
	float x = centerPos1.x;
	float y = centerPos1.y;
	float radius = radius1;

	// 矩形
	float L = centerPos2.x - size2.x / 2.0f;
	float R = centerPos2.x + size2.x / 2.0f;
	float T = centerPos2.y - size2.y / 2.0f;
	float B = centerPos2.y + size2.y / 2.0f;


	if (L - radius > x || R + radius < x || T - radius > y || B + radius < y) {//矩形の領域判定1
		return false;
	}
	if (L > x && T > y && !((L - x) * (L - x) + (T - y) * (T - y) < radius * radius)) {//左上の当たり判定
		return false;
	}
	if (R < x && T > y && !((R - x) * (R - x) + (T - y) * (T - y) < radius * radius)) {//右上の当たり判定
		return false;
	}
	if (L > x && B < y && !((L - x) * (L - x) + (B - y) * (B - y) < radius * radius)) {//左下の当たり判定
		return false;
	}
	if (R < x && B < y && !((R - x) * (R - x) + (B - y) * (B - y) < radius * radius)) {//右下の当たり判定
		return false;
	}
	return true;//すべての条件が外れたときに当たっている
}