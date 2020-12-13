//==================================================================
//								transform.h
//	�g�����X�t�H�[��
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//
//	2020/07/22	�g�����X�t�H�[���N���X�̍쐬
//
//===================================================================

#pragma once

//====== �C���N���[�h�� ======
#include "../main.h"

//===== �}�N����` =====


//===== �N���X��` =====
class CTransform
{
public:
	CTransform();
	~CTransform();

	// �Q�b�g�֐�
	float GetAngle() { return m_fAngle; }
	Float3 GetPos() { return m_pos; }
	float GetSizeX() { return m_size.x; }
	Float2 GetSize() { return m_size; }
	Float3 GetDir() { return m_dir; }
	// �Z�b�g�֐�
	void SetPos(Float3 pos) { m_pos = pos; }
	void SetPosZ(float z) { m_pos.z = z; }
	void SetAngle(float fAngle) { m_fAngle = fAngle; }
	void SetSize(Float2 size) { m_size = size; }
	void SetDir(Float3 dir) { m_dir = dir; }
private:
	Float3 m_pos;				// ���S���W
	Float2 m_size;				// �c���T�C�Y
	float m_fAngle;				// �I�u�W�F�N�g�̉�]�p�x
	Float3 m_dir;				// ����
};

