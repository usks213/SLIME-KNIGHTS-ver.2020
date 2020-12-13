//==================================================================
//								field.cpp
//	GM21 �t�B�[���h����	
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//	
//	2020/07/14	�t�B�[���h�N���X�쐬
//
//===================================================================


//====== �C���N���[�h�� ======
#include "field.h"
#include "block.h"
#include "rigidbody.h"
#include "collision.h"
#include "objectMgr.h"
#include "stageManager.h"
#include "stageChangeArea.h"
#include "stageChangeBossArea.h"
#include "camera.h"

#include "player.h"
#include "enemy.h"
#include "enemySlim.h"
#include "enemyWing.h"
#include "enemyLance.h"
#include "enemyBow.h"
#include "enemyBigWing.h"

#include "floor.h"
#include "Fire.h"
#include "needle.h"


#include "../texture.h"


//===== �}�N����` =====


//===== �萔��` =====
enum EMAP_ENEMY_TYPE
{
	ENEMY_SLIM,
	ENEMY_WING,
	ENEMY_LANCE,
	ENEMY_BOW,
	ENEMY_SOUND,
	ENEMY_ZIBAKU,
	ENEMY_BIGWING,


	MAX_MAP_ENEMY_TYPE,
};

enum EMAP_OBJECT_TYPE
{
	FLOOR,
	BOX,
	LIGHT,
	NEEDLE,

	MAX_MAP_OBJECT_TYPE,
};

enum EMAP_TYPE
{
	L,
	R,
	T,
	B,

	MAX_MAP_TYPE,
};

//===== �ÓI�����o =====
int CField::m_nHeight = 0; 
int CField::m_nWidth = 0;



//========================================
//
//	�R���X�g���N�^
//
//========================================
CField::CField()
{
}


//========================================
//
//	�f�X�g���N�^
//
//========================================
CField::~CField()
{
	
}


//========================================
//
//	������
//
//========================================
void CField::Init()
{


}

//========================================
//
//	�I������
//
//========================================
void CField::Uninit()
{
	
}



//========================================
//
//	����
//
//========================================
void CField::Create(const char *pszCSV, CTexture* pTex, int nSplitX, int nSplitY)
{
	FILE *fp;
	int x, y;

	// �t�@�C���I�[�v��
	fp = fopen(pszCSV, "rt");
	if (fp == nullptr) return;

	int nMapWidth = 0;
	int nMapHeight = 0;

	// �����Ő��𐔂���
	char cChar;
	while (fscanf(fp, "%c", &cChar) != EOF)
	{
		if (nMapHeight == 0 && cChar == ',') nMapWidth++;

		if (cChar == '\n') nMapHeight++;
	}
	nMapWidth++;

	// �}�b�v�T�C�Y�i�[
	m_nHeight = nMapHeight;
	m_nWidth = nMapWidth;

	// �}�b�v�f�[�^�̊m��
	int* pnMap = new int[nMapWidth * nMapHeight];

	// CSV�̓ǂݍ���
	fseek(fp, 0, SEEK_SET);
	for (y = 0; y < nMapHeight; y++)
	{
		for (x = 0; x < nMapWidth; x++)
		{
			fscanf(fp, "%d,", &pnMap[y * nMapWidth + x]);
		}
	}

	// �u���b�N�̔z�u
	for (y = 0; y < nMapHeight; y++)
	{
		for (x = 0; x < nMapWidth; x++)
		{
			if (pnMap[y * nMapWidth + x] < 0 || pnMap[y * nMapWidth + x] > nMapWidth * nMapHeight) continue;

			// Test
			//if (pnMap[y * nMapWidth + x] == 12) continue;

			CBlock *pBlock = CBlock::Create(Float3{ (float)96 * x, (float)96 * y, 0 }, pTex, pnMap[y * nMapWidth + x], nSplitX, nSplitY);

			// �z��O�͏���
			// �����ŏ㉺���E�̂ǂꂩ���|�P���������
			if (x > 0)
			{
				if (pnMap[y * nMapWidth + (x - 1)] == -1) continue;
			}
			if (x + 1 < nMapWidth)
			{
				if (pnMap[y * nMapWidth + (x + 1)] == -1) continue;
			}
			if (y > 0)
			{
				if (pnMap[(y - 1) * nMapWidth + x] == -1) continue;
			}
			if (y + 1 < nMapHeight)
			{
				if (pnMap[(y + 1) * nMapWidth + x] == -1) continue;
			}
			
			// �����蔻��̏���
			pBlock->GetRigid()->Destroy();
			pBlock->GetCol()->Destroy();
		}
	}

	// �t�@�C���N���[�Y
	fclose(fp);

	// �}�b�v�f�[�^
	delete[] pnMap;

	// �l���؂̋�ԃT�C�Y
	CCell::SetMapSize((float)nMapWidth * DEFAULT_OBJECT_SIZE, (float)nMapHeight * DEFAULT_OBJECT_SIZE);

	// �J�������W�̌��E�T�C�Y
	CCamera::SetCameraLimit((float)(nMapWidth - 1) * DEFAULT_OBJECT_SIZE, (float)(nMapHeight - 1) * DEFAULT_OBJECT_SIZE);
}

