//==================================================================
//								sceneGame.h
//	GM21 �Q�[���V�[��
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//
//	2020/07/18	�Q�[���V�[���N���X�쐬
//
//===================================================================


//====== �C���N���[�h�� ======
#include "sceneTitle.h"
#include "sceneManager.h"
#include "sceneGame.h"

#include "stageManager.h"
#include "stageDebug.h"
#include "stageMaker.h"
#include "stageStartMap.h"
#include "stageTutorial.h"

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
#include "field.h"
#include "bullet.h"
#include "attackBase.h"
#include "enemySlim.h"
#include "enemyWing.h"
#include "enemyLance.h"
#include "playerUI.h"
#include "key.h"
#include "characterAction.h"
#include "weapon.h"

#include "objectMgr.h"
#include "collision.h"
#include "animator.h"
#include "rigidbody.h"
#include "status.h"
#include "string.h"


#ifdef _WIN32
#include "../input.h"
#include "../Sound.h"
#endif // _WIN32


//===== �}�N����` =====


//===== �O���[�o���ϐ� =====
static CSound g_BGM;
static CTexture g_TexBG;
static CTexture g_TexTile;
static CTexture g_CMark;
static CTexture g_Title;

static CEnemy* g_pEnemy;
//static STRING::CString* g_pString;
static STRING::CString* g_pStringPush;
static STRING::CString* g_pStringName;

//========================================
//
//	�R���X�g���N�^
//
//========================================
CSceneTitle::CSceneTitle()
{
	
}


//========================================
//
//	�f�X�g���N�^
//
//========================================
CSceneTitle::~CSceneTitle()
{

}


//========================================
//
//	������
//
//========================================
void CSceneTitle::Init()
{
	// �T�E���h
	g_BGM.Load(FILE_PATH"sound/bgm/TitleBGM.mp3", true);
	g_BGM.Play(0.9f);

	// �e�N�X�`��
	g_TexBG.LoadTexture(FILE_PATH"map/renga/bg.png");
	g_TexTile.LoadTexture(FILE_PATH"map/renga/tile.png");
	g_CMark.LoadTexture(FILE_PATH"ui/c_mark.tga");
	g_Title.LoadTexture(FILE_PATH"ui/slime_knights.tga");

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
	// �E�F�|��
	CWeapon::Init();

	// �L�����N�^�[�A�N�V�����̏�����
	CCharacterAction::Init();

	// �}�b�v�̃��[�h
	// ���[�h����}�b�v�̃p�X���쐬
	//BG
	CField::CreateBg(FILE_PATH"map/titleMap/map_bg.csv", &g_TexBG, 1, 1);
	// TILE
	CField::Create(FILE_PATH"map/titleMap/map_tile.csv", &g_TexTile, 11, 5);
	// OBJECT
	CField::SetObject(FILE_PATH"map/titleMap/map_object.csv");
	// ENEMY
	CField::SetEnemy(FILE_PATH"map/titleMap/map_enemy.csv");
	// PLAYER
	CField::SetPlayer(FILE_PATH"map/titleMap/map_player.csv", 0);
	// AREA
	CField::SetChangeArea(FILE_PATH"map/titleMap/map_area.csv");


	// �G�̐���
	g_pEnemy = CObjectManager::CreateObject<CEnemySlim>(Float3{ 96 * 15, 96 * 11, 0 });
	g_pEnemy->GetUI()->SetDraw(false);
	// �J����
	CCamera::SetCameraTarget(g_pEnemy->GetTransform());

	// �e�L�X�g
	/*g_pString = new	STRING::CString("SLIME KNIGHTS", Float3{ 0, -100, 0 }, Float2{ 150, 150 },
		Float4{ 1,1,1,1 }, STRING::CENTER_X, STRING::CENTER_Y);*/
	g_pStringPush = new	STRING::CString("Push Enter", Float3{ 0, 0, 0 }, Float2{ 50, 50 },
		Float4{ 1,1,1,1 }, STRING::CENTER_X, STRING::CENTER_Y);
	g_pStringName = new	STRING::CString("Koshi Usami 2020", Float3{ -530, 310, 0 }, Float2{ 24, 24 },
		Float4{ 1,1,1,1 }, STRING::LEFT, STRING::CENTER_Y);
}

//========================================
//
//	�I������
//
//========================================
void CSceneTitle::Uninit()
{
	// �e�L�X�g
	//g_pString->Destroy();
	g_pStringPush->Destroy();
	g_pStringName->Destroy();

	// �L�����N�^�[�A�N�V�����̏I������
	CCharacterAction::Uninit();

	// �E�F�|��
	CWeapon::Uninit();
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

	// �T�E���h
	g_BGM.Stop();

	// �e�N�X�`��
	g_TexBG.UnloadTexture();
	g_TexTile.UnloadTexture();
	g_CMark.UnloadTexture();
	g_Title.UnloadTexture();
}

//========================================
//
//	�S�ẴI�u�W�F�N�g�̍X�V
//
//========================================
void CSceneTitle::Update()
{
	// �J����
	static CTransform enemyTrans = *g_pEnemy->GetTransform();
	enemyTrans = *g_pEnemy->GetTransform();
	Float3 pos = enemyTrans.GetPos();
	pos.y -= 96 * 3;
	enemyTrans.SetPos(pos);

	CCamera::SetCameraTarget(&enemyTrans);

#ifdef _WIN32
	if(GetKeyRelease(VK_RETURN))
	{
		CSceneManager::SetNextScene(new CSceneGame());
	}
	
#endif // _WIN32

}

//========================================
//
//	�S�ẴI�u�W�F�N�g�̕`��
//
//========================================
void CSceneTitle::Draw()
{
	// BG
	CSprite bg;
	CTransform trans;
	bg.SetColor(Float4{ 0.0f, 0.0f, 0.0f, 0.25f });
	trans.SetSize(Float2{ SCREEN_WIDTH, SCREEN_HEIGHT });
	bg.Draw(&trans, nullptr, false);

	// �e�L�X�g
	static int nPushDraw = 0;
	if (nPushDraw++ % 100 > 30)
	{
		g_pStringPush->Draw();
	}

	// �^�C�g��
	//g_pString->Draw();
	trans.SetSize(Float2{ 250 * 3, 27 * 8 });
	trans.SetPos(Float3{ 0, -180, 0 });
	bg.SetColor(Float4{ 1,1,1,1 });
	bg.Draw(&trans, &g_Title, false);


	// ���O
	g_pStringName->Draw();

	// C�}�[�N
	trans.SetSize(Float2{ 24, 24 });
	trans.SetPos(Float3{ -560, 309, 0 });
	bg.SetColor(Float4{ 1,1,1,1 });
	bg.Draw(&trans, &g_CMark, false);
}

