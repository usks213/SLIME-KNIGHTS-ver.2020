//==================================================================
//									status.h
//	�X�e�[�^�X
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//
//	2020/08/02	�X�e�[�^�X�N���X�̍쐬
//
//===================================================================

//====== �C���N���[�h�� ======
#include "status.h"
#include <stdlib.h>
#include "stageManager.h"


//===== �}�N����` =====


//===== �N���X��` =====



//===== �v���g�^�C�v�錾 =====


//===== �ÓI�����o =====
static List<CStatus> m_list;
//List<CStatus> CStatus::m_list;



//========================================
//
//	�R���X�g���N�^
//
//========================================
CStatus::CStatus()
{
	// ��{�X�e�[�^�X
	m_nLevel = 1;			// ���x��
	m_nMaxHp = m_nHp = 5;				// �̗�
	m_nDamage = 1;			// �U����
	m_nAttackSpeed = 1;		// �U�����x
	m_nMoveSpeed = 1;		// �ړ����x

	m_nMoney = 10;			// ����
	m_nExperience = 1;		// �o���l
	m_nRequiredExperience = 10;// �K�v�o���l

	// ���
	m_bInvincible = false;		// ���G�t���O
	m_nInvincibleCnt = 0;	// ���G�J�E���g
	m_nInvincibleTime = 15;	// ���G����

	// ��Ԉُ�
	m_nPoisonResis = 10;		// �őϐ�
	m_nPoisonCnt = 0;
	m_nPoisonTime = 120;
	m_nParalysisResis = 10;	// ��ბϐ�
	m_nParalysisCnt = 0;
	m_nParalysisTime = 120;

	m_bStop = false;

	// ���X�g�Ɋi�[
	m_list.AddNode(this);


	// ���x�����Z�b�g
	// �K�w���Q�Ƃ���
	SetLevel(CStageManager::GetStageLevel() * 10 + (rand() %(5 * (CStageManager::GetStageLevel() + 1))) + 1);
}


//========================================
//
//	�f�X�g���N�^
//
//========================================
CStatus::~CStatus()
{
	// ���X�g�̏���
	m_list.DestroyNode(this);
}


//========================================
//
//	�X�V����
//
//========================================
void CStatus::Update()
{
	if (m_bStop) return;

	// ���G�J�E���g
	if(m_bInvincible)
		m_nInvincibleCnt--;
	if (m_nInvincibleCnt < 0)
	{
		m_bInvincible = false;
	}

	// ��Ԉُ�

	// �o�t

	// �f�o�t

}


//========================================
//
//	�`�揈��
//
//========================================
void CStatus::Draw()
{
	// �_���[�W�E���G

	// ��Ԉُ�

	// �o�t

	// �f�o�t

}


//========================================
//
//	�_���[�W�v�Z�֐� �߂�l�F�c��HP
//
//========================================
int CStatus::AttackDamage(CStatus *pStatus, bool bCritical)
{
	// �N���e�B�J������
	if (bCritical)
	{
		// �������̓_���[�W�A�b�v
		m_nHp -= pStatus->m_nDamage * 2;
	}
	else
	{
		// �X�e�[�^�X�̌v�Z
		m_nHp -= pStatus->m_nDamage;
	}

	// �[���ȉ��Ȃ�
	if (m_nHp < 0) m_nHp = 0;

	// ���G
	m_bInvincible = true;
	m_nInvincibleCnt = m_nInvincibleTime;


	return m_nHp;
}




//========================================
//
//	���X�g�̍X�V
//
//========================================
void CStatus::ListUpdate()
{
	// �擪���X�g�̎擾
	List<CStatus>* pHead = m_list.GetHead();

	// �m�[�h����
	if (pHead == nullptr) return;

	// ���X�g���̈�čX�V
	List<CStatus> *pNode = nullptr;
	for (pNode = pHead; pNode != nullptr; pNode = pNode->GetNext())
	{
		pNode->GetThis()->Update();

	}
}

//========================================
//
//	���x���̃Z�b�g
//
//========================================
void CStatus::SetLevel(int nSet)
{
	m_nLevel = nSet;

	// �ȉ��̃X�e�[�^�X�����x�������ƂɎ����Z�o
	m_nMaxHp = m_nHp = (int)(5 + nSet * 2.45f + rand() % (nSet / 2 + 1)) + 10;
	m_nDamage = (int)(nSet * 1.45f + rand() % (nSet / 4 + 1)) + 1 + 2;
	m_nMoney = (int)(nSet * 3.3f + rand() % (nSet + 1));
	m_nExperience = (int)(nSet * 3.66f + rand() % (nSet / 2 + 1)) + 3;

	m_nMoveSpeed = m_nLevel;
	m_nAttackSpeed = m_nLevel;
}