//========================================
//
//	����
//
//========================================
void CField::CreateBg(const char *pszCSV, CTexture* pTex, int nSplitX, int nSplitY)
{
	FILE *fp;
	int x, y;

	// �t�@�C���I�[�v��
	fp = fopen(pszCSV, "rt");
	if (fp == nullptr) return;

	int nMapWidth = 0;
	int nMapHeight = 0;

	// �����Ő��𐔂���
	char cChar;
	while (fscanf(fp, "%c", &cChar) != EOF)
	{
		if (nMapHeight == 0 && cChar == ',') nMapWidth++;

		if (cChar == '\n') nMapHeight++;
	}
	nMapWidth++;


	// �}�b�v�f�[�^�̊m��
	int* pnMap = new int[nMapWidth * nMapHeight];

	// CSV�̓ǂݍ���
	fseek(fp, 0, SEEK_SET);
	for (y = 0; y < nMapHeight; y++)
	{
		for (x = 0; x < nMapWidth; x++)
		{
			fscanf(fp, "%d,", &pnMap[y * nMapWidth + x]);
		}
	}

	// �u���b�N�̔z�u
	for (y = 0; y < nMapHeight; y++)
	{
		for (x = 0; x < nMapWidth; x++)
		{
			if (pnMap[y * nMapWidth + x] < 0 || pnMap[y * nMapWidth + x] > nMapWidth * nMapHeight) continue;

			CBlock *pBlock = CBlock::Create(Float3{ (float)96 * x, (float)96 * y, 0 }, pTex, pnMap[y * nMapWidth + x], nSplitX, nSplitY);

			// �����蔻��̏���
			pBlock->GetRigid()->Destroy();
			pBlock->GetCol()->Destroy();

			//BG
			pBlock->SetLayer(LAYER::BG);
			pBlock->GetSprite()->SetColor(Float4{ 1.f, 1.0f, 1.f, 1.0f });
		}
	}

	// �t�@�C���N���[�Y
	fclose(fp);

	delete[] pnMap;
}


