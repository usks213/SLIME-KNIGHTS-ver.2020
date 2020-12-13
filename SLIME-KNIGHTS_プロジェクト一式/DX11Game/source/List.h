//==================================================================
//								List.h
//	汎用リスト
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//
//	2020/06/18	テンプレートの汎用リストを作成(テスト)
//
//===================================================================
#pragma once

//====== インクルード部 ======


//===== クラス定義 =====
template <class T>
class List
{
public:
	List<T>();
	~List<T>();
	// リストにノードの追加
	//static void AddNode(T *);
	void AddNode(T *);
	// リストにあるの消去
	//static void DestroyNode(T *);
	bool DestroyNode(T *);
	bool DestroyNode(List<T>* pNode);
	// リスト内のノードの一斉更新
	//static void UpdateList();
	// リスト内のノードの一斉の描画
	//static void DrawList();

	// ゲット関数
	// リストの先頭取得
	//static List<T>* GetHead() { return m_pHead; }
	List<T>* GetHead() { return m_pHead; }
	// リストの最後尾取得
	//static List<T>* GetTail() { return m_pTail; }
	List<T>* GetTail() { return m_pTail; }
	// ノードの次のポインタ
	List<T>* GetNext() { return this->m_pNext; }
	// ノードの前のポインタ
	List<T>* GetPrev() { return this->m_pPrev; }
	// ノードの次のポインタ
	T* GetThis() { return this->m_pStoreThis; }
	// ノードの最大数
	int GetMaxNode() { return m_nMaxNode; }

	// セット関数
	void SetThis(T* pThis) { m_pStoreThis = pThis; }
	void ClearHead() { m_pHead = nullptr; }
	void ClearTail() { m_pTail = nullptr; }


	// プッシュ・ホップを実装する
	void Push(List<T>* pNode);
	void PushPosNext(List<T>* pHead, List<T>* pTail);
	void Pop()
	{
		List<T>* pNext = this->m_pNext;
		List<T>* pPrev = this->m_pPrev;
		
		if (pPrev != nullptr)
		{
			pPrev->m_pNext = pNext;
		}
		if (pNext != nullptr)
		{
			pNext->m_pPrev = pPrev;
		}

		this->m_pNext = nullptr;
		this->m_pPrev = nullptr;
	}

protected:
	// ノードの前後ポインタ リスト
	List<T>* m_pNext;
	List<T>* m_pPrev;
	// 格納されてるオブジェクトのポインタ
	T* m_pStoreThis;
	// リストの先頭アドレス
	//static List<T>* m_pHead;
	List<T>* m_pHead;
	// リストの最後尾アドレス
	//static List<T>* m_pTail;
	List<T>* m_pTail;

	static int m_nMaxNode;

private:

};

template <class T>
int List<T>::m_nMaxNode = 0;

// リストの先頭アドレス
//template <class T>
//List<T>* List<T>:: m_pHead = nullptr;
// リストの最後尾アドレス
//template <class T>
//List<T>* List<T>::m_pTail = nullptr;


//========================================
//
//	コンストラクタ
//
//========================================
template <class T>
List<T>::List()
{
	m_pNext = nullptr;
	m_pPrev = nullptr;
	m_pStoreThis = nullptr;
	m_pHead = nullptr;
	m_pTail = nullptr;
	m_nMaxNode++;
}

//========================================
//
//	デストラクタ
//
//========================================
template <class T>
List<T>::~List()
{
	m_pNext = nullptr;
	m_pPrev = nullptr;
	m_pStoreThis = nullptr;
	m_pHead = nullptr;
	m_pTail = nullptr;
	m_nMaxNode--;
}


//========================================
//
//	ノードの追加
//
//========================================
template <class T>
void List<T>::AddNode(T* pAdd)
{
	// 新しいノードの作成
	List<T>* pNewNode = new List<T>;

	// ノードの初期化
	pNewNode->m_pStoreThis = pAdd;
	pNewNode->m_pHead = m_pHead;
	pNewNode->m_pTail = m_pTail;
	
	// リストに格納
	// 先頭アドレスが空だったら
	if (m_pHead == nullptr)
	{
		// 頭とおしりを設定
		m_pHead = m_pTail = pNewNode;
		pNewNode->m_pHead = pNewNode->m_pTail = pNewNode;
		pNewNode->m_pNext = nullptr;
		pNewNode->m_pPrev = nullptr;
	}
	else
	{
		// 一番後ろに代入
		m_pTail->m_pNext = pNewNode;
		// おしりなので次は無し
		pNewNode->m_pNext = nullptr;
		// 一つ前は前回までの最後
		pNewNode->m_pPrev = m_pTail;
		// おしりの更新
		m_pTail = pNewNode->m_pTail = pNewNode;
	}
}

