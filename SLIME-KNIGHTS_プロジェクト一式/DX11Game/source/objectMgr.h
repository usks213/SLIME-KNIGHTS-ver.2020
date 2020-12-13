//==================================================================
//								objectMgr.h
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

#pragma once

//====== インクルード部 ======
#include "../main.h"
#include "List.h"
#include "object.h"
#include <list>


//===== クラス定義 =====
class CObjectManager
{
public:
	CObjectManager();
	~CObjectManager();

	static void Init();
	static void Uninit();

	template <class T>
	static T* CreateObject(Float3 pos = Float3{ 0, 0, 0 })
	{
		T* pObj = new T();
		//list.AddNode(pObj);
		//std::shared_ptr<CObject> ptr;
		//ptr.reset(pObj);
		m_list.push_back(pObj);
		pObj->GetTransform()->SetPos(pos);

		return pObj;
	}
	static void Update();
	static void LateUpdate();
	static void Draw();

	// ここをターミネーターを使ったバッチ処理にする
	template <class T>
	static void DestroyObject(T* pObj)
	{
		if (pObj == nullptr) return;
		SetTerminator(pObj);
		/*list.DestroyNode(pObj);
		delete pObj;
		pObj = nullptr;*/
	}
	//static void Uninit();
	static void SortList();
	static void QuickSortList();
	static void AllClearList();
	static void SelectClearList(LAYER::LAYER eLayer);

	static void SetTerminator(CObject* pObj);
	static void UpdateTerminator();

private:
	//static List<CObject> list;
	//static List<CObject> m_terminatorList;

	using obj_shr = std::shared_ptr<CObject>;
	static std::list<CObject*> m_list;
	static std::list<std::list<CObject*>::iterator> m_terminatorList;
};
