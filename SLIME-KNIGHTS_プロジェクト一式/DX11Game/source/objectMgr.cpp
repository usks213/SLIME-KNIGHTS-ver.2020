//==================================================================
//								objectManager.cpp
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


//====== �C���N���[�h�� ======
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

//===== �}�N����` =====


//===== �O���[�o���ϐ� =====


// �ÓI�����o�̏�����
//List<CObject> CObjectManager::list;
//List<CObject> CObjectManager::m_terminatorList;
list<CObject*> CObjectManager::m_list;
list<std::list<CObject*>::iterator> CObjectManager::m_terminatorList;


//========================================
//
//	�R���X�g���N�^
//
//========================================
CObjectManager::CObjectManager()
{
	
}


//========================================
//
//	�f�X�g���N�^
//
//========================================
CObjectManager::~CObjectManager()
{

}


//========================================
//
//	������
//
//========================================
void CObjectManager::Init()
{
	
}

//========================================
//
//	�I������
//
//========================================
void CObjectManager::Uninit()
{
	// ���X�g�̏���
	AllClearList();
	// �����Ń^�[�~�i�����Ă�
	UpdateTerminator();

}

//========================================
//
//	�S�ẴI�u�W�F�N�g�̍X�V
//
//========================================
void CObjectManager::Update()
{
	//// �擪���X�g�̎擾
	//List<CObject>* pHead = list.GetHead();

	//// �m�[�h����
	//if (pHead == nullptr) return;

	//// �I�u�W�F�N�g
	//CObject* pObj = nullptr;

	//// ���X�g���̈�čX�V
	//List<CObject> *pNode = nullptr;
	//List<CObject> *pNextBack = nullptr;
	//for (pNode = pHead; pNode != nullptr; pNode = pNextBack)
	//{
	//	// ���̃|�C���^�̃o�b�N�A�b�v�����
	//	pNextBack = pNode->GetNext();

	//	// �I�u�W�F�N�g�̍X�V
	//	pObj = pNode->GetThis();

	//	// �q�b�g�X�g�b�v
	//	if (pObj->GetStop()) continue;

	//	// �J�����O���J�����O
	//	if (pObj->GetLayer() == LAYER::PLAYER ||
	//		CheckCollisionRectToRect(CCamera::GetCameraPos(), pObj->GetTransform()->GetPos(),
	//		Float2{ SCREEN_WIDTH / CCamera::GetScale()*3.1f, SCREEN_HEIGHT / CCamera::GetScale()*3.1f }, pObj->GetTransform()->GetSize()))
	//	{
	//		// ��čX�V
	//		pNode->GetThis()->Update();
	//	}
	//}

	for (const auto& obj : m_list) 
	{
		if (obj->GetStop()) continue;

		// �J�����O���J�����O
		if (obj->GetLayer() == LAYER::PLAYER ||
			CheckCollisionRectToRect(CCamera::GetCameraPos(), obj->GetTransform()->GetPos(),
				Float2{ SCREEN_WIDTH / CCamera::GetScale()*3.1f, SCREEN_HEIGHT / CCamera::GetScale()*3.1f }, obj->GetTransform()->GetSize()))
		{
			obj->Update();
		}
	}

	//// �ϑԃv���O����
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
//	�S�ẴI�u�W�F�N�g�̒x���X�V
//
//========================================
void CObjectManager::LateUpdate()
{
	//// �擪���X�g�̎擾
	//List<CObject>* pHead = list.GetHead();

	//// �m�[�h����
	//if (pHead == nullptr) return;

	//// �I�u�W�F�N�g
	//CObject* pObj = nullptr;

	//// ���X�g���̈�čX�V
	//List<CObject> *pNode = nullptr;
	//List<CObject> *pNextBack = nullptr;
	//for (pNode = pHead; pNode != nullptr; pNode = pNextBack)
	//{
	//	// ���̃|�C���^�̃o�b�N�A�b�v�����
	//	pNextBack = pNode->GetNext();

	//	// �I�u�W�F�N�g�̍X�V
	//	pObj = pNode->GetThis();

	//	// �q�b�g�X�g�b�v
	//	if (pObj->GetStop()) continue;

	//	// �J�����O���J�����O
	//	//if (CheckCollisionRectToRect(CCamera::GetCameraPos(), pObj->GetTransform()->GetPos(),
	//		//Float2{ SCREEN_WIDTH / CCamera::GetScale()*1.1f, SCREEN_HEIGHT / CCamera::GetScale()*1.1f }, pObj->GetTransform()->GetSize()))
	//	{
	//		// ��čX�V
	//		pNode->GetThis()->LateUpdate();
	//	}
	//}

	for (const auto& obj : m_list)
	{
		if (obj->GetStop()) continue;

		//// �J�����O���J�����O
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
//	�S�ẴI�u�W�F�N�g�̕`��
//
//========================================
void CObjectManager::Draw()
{
	//// �����Ń^�[�~�i�����Ă�
	//UpdateTerminator();
	//// ���X�g�̃\�[�g
	////SortList();
	//QuickSortList();

	//// �擪���X�g�̎擾
	//List<CObject>* pHead = list.GetHead();

	//// �m�[�h����
	//if (pHead == nullptr) return;

	//// �I�u�W�F�N�g
	//CObject* pObj = nullptr;

	//// ���X�g���̈�ĕ`��
	//List<CObject> *pNode = nullptr;
	//List<CObject> *pNextBack = nullptr;
	//for (pNode = pHead; pNode != nullptr; pNode = pNextBack)
	//{
	//	// ���̃|�C���^�̃o�b�N�A�b�v�����
	//	pNextBack = pNode->GetNext();

	//	// �I�u�W�F�N�g�̍X�V
	//	pObj = pNode->GetThis();

	//	// �J�����O���J�����O
	//	/*if (CheckCollisionRectToRect(CCamera::GetCameraPos(), pObj->GetTransform()->GetPos(),
	//		Float2{ SCREEN_WIDTH/CCamera::GetScale()*1.1f, SCREEN_HEIGHT/CCamera::GetScale()*1.1f }, pObj->GetTransform()->GetSize()))*/
	//	{
	//		// Z���W�Ƀ��C���[���i�[����
	//		//pObj->GetTransform()->SetPosZ(-pObj->GetLayer());

	//		// ��ĕ`��
	//		pNode->GetThis()->Draw();
	//	}
	//	
	//}

	// �����Ń^�[�~�i�����Ă�
	UpdateTerminator();

	// ����ւ�
	m_list.sort(comp);

	for (const auto& obj : m_list)
	{
		//if (obj->GetStop()) continue;

		//// �J�����O���J�����O
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
//	���X�g���̃I�u�W�F�N�g�����C���[���Ƀ\�[�g
//
//========================================================
void CObjectManager::SortList()
{
	//// �擪���X�g�̎擾
	//List<CObject>* pHead = list.GetHead();

	//// �m�[�h����
	//if (pHead == nullptr) return;

	//// ���X�g���̈�ĕ`��
	//List<CObject> *pNode = nullptr;
	//List<CObject> *pNextBack = nullptr;
	//bool bSortFlag = true;
	//CObject* pWork;

	//// ����ւ�肪�Ȃ��Ȃ�܂Ń��[�v����
	//while (bSortFlag)
	//{
	//	// �t���O��������
	//	bSortFlag = false;

	//	// �o�u���\�[�g
	//	for (pNode = pHead; pNode != nullptr; pNode = pNextBack)
	//	{
	//		// ���̃|�C���^�̃o�b�N�A�b�v�����
	//		pNextBack = pNode->GetNext();
	//		if (pNextBack == nullptr) break;
	//		// ���X�g�̔�r������
	//		// �����ŃX���b�v���X�g
	//		// ���X�g���q�������̂ł͂Ȃ��A���g�̃f�[�^�̃|�C���^�����ւ���
	//		// pStoreThis�����ւ���
	//		if (pNode->GetThis()->GetLayer() > pNextBack->GetThis()->GetLayer())
	//		{
	//			// ���[�N���g���ē���ւ�
	//			pWork = pNode->GetThis();
	//			pNode->SetThis(pNextBack->GetThis());
	//			pNextBack->SetThis(pWork);
	//			// �t���O�𗧂Ă�
	//			bSortFlag = true;
	//		}
	//	}
	//}

}


// ����ւ�
void NodeSwap(List<CObject>* pNodeA, List<CObject>* pNodeB)
{
	CObject* pWork;

	// ���[�N���g���ē���ւ�
	pWork = pNodeA->GetThis();
	pNodeA->SetThis(pNodeB->GetThis());
	pNodeB->SetThis(pWork);
}


//========================================================
//
//	���X�g���̃I�u�W�F�N�g�����C���[���Ƀ\�[�g
//
//========================================================
void CObjectManager::QuickSortList()
{
	//// �擪���X�g�̎擾
	//List<CObject>* pHead = list.GetHead();
	//List<CObject>* pTail = list.GetTail();
	//
	//// �m�[�h����
	//if (pHead == nullptr) return;

	//// �m�[�h�̐�
	//int nMaxNode = list.GetMaxNode();
	//// �w�b�h�e�[���i�[�p
	//struct SHeadTail
	//{
	//	List<CObject> *pHead;
	//	List<CObject> *pTail;
	//	int nLeft;
	//	int nRight;
	//};

	//SHeadTail *startWork = new SHeadTail{pHead, pTail, 0, nMaxNode};
	//SHeadTail *hdtlWork;
	//// �X�^�b�N
	//List<SHeadTail> stack;
	////List<CObject> objStack;
	//// ��l
	//int nPivot = 0;
	//// ���X�g�̓Y����
	//int pLeft = 0;
	//int pRight = 0;
	//int left;
	//int right;
	//int ptr = 0;

	//// �X�^�b�N�̏�����
	//stack.AddNode(startWork);
	//ptr++;

	//List<CObject>* pWorkL = nullptr;
	//List<CObject>* pWorkR = nullptr;
	//List<CObject> *pNode = nullptr;

	//static int nCnt = 0;
	//nCnt = 0;

	//while (ptr-- > 0)
	//{
	//	// �X�^�b�N�̎��o��
	//	hdtlWork = stack.GetTail()->GetThis();
	//	pLeft = left = hdtlWork->nLeft;
	//	pRight = right = hdtlWork->nRight;
	//	pWorkL = pHead = hdtlWork->pHead;
	//	pWorkR = pTail = hdtlWork->pTail;

	//	stack.DestroyNode(hdtlWork);
	//	delete hdtlWork;

	//	// �@ ��l�̌���
	//	if (pTail == nullptr || pHead == nullptr) continue;

	//	//nPivot = (pHead->GetThis()->GetLayer() + pTail->GetThis()->GetLayer()) / 2;
	//	nPivot = (pHead->GetThis()->GetLayer() + pTail->GetThis()->GetLayer()) / 2;

	//	// �A ���X�g�̃w�b�h�ƃe�[�����ꂼ�ꂩ���l�Ɣ�r�T������
	//	//    ��l�����ƂɁA�傫���A�������A�������̎O�̃O���[�v�ɕ�����
	//	do
	//	{
	//		// �w�b�h�ƃe�[������T������
	//		// �������l�Ɣ�r
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
	//		//	//	// ������������X�^�b�N�Ɋi�[
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
	//		//	//	// ������������X�^�b�N�Ɋi�[
	//		//	//	objStack.Push(pWorkR);
	//		//	//	pWorkR->Pop();
	//		//	//}
	//		//	////if (pWorkR->GetPrev() == nullptr) break;
	//		//}

	//		if (pWorkL == nullptr || pWorkR == nullptr) break;

	//		// �傫�����Ə������������ւ���
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

	//	// ������pWorkL,R�̊Ԃ�nPivot�Ɠ����l�̃X�^�b�N���i�[����
	//	//pWorkR->PushPosNext(objStack.GetHead(), objStack.GetTail());

	//	// ��������
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


	//	// �B �A�̑傫���A���������X�Ɋ�l�����߂ĕ������Ă� ���̎��X�^�b�N�Ɋi�[���Ă�

	//	// �C �w�b�h�ƃe�[���������ɂȂ����炻�̃X�^�b�N�͏I�����Ď��̃X�^�b�N��

	//	// �D �X�^�b�N����ɂȂ�����\�[�g����
	//}

	//nCnt++;
}


//========================================================
//
//	List���̃I�u�W�F�N�g�����ׂď���
//
//========================================================
void CObjectManager::AllClearList()
{
	//// �擪���X�g�̎擾
	//List<CObject>* pHead = list.GetHead();

	//// �m�[�h����
	//if (pHead == nullptr) return;

	//// ���X�g���̈�čX�V
	//List<CObject> *pNode = nullptr;
	//List<CObject> *pNextBack = nullptr;
	//for (pNode = pHead; pNode != nullptr; pNode = pNextBack)
	//{
	//	// ���̃|�C���^�̃o�b�N�A�b�v�����
	//	pNextBack = pNode->GetNext();

	//	if (pNode->GetThis()->GetLayer() < LAYER::MAX_LAYER)
	//	{
	//		if (pNode->GetThis()->GetLayer() == LAYER::PLAYER) continue;
	//		if (pNode->GetThis()->GetLayer() == LAYER::PLAYERATTACK) continue;
	//		if (pNode->GetThis()->GetLayer() == LAYER::ENEMYATTACK) continue;
	//		if (pNode->GetThis()->GetLayer() == LAYER::WEAPON) continue;
	//		if (pNode->GetThis()->GetLayer() == LAYER::STRING) continue;
	//		if (pNode->GetThis()->GetLayer() == LAYER::UI) continue;

	//		//�I�u�W�F�N�g�̏���
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

			//�I�u�W�F�N�g�̏���
			CObjectManager::DestroyObject(*itr);

			//SetTerminator(*itr);
			//m_terminatorList.push_back(itr);
			// ���X�g�������
			//m_list.erase(itr);
		}
	}

}

//========================================================
//
//	List���̎w�肵�����C���[�̃I�u�W�F�N�g�����ׂď���
//
//========================================================
void CObjectManager::SelectClearList(LAYER::LAYER eLayer)
{
	//// �擪���X�g�̎擾
	//List<CObject>* pHead = list.GetHead();

	//// �m�[�h����
	//if (pHead == nullptr) return;

	//// ���X�g���̈�čX�V
	//List<CObject> *pNode = nullptr;
	//List<CObject> *pNextBack = nullptr;
	//for (pNode = pHead; pNode != nullptr; pNode = pNextBack)
	//{
	//	// ���̃|�C���^�̃o�b�N�A�b�v�����
	//	pNextBack = pNode->GetNext();

	//	// �������C���[��������
	//	if (pNode->GetThis()->GetLayer() == eLayer)
	//	{
	//		//�I�u�W�F�N�g�̏���
	//		CObjectManager::DestroyObject(pNode->GetThis());
	//	}
	//}

	for (const auto& obj : m_list)
	{
		if (obj->GetLayer() == eLayer)
		{
			//�I�u�W�F�N�g�̏���
			CObjectManager::DestroyObject(obj);
		}
	}
}

//========================================================
//
//	�^�[�~�l�[�^�[���̃I�u�W�F�N�g������
//
//========================================================
void CObjectManager::SetTerminator(CObject* pObj)
{
	// ����
	auto itr = find(m_list.begin(), m_list.end(), pObj);

	// ���X�g�ɂȂ�������
	if (itr == m_list.end()) return;

	if (pObj->m_bDestroy) return;

	pObj->m_bDestroy = true;

	// �^�[�~�l�[�^�[���Ō���
	//auto terItr = find(m_terminatorList.begin(), m_terminatorList.end(), itr);

	// �^�[�~�l�[�^�[���X�g�Ɋ��ɂ�������
	//if (terItr != m_terminatorList.end()) return;

	// �^�[�~�l�[�^�[�i�[
	m_terminatorList.push_back(itr);

	// ���X�g�������
	//m_list.erase(itr);

	//// �m�[�h����
	//if (m_terminatorList.GetHead() == nullptr)
	//{
	//	// �m�[�h��������̂����������Ȃ�
	//	if (list.DestroyNode(pObj))
	//	{
	//		m_terminatorList.AddNode(pObj);
	//	}
	//	return;
	//}

	//// �擪���X�g�̎擾
	//List<CObject>* pHead = m_terminatorList.GetHead();
	//// ���X�g���̈�čX�V
	//List<CObject> *pNode = nullptr;
	//List<CObject> *pNextBack = nullptr;
	//for (pNode = pHead; pNode != nullptr; pNode = pNextBack)
	//{
	//	// ���̃|�C���^�̃o�b�N�A�b�v�����
	//	pNextBack = pNode->GetNext();

	//	// ���Ɋi�[����Ă��ꍇ�͏����Ȃ�
	//	if (pNode->GetThis() == pObj)
	//	{
	//		return;
	//	}
	//}

	//// �m�[�h��������̂����������Ȃ�
	//if (list.DestroyNode(pObj))
	//{
	//	m_terminatorList.AddNode(pObj);
	//}
}

//========================================================
//
//	�^�[�~�l�[�^�[���̃I�u�W�F�N�g������
//
//========================================================
void CObjectManager::UpdateTerminator()
{
	//// �擪���X�g�̎擾
	//List<CObject>* pHead = m_terminatorList.GetHead();

	//// �m�[�h����
	//if (m_terminatorList.GetHead() == nullptr) return;

	//// ���X�g���̈�čX�V
	//List<CObject> *pNode = nullptr;
	//List<CObject> *pNextBack = nullptr;
	//CObject *pObj;
	//for (pNode = pHead; pNode != nullptr; pNode = pNextBack)
	//{
	//	// ���̃|�C���^�̃o�b�N�A�b�v�����
	//	pNextBack = pNode->GetNext();
	//	pObj = pNode->GetThis();

	//	// �m�[�h��������̂����������Ȃ�
	//	if (m_terminatorList.DestroyNode(pNode))
	//	{
	//		//�I�u�W�F�N�g�̏���
	//		delete pObj;
	//	}
	//}

	//m_terminatorList.clear();
	for (auto itr : m_terminatorList)
	{
		// �I�u�W�F�N�g�̏���
		delete (*itr);
		// ���X�g�������
		m_list.erase(itr);
	}

	m_terminatorList.clear();

	//for (auto obj : m_terminatorList)
	//{
	//	delete obj;
	//}
	//m_terminatorList.clear();
}