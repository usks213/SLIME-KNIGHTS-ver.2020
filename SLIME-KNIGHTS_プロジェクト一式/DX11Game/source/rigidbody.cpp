//==================================================================
//									rigidbody.h
//	���W�b�h�{�f�B
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//
//	2020/07/12	���W�b�h�{�f�B�N���X�쐬
//
//===================================================================

//====== �C���N���[�h�� ======
#include "rigidbody.h"
#include "collision.h"
#include "object.h"
#include "field.h"


//===== �}�N����` =====
#define GRAVITY (1.0f)
#define DRAG (1.0f)

#define MAX_VELOCITY (48)

//===== �N���X��` =====



//===== �v���g�^�C�v�錾 =====


// �ÓI�����o�̏�����
List<CRigidbody> CRigidbody::m_list;


//========================================
//
//	�R���X�g���N�^
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
//	�f�X�g���N�^
//
//========================================
CRigidbody::~CRigidbody()
{

}


//========================================
//
//	������
//
//========================================
void CRigidbody::Init()
{
	

}

//========================================
//
//	�I������
//
//========================================
void CRigidbody::Uninit()
{
	// �擪���X�g�̎擾
	List<CRigidbody>* pHead = m_list.GetHead();

	// �m�[�h����
	if (pHead == nullptr) return;

	CRigidbody *pRb;

	// ���X�g���̈�čX�V
	List<CRigidbody> *pNode = nullptr;
	List<CRigidbody> *pNextBack = nullptr;
	for (pNode = pHead; pNode != nullptr; pNode = pNode->GetNext())
	{
		pNextBack = pNode->GetNext();

		// ���W�b�h�{�f�B�擾
		pRb = pNode->GetThis();

		pNode->DestroyNode(pNode);
		delete pRb;
	}

	// ���X�g�N���A
	m_list.ClearHead();
	m_list.ClearTail();

}

//========================================
//
//	�X�V
//
//========================================
void CRigidbody::Update()
{
	// �擪���X�g�̎擾
	List<CRigidbody>* pHead = m_list.GetHead();

	// �m�[�h����
	if (pHead == nullptr) return;

	CRigidbody *pRb;
	CTransform *pTrans;
	Float3 pos;

	// ���X�g���̈�čX�V
	List<CRigidbody> *pNode = nullptr;
	List<CRigidbody> *pNextBack = nullptr;
	for (pNode = pHead; pNode != nullptr; pNode = pNode->GetNext())
	{
		// ���W�b�h�{�f�B�擾
		pRb = pNode->GetThis();
		// �I�u�W�F�N�g�̎擾
		pTrans = pRb->GetObj();

		// �J�����O�Ȃ�͂���


		// �X�g�b�v���I���Ȃ�Ƃ΂�
		if (pRb->m_bStop) continue;

		if (pRb->m_bSolid) continue;

		// �ړ���
		pRb->m_velocity.x = 0;
		pRb->m_velocity.y = 0;

		// �d��
		if (pRb->m_bUseGravity)
		{
			pRb->m_force.y += pRb->m_fGraviyForce;
		}
		// �d�͂��I��
		pRb->m_bUseGravity = true;

		//// �O��	�O�͂�AddForce��
		pRb->m_velocity.x += pRb->m_force.x;
		pRb->m_velocity.y += pRb->m_force.y;

		// �����ő��x����������v�Z
		pRb->m_dir = Normalize(pRb->m_velocity);

		// ���x���E
		if (pRb->m_velocity.x >  MAX_VELOCITY) pRb->m_velocity.x =  MAX_VELOCITY;
		if (pRb->m_velocity.y >  MAX_VELOCITY) pRb->m_velocity.y =  MAX_VELOCITY;
		if (pRb->m_velocity.x < -MAX_VELOCITY) pRb->m_velocity.x = -MAX_VELOCITY;
		if (pRb->m_velocity.y < -MAX_VELOCITY) pRb->m_velocity.y = -MAX_VELOCITY;

		// �ʒu�̍X�V
		pos = pTrans->GetPos();
		pos.x += pRb->m_velocity.x;
		pos.y += pRb->m_velocity.y;
		// �ړ����E
		if (pos.x < 0.0f) pos.x = 0.0f;
		if (pos.y < 0.0f) pos.y = 0.0f;
		if (pos.x > (CField::GetWidth() - 1 ) * DEFAULT_OBJECT_SIZE) pos.x = (CField::GetWidth() - 1) * DEFAULT_OBJECT_SIZE;
		if (pos.y > (CField::GetHieght() - 1) * DEFAULT_OBJECT_SIZE) pos.y = (CField::GetHieght() - 1) * DEFAULT_OBJECT_SIZE;
		pTrans->SetPos(pos);

		// ��R�ŉ����x�����炷	fDrag(0.0f �` 1.0f)
		pRb->m_force.x *= (1.0f - pRb->m_fDragX);
		if (fabsf(pRb->m_force.x) < 0.01f) pRb->m_force.x = 0.0f;
		//pRb->m_force.y *= (1.0f - pRb->m_fDrag);
		if (fabsf(pRb->m_force.y) < 0.01f) pRb->m_force.y = 0.0f;
	}

}

