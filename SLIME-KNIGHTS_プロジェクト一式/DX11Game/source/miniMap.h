//==================================================================
//								miniMap.h
//	�~�j�}�b�v�p�u���b�N
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//	
//	2020/09/04	�~�j�}�b�v�N���X�̍쐬
//
//===================================================================

#pragma once

//====== �C���N���[�h�� ======
#include "../main.h"
#include "object.h"


//===== �N���X��` =====

class CMiniMap : public CObject
{
public:
	CMiniMap();
	~CMiniMap();
	void Destroy();

	// �ÓI�֐�
	static void Init();
	static void Uninit();
	static CMiniMap* Create(Float3 pos, CTexture* nTex, int nTexPos, int nSplitX, int nSplitY);

	// ���z�֐�
	virtual void Update();
	virtual void Draw();
	// �����蔻��p�̊֐�
	virtual void OnCollision(CCollision *pCollision) { return; }

	void SetLayer(LAYER::LAYER eLayer) { m_enLayer = eLayer; }

protected:
	CTexture*	m_pTexture;

private:

};

