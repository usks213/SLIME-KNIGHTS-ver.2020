//==================================================================
//								objectManager.cpp
//	GM21 オブジェクトのリスト管理
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//
//	2020/06/19	オブジェクトのリストを管理するクラスを作成
//	2020/10/26	STL化
//
//===================================================================


//====== インクルード部 ======
#include "objectMgr.h"
#include "../texture.h"
#include "collision.h"

#include "../main.h"
#include "List.h"
#include "object.h"
#include "camera.h"

#include <functional>

using namespace std;

using obj_shr = std::shared_ptr<CObject>;
using obj_weak = std::weak_ptr<CObject>;

template <class T>
class CWeakPtr
{
public:
	CWeakPtr() {
	}
	CWeakPtr(std::shared_ptr<T> obj) {
		m_ptr = obj;
	}

	T* operator ->() {
		std::shared_ptr<T> ptr = (m_ptr.lock());
		if (ptr) {
			return &(*ptr);
		}
		else {
			return nullptr;
		}
	}

private:
	std::weak_ptr<T> m_ptr;
};

//===== マクロ定義 =====


//===== グローバル変数 =====


// 静的メンバの初期化
//List<CObject> CObjectManager::list;
//List<CObject> CObjectManager::m_terminatorList;
list<CObject*> CObjectManager::m_list;
list<std::list<CObject*>::iterator> CObjectManager::m_terminatorList;


//========================================
//
//	コンストラクタ
//
//========================================
CObjectManager::CObjectManager()
{
	
}


//========================================
//
//	デストラクタ
//
//========================================
CObjectManager::~CObjectManager()
{

}


//========================================
//
//	初期化
//
//========================================
void CObjectManager::Init()
{
	
}

//========================================
//
//	終了処理
//
//========================================
void CObjectManager::Uninit()
{
	// リストの消去
	AllClearList();
	// ここでターミナルを呼ぶ
	UpdateTerminator();

}

//========================================
//
//	全てのオブジェクトの更新
//
//========================================
void CObjectManager::Update()
{
	//// 先頭リストの取得
	//List<CObject>* pHead = list.GetHead();

	//// ノード無し
	//if (pHead == nullptr) return;

	//// オブジェクト
	//CObject* pObj = nullptr;

	//// リスト内の一斉更新
	//List<CObject> *pNode = nullptr;
	//List<CObject> *pNextBack = nullptr;
	//for (pNode = pHead; pNode != nullptr; pNode = pNextBack)
	//{
	//	// 次のポインタのバックアップを取る
	//	pNextBack = pNode->GetNext();

	//	// オブジェクトの更新
	//	pObj = pNode->GetThis();

	//	// ヒットストップ
	//	if (pObj->GetStop()) continue;

	//	// カメラ外をカリング
	//	if (pObj->GetLayer() == LAYER::PLAYER ||
	//		CheckCollisionRectToRect(CCamera::GetCameraPos(), pObj->GetTransform()->GetPos(),
	//		Float2{ SCREEN_WIDTH / CCamera::GetScale()*3.1f, SCREEN_HEIGHT / CCamera::GetScale()*3.1f }, pObj->GetTransform()->GetSize()))
	//	{
	//		// 一斉更新
	//		pNode->GetThis()->Update();
	//	}
	//}

	for (const auto& obj : m_list) 
	{
		if (obj->GetStop()) continue;

		// カメラ外をカリング
		if (obj->GetLayer() == LAYER::PLAYER ||
			CheckCollisionRectToRect(CCamera::GetCameraPos(), obj->GetTransform()->GetPos(),
				Float2{ SCREEN_WIDTH / CCamera::GetScale()*3.1f, SCREEN_HEIGHT / CCamera::GetScale()*3.1f }, obj->GetTransform()->GetSize()))
		{
			obj->Update();
		}
	}

	//// 変態プログラム
	//for (CWeakPtr<CObject> obj : m_list) { obj->Update(); }
	//for (CWeakPtr<CObject> obj : m_list) { obj->Draw(); }

	//int i = 0;

	//function<void(CWeakPtr<CObject>)> update[2] = { [&i](CWeakPtr<CObject> obj) { obj->Update(); i = ++i % 2; },
	//												[&i](CWeakPtr<CObject> obj) { obj->Draw();   i = ++i % 2; } };
	//function<void(CWeakPtr<CObject>)> draw	 =	[](CWeakPtr<CObject> obj) { obj->Draw(); };

	//for_each(m_list.begin(), m_list.end(), update[i]);
	//for_each(m_list.begin(), m_list.end(), draw);
	
}

