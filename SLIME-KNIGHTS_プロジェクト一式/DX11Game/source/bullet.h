//==================================================================
//								bullet.h
//	GM21 �o���b�g	
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//	
//	2020/07/17	�o���b�g�N���X�쐬
//
//===================================================================

#pragma once

//====== �C���N���[�h�� ======
#include "../main.h"
#include "object.h"
#include "status.h"

namespace BULLET
{
	enum EBULLET_TYPE
	{
		BLUE,
		GREEN,
		PURPLE,
		ARROW,

		MAX_BULLET_TYPE,
	};
}


//===== �N���X��` =====

class CBullet : public CObject
{
public:
	CBullet();
	~CBullet();
	void Destroy();

	// �ÓI�֐�
	static void Init();
	static void Uninit();
	static CBullet* Create(Float3 pos, Float3 force, CStatus *pStatus, BULLET::EBULLET_TYPE eType = BULLET::BLUE);

	// ���z�֐�
	virtual void Update();
	virtual void Draw();
	// �����蔻��p�̊֐�
	virtual void OnCollision(CCollision *pCollision);


	CRigidbody* GetRigid() { return m_pRigidbody; }
	CCollision* GetCol() { return m_pCollision; }
	virtual CStatus* GetStatus() { return &m_pParentStatus; }

protected:
	CCollision* m_pCollision;	// �R���|�[�l���g
	CRigidbody* m_pRigidbody;	// ���W�b�h�{�f�B

	BULLET::EBULLET_TYPE m_eType;
 	static CTexture sm_texture[BULLET::MAX_BULLET_TYPE];
private:
	CStatus m_pParentStatus;
};

