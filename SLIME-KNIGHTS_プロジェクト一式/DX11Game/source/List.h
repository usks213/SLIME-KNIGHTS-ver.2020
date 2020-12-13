//==================================================================
//								List.h
//	�ėp���X�g
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//
//	2020/06/18	�e���v���[�g�̔ėp���X�g���쐬(�e�X�g)
//
//===================================================================
#pragma once

//====== �C���N���[�h�� ======


//===== �N���X��` =====
template <class T>
class List
{
public:
	List<T>();
	~List<T>();
	// ���X�g�Ƀm�[�h�̒ǉ�
	//static void AddNode(T *);
	void AddNode(T *);
	// ���X�g�ɂ���̏���
	//static void DestroyNode(T *);
	bool DestroyNode(T *);
	bool DestroyNode(List<T>* pNode);
	// ���X�g���̃m�[�h�̈�čX�V
	//static void UpdateList();
	// ���X�g���̃m�[�h�̈�Ă̕`��
	//static void DrawList();

	// �Q�b�g�֐�
	// ���X�g�̐擪�擾
	//static List<T>* GetHead() { return m_pHead; }
	List<T>* GetHead() { return m_pHead; }
	// ���X�g�̍Ō���擾
	//static List<T>* GetTail() { return m_pTail; }
	List<T>* GetTail() { return m_pTail; }
	// �m�[�h�̎��̃|�C���^
	List<T>* GetNext() { return this->m_pNext; }
	// �m�[�h�̑O�̃|�C���^
	List<T>* GetPrev() { return this->m_pPrev; }
	// �m�[�h�̎��̃|�C���^
	T* GetThis() { return this->m_pStoreThis; }
	// �m�[�h�̍ő吔
	int GetMaxNode() { return m_nMaxNode; }

	// �Z�b�g�֐�
	void SetThis(T* pThis) { m_pStoreThis = pThis; }
	void ClearHead() { m_pHead = nullptr; }
	void ClearTail() { m_pTail = nullptr; }


	// �v�b�V���E�z�b�v����������
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
	// �m�[�h�̑O��|�C���^ ���X�g
	List<T>* m_pNext;
	List<T>* m_pPrev;
	// �i�[����Ă�I�u�W�F�N�g�̃|�C���^
	T* m_pStoreThis;
	// ���X�g�̐擪�A�h���X
	//static List<T>* m_pHead;
	List<T>* m_pHead;
	// ���X�g�̍Ō���A�h���X
	//static List<T>* m_pTail;
	List<T>* m_pTail;

	static int m_nMaxNode;

private:

};

template <class T>
int List<T>::m_nMaxNode = 0;

// ���X�g�̐擪�A�h���X
//template <class T>
//List<T>* List<T>:: m_pHead = nullptr;
// ���X�g�̍Ō���A�h���X
//template <class T>
//List<T>* List<T>::m_pTail = nullptr;


//========================================
//
//	�R���X�g���N�^
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
//	�f�X�g���N�^
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
//	�m�[�h�̒ǉ�
//
//========================================
template <class T>
void List<T>::AddNode(T* pAdd)
{
	// �V�����m�[�h�̍쐬
	List<T>* pNewNode = new List<T>;

	// �m�[�h�̏�����
	pNewNode->m_pStoreThis = pAdd;
	pNewNode->m_pHead = m_pHead;
	pNewNode->m_pTail = m_pTail;
	
	// ���X�g�Ɋi�[
	// �擪�A�h���X���󂾂�����
	if (m_pHead == nullptr)
	{
		// ���Ƃ������ݒ�
		m_pHead = m_pTail = pNewNode;
		pNewNode->m_pHead = pNewNode->m_pTail = pNewNode;
		pNewNode->m_pNext = nullptr;
		pNewNode->m_pPrev = nullptr;
	}
	else
	{
		// ��Ԍ��ɑ��
		m_pTail->m_pNext = pNewNode;
		// ������Ȃ̂Ŏ��͖���
		pNewNode->m_pNext = nullptr;
		// ��O�͑O��܂ł̍Ō�
		pNewNode->m_pPrev = m_pTail;
		// ������̍X�V
		m_pTail = pNewNode->m_pTail = pNewNode;
	}
}

