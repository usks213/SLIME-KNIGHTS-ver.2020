//==================================================================
//								light.h
//	�}�b�v�̃��C�g	
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//	
//	2020/09/06	���C�g�N���X�̍쐬
//
//===================================================================

#pragma once

//====== �C���N���[�h�� ======
#include "../main.h"
#include "object.h"


//===== �N���X��` =====


class CLight : public CObject
{
public:
	CLight();
	~CLight();

	// �ÓI�֐�
	static CLight* Create(CTransform *pTrans, float fScale);
	static void Init();
	static void Uninit();

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
	static void SetBoss(bool bFlag) { m_bBoss = bFlag; }

protected:
	// �R���|�[�l���g
	CCollision* m_pCollision;	// �R���W����
	static CTexture sm_texture;

	CTransform *m_pParent;
	float m_fBaseSize;
	bool m_bExpansion;
	static bool m_bBoss;

private:

};

