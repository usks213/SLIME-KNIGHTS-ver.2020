//==================================================================
//								objectMgr.h
//	GM21 �I�u�W�F�N�g�̃��X�g�Ǘ�
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//
//	2020/06/19	�I�u�W�F�N�g�̃��X�g���Ǘ�����N���X���쐬
//	2020/10/26	STL��
//
//===================================================================

#pragma once

//====== �C���N���[�h�� ======
#include "../main.h"
#include "List.h"
#include "object.h"
#include <list>


//===== �N���X��` =====
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

	// �������^�[�~�l�[�^�[���g�����o�b�`�����ɂ���
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
