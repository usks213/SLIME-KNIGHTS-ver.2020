//==================================================================
//								needle.h
//	�}�b�v�̐j	
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//	
//	2020/09/06	�j�[�h���N���X�̍쐬
//
//===================================================================

#pragma once

//====== �C���N���[�h�� ======
#include "../main.h"
#include "object.h"
#include "status.h"


//===== �N���X��` =====

class CNeedl : public CObject
{
public:
	CNeedl();
	~CNeedl();
	void Destroy();

	// �ÓI�֐�
	static void Init();
	static void Uninit();
	static CNeedl* Create(Float3 pos);

	// ���z�֐�
	virtual void Update();
	virtual void Draw();
	// �����蔻��p�̊֐�
	virtual void OnCollision(CCollision *pCollision);


	CRigidbody* GetRigid() { return m_pRigidbody; }
	CCollision* GetCol() { return m_pCollision; }
	virtual CStatus* GetStatus() { return &m_status; }

protected:
	CCollision* m_pCollision;	// �R���|�[�l���g
	CRigidbody* m_pRigidbody;	// ���W�b�h�{�f�B

 	static CTexture sm_texture;
	CStatus m_status;
private:
};

