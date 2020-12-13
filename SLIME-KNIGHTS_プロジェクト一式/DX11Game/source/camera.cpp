//==================================================================
//								camera.cpp
//	GM21 �J����
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//	
//	2020/07/14	�J�����N���X�쐬
//
//===================================================================


//====== �C���N���[�h�� ======
#include "camera.h"
#include "../input.h"

//===== �}�N����` =====
#define AngleToRadian(a) (a / 180.0f * 3.1415f)

//===== �}�N����` =====


//===== �ÓI�����o =====
CTransform* CCamera::m_pTarget = nullptr;

float CCamera::m_elevation;		// �c��]
float CCamera::m_azimuth;		// ����]
float CCamera::m_distance = -5.0f;		// �J�����̋���

XMVECTOR CCamera::m_focusPos;	// �����_
XMVECTOR CCamera::m_eyePos;		// �J���������W
XMVECTOR CCamera::m_upVec;		// �J�����̏�x�N�g��
XMVECTOR CCamera::m_dir;		// �J�����̌���

float CCamera::m_fScale = 1.5f;	// �X�P�[��
Float3 CCamera::m_pos;					// �J�������W
bool CCamera::m_bShake;					// �U���t���O
int CCamera::m_nShakeFrame;				// �U���t���[����
int CCamera::m_nShakeOffSet = 20;		// �U����

float CCamera::m_fFieldWidth  = 0;
float CCamera::m_fFieldHeight = 0;


//========================================
//
//	�R���X�g���N�^
//
//========================================
CCamera::CCamera()
{
	m_elevation = 0.0f;		// �c��]
	m_azimuth	= 0.0f;		// ����]
	m_distance	= 1.5f;		// ����

	m_fScale = 1.5f;

	m_pos = Float3{ 0, 0, 0 };

}


//========================================
//
//	�f�X�g���N�^
//
//========================================
CCamera::~CCamera()
{
	
}


//========================================
//
//	������
//
//========================================
void CCamera::Init()
{
	m_pos = Float3{ 0, 0, 0 };
	m_fFieldHeight = 0;
	m_fFieldWidth  = 0;

}

//========================================
//
//	�I������
//
//========================================
void CCamera::Uninit()
{
	m_pos = Float3{ 0, 0, 0 };
	m_fFieldHeight = 0;
	m_fFieldWidth = 0;
}


//========================================
//
//	�X�V����
//
//========================================
void CCamera::Update()
{
	//// �J��������
	//if (GetKeyPress(VK_Q))
	//	m_distance += 0.1f;

	//if (GetKeyPress(VK_E))
	//	m_distance -= 0.1f;

	// �X�P�[��
	m_fScale = powf(1.1f, m_distance);

	// �J�������W
	if (m_pTarget)
	{
		m_pos = m_pTarget->GetPos();
	}
	
	// �J�������W�̌��E
	if (m_pos.x > m_fFieldWidth - SCREEN_CENTER_X / m_fScale)  m_pos.x = m_fFieldWidth - SCREEN_CENTER_X / m_fScale;
	if (m_pos.y > m_fFieldHeight - SCREEN_CENTER_Y / m_fScale) m_pos.y = m_fFieldHeight - SCREEN_CENTER_Y / m_fScale;
	if (m_pos.x < SCREEN_CENTER_X / m_fScale) m_pos.x = SCREEN_CENTER_X / m_fScale;
	if (m_pos.y < SCREEN_CENTER_Y / m_fScale) m_pos.y = SCREEN_CENTER_Y / m_fScale;


	// �J�����U��
	m_nShakeFrame--;
	if (m_nShakeFrame < 0)
	{
		m_bShake = false;
	}
	if (m_bShake)
	{
		m_pos.x += -m_nShakeOffSet + rand() % (m_nShakeOffSet * 2);
		m_pos.y += -m_nShakeOffSet + rand() % (m_nShakeOffSet * 2);
	}
	

	//distance -= detail.input->getMouseState().lZ / 10;

	//Float3 *pPos = &m_pTarget->GetPos();

	//// �����Ƀv���C���[�̍��W��
	//m_focusPos = XMVectorSet(pPos->x, pPos->y, pPos->z, 1);

	//m_eyePos = XMVectorSet(
	//	m_distance * sinf(AngleToRadian(m_elevation)) * cosf(AngleToRadian(m_azimuth)),
	//	m_distance * cosf(AngleToRadian(m_elevation)),
	//	m_distance * sinf(AngleToRadian(m_azimuth)) * sinf(AngleToRadian(m_elevation)),
	//	1.0f);
	//m_eyePos += m_focusPos;

	//m_upVec = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);			// ���_�̏�x�N�g��

	//// �J�����̌������v�Z
	//m_dir = m_focusPos - m_eyePos;
	//// �x�N�g���̐��K��
	//m_dir = XMVector4Normalize(m_dir);
}


//========================================
//
//	�^�[�Q�b�g�̃Z�b�g
//
//========================================
void CCamera::SetCameraTarget(CTransform *pTarget)
{
	m_pTarget = pTarget;
}



//========================================
//
//	����
//
//========================================
void CCamera::Create()
{
	
}

//========================================
//
//	������
//
//========================================
void CCamera::Destroy()
{

}