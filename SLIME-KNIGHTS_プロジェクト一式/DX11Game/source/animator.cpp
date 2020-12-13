//==================================================================
//									Animator.h
//	�R���W����
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//
//	2020/07/08	�A�j���[�^�[�N���X�̍쐬
//
//===================================================================

//====== �C���N���[�h�� ======
#include "animator.h"
#include "object.h"
#include "animation.h"
#include "../sprite.h"


//===== �}�N����` =====


//===== �N���X��` =====



//===== �v���g�^�C�v�錾 =====


// �ÓI�����o�̏�����
List<CAnimator> CAnimator::m_list;


//========================================
//
//	�R���X�g���N�^
//
//========================================
CAnimator::CAnimator()
{
	m_nCurrentAnimNo = 0;
	m_nFrame = 0;
	m_nSpeed = 0;
	m_nSplitX = 0;
	m_nSplitY = 0;
	m_pCurrentAnimation = nullptr;
	m_pSpr = nullptr;
	m_bStop = false;
}


//========================================
//
//	�f�X�g���N�^
//
//========================================
CAnimator::~CAnimator()
{

}


//========================================
//
//	������
//
//========================================
void CAnimator::Init()
{
	

}

//========================================
//
//	�I������
//
//========================================
void CAnimator::Uninit()
{

}

//========================================
//
//	�X�V
//
//========================================
void CAnimator::Update()
{
	// �擪���X�g�̎擾
	List<CAnimator>* pHead = m_list.GetHead();
	List<CAnimator>* pTail = m_list.GetTail();

	// �m�[�h����
	if (pHead == nullptr) return;

	// �A�j���[�^�[�̃��[�N
	CAnimator *pAnimator;
	CAnimation *pAnimation;
	CSprite *pSpr;
	Float2 texPos;

	// ���X�g���̈�čX�V
	List<CAnimator> *pNode = nullptr;
	List<CAnimator> *pNextBack = nullptr;
	for (pNode = pHead; pNode != nullptr; pNode = pNextBack)
	{
		// ���̃|�C���^�̃o�b�N�A�b�v�����
		pNextBack = pNode->GetNext();

		// ��Ȃ��΂�
		if (pNode->GetThis()->m_pCurrentAnimation == nullptr) continue;

		// �m�[�h�̏����擾
		pAnimator = pNode->GetThis();
		pAnimation = pAnimator->m_pCurrentAnimation;
		pSpr = pAnimator->GetSpr();

		// �A�j���[�V�����̃R�}�̍X�V
		if (0 == pAnimator->m_nFrame % pAnimator->m_nSpeed)
		{	
			// �e�N�X�`�����W�̍X�V
			texPos.x = pSpr->GetTexSize().x * (pAnimation->GetAnimNoArray()[pAnimator->m_nCurrentAnimNo] % pAnimator->m_nSplitX);
			texPos.y = pSpr->GetTexSize().y * (pAnimation->GetAnimNoArray()[pAnimator->m_nCurrentAnimNo] / pAnimator->m_nSplitX);
			pSpr->SetTexPos(texPos);

			if (pAnimator->m_bStop) continue;
			// ���݂̃R�}�ԍ��̍X�V
			pAnimator->m_nCurrentAnimNo++;
			pAnimator->m_nFrame = 0;
		}

		if (pAnimator->m_bStop) continue;

		//  �t���[���̍X�V
		pAnimator->m_nFrame++;

		// �A�j���[�V�����̏I��(�ŏI�t���[��)
		if (pAnimator->m_nCurrentAnimNo >= pAnimation->GetArraySize() && pAnimator->m_nFrame >= pAnimator->m_nSpeed)
		{
			// �����ɃA�j���[�V�����̃A�b�v�f�[�g������
			pNode->GetThis()->m_pObj->OnAnimator(pNode->GetThis());

			pAnimator->m_nCurrentAnimNo = 0;
		}
	}


}


//========================================
//
//	����
//
//========================================
CAnimator* CAnimator::Create(CSprite *pSpr, CObject* pObj)
{
	CAnimator *pAniml = new CAnimator;

	m_list.AddNode(pAniml);

	pAniml->m_pSpr = pSpr;	
	pAniml->m_pObj = pObj;

	return pAniml;
}


//========================================
//
//	����
//
//========================================
void CAnimator::Destroy()
{
	// �擪���X�g�̎擾
	List<CAnimation>* pHead = m_animationList.GetHead();

	// �m�[�h����
	if (pHead != nullptr)
	{
		CAnimation *pAnim;
		// ���X�g���Ō���
		List<CAnimation> *pNode = nullptr;
		List<CAnimation> *pNextBack = nullptr;
		for (pNode = pHead; pNode != nullptr; pNode = pNextBack)
		{
			// ���̃|�C���^�̃o�b�N�A�b�v�����
			pNextBack = pNode->GetNext();

			// �A�j���[�^�[�������Ȃ�
			//if (this == pNode->GetThis()->GetAnimator())
			{
				pAnim = pNode->GetThis();
				if (m_animationList.DestroyNode(pNode))
				{
					pAnim->Destroy();
				}
			}
		}
	}

	if (m_list.DestroyNode(this))
	{
		delete this;
	}
}


//========================================
//
//	�A�j���[�^�[�ɃA�j���[�V�����̃Z�b�g
//
//========================================
void CAnimator::SetAnimation(const char *pszName)
{
	// �擪���X�g�̎擾
	List<CAnimation>* pHead = m_animationList.GetHead();

	// �m�[�h����
	if (pHead == nullptr) return;

	// �A�j���[�V�����̍Đ�
	//m_bStop = false;

	// ���X�g���Ō���
	List<CAnimation> *pNode = nullptr;
	List<CAnimation> *pNextBack = nullptr;
	for (pNode = pHead; pNode != nullptr; pNode = pNextBack)
	{
		// ���̃|�C���^�̃o�b�N�A�b�v�����
		pNextBack = pNode->GetNext();

		// ���O�Ɠ����̂�����΃Z�b�g
		if (pNode->GetThis()->GetName() == pszName)
		{
			// �A�j���[�V�������ς���ĂȂ��Ȃ�
			if (m_pCurrentAnimation == pNode->GetThis()) return;

			m_pCurrentAnimation = pNode->GetThis();
			m_nFrame = 0;
			m_nCurrentAnimNo = 0;
			return;
		}
	}

}
//========================================
//
//	�A�j���[�^�[�ɃA�j���[�V�����̃Z�b�g
//
//========================================
void CAnimator::SetAnimation(const char *pszName, int nSpeed)
{
	SetAnimation(pszName);
	if(nSpeed > 0)
		m_nSpeed = nSpeed;
}
//========================================
//
//	�A�j���[�^�[�ɃA�j���[�V�����̃Z�b�g
//
//========================================
void CAnimator::SetAnimation(const char *pszName, int nSpeed, int nSplitX, int nSplitY)
{
	SetAnimation(pszName, nSpeed);
	m_nSplitX = nSplitX;
	m_nSplitY = nSplitY;

	Float2 texSize;
	texSize.x = 1.0f / nSplitX;
	texSize.y = 1.0f / nSplitY;

	m_pSpr->SetTexSize(texSize);
}