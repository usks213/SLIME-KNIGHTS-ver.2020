//==================================================================
//								attackBase.h
//	�U��	
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//	
//	2020/08/03	�U���̃N���X
//
//===================================================================

#pragma once

//====== �C���N���[�h�� ======
#include "../main.h"
#include "object.h"


//===== �N���X��` =====

class CAttackBase : public CObject
{
public:
	CAttackBase();
	~CAttackBase();

	// �ÓI�֐�
	static CAttackBase* Create(CStatus *pStatus, CTransform *pParent, float fOffSetX = 0.0f);

	// ���z�֐�
	virtual void Update();
	virtual void LateUpdate();
	virtual void Draw();
	virtual void Destroy();

	// �����蔻��p�̊֐�
	virtual void OnCollision(CCollision *pCollision);
	virtual void OnAnimator(CAnimator  *pAnimator);

	// �Q�b�g�֐�
	CCollision* GetCol() { return m_pCollision; }
	virtual CStatus* GetStatus() { return m_pParentStatus; }

	// �Z�b�g�֐�
	void SetOffSetX(float fOffSetX) { m_fOffSetX = fOffSetX; }
	void SetLayer(LAYER::LAYER eLayer) { m_enLayer = eLayer; }

protected:
	// �R���|�[�l���g
	CCollision* m_pCollision;	// �R���W����
	CAnimator*  m_pAnimator;	// �A�j���[�^�[

	// �e�̃X�e�[�^�X
	CStatus* m_pParentStatus;
	// ���W�n�X�V�p
	CTransform* m_pParentTrans;
	float m_fOffSetX;


private:

};

