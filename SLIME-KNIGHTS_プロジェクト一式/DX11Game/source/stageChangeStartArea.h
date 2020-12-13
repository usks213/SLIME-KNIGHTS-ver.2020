//==================================================================
//											stageChageStartArea.h
//	�X�e�[�W�`�F���W�G���A�̃X�^�[�g�}�b�v��
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//	
//	2020/09/04	�X�e�[�W�`�F���W�X�^�[�g�G���A�N���X�̍쐬
//
//===================================================================

#pragma once

//====== �C���N���[�h�� ======
#include "../main.h"
#include "object.h"


//===== �N���X��` =====

class CStageChangeStartArea : public CObject
{
public:
	CStageChangeStartArea();
	~CStageChangeStartArea();

	// �ÓI�֐�
	static CStageChangeStartArea* Create(Float3 pos);

	// ���z�֐�
	virtual void Update();
	virtual void LateUpdate();
	virtual void Draw();
	virtual void Destroy();

	// �����蔻��p�̊֐�
	virtual void OnCollision(CCollision *pCollision);

	// �Q�b�g�֐�
	CCollision* GetCol() { return m_pCollision; }

protected:
	// �R���|�[�l���g
	CCollision* m_pCollision;	// �R���W����


	bool m_Hit;
private:

};