//========================================
//
//	全てのオブジェクトの遅延更新
//
//========================================
void CObjectManager::LateUpdate()
{
	//// 先頭リストの取得
	//List<CObject>* pHead = list.GetHead();

	//// ノード無し
	//if (pHead == nullptr) return;

	//// オブジェクト
	//CObject* pObj = nullptr;

	//// リスト内の一斉更新
	//List<CObject> *pNode = nullptr;
	//List<CObject> *pNextBack = nullptr;
	//for (pNode = pHead; pNode != nullptr; pNode = pNextBack)
	//{
	//	// 次のポインタのバックアップを取る
	//	pNextBack = pNode->GetNext();

	//	// オブジェクトの更新
	//	pObj = pNode->GetThis();

	//	// ヒットストップ
	//	if (pObj->GetStop()) continue;

	//	// カメラ外をカリング
	//	//if (CheckCollisionRectToRect(CCamera::GetCameraPos(), pObj->GetTransform()->GetPos(),
	//		//Float2{ SCREEN_WIDTH / CCamera::GetScale()*1.1f, SCREEN_HEIGHT / CCamera::GetScale()*1.1f }, pObj->GetTransform()->GetSize()))
	//	{
	//		// 一斉更新
	//		pNode->GetThis()->LateUpdate();
	//	}
	//}

	for (const auto& obj : m_list)
	{
		if (obj->GetStop()) continue;

		//// カメラ外をカリング
		//if (obj->GetLayer() == LAYER::PLAYER ||
		//	CheckCollisionRectToRect(CCamera::GetCameraPos(), obj->GetTransform()->GetPos(),
		//		Float2{ SCREEN_WIDTH / CCamera::GetScale()*3.1f, SCREEN_HEIGHT / CCamera::GetScale()*3.1f }, obj->GetTransform()->GetSize()))
		{
			obj->LateUpdate();
		}
	}
}

bool comp(CObject *v1, CObject *v2)
{
	if (v1->GetLayer() < v2->GetLayer()) {
		return true;
	}
	else {
		return (v1->GetLayer() < v2->GetLayer());
	}

	// NOTREACHED
	return false;
}

//========================================
//
//	全てのオブジェクトの描画
//
//========================================
void CObjectManager::Draw()
{
	//// ここでターミナルを呼ぶ
	//UpdateTerminator();
	//// リストのソート
	////SortList();
	//QuickSortList();

	//// 先頭リストの取得
	//List<CObject>* pHead = list.GetHead();

	//// ノード無し
	//if (pHead == nullptr) return;

	//// オブジェクト
	//CObject* pObj = nullptr;

	//// リスト内の一斉描画
	//List<CObject> *pNode = nullptr;
	//List<CObject> *pNextBack = nullptr;
	//for (pNode = pHead; pNode != nullptr; pNode = pNextBack)
	//{
	//	// 次のポインタのバックアップを取る
	//	pNextBack = pNode->GetNext();

	//	// オブジェクトの更新
	//	pObj = pNode->GetThis();

	//	// カメラ外をカリング
	//	/*if (CheckCollisionRectToRect(CCamera::GetCameraPos(), pObj->GetTransform()->GetPos(),
	//		Float2{ SCREEN_WIDTH/CCamera::GetScale()*1.1f, SCREEN_HEIGHT/CCamera::GetScale()*1.1f }, pObj->GetTransform()->GetSize()))*/
	//	{
	//		// Z座標にレイヤーを格納する
	//		//pObj->GetTransform()->SetPosZ(-pObj->GetLayer());

	//		// 一斉描画
	//		pNode->GetThis()->Draw();
	//	}
	//	
	//}

	// ここでターミナルを呼ぶ
	UpdateTerminator();

	// 入れ替え
	m_list.sort(comp);

	for (const auto& obj : m_list)
	{
		//if (obj->GetStop()) continue;

		//// カメラ外をカリング
		//if (obj->GetLayer() == LAYER::PLAYER ||
		//	CheckCollisionRectToRect(CCamera::GetCameraPos(), obj->GetTransform()->GetPos(),
		//		Float2{ SCREEN_WIDTH / CCamera::GetScale()*3.1f, SCREEN_HEIGHT / CCamera::GetScale()*1.1f }, obj->GetTransform()->GetSize()))
		{
			obj->Draw();
		}
	}
}


