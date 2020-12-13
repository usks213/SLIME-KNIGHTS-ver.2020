//==================================================================
//								field.cpp
//	GM21 フィールド生成	
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//	
//	2020/07/14	フィールドクラス作成
//
//===================================================================


//====== インクルード部 ======
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


//===== マクロ定義 =====


//===== 定数定義 =====
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

//===== 静的メンバ =====
int CField::m_nHeight = 0; 
int CField::m_nWidth = 0;



//========================================
//
//	コンストラクタ
//
//========================================
CField::CField()
{
}


//========================================
//
//	デストラクタ
//
//========================================
CField::~CField()
{
	
}


//========================================
//
//	初期化
//
//========================================
void CField::Init()
{


}

//========================================
//
//	終了処理
//
//========================================
void CField::Uninit()
{
	
}



//========================================
//
//	生成
//
//========================================
void CField::Create(const char *pszCSV, CTexture* pTex, int nSplitX, int nSplitY)
{
	FILE *fp;
	int x, y;

	// ファイルオープン
	fp = fopen(pszCSV, "rt");
	if (fp == nullptr) return;

	int nMapWidth = 0;
	int nMapHeight = 0;

	// ここで数を数える
	char cChar;
	while (fscanf(fp, "%c", &cChar) != EOF)
	{
		if (nMapHeight == 0 && cChar == ',') nMapWidth++;

		if (cChar == '\n') nMapHeight++;
	}
	nMapWidth++;

	// マップサイズ格納
	m_nHeight = nMapHeight;
	m_nWidth = nMapWidth;

	// マップデータの確保
	int* pnMap = new int[nMapWidth * nMapHeight];

	// CSVの読み込み
	fseek(fp, 0, SEEK_SET);
	for (y = 0; y < nMapHeight; y++)
	{
		for (x = 0; x < nMapWidth; x++)
		{
			fscanf(fp, "%d,", &pnMap[y * nMapWidth + x]);
		}
	}

	// ブロックの配置
	for (y = 0; y < nMapHeight; y++)
	{
		for (x = 0; x < nMapWidth; x++)
		{
			if (pnMap[y * nMapWidth + x] < 0 || pnMap[y * nMapWidth + x] > nMapWidth * nMapHeight) continue;

			// Test
			//if (pnMap[y * nMapWidth + x] == 12) continue;

			CBlock *pBlock = CBlock::Create(Float3{ (float)96 * x, (float)96 * y, 0 }, pTex, pnMap[y * nMapWidth + x], nSplitX, nSplitY);

			// 配列外は除く
			// ここで上下左右のどれかが－１だったら壁
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
			
			// 当たり判定の消去
			pBlock->GetRigid()->Destroy();
			pBlock->GetCol()->Destroy();
		}
	}

	// ファイルクローズ
	fclose(fp);

	// マップデータ
	delete[] pnMap;

	// 四分木の空間サイズ
	CCell::SetMapSize((float)nMapWidth * DEFAULT_OBJECT_SIZE, (float)nMapHeight * DEFAULT_OBJECT_SIZE);

	// カメラ座標の限界サイズ
	CCamera::SetCameraLimit((float)(nMapWidth - 1) * DEFAULT_OBJECT_SIZE, (float)(nMapHeight - 1) * DEFAULT_OBJECT_SIZE);
}