//========================================
//
//	�m�[�h�̒ǉ�
//
//========================================
template <class T>
void List<T>::Push(List<T>* pNode)
{
	// �m�[�h�̏�����
	pNode->m_pHead = m_pHead;
	pNode->m_pTail = m_pTail;

	// ���X�g�Ɋi�[
	// �擪�A�h���X���󂾂�����
	if (m_pHead == nullptr)
	{
		// ���Ƃ������ݒ�
		m_pHead = m_pTail = pNode;
		pNode->m_pNext = nullptr;
		pNode->m_pPrev = nullptr;
	}
	else
	{
		// ��Ԍ��ɑ��
		m_pTail->m_pNext = pNode;
		// ������Ȃ̂Ŏ��͖���
		pNode->m_pNext = nullptr;
		// ��O�͑O��܂ł̍Ō�
		pNode->m_pPrev = m_pTail;
		// ������̍X�V
		m_pTail = pNode;
	}
}

//========================================
//
//	�m�[�h�̒ǉ�
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
//	�m�[�h�̏���
//
//========================================
template <class T>
bool List<T>::DestroyNode(T *pDest)
{
	// �m�[�h�̌���
	List<T> *pNode = nullptr;
	for (pNode = m_pHead; pNode != nullptr; pNode = pNode->m_pNext)
	{
		// ���X�g���ɏ�������|�C���^�����m�[�h���������Ȃ�
		if (pNode->m_pStoreThis == pDest)
		{
			break;
		}
	}
	// �����m�[�h���Ȃ�����
	if (pNode == nullptr) return false ;
	
	// ���������m�[�h
	List<T> *pMyNext = pNode->m_pNext;
	List<T> *pMyPrev = pNode->m_pPrev;

	// �m�[�h�������������
	if (pMyNext == nullptr && pMyPrev == nullptr)
	{
		// �m�[�h�̏���
		delete pNode;
		// ���X�g�̏�����
		m_pHead = nullptr;
		m_pTail = nullptr;
		return true;
	}

	// ���X�g�������
	// �擪�A�h���X��������
	if (pMyPrev == nullptr)
	{
		// �����̎��̃|�C���^�͐擪�A�h���X�ɂȂ�
		m_pHead = pMyNext;
		m_pHead->m_pPrev = nullptr;
	}
	else
	{
		// �u�����̑O�̃|�C���^�̎��v���u�����̎��̃|�C���^�v��
		pMyPrev->m_pNext = pMyNext;
	}

	// ������������
	if (pMyNext == nullptr)
	{
		// �����̑O�̃|�C���^�͂����ɂȂ�
		m_pTail = pMyPrev;
		m_pTail->m_pNext = nullptr;
	}
	else
	{
		// �u�����̎��̃|�C���^�̑O�v���u�����̑O�̃|�C���^�v��
		pMyNext->m_pPrev = pMyPrev;
	}

	// �m�[�h�̏���
	delete pNode;

	return true;
}

//========================================
//
//	�m�[�h�̏���
//
//========================================
template <class T>
bool List<T>::DestroyNode(List<T>* pNode)
{
	// �����m�[�h���Ȃ�����
	if (pNode == nullptr) return false;

	// ���������m�[�h
	List<T> *pMyNext = pNode->m_pNext;
	List<T> *pMyPrev = pNode->m_pPrev;

	// �m�[�h�������������
	if (pMyNext == nullptr && pMyPrev == nullptr)
	{
		// �m�[�h�̏���
		delete pNode;
		// ���X�g�̏�����
		m_pHead = nullptr;
		m_pTail = nullptr;
		return true;
	}

	// ���X�g�������
	// �擪�A�h���X��������
	if (pMyPrev == nullptr)
	{
		// �����̎��̃|�C���^�͐擪�A�h���X�ɂȂ�
		m_pHead = pMyNext;
		m_pHead->m_pPrev = nullptr;
	}
	else
	{
		// �u�����̑O�̃|�C���^�̎��v���u�����̎��̃|�C���^�v��
		pMyPrev->m_pNext = pMyNext;
	}

	// ������������
	if (pMyNext == nullptr)
	{
		// �����̑O�̃|�C���^�͂����ɂȂ�
		m_pTail = pMyPrev;
		m_pTail->m_pNext = nullptr;
	}
	else
	{
		// �u�����̎��̃|�C���^�̑O�v���u�����̑O�̃|�C���^�v��
		pMyNext->m_pPrev = pMyPrev;
	}

	// �m�[�h�̏���
	delete pNode;

	return true;
}



////========================================
////
////	���X�g���̃A�b�v�f�[�g
////
////========================================
//template <class T>
//void List<T>::UpdateList()
//{
//	// �m�[�h����
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
////	���X�g���̈�ĕ`��
////
////========================================
//template <class T>
//void List<T>::DrawList()
//{
//	// �m�[�h����
//	if (m_pHead == nullptr) return;
//
//	List<T> *pNode = nullptr;
//	for (pNode = m_pHead; pNode != nullptr; pNode = pNode->m_pNext)
//	{
//		pNode->m_pStoreThis->Draw();
//	}
//}