//==================================================================
//											stageChageBossArea.h
//	�X�e�[�W�`�F���W�G���A�̃{�X������
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//	
//	2020/09/04	�X�e�[�W�`�F���W�{�X�G���A�N���X�̍쐬
//
//===================================================================

#pragma once

//====== �C���N���[�h�� ======
#include "../main.h"
#include "object.h"


//===== �N���X��` =====

class CStageChangeBossArea : public CObject
{
public:
	CStageChangeBossArea();
	~CStageChangeBossArea();

	// �ÓI�֐�
	static CStageChangeBossArea* Create(Float3 pos);
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

protected:
	// �R���|�[�l���g
	CCollision* m_pCollision;	// �R���W����
	static CTexture sm_texture;

	bool m_Hit;
private:

};