//========================================
//
//	ノードの追加
//
//========================================
template <class T>
void List<T>::Push(List<T>* pNode)
{
	// ノードの初期化
	pNode->m_pHead = m_pHead;
	pNode->m_pTail = m_pTail;

	// リストに格納
	// 先頭アドレスが空だったら
	if (m_pHead == nullptr)
	{
		// 頭とおしりを設定
		m_pHead = m_pTail = pNode;
		pNode->m_pNext = nullptr;
		pNode->m_pPrev = nullptr;
	}
	else
	{
		// 一番後ろに代入
		m_pTail->m_pNext = pNode;
		// おしりなので次は無し
		pNode->m_pNext = nullptr;
		// 一つ前は前回までの最後
		pNode->m_pPrev = m_pTail;
		// おしりの更新
		m_pTail = pNode;
	}
}

//========================================
//
//	ノードの追加
//
//========================================
template <class T>
void List<T>::PushPosNext(List<T>* pHead, List<T>* pTail)
{
	List<T>* pNextBack = this->m_pNext;

	this->m_pNext = pHead;
	pHead->m_pPrev = this;

	if (pNextBack != nullptr)
	{
		pNextBack->m_pPrev = pTail;
		pTail->m_pNext = pNextBack;
	}
}


//========================================
//
//	ノードの消去
//
//========================================
template <class T>
bool List<T>::DestroyNode(T *pDest)
{
	// ノードの検索
	List<T> *pNode = nullptr;
	for (pNode = m_pHead; pNode != nullptr; pNode = pNode->m_pNext)
	{
		// リスト内に消去するポインタを持つノードがあったなら
		if (pNode->m_pStoreThis == pDest)
		{
			break;
		}
	}
	// 同じノードがなかった
	if (pNode == nullptr) return false ;
	
	// 検索したノード
	List<T> *pMyNext = pNode->m_pNext;
	List<T> *pMyPrev = pNode->m_pPrev;

	// ノードが一個だけだった
	if (pMyNext == nullptr && pMyPrev == nullptr)
	{
		// ノードの消去
		delete pNode;
		// リストの初期化
		m_pHead = nullptr;
		m_pTail = nullptr;
		return true;
	}

	// リストから消去
	// 先頭アドレスだったら
	if (pMyPrev == nullptr)
	{
		// 自分の次のポインタは先頭アドレスになる
		m_pHead = pMyNext;
		m_pHead->m_pPrev = nullptr;
	}
	else
	{
		// 「自分の前のポインタの次」を「自分の次のポインタ」に
		pMyPrev->m_pNext = pMyNext;
	}

	// おけつだったら
	if (pMyNext == nullptr)
	{
		// 自分の前のポインタはおけつになる
		m_pTail = pMyPrev;
		m_pTail->m_pNext = nullptr;
	}
	else
	{
		// 「自分の次のポインタの前」を「自分の前のポインタ」に
		pMyNext->m_pPrev = pMyPrev;
	}

	// ノードの消去
	delete pNode;

	return true;
}

//========================================
//
//	ノードの消去
//
//========================================
template <class T>
bool List<T>::DestroyNode(List<T>* pNode)
{
	// 同じノードがなかった
	if (pNode == nullptr) return false;

	// 検索したノード
	List<T> *pMyNext = pNode->m_pNext;
	List<T> *pMyPrev = pNode->m_pPrev;

	// ノードが一個だけだった
	if (pMyNext == nullptr && pMyPrev == nullptr)
	{
		// ノードの消去
		delete pNode;
		// リストの初期化
		m_pHead = nullptr;
		m_pTail = nullptr;
		return true;
	}

	// リストから消去
	// 先頭アドレスだったら
	if (pMyPrev == nullptr)
	{
		// 自分の次のポインタは先頭アドレスになる
		m_pHead = pMyNext;
		m_pHead->m_pPrev = nullptr;
	}
	else
	{
		// 「自分の前のポインタの次」を「自分の次のポインタ」に
		pMyPrev->m_pNext = pMyNext;
	}

	// おけつだったら
	if (pMyNext == nullptr)
	{
		// 自分の前のポインタはおけつになる
		m_pTail = pMyPrev;
		m_pTail->m_pNext = nullptr;
	}
	else
	{
		// 「自分の次のポインタの前」を「自分の前のポインタ」に
		pMyNext->m_pPrev = pMyPrev;
	}

	// ノードの消去
	delete pNode;

	return true;
}



////========================================
////
////	リスト内のアップデート
////
////========================================
//template <class T>
//void List<T>::UpdateList()
//{
//	// ノード無し
//	if (m_pHead == nullptr) return;
//
//	List<T> *pNode = nullptr;
//	for (pNode = m_pHead; pNode != nullptr; pNode = pNode->m_pNext)
//	{
//		pNode->m_pStoreThis->Update();
//	}
//}
//
//
////========================================
////
////	リスト内の一斉描画
////
////========================================
//template <class T>
//void List<T>::DrawList()
//{
//	// ノード無し
//	if (m_pHead == nullptr) return;
//
//	List<T> *pNode = nullptr;
//	for (pNode = m_pHead; pNode != nullptr; pNode = pNode->m_pNext)
//	{
//		pNode->m_pStoreThis->Draw();
//	}
//}