//========================================================
//
//	リスト内のオブジェクトをレイヤー順にソート
//
//========================================================
void CObjectManager::SortList()
{
	//// 先頭リストの取得
	//List<CObject>* pHead = list.GetHead();

	//// ノード無し
	//if (pHead == nullptr) return;

	//// リスト内の一斉描画
	//List<CObject> *pNode = nullptr;
	//List<CObject> *pNextBack = nullptr;
	//bool bSortFlag = true;
	//CObject* pWork;

	//// 入れ替わりがなくなるまでループする
	//while (bSortFlag)
	//{
	//	// フラグを下げる
	//	bSortFlag = false;

	//	// バブルソート
	//	for (pNode = pHead; pNode != nullptr; pNode = pNextBack)
	//	{
	//		// 次のポインタのバックアップを取る
	//		pNextBack = pNode->GetNext();
	//		if (pNextBack == nullptr) break;
	//		// リストの比較をして
	//		// ここでスワップリスト
	//		// リストを繋ぎ直すのではなく、中身のデータのポインタを入れ替える
	//		// pStoreThisを入れ替える
	//		if (pNode->GetThis()->GetLayer() > pNextBack->GetThis()->GetLayer())
	//		{
	//			// ワークを使って入れ替え
	//			pWork = pNode->GetThis();
	//			pNode->SetThis(pNextBack->GetThis());
	//			pNextBack->SetThis(pWork);
	//			// フラグを立てる
	//			bSortFlag = true;
	//		}
	//	}
	//}

}


// 入れ替え
void NodeSwap(List<CObject>* pNodeA, List<CObject>* pNodeB)
{
	CObject* pWork;

	// ワークを使って入れ替え
	pWork = pNodeA->GetThis();
	pNodeA->SetThis(pNodeB->GetThis());
	pNodeB->SetThis(pWork);
}


//========================================================
//
//	リスト内のオブジェクトをレイヤー順にソート
//
//========================================================
void CObjectManager::QuickSortList()
{
	//// 先頭リストの取得
	//List<CObject>* pHead = list.GetHead();
	//List<CObject>* pTail = list.GetTail();
	//
	//// ノード無し
	//if (pHead == nullptr) return;

	//// ノードの数
	//int nMaxNode = list.GetMaxNode();
	//// ヘッドテール格納用
	//struct SHeadTail
	//{
	//	List<CObject> *pHead;
	//	List<CObject> *pTail;
	//	int nLeft;
	//	int nRight;
	//};

	//SHeadTail *startWork = new SHeadTail{pHead, pTail, 0, nMaxNode};
	//SHeadTail *hdtlWork;
	//// スタック
	//List<SHeadTail> stack;
	////List<CObject> objStack;
	//// 基準値
	//int nPivot = 0;
	//// リストの添え字
	//int pLeft = 0;
	//int pRight = 0;
	//int left;
	//int right;
	//int ptr = 0;

	//// スタックの初期化
	//stack.AddNode(startWork);
	//ptr++;

	//List<CObject>* pWorkL = nullptr;
	//List<CObject>* pWorkR = nullptr;
	//List<CObject> *pNode = nullptr;

	//static int nCnt = 0;
	//nCnt = 0;

	//while (ptr-- > 0)
	//{
	//	// スタックの取り出し
	//	hdtlWork = stack.GetTail()->GetThis();
	//	pLeft = left = hdtlWork->nLeft;
	//	pRight = right = hdtlWork->nRight;
	//	pWorkL = pHead = hdtlWork->pHead;
	//	pWorkR = pTail = hdtlWork->pTail;

	//	stack.DestroyNode(hdtlWork);
	//	delete hdtlWork;

	//	// ① 基準値の決定
	//	if (pTail == nullptr || pHead == nullptr) continue;

	//	//nPivot = (pHead->GetThis()->GetLayer() + pTail->GetThis()->GetLayer()) / 2;
	//	nPivot = (pHead->GetThis()->GetLayer() + pTail->GetThis()->GetLayer()) / 2;

	//	// ② リストのヘッドとテールそれぞれから基準値と比較探索する
	//	//    基準値をもとに、大きい、等しい、小さいの三つのグループに分ける
	//	do
	//	{
	//		// ヘッドとテールから探索して
	//		// 頭から基準値と比較
	//		for (; pWorkL != nullptr && pWorkL->GetThis()->GetLayer() < nPivot; pWorkL = pWorkL->GetNext())
	//		{
	//			//if (pWorkL->GetNext() == nullptr) break;
	//			pLeft++;
	//		}
	//		pLeft++;

	//		for (; pWorkR != nullptr && pWorkR->GetThis()->GetLayer() > nPivot; pWorkR = pWorkR->GetPrev())
	//		{
	//			//if (pWorkR->GetNext() == nullptr) break;
	//			pRight--;
	//		}
	//		//for (; pWorkL != nullptr; pWorkL = pWorkL->GetNext())
	//		//{
	//		//	if (pWorkL->GetThis()->GetLayer() < nPivot)
	//		//	{
	//		//		pLeft++;
	//		//	}
	//		//	//else if (pWorkL->GetThis()->GetLayer() == nPivot)
	//		//	//{
	//		//	//	// 同じだったらスタックに格納
	//		//	//	objStack.Push(pWorkL);
	//		//	//	pWorkL->Pop();
	//		//	//}
	//		//	////if (pWorkL->GetNext() == nullptr) break;

	//		//}
	//		//for (; pWorkR != nullptr; pWorkR = pWorkR->GetPrev())
	//		//{
	//		//	if (pWorkR->GetThis()->GetLayer() > nPivot)
	//		//	{
	//		//		pRight--;
	//		//	}
	//		//	//else if (pWorkR->GetThis()->GetLayer() == nPivot)
	//		//	//{
	//		//	//	// 同じだったらスタックに格納
	//		//	//	objStack.Push(pWorkR);
	//		//	//	pWorkR->Pop();
	//		//	//}
	//		//	////if (pWorkR->GetPrev() == nullptr) break;
	//		//}

	//		if (pWorkL == nullptr || pWorkR == nullptr) break;

	//		// 大きい方と小さい方を入れ替える
	//		if (pLeft <= pRight)
	//		{
	//			NodeSwap(pWorkL, pWorkR);
	//			//if (pWorkL->GetNext() != nullptr)
	//			{
	//				pWorkL = pWorkL->GetNext();
	//				pLeft++;
	//			}
	//			//if (pWorkR->GetPrev() != nullptr)
	//			{
	//				pWorkR = pWorkR->GetPrev();
	//				pRight--;
	//			}
	//			nCnt++;
	//		}

	//	} while (pLeft <= pRight);

	//	// ここでpWorkL,Rの間にnPivotと同じ値のスタックを格納する
	//	//pWorkR->PushPosNext(objStack.GetHead(), objStack.GetTail());

	//	// 分割する
	//	if (left < pRight)
	//	{
	//		hdtlWork = new SHeadTail{ pHead, pWorkR, left, pRight };
	//		stack.AddNode(hdtlWork);
	//		ptr++;
	//	}
	//	if (pLeft < right)
	//	{
	//		hdtlWork = new SHeadTail{ pWorkL, pTail, pLeft, right };
	//		stack.AddNode(hdtlWork);
	//		ptr++;
	//	}


	//	// ③ ②の大きい、小さいを更に基準値を決めて分割してく この時スタックに格納してく

	//	// ④ ヘッドとテールが同じになったらそのスタックは終了して次のスタックへ

	//	// ⑤ スタックが空になったらソート完了
	//}

	//nCnt++;
}