//========================================
//
//	�I�u�W�F�N�g�̔z�u
//
//========================================
void CField::SetObject(const char *pszCSV, bool bBoss)
{
	FILE *fp;
	int x, y;
	int nMapWidth = 0;
	int nMapHeight = 0;

	// �t�@�C���I�[�v��
	fp = fopen(pszCSV, "rt");
	if (!fp) return;

	// �����Ő��𐔂���
	char cChar;
	while (fscanf(fp, "%c", &cChar) != EOF)
	{
		if (nMapHeight == 0 && cChar == ',') nMapWidth++;

		if (cChar == '\n') nMapHeight++;
	}
	nMapWidth++;

	// �}�b�v�f�[�^�̊m��
	int *pnMap = new int[nMapWidth * nMapHeight];

	// CSV�̓ǂݍ���
	fseek(fp, 0, SEEK_SET);
	for (y = 0; y < nMapHeight; y++)
	{
		for (x = 0; x < nMapWidth; x++)
		{
			fscanf(fp, "%d,", &pnMap[y * nMapWidth + x]);
		}
	}

	// �I�u�W�F�N�g�̔z�u
	for (y = 0; y < nMapHeight; y++)
	{
		for (x = 0; x < nMapWidth; x++)
		{
			if (pnMap[y * nMapWidth + x] < 0 || pnMap[y * nMapWidth + x] > nMapWidth * nMapHeight) continue;

			Float3 pos = { (float)96 * x, (float)96 * y, 0 };

			// �I�u�W�F�N�g
			switch (pnMap[y * nMapWidth + x])
			{
			case FLOOR:
				CFloor::Create(pos);
				break;
			case BOX:
				if (bBoss)
				{
					CStageChangeBossArea::Create(pos);
				}
				else
				{

				}
				break;
			case LIGHT:
				CFire::Create(pos);
				break;
			case NEEDLE:
				CNeedl::Create(pos);
				break;
			}
		}
	}

	// �t�@�C���N���[�Y
	fclose(fp);

	// �}�b�v�f�[�^�̔j��
	delete[] pnMap;

}


//========================================
//
//	�G�l�~�[�̔z�u
//
//========================================
void CField::SetEnemy(const char *pszCSV)
{
	FILE *fp;
	int x, y;
	int nMapWidth = 0;
	int nMapHeight = 0;

	// �t�@�C���I�[�v��
	fp = fopen(pszCSV, "rt");
	if (!fp) return;

	// �����Ő��𐔂���
	char cChar;
	while (fscanf(fp, "%c", &cChar) != EOF)
	{
		if (nMapHeight == 0 && cChar == ',') nMapWidth++;

		if (cChar == '\n') nMapHeight++;
	}
	nMapWidth++;

	// �}�b�v�f�[�^�̊m��
	int *pnMap = new int[nMapWidth * nMapHeight];

	// CSV�̓ǂݍ���
	fseek(fp, 0, SEEK_SET);
	for (y = 0; y < nMapHeight; y++)
	{
		for (x = 0; x < nMapWidth; x++)
		{
			fscanf(fp, "%d,", &pnMap[y * nMapWidth + x]);
		}
	}

	// �I�u�W�F�N�g�̔z�u
	for (y = 0; y < nMapHeight; y++)
	{
		for (x = 0; x < nMapWidth; x++)
		{
			if (pnMap[y * nMapWidth + x] < 0 || pnMap[y * nMapWidth + x] > nMapWidth * nMapHeight) continue;

			Float3 pos = { (float)96 * x, (float)96 * y, 0 };

			// �I�u�W�F�N�g
			switch (pnMap[y * nMapWidth + x])
			{
			case ENEMY_SLIM:
				CObjectManager::CreateObject<CEnemySlim>(pos);
				break;
			case ENEMY_WING:
				CObjectManager::CreateObject<CEnemyWing>(pos);
				break;
			case ENEMY_LANCE:
				CObjectManager::CreateObject<CEnemyLance>(pos);
				break;
			case ENEMY_BOW:
				CObjectManager::CreateObject<CEnemyBow>(pos);
				break;
			case ENEMY_SOUND:
				CObjectManager::CreateObject<CEnemyBigWing>(pos);
				break;
			case ENEMY_ZIBAKU:
				break;
			case ENEMY_BIGWING:
				CObjectManager::CreateObject<CEnemyBigWing>(pos);
				break;

			}

		}
	}

	// �t�@�C���N���[�Y
	fclose(fp);

	// �}�b�v�f�[�^�̔j��
	delete[] pnMap;

}

