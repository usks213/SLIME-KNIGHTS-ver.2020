//==================================================================
//								sceneTutorial.cpp
//	�`���[�g���A���}�b�v
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//
//	2020/09/05	�`���[�g���A���}�b�v�N���X�̍쐬
//
//===================================================================


//====== �C���N���[�h�� ======
#include "stageTutorial.h"
#include "field.h"
#include "stageManager.h"
#include "stageMaker.h"
#include "sceneManager.h"
#include "stageChangeStartArea.h"
#include "key.h"

#ifdef _WIN32
#include "../input.h"
#include "../Sound.h"
#endif // _WIN32

//===== �}�N����` =====

enum ETEXT_TYPE
{
	MOVE,
	JUMP,
	DOWN,
	ATTACK,

	MAX_TEXT_TYPE,
};

//===== �O���[�o���ϐ� =====
static CTexture g_TexBG;
static CTexture g_TexTile;
static STRING::CString* g_pString[MAX_TEXT_TYPE];

//========================================
//
//	�R���X�g���N�^
//
//========================================
CStageTutorial::CStageTutorial()
{
	
}


//========================================
//
//	�f�X�g���N�^
//
//========================================
CStageTutorial::~CStageTutorial()
{

}


//========================================
//
//	������
//
//========================================
void CStageTutorial::Init()
{
	// �e�N�X�`��
	g_TexBG.LoadTexture(FILE_PATH"map/renga/bg.png");
	g_TexTile.LoadTexture(FILE_PATH"map/renga/tile.png");


	// �}�b�v�̃��[�h
	// ���[�h����}�b�v�̃p�X���쐬
	//BG
	CField::CreateBg(FILE_PATH"map/tutorial/map_bg.csv", &g_TexBG, 1, 1);
	// TILE
	CField::Create(FILE_PATH"map/tutorial/map_tile.csv", &g_TexTile, 11, 5);
	// OBJECT
	CField::SetObject(FILE_PATH"map/tutorial/map_object.csv");
	// ENEMY
	CField::SetEnemy(FILE_PATH"map/tutorial/map_enemy.csv");
	// PLAYER
	CField::SetPlayer(FILE_PATH"map/tutorial/map_player.csv", 0);
	// AREA
	//CField::SetChangeArea(FILE_PATH"map/tutorial/map_area.csv");
	// ���O�̃G���A�ݒu
	CStageChangeStartArea::Create(Float3{ 96 * 99, 96 * 17, 0 });

	// BGM�Đ�
	CStageManager::SetBGM(BGM::START_MAP);


	// �`���[�g���A���e�L�X�g��\��
	CKey::Create(KEY::W, Float3{ 96 * 6, 96 * 19, 0 });
	CKey::Create(KEY::A, Float3{ 96 * 5, 96 * 20, 0 });
	CKey::Create(KEY::S, Float3{ 96 * 6, 96 * 20, 0 });
	CKey::Create(KEY::D, Float3{ 96 * 7, 96 * 20, 0 });
	CKey::Create(KEY::UP,		Float3{ 96 * 10, 96 * 19, 0 });
	CKey::Create(KEY::LEFT,		Float3{ 96 * 9, 96 * 20, 0 });
	CKey::Create(KEY::DOWN,		Float3{ 96 * 10, 96 * 20, 0 });
	CKey::Create(KEY::RIGHT,	Float3{ 96 * 11, 96 * 20, 0 });

	// �W�����v
	CKey::Create(KEY::SPACE, Float3{ 96 * 33, 96 * 13.5f, 0 });
	CKey::Create(KEY::X,	 Float3{ 96 * 34.75f, 96 * 13.5f, 0 });
	CKey::Create(KEY::K,	 Float3{ 96 * 36, 96 * 13.5f, 0 });

	// ���������
	CKey::Create(KEY::S,	Float3{ 96 * 66, 96 * 9, 0 });
	CKey::Create(KEY::DOWN, Float3{ 96 * 68, 96 * 9, 0 });

	// �U��
	CKey::Create(KEY::Z, Float3{ 96 * 74.5f, 96 * 16, 0 });
	CKey::Create(KEY::L, Float3{ 96 * 76.5f, 96 * 16, 0 });

	// �e�L�X�g
	g_pString[MOVE] = new	STRING::CString("�ړ�", Float3{ 96 * 8, 96 * 19, 0 }, Float2{ 64, 64 },
		Float4{ 1,1,1,1 },	STRING::CENTER_X, STRING::CENTER_Y, true);
	g_pString[JUMP] = new	STRING::CString("�W�����v", Float3{ 96 * 34.5f, 96 * 12.5f, 0 }, Float2{ 64, 64 },
		Float4{ 1,1,1,1 },	STRING::CENTER_X, STRING::CENTER_Y, true);
	g_pString[DOWN] = new	STRING::CString("�����", Float3{ 96 * 67, 96 * 8, 0 }, Float2{ 64, 64 },
		Float4{ 1,1,1,1 },	STRING::CENTER_X, STRING::CENTER_Y, true);
	g_pString[ATTACK] = new STRING::CString("�U��", Float3{ 96 * 75.5f, 96 * 15, 0 }, Float2{ 64, 64 },
		Float4{ 1,1,1,1 },	STRING::CENTER_X, STRING::CENTER_Y, true);
	
}

//========================================
//
//	�I������
//
//========================================
void CStageTutorial::Uninit()
{
	// �e�N�X�`��
	g_TexBG.UnloadTexture();
	g_TexTile.UnloadTexture();

	// �e�L�X�g
	for (int i = 0; i < MAX_TEXT_TYPE; i++)
	{
		if (g_pString[i])
		{
			g_pString[i]->Destroy();
			g_pString[i] = nullptr;
		}
	}


}

//========================================
//
//	�S�ẴI�u�W�F�N�g�̍X�V
//
//========================================
void CStageTutorial::Update()
{
	// �e�L�X�g
	for (int i = 0; i < MAX_TEXT_TYPE; i++)
	{
		if (g_pString[i])
		{
			g_pString[i]->Update();
		}
	}

#ifdef _WIN32
	
#endif // _WIN32
}


//========================================
//
//	�S�ẴI�u�W�F�N�g�̕`��
//
//========================================
void CStageTutorial::Draw()
{
	// �e�L�X�g
	for (int i = 0; i < MAX_TEXT_TYPE; i++)
	{
		if (g_pString[i])
		{
			g_pString[i]->Draw();
		}
	}
}