//========================================================
//
//	List内のオブジェクトをすべて消去
//
//========================================================
void CObjectManager::AllClearList()
{
	//// 先頭リストの取得
	//List<CObject>* pHead = list.GetHead();

	//// ノード無し
	//if (pHead == nullptr) return;

	//// リスト内の一斉更新
	//List<CObject> *pNode = nullptr;
	//List<CObject> *pNextBack = nullptr;
	//for (pNode = pHead; pNode != nullptr; pNode = pNextBack)
	//{
	//	// 次のポインタのバックアップを取る
	//	pNextBack = pNode->GetNext();

	//	if (pNode->GetThis()->GetLayer() < LAYER::MAX_LAYER)
	//	{
	//		if (pNode->GetThis()->GetLayer() == LAYER::PLAYER) continue;
	//		if (pNode->GetThis()->GetLayer() == LAYER::PLAYERATTACK) continue;
	//		if (pNode->GetThis()->GetLayer() == LAYER::ENEMYATTACK) continue;
	//		if (pNode->GetThis()->GetLayer() == LAYER::WEAPON) continue;
	//		if (pNode->GetThis()->GetLayer() == LAYER::STRING) continue;
	//		if (pNode->GetThis()->GetLayer() == LAYER::UI) continue;

	//		//オブジェクトの消去
	//		CObjectManager::DestroyObject(pNode->GetThis());
	//	}
	//}

	for (auto itr = m_list.begin(); itr != m_list.end(); itr++)
	{
		if ((*itr)->GetLayer() < LAYER::MAX_LAYER)
		{
			if ((*itr)->GetLayer() == LAYER::PLAYER) continue;
			if ((*itr)->GetLayer() == LAYER::PLAYERATTACK) continue;
			if ((*itr)->GetLayer() == LAYER::ENEMYATTACK) continue;
			if ((*itr)->GetLayer() == LAYER::WEAPON) continue;
			if ((*itr)->GetLayer() == LAYER::STRING) continue;
			if ((*itr)->GetLayer() == LAYER::UI) continue;

			//オブジェクトの消去
			CObjectManager::DestroyObject(*itr);

			//SetTerminator(*itr);
			//m_terminatorList.push_back(itr);
			// リストから消去
			//m_list.erase(itr);
		}
	}

}

