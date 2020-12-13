//==================================================================
//									rigidbody.h
//	リジッドボディ
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//
//	2020/07/12	リジッドボディクラス作成
//
//===================================================================

//====== インクルード部 ======
#include "rigidbody.h"
#include "collision.h"
#include "object.h"
#include "field.h"


//===== マクロ定義 =====
#define GRAVITY (1.0f)
#define DRAG (1.0f)

#define MAX_VELOCITY (48)

//===== クラス定義 =====



//===== プロトタイプ宣言 =====


// 静的メンバの初期化
List<CRigidbody> CRigidbody::m_list;


//========================================
//
//	コンストラクタ
//
//========================================
CRigidbody::CRigidbody()
{
	m_fDragX = DRAG;
	m_fMass = 1.0f;
	m_force = Float3{ 0, 0 ,0 };
	m_pTrans = nullptr;
	m_velocity = Float3{ 0, 0, 0 };
	m_bUseGravity = true;
	m_bSolid = false;
	m_enHitDir = DIRECTION::MAX_DIRECTION;
	m_dir = Float3{ 0, 0, 0 };
	m_fGraviyForce = GRAVITY;
	m_bStop = false;
}


//========================================
//
//	デストラクタ
//
//========================================
CRigidbody::~CRigidbody()
{

}


//========================================
//
//	初期化
//
//========================================
void CRigidbody::Init()
{
	

}

//========================================
//
//	終了処理
//
//========================================
void CRigidbody::Uninit()
{
	// 先頭リストの取得
	List<CRigidbody>* pHead = m_list.GetHead();

	// ノード無し
	if (pHead == nullptr) return;

	CRigidbody *pRb;

	// リスト内の一斉更新
	List<CRigidbody> *pNode = nullptr;
	List<CRigidbody> *pNextBack = nullptr;
	for (pNode = pHead; pNode != nullptr; pNode = pNode->GetNext())
	{
		pNextBack = pNode->GetNext();

		// リジッドボディ取得
		pRb = pNode->GetThis();

		pNode->DestroyNode(pNode);
		delete pRb;
	}

	// リストクリア
	m_list.ClearHead();
	m_list.ClearTail();

}

//========================================
//
//	更新
//
//========================================
void CRigidbody::Update()
{
	// 先頭リストの取得
	List<CRigidbody>* pHead = m_list.GetHead();

	// ノード無し
	if (pHead == nullptr) return;

	CRigidbody *pRb;
	CTransform *pTrans;
	Float3 pos;

	// リスト内の一斉更新
	List<CRigidbody> *pNode = nullptr;
	List<CRigidbody> *pNextBack = nullptr;
	for (pNode = pHead; pNode != nullptr; pNode = pNode->GetNext())
	{
		// リジッドボディ取得
		pRb = pNode->GetThis();
		// オブジェクトの取得
		pTrans = pRb->GetObj();

		// カメラ外ならはじく


		// ストップがオンならとばす
		if (pRb->m_bStop) continue;

		if (pRb->m_bSolid) continue;

		// 移動量
		pRb->m_velocity.x = 0;
		pRb->m_velocity.y = 0;

		// 重力
		if (pRb->m_bUseGravity)
		{
			pRb->m_force.y += pRb->m_fGraviyForce;
		}
		// 重力をオン
		pRb->m_bUseGravity = true;

		//// 外力	外力はAddForceに
		pRb->m_velocity.x += pRb->m_force.x;
		pRb->m_velocity.y += pRb->m_force.y;

		// ここで速度から向きを計算
		pRb->m_dir = Normalize(pRb->m_velocity);

		// 速度限界
		if (pRb->m_velocity.x >  MAX_VELOCITY) pRb->m_velocity.x =  MAX_VELOCITY;
		if (pRb->m_velocity.y >  MAX_VELOCITY) pRb->m_velocity.y =  MAX_VELOCITY;
		if (pRb->m_velocity.x < -MAX_VELOCITY) pRb->m_velocity.x = -MAX_VELOCITY;
		if (pRb->m_velocity.y < -MAX_VELOCITY) pRb->m_velocity.y = -MAX_VELOCITY;

		// 位置の更新
		pos = pTrans->GetPos();
		pos.x += pRb->m_velocity.x;
		pos.y += pRb->m_velocity.y;
		// 移動限界
		if (pos.x < 0.0f) pos.x = 0.0f;
		if (pos.y < 0.0f) pos.y = 0.0f;
		if (pos.x > (CField::GetWidth() - 1 ) * DEFAULT_OBJECT_SIZE) pos.x = (CField::GetWidth() - 1) * DEFAULT_OBJECT_SIZE;
		if (pos.y > (CField::GetHieght() - 1) * DEFAULT_OBJECT_SIZE) pos.y = (CField::GetHieght() - 1) * DEFAULT_OBJECT_SIZE;
		pTrans->SetPos(pos);

		// 抵抗で加速度を減らす	fDrag(0.0f ～ 1.0f)
		pRb->m_force.x *= (1.0f - pRb->m_fDragX);
		if (fabsf(pRb->m_force.x) < 0.01f) pRb->m_force.x = 0.0f;
		//pRb->m_force.y *= (1.0f - pRb->m_fDrag);
		if (fabsf(pRb->m_force.y) < 0.01f) pRb->m_force.y = 0.0f;
	}

}

