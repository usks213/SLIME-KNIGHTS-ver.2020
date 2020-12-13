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
#pragma once

//====== �C���N���[�h�� ======
#include "List.h"
#include <stdlib.h>
#include "levelupText.h"

//===== �}�N����` =====


//===== �N���X��` =====

class CStatus
{
public:
	CStatus();
	~CStatus();
	// �X�e�[�^�X�̍X�V
	void Update();
	// �X�e�[�^�X�n�G�t�F�N�g�ƕ`��
	void Draw();

	// �_���[�W��^����
	int AttackDamage(CStatus *pStatus, bool bCritical = false);

	// ���Z�֐�
	void AddLevel(int nAdd)
	{
		m_nLevel += nAdd;
		if (m_nLevel > 9999999) m_nLevel = 9999999;
		// �X�e�[�^�X���グ��
		m_nMaxHp = m_nHp = (int)(5 + m_nLevel * 6.45f + m_nLevel / 2 * 1.3f + 50);
		m_nDamage = (int)(m_nLevel * 1.45f + m_nLevel / 5 + 1) + 5;
		m_nMoveSpeed = m_nLevel;
		m_nAttackSpeed = m_nLevel;
	}
	void AddHp(int nAdd) { m_nHp += nAdd; };
	void AddDamage(int nAdd) { m_nDamage += nAdd; };
	void AddAttackSpeed(int nAdd) { m_nAttackSpeed += nAdd; };
	void AddMoveSpeed(int nAdd) { m_nMoveSpeed += nAdd; };
	void AddMoney(int nAdd) { m_nMoney += nAdd; };
	void AddExperience(int nAdd, Float3 pos)
	{
		m_nExperience += nAdd;
		// �o���l�����܂���
		while (m_nExperience >= m_nRequiredExperience)
		{
			// ���x���A�b�v
			AddLevel(1);
			// �e�L�X�g����
			CLevelUpText::Create(pos);
			// �o���l�̃��Z�b�g
			m_nExperience -= m_nRequiredExperience;
			// �K�v�o���l��ݒ�
			//m_nRequiredExperience = m_nLevel * (m_nLevel / 4 + rand() % (m_nLevel / 4 + 1));
			m_nRequiredExperience = (int)(m_nLevel * 9.531f);
		}
	}

	// �Z�b�g�֐�
	void SetLevel(int nSet);
	void SetHp(int nSet) { m_nHp = nSet; }
	void SetMaxHp(int nSet) { m_nMaxHp = nSet; }
	void SetDamage(int nSet) { m_nDamage = nSet; }
	void SetAttackSpeed(int nSet) { m_nAttackSpeed = nSet; }
	void SetMoveSpeed(int nSet) { m_nMoveSpeed = nSet; }
	void SetMoney(int nSet) { m_nMoney = nSet; }
	void SetExperience(int nSet) { m_nExperience = nSet;}
	void SetStop(bool bStop) { m_bStop = bStop; }
	void SetInvincibleTime(int nFrame) { m_nInvincibleTime = nFrame; }
	void SetInvincibleCnt(int nFrame) { m_nInvincibleCnt = nFrame; }
	void SetInvincible(bool bFlag) { m_bInvincible = bFlag; }

	// �Q�b�g�֐�
	int GetLevel() { return m_nLevel; }
	int GetHp() { return m_nHp; }
	int GetMaxHp() { return m_nMaxHp; }
	int GetDamage() { return m_nDamage; }
	int GetAttackSpeed() { return m_nAttackSpeed; }
	int GetMoveSpeed() { return m_nMoveSpeed; }
	int GetMoney() { return m_nMoney; }
	int GetExperience() { return m_nExperience; }
	int GetRequiredExperience() { return m_nRequiredExperience; }
	bool GetInvincible() { return m_bInvincible; }

	// ���X�g
	static void ListUpdate();

private:
	// �X�e�[�^�X�Ǘ����X�g
	//static List<CStatus> m_list;

	// �L�����N�^�[


	// ��{�X�e�[�^�X
	int m_nLevel;			// ���x��
	int m_nMaxHp;			// �ő�̗�
	int m_nHp;				// �̗�
	int m_nDamage;			// �U����
	int m_nAttackSpeed;		// �U�����x
	int m_nMoveSpeed;		// �ړ����x

	int m_nMoney;			// ����
	int m_nExperience;		// �o���l
	int m_nRequiredExperience;// �K�v�o���l

	// ���
	bool m_bInvincible;		// ���G�t���O
	int m_nInvincibleCnt;	// ���G�J�E���g
	int m_nInvincibleTime;	// ���G����

	// ��Ԉُ�
	int m_nPoisonResis;		// �őϐ�
	int m_nPoisonCnt;
	int m_nPoisonTime;
	int m_nParalysisResis;	// ��ბϐ�
	int m_nParalysisCnt;
	int m_nParalysisTime;

	// �o�t
	// HP���W�F�l
	// �X�e�[�^�XUP�n

	// �f�o�t
	// �ړ����xDOWN
	// �X�e�[�^�XDOWN�n


	// �X�g�b�v�t���O
	bool m_bStop;
};

