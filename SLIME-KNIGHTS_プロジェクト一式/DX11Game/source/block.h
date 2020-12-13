//==================================================================
//								block.h
//	GM21 �t�B�[���h�p�u���b�N	
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//	
//	2020/07/12	�u���b�N�N���X�쐬
//
//===================================================================

#pragma once

//====== �C���N���[�h�� ======
#include "../main.h"
#include "object.h"


//===== �N���X��` =====

class CBlock : public CObject
{
public:
	CBlock();
	~CBlock();
	void Destroy();

	// �ÓI�֐�
	static void Init();
	static void Uninit();
	static CBlock* Create(Float3 pos, CTexture* nTex, int nTexPos, int nSplitX, int nSplitY);

	// ���z�֐�
	virtual void Update();
	virtual void Draw();
	// �����蔻��p�̊֐�
	virtual void OnCollision(CCollision *pCollision) { return; }


	CRigidbody* GetRigid() { return m_pRigidBody; }
	CCollision* GetCol() { return m_pCollision; }

	void SetRigid(CRigidbody* pRb) { m_pRigidBody = pRb; }
	void SetCol(CCollision* pCol) { m_pCollision = pCol; }
	void SetLayer(LAYER::LAYER eLayer) { m_enLayer = eLayer; }

protected:
	CCollision* m_pCollision;	// �R���|�[�l���g
	CRigidbody* m_pRigidBody;
	CTexture*	m_pTexture;

private:

};