//========================================
//
//	�����o������
//
//========================================
void CRigidbody::Extrusion(CRigidbody *pOther)
{
	// �\���b�h�Ȃ�
	if (m_bSolid) return;

	// �ŒZ
	float fMinLenX;
	float fMinLenY;
	float fLenX;
	float fLenY;
	// �Փˌ�̗�
	float fForceX;
	float fForceY;

	// �����̏�����
	m_enHitDir = DIRECTION::MAX_DIRECTION;

	//--- �ŒZ�ʒu�̌v�Z ---
	// ��
	fLenX = pOther->m_pTrans->GetPos().x - pOther->m_pTrans->GetSize().x / 2 - m_pTrans->GetPos().x - m_pTrans->GetSize().x / 2;
	fMinLenX = fLenX;

	// �E
	fLenX = pOther->m_pTrans->GetPos().x + pOther->m_pTrans->GetSize().x / 2 - m_pTrans->GetPos().x + m_pTrans->GetSize().x / 2;
	if (fabsf(fLenX) < fabsf(fMinLenX))
	{
		fMinLenX = fLenX;
	}

	// ��
	fLenY = pOther->m_pTrans->GetPos().y - pOther->m_pTrans->GetSize().y / 2 - m_pTrans->GetPos().y - m_pTrans->GetSize().y / 2;
	fMinLenY = fLenY;

	// ��
	fLenY = pOther->m_pTrans->GetPos().y + pOther->m_pTrans->GetSize().y / 2 - m_pTrans->GetPos().y + m_pTrans->GetSize().y / 2;
	if (fabsf(fLenY) < fabsf(fMinLenY))
	{
		fMinLenY = fLenY;
	}

	// �w�C�x�̍ŒZ��r
	if (fabsf(fMinLenX) < fabsf(fMinLenY))	// �����łԂ�����������������!!
	{	// �w��

		// ����
		if (fMinLenX < 0)
		{
			// ��
			m_enHitDir = DIRECTION::LEFT;
			pOther->m_enHitDir = DIRECTION::RIGHT;
		}
		else
		{
			// �E
			m_enHitDir = DIRECTION::RIGHT;
			pOther->m_enHitDir = DIRECTION::LEFT;
		}

		// �g���K�[�Ȃ牟���o�����Ȃ�
		if (m_bTrigger) return;
		if (pOther->m_bTrigger) return;
		
		// ���݂��\���b�h����Ȃ�
		if (!pOther->m_bSolid)
		{
			m_velocity.x += fMinLenX;
			// �����������̗͐ς����߂�
			fForceX = ((m_fMass - pOther->m_fMass) * m_velocity.x + pOther->m_fMass * pOther->m_velocity.x) / (m_fMass + pOther->m_fMass);
			m_force.x = -fForceX;

			m_velocity.x += m_force.x;
			m_pTrans->SetPos(Float3{ m_pTrans->GetPos().x + m_velocity.x, m_pTrans->GetPos().y, 0 });
			return;
		}

		// ���葤�\���b�h�Ȃ�
		if (fMinLenX > 0)
		{
			// �E����
			// �����o��
			m_pTrans->SetPos(Float3{ pOther->m_pTrans->GetPos().x + pOther->m_pTrans->GetSize().x / 2 + m_pTrans->GetSize().x / 2, 
				m_pTrans->GetPos().y, 0});
		}
		else
		{
			// ������
			// �����o��
			m_pTrans->SetPos(Float3{ pOther->m_pTrans->GetPos().x - pOther->m_pTrans->GetSize().x / 2 - m_pTrans->GetSize().x / 2,
				m_pTrans->GetPos().y, 0 });
		}
	}
	else
	{	// �x��
		
		// �ォ��Ԃ��������̓f�t�H���g�ŏd�͂�����
		if (fMinLenY < 0)
		{
			m_enHitDir = DIRECTION::UP;
			pOther->m_enHitDir = DIRECTION::DOWN;
			// �g���K�[�Ȃ牟���o�����Ȃ�
			if (m_bTrigger) return;
			if (pOther->m_bTrigger) return;
			// ��
			m_bUseGravity = false;
			if (m_force.y > 0)
				m_force.y = 0;
		}
		else
		{
			m_enHitDir = DIRECTION::DOWN;
			pOther->m_enHitDir = DIRECTION::UP;
			// �g���K�[�Ȃ牟���o�����Ȃ�
			if (m_bTrigger) return;
			if (pOther->m_bTrigger) return;
			// ��
			if (m_force.y < 0)
				m_force.y = 0;
		}

		// ���݂��\���b�h����Ȃ�
		if (!pOther->m_bSolid)
		{
			m_velocity.y += fMinLenY;
			// �����������̗͐ς����߂�
			fForceY = ((m_fMass - pOther->m_fMass) * m_velocity.y + pOther->m_fMass * pOther->m_velocity.y) / (m_fMass + pOther->m_fMass);
			m_force.y = -fForceY;
			
			m_velocity.y += m_force.y;
			m_pTrans->SetPos(Float3{ m_pTrans->GetPos().x, m_pTrans->GetPos().y + m_velocity.y, 0 });
			return;
		}

		// ���葤�\���b�h�Ȃ�
		if (fMinLenY > 0)
		{
			// ������
			// �����o��
			m_pTrans->SetPos(Float3{ m_pTrans->GetPos().x, 
				pOther->m_pTrans->GetPos().y + pOther->m_pTrans->GetSize().y / 2 + m_pTrans->GetSize().y / 2, 0 });
		}
		else
		{
			// �ォ��
			// �����o��
			m_pTrans->SetPos(Float3{ m_pTrans->GetPos().x, 
				pOther->m_pTrans->GetPos().y - pOther->m_pTrans->GetSize().y / 2 - m_pTrans->GetSize().y / 2, 0 });
		}
	}
}