//========================================
//
//	生成
//
//========================================
void CField::CreateBg(const char *pszCSV, CTexture* pTex, int nSplitX, int nSplitY)
{
	FILE *fp;
	int x, y;

	// ファイルオープン
	fp = fopen(pszCSV, "rt");
	if (fp == nullptr) return;

	int nMapWidth = 0;
	int nMapHeight = 0;

	// ここで数を数える
	char cChar;
	while (fscanf(fp, "%c", &cChar) != EOF)
	{
		if (nMapHeight == 0 && cChar == ',') nMapWidth++;

		if (cChar == '\n') nMapHeight++;
	}
	nMapWidth++;


	// マップデータの確保
	int* pnMap = new int[nMapWidth * nMapHeight];

	// CSVの読み込み
	fseek(fp, 0, SEEK_SET);
	for (y = 0; y < nMapHeight; y++)
	{
		for (x = 0; x < nMapWidth; x++)
		{
			fscanf(fp, "%d,", &pnMap[y * nMapWidth + x]);
		}
	}

	// ブロックの配置
	for (y = 0; y < nMapHeight; y++)
	{
		for (x = 0; x < nMapWidth; x++)
		{
			if (pnMap[y * nMapWidth + x] < 0 || pnMap[y * nMapWidth + x] > nMapWidth * nMapHeight) continue;

			CBlock *pBlock = CBlock::Create(Float3{ (float)96 * x, (float)96 * y, 0 }, pTex, pnMap[y * nMapWidth + x], nSplitX, nSplitY);

			// 当たり判定の消去
			pBlock->GetRigid()->Destroy();
			pBlock->GetCol()->Destroy();

			//BG
			pBlock->SetLayer(LAYER::BG);
			pBlock->GetSprite()->SetColor(Float4{ 1.f, 1.0f, 1.f, 1.0f });
		}
	}

	// ファイルクローズ
	fclose(fp);

	delete[] pnMap;
}


