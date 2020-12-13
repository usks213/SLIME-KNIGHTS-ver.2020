//==================================================================
//								sceneManager.h
//	GM21 �V�[���Ǘ�
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//
//	2020/07/16	�V�[���Ǘ��N���X�쐬
//
//===================================================================


//====== �C���N���[�h�� ======
#include "sceneManager.h"
#include "sceneGame.h"
#include "sceneTitle.h"
#include "fade.h"
#include "flash.h"
#include "camera.h"
#include "stageMaker.h"

#include "objectMgr.h"
#include "collision.h"
#include "animator.h"
#include "rigidbody.h"
#include "status.h"
#include "characterAction.h"
#include "string.h"


//===== �}�N����` =====


//===== �O���[�o���ϐ� =====
static FADE *g_pFade;

CScene* CSceneManager::m_pCurrentScene	= nullptr;
CScene* CSceneManager::m_pNextScene		= nullptr;
bool CSceneManager::m_bStop = false;
CFlash* CSceneManager::m_pFlash = nullptr;



//========================================
//
//	�R���X�g���N�^
//
//========================================
CSceneManager::CSceneManager()
{
	// �ŏ��̃V�[��
	m_pCurrentScene = nullptr;
	m_pNextScene = nullptr;
}


//========================================
//
//	�f�X�g���N�^
//
//========================================
CSceneManager::~CSceneManager()
{
	// �ŏ��̃V�[��
	m_pCurrentScene = nullptr;
	m_pNextScene = nullptr;
}


//========================================
//
//	������
//
//========================================
void CSceneManager::Init()
{
	// �ŏ��̃V�[���̃Z�b�g
	//m_pCurrentScene	= new CSceneGame();
	m_pCurrentScene	= new CSceneTitle();
	m_pNextScene	= m_pCurrentScene;

	// �I�u�W�F�N�g�}�l�[�W���[�̏�����
	CObjectManager::Init();

	// �����_���X�e�[�W�̐���
	CStageMaker::CreateRendomMap();

	// �ŏ��̃V�[���̏�����
	m_pCurrentScene->Init();

	// ������\���̏�����
	STRING::CString::Init();

	// �t�F�[�h�̐���
	g_pFade = new FADE(SetSceneChange);
	// �t���b�V���̐���
	m_pFlash = new CFlash();

	// �X�g�b�v�t���O
	m_bStop = false;
}


//========================================
//
//	�I������
//
//========================================
void CSceneManager::Uninit()
{
	// �t���b�V���̏���
	delete m_pFlash;
	// �t�F�[�h�̏���
	delete g_pFade;

	// ������\���̏I������
	STRING::CString::Uninit();

	// �V�[���̏I������
	m_pCurrentScene->Uninit();

	// �I�u�W�F�N�g�}�l�[�W���[�̏I������
	CObjectManager::Uninit();
}


//========================================
//
//	�S�ẴI�u�W�F�N�g�̍X�V
//
//========================================
void CSceneManager::Update()
{
	// �J���� 
	CCamera::SetCameraTarget(nullptr);

	// ���݂̃V�[���̍X�V����
	m_pCurrentScene->Update();

	// �I�u�W�F�N�g�n�̍X�V����
	if (!m_bStop)
	{
		// �I�u�W�F�N�g�̈�čX�V
		CObjectManager::Update();

		// ���W�b�h�{�f�B
		CRigidbody::Update();
		// �����蔻��̍X�V����
		CCollision::Update();
		// �A�j���[�V�����̍X�V
		CAnimator::Update();
		// �X�e�[�^�X�̍X�V
		CStatus::ListUpdate();
		// �L�����N�^�[�A�N�V�����̍X�V
		CCharacterAction::ListUpdate();
		// �I�u�W�F�N�g�̒x���X�V
		CObjectManager::LateUpdate();
	}
	else
	{
		//�@UI�̍X�V����

	}

	// �t�F�[�h�̍X�V����
	g_pFade->Update();
	// �t���b�V���̍X�V����
	m_pFlash->Update();

	// �J����
	CCamera::Update();
}


//========================================
//
//	�S�ẴI�u�W�F�N�g�̕`��
//
//========================================
void CSceneManager::Draw()
{
	// �I�u�W�F�N�g�̈�ĕ`��
	CObjectManager::Draw();

	// ���݂̃V�[���̕`�揈��
	m_pCurrentScene->Draw();

	// �R���W�����̕`��
	if(GetDebugFlag()) CCollision::Draw();

	// �t�F�[�h�̕`�揈��
	g_pFade->Draw();
	// �t���b�V���̕`�揈��
	m_pFlash->Draw();
}


//========================================================
//
//	���̃V�[�����Z�b�g
//
//========================================================
void CSceneManager::SetNextScene(CScene *pNextScene)
{
	// ���̃V�[�����i�[
	m_pNextScene = pNextScene;

	// �V�[���̃G�t�F�N�g�Ȃ�
	// �X�C�b�`���Ƃ��łǂ̃V�[���G�t�F�N�g�A�t�F�[�h���g�����I�ׂ���ʔ�����
	g_pFade->StartFadeOut();

}

//========================================================
//
//	���̃V�[���ֈړ�
//
//========================================================
void CSceneManager::SetSceneChange()
{
	// ���݂̃V�[���̏I���������Ă�
	m_pCurrentScene->Uninit();

	// �I�u�W�F�N�g�}�l�[�W���[�̏I������
	CObjectManager::Uninit();

	// ���݂̃V�[���̏���
	delete m_pCurrentScene;

	// ���݂̃V�[���̕ύX
	m_pCurrentScene = m_pNextScene;

	// �I�u�W�F�N�g�}�l�[�W���[�̏�����
	CObjectManager::Init();

	// ���̃V�[���̏�����
	m_pCurrentScene->Init();
}