//========================================
//
//	�����o������ �~�Ɖ~
//
//========================================
void CRigidbody::ExtrusionCircleToCircle(CRigidbody *pOther)
{
	FLOAT TotalWeight = m_fMass + pOther->m_fMass; // ���ʂ̍��v
	FLOAT RefRate = (1.0f);// + res_A * res_B); // ������

	Float3 C = pOther->GetObj()->GetPos(); // �Փˎ��x�N�g��
	C.x -= m_pTrans->GetPos().x;
	C.y -= m_pTrans->GetPos().y;
	C.z -= m_pTrans->GetPos().z;
	// ���K��
	C = Normalize(C);

	Float3 velowork = m_velocity;
	velowork.x -= pOther->m_velocity.x;
	velowork.y -= pOther->m_velocity.y;
	velowork.z -= pOther->m_velocity.z;
	FLOAT fDot = Dot(velowork, C); // ���ώZ�o

	Float3 ConstVec;
	ConstVec.x = RefRate * fDot / TotalWeight * C.x; // �萔�x�N�g��
	ConstVec.y = RefRate * fDot / TotalWeight * C.y; // �萔�x�N�g��
	ConstVec.z = RefRate * fDot / TotalWeight * C.z; // �萔�x�N�g��

	
	// �Փˌ㑬�x�x�N�g���̎Z�o
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

	
	// �Փˌ�ʒu�̎Z�o
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
//	����
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
//	����
//
//========================================
void CRigidbody::Destroy()
{
	if (m_list.DestroyNode(this))
	{
		delete this;
	}
}

