//==================================================================
//								viewArea.h
//	����G���A	
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//	
//	2020/08/18	����G���A�N���X�̍쐬
//
//===================================================================

#pragma once

//====== �C���N���[�h�� ======
#include "../main.h"
#include "object.h"


//===== �N���X��` =====

class CEnemy;

class CViewArea : public CObject
{
public:
	CViewArea();
	~CViewArea();

	// �ÓI�֐�
	static CViewArea* Create(CEnemy *pEnemy);

	// ���z�֐�
	virtual void Update();
	virtual void LateUpdate();
	virtual void Draw();
	virtual void Destroy();

	// �����蔻��p�̊֐�
	virtual void OnCollision(CCollision *pCollision);

	// �Q�b�g�֐�
	CCollision* GetCol() { return m_pCollision; }

	// �Z�b�g�֐�

protected:
	// �R���|�[�l���g
	CCollision* m_pCollision;	// �R���W����

	// �G�l�~�[
	CEnemy *m_pParentEnemy;

private:

};

