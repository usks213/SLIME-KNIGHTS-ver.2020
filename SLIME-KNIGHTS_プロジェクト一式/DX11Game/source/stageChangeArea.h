//==================================================================
//								stageChageArea.h
//	�X�e�[�W�`�F���W�G���A	
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//	
//	2020/08/23	�X�e�[�W�`�F���W�G���A
//
//===================================================================

#pragma once

//====== �C���N���[�h�� ======
#include "../main.h"
#include "object.h"


//===== �N���X��` =====

class CStageChangeArea : public CObject
{
public:
	CStageChangeArea();
	~CStageChangeArea();

	// �ÓI�֐�
	static CStageChangeArea* Create(Float3 pos, int nAreaType);

	// ���z�֐�
	virtual void Update();
	virtual void LateUpdate();
	virtual void Draw();
	virtual void Destroy();

	// �����蔻��p�̊֐�
	virtual void OnCollision(CCollision *pCollision);

	// �Q�b�g�֐�
	CCollision* GetCol() { return m_pCollision; }
	static int GetGotoChangeArea() { return m_nGotoChangeArea; }

	// �Z�b�g�֐�
	static void SetGotoChangeArea(int nAreaType) { m_nGotoChangeArea = nAreaType; }

protected:
	// �R���|�[�l���g
	CCollision* m_pCollision;	// �R���W����
//	CRigidbody* m_pRb;

	// �ړ��G���A�̃^�C�v
	int m_nChangeAreaType;

	// �v���C���[�̃X�e�[�W�ړ��X�e�[�g
	static int m_nGotoChangeArea;

	bool m_Hit;
private:

};

