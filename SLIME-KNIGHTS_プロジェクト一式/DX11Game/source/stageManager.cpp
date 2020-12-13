//==================================================================
//								stageManager.h
//	�X�e�[�W�Ǘ�
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//
//	2020/08/23	�X�e�[�W�Ǘ��N���X�쐬
//
//===================================================================


//====== �C���N���[�h�� ======
#include "stageManager.h"
#include "stageDebug.h"
#include "stageMaker.h"
#include "sceneManager.h"
#include "stageBoss.h"
#include "stageStartMap.h"
#include "stageTutorial.h"
#include "stageChangeBossArea.h"

#include "fade.h"
#include "camera.h"
#include "object.h"
#include "bg.h"
#include "block.h"
#include "floor.h"
#include "Fire.h"
#include "light.h"
#include "needle.h"

#include "player.h"
#include "enemy.h"
#include "effect.h"
#include "fade.h"
#include "field.h"
#include "bullet.h"
#include "attackBase.h"
#include "enemySlim.h"
#include "enemyWing.h"
#include "enemyLance.h"
#include "playerUI.h"
#include "key.h"
#include "resultUI.h"
#include "movieUI.h"

#include "objectMgr.h"
#include "collision.h"
#include "animator.h"
#include "rigidbody.h"
#include "status.h"
#include "characterAction.h"
#include "string.h"


#ifdef _WIN32
#include "../input.h"
#include "../Sound.h"
#endif // _WIN32

//===== �}�N����` =====
#define SAVE_DATA_FILE (FILE_PATH"savedata.bin")


//===== �\���� =====
struct SSAVE_DATA
{
	CStatus m_status;
	bool m_bTutorialClear = false;
	int m_nStageLevel = 0;
};


//===== �O���[�o���ϐ� =====
static FADE *g_pFadeStage;
static CMovieUI* g_pMovieUI;
static CPlayerUI* g_pPlayerUI;
static CSound g_SE;

CStage* CStageManager::m_pCurrentStage	= nullptr;
CStage* CStageManager::m_pNextStage		= nullptr;
CPlayer* CStageManager::m_pMainPlayer	= nullptr;
int CStageManager::m_nTimer	= -1;
int CStageManager::m_nStageLevel = 0;
bool CStageManager::m_bTutorialClear = false;
int CStageManager::m_nGameTime = 0;
CResultUI* CStageManager::m_pResultUI = nullptr;


CSound CStageManager::sm_aBGM[BGM::MAX_MAP_BGM];
BGM::EMAP_BGM CStageManager::m_eCurBGM = BGM::RENGA_RANDOM;


//========================================
//
//	�R���X�g���N�^
//
//========================================
CStageManager::CStageManager()
{
	// �ŏ��̃V�[��
	m_pCurrentStage = nullptr;
	m_pNextStage = nullptr;
}


//========================================
//
//	�f�X�g���N�^
//
//========================================
CStageManager::~CStageManager()
{
	// �ŏ��̃V�[��
	m_pCurrentStage = nullptr;
	m_pNextStage = nullptr;
}