//========================================================
//
//	List内の指定したレイヤーのオブジェクトをすべて消去
//
//========================================================
void CObjectManager::SelectClearList(LAYER::LAYER eLayer)
{
	//// 先頭リストの取得
	//List<CObject>* pHead = list.GetHead();

	//// ノード無し
	//if (pHead == nullptr) return;

	//// リスト内の一斉更新
	//List<CObject> *pNode = nullptr;
	//List<CObject> *pNextBack = nullptr;
	//for (pNode = pHead; pNode != nullptr; pNode = pNextBack)
	//{
	//	// 次のポインタのバックアップを取る
	//	pNextBack = pNode->GetNext();

	//	// 同じレイヤーだったら
	//	if (pNode->GetThis()->GetLayer() == eLayer)
	//	{
	//		//オブジェクトの消去
	//		CObjectManager::DestroyObject(pNode->GetThis());
	//	}
	//}

	for (const auto& obj : m_list)
	{
		if (obj->GetLayer() == eLayer)
		{
			//オブジェクトの消去
			CObjectManager::DestroyObject(obj);
		}
	}
}

//========================================================
//
//	ターミネーター内のオブジェクトを消去
//
//========================================================
void CObjectManager::SetTerminator(CObject* pObj)
{
	// 検索
	auto itr = find(m_list.begin(), m_list.end(), pObj);

	// リストになかったら
	if (itr == m_list.end()) return;

	if (pObj->m_bDestroy) return;

	pObj->m_bDestroy = true;

	// ターミネーター側で検索
	//auto terItr = find(m_terminatorList.begin(), m_terminatorList.end(), itr);

	// ターミネーターリストに既にあったら
	//if (terItr != m_terminatorList.end()) return;

	// ターミネーター格納
	m_terminatorList.push_back(itr);

	// リストから消去
	//m_list.erase(itr);

	//// ノード無し
	//if (m_terminatorList.GetHead() == nullptr)
	//{
	//	// ノードがあるものしかけさせない
	//	if (list.DestroyNode(pObj))
	//	{
	//		m_terminatorList.AddNode(pObj);
	//	}
	//	return;
	//}

	//// 先頭リストの取得
	//List<CObject>* pHead = m_terminatorList.GetHead();
	//// リスト内の一斉更新
	//List<CObject> *pNode = nullptr;
	//List<CObject> *pNextBack = nullptr;
	//for (pNode = pHead; pNode != nullptr; pNode = pNextBack)
	//{
	//	// 次のポインタのバックアップを取る
	//	pNextBack = pNode->GetNext();

	//	// 既に格納されてた場合は消さない
	//	if (pNode->GetThis() == pObj)
	//	{
	//		return;
	//	}
	//}

	//// ノードがあるものしかけさせない
	//if (list.DestroyNode(pObj))
	//{
	//	m_terminatorList.AddNode(pObj);
	//}
}

//========================================================
//
//	ターミネーター内のオブジェクトを消去
//
//========================================================
void CObjectManager::UpdateTerminator()
{
	//// 先頭リストの取得
	//List<CObject>* pHead = m_terminatorList.GetHead();

	//// ノード無し
	//if (m_terminatorList.GetHead() == nullptr) return;

	//// リスト内の一斉更新
	//List<CObject> *pNode = nullptr;
	//List<CObject> *pNextBack = nullptr;
	//CObject *pObj;
	//for (pNode = pHead; pNode != nullptr; pNode = pNextBack)
	//{
	//	// 次のポインタのバックアップを取る
	//	pNextBack = pNode->GetNext();
	//	pObj = pNode->GetThis();

	//	// ノードがあるものしかけさせない
	//	if (m_terminatorList.DestroyNode(pNode))
	//	{
	//		//オブジェクトの消去
	//		delete pObj;
	//	}
	//}

	//m_terminatorList.clear();
	for (auto itr : m_terminatorList)
	{
		// オブジェクトの消去
		delete (*itr);
		// リストから消去
		m_list.erase(itr);
	}

	m_terminatorList.clear();

	//for (auto obj : m_terminatorList)
	//{
	//	delete obj;
	//}
	//m_terminatorList.clear();
}