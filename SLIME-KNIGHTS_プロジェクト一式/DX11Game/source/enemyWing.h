//==================================================================
//								enemyWnig.h
//	�H�X���C��
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//
//	2020/08/19	�H�X���C���N���X�̍쐬
//
//===================================================================

#pragma once

//====== �C���N���[�h�� ======
#include "enemy.h"

//===== �N���X��` =====
class CEnemyWing : public CEnemy
{
public:
	CEnemyWing();
	~CEnemyWing();
	// ���z�֐�
	virtual void Update();

private:
	int m_nShotInterval;
	bool m_bUp;
	bool m_bRight;
	int m_nUpPos;
	int m_nRightPos;

};