//========================================
//
//	������
//
//========================================
void CStageManager::Init()
{
	// �X�e�[�W
	CStageMaker::Init();
	CStageChangeBossArea::Init();

	// �w�i�̏�����
	CBG::Init();
	// �u���b�N�̏�����
	CBlock::Init();
	// �t���A�̏�����
	CFloor::Init();
	// ����̏�����
	CFire::Init();
	CLight::Init();
	// �j�̏�����
	CNeedl::Init();
	// �L�[�̏�����
	CKey::Init();

	// �G�l�~�[�̏�����
	CEnemy::Init();
	// �G�t�F�N�g�̏�����
	CEffect::Init();
	// �e
	CBullet::Init();
	// �v���C���[�̏�����
	CPlayer::Init();

	// �L�����N�^�[�A�N�V�����̏�����
	CCharacterAction::Init();
	// �v���C���[�A�N�V�����̏�����
	CPlayerAction::Init();
	// �v���C���[UI
	CPlayerUI::Init();
	// ���U���gUI
	CResultUI::Init();
	
	// ���[�r�[UI
	CMovieUI::Init();
	g_pMovieUI = new CMovieUI();

	// �t�F�[�h�̐���
	g_pFadeStage = new FADE(SetStageChange);
	g_pFadeStage->GetSprite()->SetColor(Float4{ 0,0,0,1 });

	// �v���C���[�̐���
	m_pMainPlayer = CObjectManager::CreateObject<CPlayer>();
	g_pPlayerUI = CPlayerUI::Create(Float3{ -SCREEN_CENTER_X / 4 * 3,-SCREEN_CENTER_Y / 5 * 4,0 });


	// �Z�[�u�f�[�^�̓ǂݍ���
	FILE *fp;
	fp = fopen(SAVE_DATA_FILE, "rb");
	if (fp)
	{
		SSAVE_DATA save;
		std::fread(&save, sizeof(save), 1, fp);
		m_bTutorialClear = save.m_bTutorialClear;
		m_nStageLevel = save.m_nStageLevel;
		*m_pMainPlayer->GetStatus() = save.m_status;

		std::fclose(fp);
	}

	// �ŏ��̃X�e�[�W�Z�b�g
	if (m_bTutorialClear)
	{
		// �N���A�ς݂Ȃ�
		m_pCurrentStage = new CStageStartMap();
		//m_pCurrentStage = new CStageDebug();
		//m_pCurrentStage	= new CStageTutorial();
		//m_pCurrentStage	= new CStageBoss();
	}
	else
	{
		m_pCurrentStage = new CStageTutorial();
		//m_pCurrentStage = new CStageStartMap();

	}
	m_pNextStage = m_pCurrentStage;


	// �ŏ��̃X�e�[�W������
	m_pCurrentStage->Init();

	// �T�E���h�̃��[�h
	sm_aBGM[BGM::START_MAP].Load(FILE_PATH"sound/bgm/BaseMapBGM.mp3", true);
	sm_aBGM[BGM::RENGA_RANDOM].Load(FILE_PATH"sound/bgm/gameBGM.wav", true);
	sm_aBGM[BGM::RENGA_BOSS].Load(FILE_PATH"sound/bgm/BossBGM.mp3", true);

	// SE
	g_SE.Load(FILE_PATH"sound/fade/sceneswitch2.mp3");

	// �ŏ��̃T�E���h�̃Z�b�g
	m_eCurBGM = BGM::START_MAP;
	PlayBGM();

	// ���U���gUI
	m_nGameTime = 0;
	m_pResultUI = nullptr;

}


//========================================
//
//	�I������
//
//========================================
void CStageManager::Uninit()
{
	// �Z�[�u�f�[�^�̏�������
	FILE *fp;
	fp = std::fopen(SAVE_DATA_FILE, "wb");

	SSAVE_DATA save;
	save.m_bTutorialClear = m_bTutorialClear;
	save.m_nStageLevel = m_nStageLevel;
	save.m_status = *m_pMainPlayer->GetStatus();

	std::fwrite(&save, sizeof(save), 1, fp);

	std::fclose(fp);

	// �T�E���h�̒�~
	sm_aBGM[m_eCurBGM].Stop();

	// �X�e�[�W�I������
	m_pCurrentStage->Uninit();

	// �v���C���[�̏���
	g_pPlayerUI->Destroy();
	CObjectManager::DestroyObject(m_pMainPlayer);
	m_pMainPlayer = nullptr;

	// �t�F�[�h�̏���
	delete g_pFadeStage;
	g_pFadeStage = nullptr;

	// ���[�r�[UI
	delete g_pMovieUI;
	g_pMovieUI = nullptr;
	CMovieUI::Uninit();

	// ���U���gUI
	CResultUI::Uninit();
	// �v���C���[UI
	CPlayerUI::Uninit();
	// �v���C���[�A�N�V�����̏I������
	CPlayerAction::Uninit();
	// �L�����N�^�[�A�N�V�����̏I������
	CCharacterAction::Uninit();

	// �v���C���[�̏I������
	CPlayer::Uninit();
	// �e
	CBullet::Uninit();
	// �G�t�F�N�g�̏I������
	CEffect::Uninit();
	// �G�l�~�[�̏I������
	CEnemy::Uninit();

	// �L�[�̏I������
	CKey::Uninit();
	// �j�̏I������
	CNeedl::Uninit();
	// ����̏I������
	CFire::Uninit();
	CLight::Uninit();
	// �t���A�̏I������
	CFloor::Uninit();
	// �u���b�N�̏I������
	CBlock::Uninit();
	// �w�i�̏I������
	CBG::Uninit();

	// �X�e�[�W
	CStageChangeBossArea::Uninit();
	CStageMaker::Uninit();
}


//========================================
//
//	�S�ẴI�u�W�F�N�g�̍X�V
//
//========================================
void CStageManager::Update()
{
	// ���݂̃X�e�[�W�̍X�V����
	m_pCurrentStage->Update();

	// ���U���gUI
	if (m_pResultUI) m_pResultUI->Update();

	// �t�F�[�h�̍X�V����
	g_pFadeStage->Update();

	// �^�C�}�[�̍X�V
	if (m_nTimer >= 0) m_nTimer--;

	// ��莞�Ԍ�ɃX�e�[�W�̈ړ�
	if (m_nTimer == 0)
	{
		// �V�[���̃G�t�F�N�g�Ȃ�
		// �X�C�b�`���Ƃ��łǂ̃V�[���G�t�F�N�g�A�t�F�[�h���g�����I�ׂ���ʔ�����
		g_pFadeStage->StartFadeOut();

		// �T�E���h
		g_SE.Play();

		// ��ʂ��~
		CSceneManager::SetStopFlag(true);
	}

	// �Q�[������
	m_nGameTime++;
}