//========================================
//
//	押し出し処理
//
//========================================
void CRigidbody::Extrusion(CRigidbody *pOther)
{
	// ソリッドなら
	if (m_bSolid) return;

	// 最短
	float fMinLenX;
	float fMinLenY;
	float fLenX;
	float fLenY;
	// 衝突後の力
	float fForceX;
	float fForceY;

	// 向きの初期化
	m_enHitDir = DIRECTION::MAX_DIRECTION;

	//--- 最短位置の計算 ---
	// 左
	fLenX = pOther->m_pTrans->GetPos().x - pOther->m_pTrans->GetSize().x / 2 - m_pTrans->GetPos().x - m_pTrans->GetSize().x / 2;
	fMinLenX = fLenX;

	// 右
	fLenX = pOther->m_pTrans->GetPos().x + pOther->m_pTrans->GetSize().x / 2 - m_pTrans->GetPos().x + m_pTrans->GetSize().x / 2;
	if (fabsf(fLenX) < fabsf(fMinLenX))
	{
		fMinLenX = fLenX;
	}

	// 上
	fLenY = pOther->m_pTrans->GetPos().y - pOther->m_pTrans->GetSize().y / 2 - m_pTrans->GetPos().y - m_pTrans->GetSize().y / 2;
	fMinLenY = fLenY;

	// 下
	fLenY = pOther->m_pTrans->GetPos().y + pOther->m_pTrans->GetSize().y / 2 - m_pTrans->GetPos().y + m_pTrans->GetSize().y / 2;
	if (fabsf(fLenY) < fabsf(fMinLenY))
	{
		fMinLenY = fLenY;
	}

	// Ｘ，Ｙの最短比較
	if (fabsf(fMinLenX) < fabsf(fMinLenY))	// ここでぶつかった方向も分かる!!
	{	// Ｘ側

		// 方向
		if (fMinLenX < 0)
		{
			// 左
			m_enHitDir = DIRECTION::LEFT;
			pOther->m_enHitDir = DIRECTION::RIGHT;
		}
		else
		{
			// 右
			m_enHitDir = DIRECTION::RIGHT;
			pOther->m_enHitDir = DIRECTION::LEFT;
		}

		// トリガーなら押し出ししない
		if (m_bTrigger) return;
		if (pOther->m_bTrigger) return;
		
		// お互いソリッドじゃない
		if (!pOther->m_bSolid)
		{
			m_velocity.x += fMinLenX;
			// 当たった時の力積を求める
			fForceX = ((m_fMass - pOther->m_fMass) * m_velocity.x + pOther->m_fMass * pOther->m_velocity.x) / (m_fMass + pOther->m_fMass);
			m_force.x = -fForceX;

			m_velocity.x += m_force.x;
			m_pTrans->SetPos(Float3{ m_pTrans->GetPos().x + m_velocity.x, m_pTrans->GetPos().y, 0 });
			return;
		}

		// 相手側ソリッドなら
		if (fMinLenX > 0)
		{
			// 右から
			// 押し出し
			m_pTrans->SetPos(Float3{ pOther->m_pTrans->GetPos().x + pOther->m_pTrans->GetSize().x / 2 + m_pTrans->GetSize().x / 2, 
				m_pTrans->GetPos().y, 0});
		}
		else
		{
			// 左から
			// 押し出し
			m_pTrans->SetPos(Float3{ pOther->m_pTrans->GetPos().x - pOther->m_pTrans->GetSize().x / 2 - m_pTrans->GetSize().x / 2,
				m_pTrans->GetPos().y, 0 });
		}
	}
	else
	{	// Ｙ側
		
		// 上からぶつかった時はデフォルトで重力を消す
		if (fMinLenY < 0)
		{
			m_enHitDir = DIRECTION::UP;
			pOther->m_enHitDir = DIRECTION::DOWN;
			// トリガーなら押し出ししない
			if (m_bTrigger) return;
			if (pOther->m_bTrigger) return;
			// 上
			m_bUseGravity = false;
			if (m_force.y > 0)
				m_force.y = 0;
		}
		else
		{
			m_enHitDir = DIRECTION::DOWN;
			pOther->m_enHitDir = DIRECTION::UP;
			// トリガーなら押し出ししない
			if (m_bTrigger) return;
			if (pOther->m_bTrigger) return;
			// 下
			if (m_force.y < 0)
				m_force.y = 0;
		}

		// お互いソリッドじゃない
		if (!pOther->m_bSolid)
		{
			m_velocity.y += fMinLenY;
			// 当たった時の力積を求める
			fForceY = ((m_fMass - pOther->m_fMass) * m_velocity.y + pOther->m_fMass * pOther->m_velocity.y) / (m_fMass + pOther->m_fMass);
			m_force.y = -fForceY;
			
			m_velocity.y += m_force.y;
			m_pTrans->SetPos(Float3{ m_pTrans->GetPos().x, m_pTrans->GetPos().y + m_velocity.y, 0 });
			return;
		}

		// 相手側ソリッドなら
		if (fMinLenY > 0)
		{
			// 下から
			// 押し出し
			m_pTrans->SetPos(Float3{ m_pTrans->GetPos().x, 
				pOther->m_pTrans->GetPos().y + pOther->m_pTrans->GetSize().y / 2 + m_pTrans->GetSize().y / 2, 0 });
		}
		else
		{
			// 上から
			// 押し出し
			m_pTrans->SetPos(Float3{ m_pTrans->GetPos().x, 
				pOther->m_pTrans->GetPos().y - pOther->m_pTrans->GetSize().y / 2 - m_pTrans->GetSize().y / 2, 0 });
		}
	}
}

