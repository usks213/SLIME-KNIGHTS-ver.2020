//==================================================================
//								floor.h
//	�t�B�[���h�p��	
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//	
//	2020/08/29	�t���A�N���X�̍쐬
//
//===================================================================

#pragma once

//====== �C���N���[�h�� ======
#include "../main.h"
#include "object.h"


//===== �N���X��` =====

class CFloor : public CObject
{
public:
	CFloor();
	~CFloor();
	void Destroy();

	// �ÓI�֐�
	static void Init();
	static void Uninit();
	static CFloor* Create(Float3 pos);

	// ���z�֐�
	virtual void Update();
	virtual void Draw();
	// �����蔻��p�̊֐�
	virtual void OnCollision(CCollision *pCollision);


	CRigidbody* GetRigid() { return m_pRigidBody; }
	CCollision* GetCol() { return m_pCollision; }

	void SetRigid(CRigidbody* pRb) { m_pRigidBody = pRb; }
	void SetCol(CCollision* pCol) { m_pCollision = pCol; }
	void SetLayer(LAYER::LAYER eLayer) { m_enLayer = eLayer; }

protected:
	CCollision* m_pCollision;	// �R���|�[�l���g
	CRigidbody* m_pRigidBody;
	static CTexture	sm_texture;

private:

};

