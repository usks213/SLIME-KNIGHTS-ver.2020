//==================================================================
//								character.h
//	GM21 
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//	
//	2020/07/03	�L�����N�^�[�N���X�쐬	
//
//===================================================================

#pragma once

//====== �C���N���[�h�� ======
#include "../main.h"
#include "object.h"
#include "status.h"
#include "characterAction.h"
#include "objectMgr.h"

//===== �N���X��` =====


class CCharacter : public CObject
{
public:
	CCharacter();
	~CCharacter();
	// ���z�֐�
	virtual void Update() = 0;
	virtual void Draw()   = 0;
	virtual void Destroy() { CObjectManager::DestroyObject(this); }
	// �����蔻��p�̊֐�
	virtual void OnCollision(CCollision *pCollision) { return; }
	// �A�j���[�V�����I�����ɌĂяo�����֐�
	virtual void OnAnimator(CAnimator *pAnimator) { return; }

	// �R���|�[�l���g
	CCollision* GetCol() { return m_pCollision; }
	CAnimator* GetAnim() { return m_pAnimator; }
	CRigidbody* GetRb()  { return m_pRigidbody; }
	virtual CStatus* GetStatus() { return &m_status; }

	// �Q�b�g�E�Z�b�g�֐�
	bool GetFloorThrough() { return m_bFloorThrough; }

protected:
	CCollision* m_pCollision;	// �R���|�[�l���g
	CAnimator* m_pAnimator;		// �R���|�[�l���g
	CRigidbody* m_pRigidbody;	// �R���|�[�l���g

	// �X�e�[�^�X
	CStatus m_status;
	//CCharacterAction m_charaAction;
	// ���p
	bool m_bFloorThrough;
private:

};



//===== �v���g�^�C�v�錾 =====