//========================================
//
//	押し出し処理 円と円
//
//========================================
void CRigidbody::ExtrusionCircleToCircle(CRigidbody *pOther)
{
	FLOAT TotalWeight = m_fMass + pOther->m_fMass; // 質量の合計
	FLOAT RefRate = (1.0f);// + res_A * res_B); // 反発率

	Float3 C = pOther->GetObj()->GetPos(); // 衝突軸ベクトル
	C.x -= m_pTrans->GetPos().x;
	C.y -= m_pTrans->GetPos().y;
	C.z -= m_pTrans->GetPos().z;
	// 正規化
	C = Normalize(C);

	Float3 velowork = m_velocity;
	velowork.x -= pOther->m_velocity.x;
	velowork.y -= pOther->m_velocity.y;
	velowork.z -= pOther->m_velocity.z;
	FLOAT fDot = Dot(velowork, C); // 内積算出

	Float3 ConstVec;
	ConstVec.x = RefRate * fDot / TotalWeight * C.x; // 定数ベクトル
	ConstVec.y = RefRate * fDot / TotalWeight * C.y; // 定数ベクトル
	ConstVec.z = RefRate * fDot / TotalWeight * C.z; // 定数ベクトル

	
	// 衝突後速度ベクトルの算出
	Float3 veloA;
	Float3 veloB;

	veloA.x = -pOther->m_fMass * ConstVec.x + m_velocity.x;
	veloA.y = -pOther->m_fMass * ConstVec.y + m_velocity.y;
	veloA.z = -pOther->m_fMass * ConstVec.z + m_velocity.z;

	veloB.x = m_fMass * ConstVec.x + pOther->m_velocity.x;
	veloB.y = m_fMass * ConstVec.y + pOther->m_velocity.y;
	veloB.z = m_fMass * ConstVec.z + pOther->m_velocity.z;

	m_velocity			= veloA;
	pOther->m_velocity	= veloB;

	
	// 衝突後位置の算出
	Float3 posA = m_pTrans->GetPos();
	Float3 posB = pOther->GetObj()->GetPos();

	posA.x += veloA.x;
	posA.y += veloA.y;
	posA.z += veloA.z;

	posB.x += veloB.x;
	posB.y += veloB.y;
	posB.z += veloB.z;

	m_pTrans->SetPos(posA);
	pOther->GetObj()->SetPos(posB);

	return;
}



//========================================
//
//	生成
//
//========================================
CRigidbody* CRigidbody::Create(CTransform *pTrans, bool bSolid, bool bUseGravity, bool bTrigger)
{
	CRigidbody *pRb = new CRigidbody;

	m_list.AddNode(pRb);

	pRb->m_pTrans = pTrans;
	pRb->m_bSolid = bSolid;
	pRb->m_bUseGravity = bUseGravity;
	pRb->m_bTrigger = bTrigger;

	return pRb;
}


//========================================
//
//	消去
//
//========================================
void CRigidbody::Destroy()
{
	if (m_list.DestroyNode(this))
	{
		delete this;
	}
}