//========================================
//
//	�v���C���[�̔z�u
//
//========================================
void CField::SetPlayer(const char *pszCSV, int nPosType)
{
	FILE *fp;
	int x, y;
	int nMapWidth = 0;
	int nMapHeight = 0;

	// �t�@�C���I�[�v��
	fp = fopen(pszCSV, "rt");
	if (!fp) return;

	// �����Ő��𐔂���
	char cChar;
	while (fscanf(fp, "%c", &cChar) != EOF)
	{
		if (nMapHeight == 0 && cChar == ',') nMapWidth++;

		if (cChar == '\n') nMapHeight++;
	}
	nMapWidth++;

	// �}�b�v�f�[�^�̊m��
	int *pnMap = new int[nMapWidth * nMapHeight];

	// CSV�̓ǂݍ���
	fseek(fp, 0, SEEK_SET);
	for (y = 0; y < nMapHeight; y++)
	{
		for (x = 0; x < nMapWidth; x++)
		{
			fscanf(fp, "%d,", &pnMap[y * nMapWidth + x]);
		}
	}

	// �I�u�W�F�N�g�̔z�u
	for (y = 0; y < nMapHeight; y++)
	{
		for (x = 0; x < nMapWidth; x++)
		{
			if (pnMap[y * nMapWidth + x] < 0 || pnMap[y * nMapWidth + x] > nMapWidth * nMapHeight) continue;

			Float3 pos = { (float)96 * x, (float)96 * y, 0 };

			// �v���C���[�̔z�u
			if (pnMap[y * nMapWidth + x] == nPosType)
			{
				CStageManager::SetPlayerPos(pos);
			}

		}
	}

	// �t�@�C���N���[�Y
	fclose(fp);

	// �}�b�v�f�[�^�̔j��
	delete[] pnMap;

}

//========================================
//
//	�`�F���W�G���A�̔z�u
//
//========================================
void CField::SetChangeArea(const char *pszCSV)
{
	FILE *fp;
	int x, y;
	int nMapWidth = 0;
	int nMapHeight = 0;

	// �t�@�C���I�[�v��
	fp = fopen(pszCSV, "rt");
	if (!fp) return;

	// �����Ő��𐔂���
	char cChar;
	while (fscanf(fp, "%c", &cChar) != EOF)
	{
		if (nMapHeight == 0 && cChar == ',') nMapWidth++;

		if (cChar == '\n') nMapHeight++;
	}
	nMapWidth++;

	// �}�b�v�f�[�^�̊m��
	int *pnMap = new int[nMapWidth * nMapHeight];

	// CSV�̓ǂݍ���
	fseek(fp, 0, SEEK_SET);
	for (y = 0; y < nMapHeight; y++)
	{
		for (x = 0; x < nMapWidth; x++)
		{
			fscanf(fp, "%d,", &pnMap[y * nMapWidth + x]);
		}
	}

	// �I�u�W�F�N�g�̔z�u
	for (y = 0; y < nMapHeight; y++)
	{
		for (x = 0; x < nMapWidth; x++)
		{
			if (pnMap[y * nMapWidth + x] < 0 || pnMap[y * nMapWidth + x] > nMapWidth * nMapHeight) continue;

			Float3 pos = { (float)96 * x, (float)96 * y, 0 };

			switch (pnMap[y * nMapWidth + x])
			{
			case L:
				// �X�e�[�W�ړ�
				CStageChangeArea::Create(pos, L);
				break;
			case R:
				// �X�e�[�W�ړ�
				CStageChangeArea::Create(pos, R);
				break;
			case T:
				// �X�e�[�W�ړ�
				CStageChangeArea::Create(pos, T);
				break;
			case B:
				// �X�e�[�W�ړ�
				CStageChangeArea::Create(pos, B);
				break;
			}
		}
	}


	// �t�@�C���N���[�Y
	fclose(fp);

	// �}�b�v�f�[�^�̔j��
	delete[] pnMap;

}

//========================================
//
//	�j��
//
//========================================
void CField::Destroy()
{
}