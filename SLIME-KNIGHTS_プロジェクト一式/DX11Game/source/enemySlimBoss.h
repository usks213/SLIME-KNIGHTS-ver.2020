//==================================================================
//								enemySlimBoss.cpp
//	�X���C���{�X
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//
//	2020/09/04	�X���C���{�X�N���X�̍쐬
//
//===================================================================

#pragma once

//====== �C���N���[�h�� ======
#include "enemy.h"
#include "bg.h"

//===== �N���X��` =====
class CEnemySlimBoss : public CEnemy
{
public:
	CEnemySlimBoss();
	~CEnemySlimBoss();
	// ���z�֐�
	virtual void Update();
	virtual void LateUpdate();
	virtual void Destroy();

	static void FlashAfter(CEnemySlimBoss* pBoss);

private:
	int m_nShotInterval;
	int m_nState;
	int m_nPrevState;
	int m_nStateTime;
	int m_nEnemyCnt;

	bool m_bMovie;
	float m_fAlpha;

	//CBG* m_pBg;
};