//========================================
//
//	�S�ẴI�u�W�F�N�g�̕`��
//
//========================================
void CStageManager::Draw()
{
	// ���݂̃X�e�[�W�`�揈��
	m_pCurrentStage->Draw();

	// ���U���gUI
	if (m_pResultUI) m_pResultUI->Draw();

	// ���[�r�[UI
	if (g_pMovieUI) g_pMovieUI->Draw();

	// �t�F�[�h�̕`�揈��
	g_pFadeStage->Draw();
}


//========================================================
//
//	���̃V�[�����Z�b�g
//
//========================================================
void CStageManager::SetNextStage(CStage *pNextStage)
{
	// ���̃V�[�����i�[
	m_pNextStage = pNextStage;

	// �V�[���̃G�t�F�N�g�Ȃ�
	// �X�C�b�`���Ƃ��łǂ̃V�[���G�t�F�N�g�A�t�F�[�h���g�����I�ׂ���ʔ�����
	g_pFadeStage->SetChangeEvent(SetStageChange);
	g_pFadeStage->StartFadeOut();

	// �T�E���h
	g_SE.Play();

	// ��ʂ��~
	CSceneManager::SetStopFlag(true);
}

//========================================================
//
//	��莞�Ԍ�Ɏ��̃V�[�����Z�b�g
//
//========================================================
void CStageManager::SetTimerNextStage(CStage *pNextStage, int nTimerFrame, void(*pFadeOutEvent)())
{
	m_nTimer = nTimerFrame;

	// ���̃V�[�����i�[
	m_pNextStage = pNextStage;

	// �t�F�[�h�C�x���g���i�[����
	g_pFadeStage->SetChangeEvent(pFadeOutEvent);
}

//========================================================
//
//	���̃V�[���ֈړ�
//
//========================================================
void CStageManager::SetStageChange()
{
	// ���U���gUI
	m_pResultUI->Destroy();
	m_pResultUI = nullptr;

	// ���݂̃V�[���̏I���������Ă�
	m_pCurrentStage->Uninit();

	// �I�u�W�F�N�g�}�l�[�W���[�̏I������
	CObjectManager::Uninit();

	// ���݂̃V�[���̏���
	delete m_pCurrentStage;

	// ���݂̃V�[���̕ύX
	m_pCurrentStage = m_pNextStage;

	// �I�u�W�F�N�g�}�l�[�W���[�̏�����
	CObjectManager::Init();

	// ���̃V�[���̏�����
	m_pCurrentStage->Init();

	// �v���C���[�f�[�^�������
	if (m_pMainPlayer)
	{
		// �J�����̃Z�b�g
		CCamera::SetCameraTarget(m_pMainPlayer->GetTransform());
		// �v���C���[�̃��Z�b�g
		m_pMainPlayer->GetRb()->SetForce(Float3{ 0,0,0 });

	}
}


//========================================================
//
//	BGM���Z�b�g
//
//========================================================
void CStageManager::SetBGM(BGM::EMAP_BGM eBGM, float fVolume)
{
	// ����BGM�Ɠ����Ȃ�p�X
	if (m_eCurBGM == eBGM) return;

	// ���݂�BGM���X�g�b�v
	for(int i = 0; i < BGM::MAX_MAP_BGM; i++)
		sm_aBGM[i].Stop();

	// �V����BGM�̃Z�b�g�E�Đ�
	m_eCurBGM = eBGM;
	sm_aBGM[m_eCurBGM].Play(fVolume);

}

//========================================================
//
//	�Q�[���̃��X�^�[�g
//
//========================================================
void CStageManager::SetRestart()
{
	// ���X�g���N���A
	//CCollision::Uninit();
	//CRigidbody::Uninit();

	// �v���C���[�̐���
	//m_pMainPlayer = CObjectManager::CreateObject<CPlayer>();
	m_pMainPlayer->SetPlayerStop(false);
	m_pMainPlayer->GetRb()->SetStop(false);
	m_pMainPlayer->SetBackUpStatus();
	m_pMainPlayer->GetStatus()->SetHp(m_pMainPlayer->GetStatus()->GetMaxHp());
	m_pMainPlayer->GetStatus()->SetStop(false);
	m_pMainPlayer->GetStatus()->SetInvincibleCnt(0);

	// Result
	CResultUI::Reset(m_pMainPlayer->GetStatus()->GetLevel());
	m_nGameTime = 0;

	// �X�e�[�W�̈ړ�
	SetStageChange();
}