//========================================
//
//	オブジェクトの配置
//
//========================================
void CField::SetObject(const char *pszCSV, bool bBoss)
{
	FILE *fp;
	int x, y;
	int nMapWidth = 0;
	int nMapHeight = 0;

	// ファイルオープン
	fp = fopen(pszCSV, "rt");
	if (!fp) return;

	// ここで数を数える
	char cChar;
	while (fscanf(fp, "%c", &cChar) != EOF)
	{
		if (nMapHeight == 0 && cChar == ',') nMapWidth++;

		if (cChar == '\n') nMapHeight++;
	}
	nMapWidth++;

	// マップデータの確保
	int *pnMap = new int[nMapWidth * nMapHeight];

	// CSVの読み込み
	fseek(fp, 0, SEEK_SET);
	for (y = 0; y < nMapHeight; y++)
	{
		for (x = 0; x < nMapWidth; x++)
		{
			fscanf(fp, "%d,", &pnMap[y * nMapWidth + x]);
		}
	}

	// オブジェクトの配置
	for (y = 0; y < nMapHeight; y++)
	{
		for (x = 0; x < nMapWidth; x++)
		{
			if (pnMap[y * nMapWidth + x] < 0 || pnMap[y * nMapWidth + x] > nMapWidth * nMapHeight) continue;

			Float3 pos = { (float)96 * x, (float)96 * y, 0 };

			// オブジェクト
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

	// ファイルクローズ
	fclose(fp);

	// マップデータの破棄
	delete[] pnMap;

}


//========================================
//
//	エネミーの配置
//
//========================================
void CField::SetEnemy(const char *pszCSV)
{
	FILE *fp;
	int x, y;
	int nMapWidth = 0;
	int nMapHeight = 0;

	// ファイルオープン
	fp = fopen(pszCSV, "rt");
	if (!fp) return;

	// ここで数を数える
	char cChar;
	while (fscanf(fp, "%c", &cChar) != EOF)
	{
		if (nMapHeight == 0 && cChar == ',') nMapWidth++;

		if (cChar == '\n') nMapHeight++;
	}
	nMapWidth++;

	// マップデータの確保
	int *pnMap = new int[nMapWidth * nMapHeight];

	// CSVの読み込み
	fseek(fp, 0, SEEK_SET);
	for (y = 0; y < nMapHeight; y++)
	{
		for (x = 0; x < nMapWidth; x++)
		{
			fscanf(fp, "%d,", &pnMap[y * nMapWidth + x]);
		}
	}

	// オブジェクトの配置
	for (y = 0; y < nMapHeight; y++)
	{
		for (x = 0; x < nMapWidth; x++)
		{
			if (pnMap[y * nMapWidth + x] < 0 || pnMap[y * nMapWidth + x] > nMapWidth * nMapHeight) continue;

			Float3 pos = { (float)96 * x, (float)96 * y, 0 };

			// オブジェクト
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

	// ファイルクローズ
	fclose(fp);

	// マップデータの破棄
	delete[] pnMap;

}

//========================================
//
//	プレイヤーの配置
//
//========================================
void CField::SetPlayer(const char *pszCSV, int nPosType)
{
	FILE *fp;
	int x, y;
	int nMapWidth = 0;
	int nMapHeight = 0;

	// ファイルオープン
	fp = fopen(pszCSV, "rt");
	if (!fp) return;

	// ここで数を数える
	char cChar;
	while (fscanf(fp, "%c", &cChar) != EOF)
	{
		if (nMapHeight == 0 && cChar == ',') nMapWidth++;

		if (cChar == '\n') nMapHeight++;
	}
	nMapWidth++;

	// マップデータの確保
	int *pnMap = new int[nMapWidth * nMapHeight];

	// CSVの読み込み
	fseek(fp, 0, SEEK_SET);
	for (y = 0; y < nMapHeight; y++)
	{
		for (x = 0; x < nMapWidth; x++)
		{
			fscanf(fp, "%d,", &pnMap[y * nMapWidth + x]);
		}
	}

	// オブジェクトの配置
	for (y = 0; y < nMapHeight; y++)
	{
		for (x = 0; x < nMapWidth; x++)
		{
			if (pnMap[y * nMapWidth + x] < 0 || pnMap[y * nMapWidth + x] > nMapWidth * nMapHeight) continue;

			Float3 pos = { (float)96 * x, (float)96 * y, 0 };

			// プレイヤーの配置
			if (pnMap[y * nMapWidth + x] == nPosType)
			{
				CStageManager::SetPlayerPos(pos);
			}

		}
	}

	// ファイルクローズ
	fclose(fp);

	// マップデータの破棄
	delete[] pnMap;

}

//========================================
//
//	チェンジエリアの配置
//
//========================================
void CField::SetChangeArea(const char *pszCSV)
{
	FILE *fp;
	int x, y;
	int nMapWidth = 0;
	int nMapHeight = 0;

	// ファイルオープン
	fp = fopen(pszCSV, "rt");
	if (!fp) return;

	// ここで数を数える
	char cChar;
	while (fscanf(fp, "%c", &cChar) != EOF)
	{
		if (nMapHeight == 0 && cChar == ',') nMapWidth++;

		if (cChar == '\n') nMapHeight++;
	}
	nMapWidth++;

	// マップデータの確保
	int *pnMap = new int[nMapWidth * nMapHeight];

	// CSVの読み込み
	fseek(fp, 0, SEEK_SET);
	for (y = 0; y < nMapHeight; y++)
	{
		for (x = 0; x < nMapWidth; x++)
		{
			fscanf(fp, "%d,", &pnMap[y * nMapWidth + x]);
		}
	}

	// オブジェクトの配置
	for (y = 0; y < nMapHeight; y++)
	{
		for (x = 0; x < nMapWidth; x++)
		{
			if (pnMap[y * nMapWidth + x] < 0 || pnMap[y * nMapWidth + x] > nMapWidth * nMapHeight) continue;

			Float3 pos = { (float)96 * x, (float)96 * y, 0 };

			switch (pnMap[y * nMapWidth + x])
			{
			case L:
				// ステージ移動
				CStageChangeArea::Create(pos, L);
				break;
			case R:
				// ステージ移動
				CStageChangeArea::Create(pos, R);
				break;
			case T:
				// ステージ移動
				CStageChangeArea::Create(pos, T);
				break;
			case B:
				// ステージ移動
				CStageChangeArea::Create(pos, B);
				break;
			}
		}
	}


	// ファイルクローズ
	fclose(fp);

	// マップデータの破棄
	delete[] pnMap;

}

//========================================
//
//	破棄
//
//========================================
void CField::Destroy()
{
}