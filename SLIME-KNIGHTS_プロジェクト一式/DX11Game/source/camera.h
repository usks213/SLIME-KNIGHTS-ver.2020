//==================================================================
//								camera.h
//	GM21 �J��������	
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//	
//	2020/07/14	�J�����N���X�쐬
//
//===================================================================

#pragma once

//====== �C���N���[�h�� ======
#include "../main.h"
#include "transform.h"


//===== �N���X��` =====

class CCamera
{
public:
	CCamera();
	~CCamera();
	void Destroy();

	// �ÓI�֐�
	static void Init();
	static void Uninit();
	static void Update();
	static void Create();

	static void SetCameraTarget(CTransform *pTarget);

	// �Z�b�g�֐�
	static void SetCameraShake(int nFrame, int nShakeOffSet) 
	{
		m_bShake = true;
		m_nShakeFrame = nFrame;
		m_nShakeOffSet = nShakeOffSet;
	}

	static void SetCameraLimit(float fWidth, float fHeight) {
		m_fFieldWidth = fWidth;
		m_fFieldHeight = fHeight;
	}

	// �Q�b�g�֐�
	static XMVECTOR GetEyePos() { return m_eyePos; }
	static XMVECTOR GetFocusPos() { return m_focusPos; }
	static XMVECTOR GetUpVec() { return m_upVec; }
	static XMVECTOR GetDir() { return m_dir; }
	static float GetScale() { return m_fScale; }
	static Float3 GetCameraPos() { return m_pos; }

	// ���z�֐�
protected:

private:
	// �ÓI�����o
	static float m_elevation;		// �c��]
	static float m_azimuth;			// ����]
	static float m_distance;		// �J�����̋���

	static XMVECTOR m_focusPos;		// �����_
	static XMVECTOR m_eyePos;		// �J���������W
	static XMVECTOR m_upVec;		// �J�����̏�x�N�g��

	static XMVECTOR m_dir;			// �J�����̌���
	static float m_fScale;			// �X�P�[��
	static Float3 m_pos;			// �J�������W
	static bool m_bShake;			// �U���t���O
	static int m_nShakeFrame;		// �U���t���[����
	static int m_nShakeOffSet;		// �U����

	// �J�������W�̃��~�b�g (�}�b�v�̑傫��)
	static float m_fFieldWidth;
	static float m_fFieldHeight;

	// �^�[�Q�b�g
	static CTransform* m_pTarget;
};

