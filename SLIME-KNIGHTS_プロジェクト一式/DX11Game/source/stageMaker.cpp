//==================================================================
//								stageMaker.cpp
//	ランダムステージメイカー
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//
//	2020/08/25	ステージメイカークラスの作成
//
//===================================================================


//====== インクルード部 ======
#include "stageMaker.h"
#include "block.h"
#include "camera.h"
#include "collision.h"
#include "field.h"
#include "stageChangeArea.h"
#include "string.h"
#include "stageManager.h"
#include "miniMap.h"
#include "objectMgr.h"

#include "transform.h"
#include "rigidbody.h"
#include "collision.h"


//===== マクロ定義 =====



//===== 列挙型・定数定義 =====
enum EMAP_TYPE
{
	// 1通
	L,
	R,
	T,
	B,

	// 2通
	LR,
	LT,
	LB,
	RT,
	RB,
	TB,

	// 3通
	LRT,
	LRB,
	LTB,
	RTB,

	// 4通
	LRTB,

	MAX_MAP_TYPE,
};


//===== グローバル変数 =====
static CTexture g_TexBG;
static CTexture g_TexTile;


//===== 静的メンバ =====
//CStageMaker::SMAP_DATA* CStageMaker::m_pMapData = nullptr;
CStageMaker::SMAP_DATA CStageMaker::m_pMapData[MAP_HEIGHT * MAP_WIDTH];
CTexture CStageMaker::sm_minimapTexture;
CTexture CStageMaker::sm_minimapUITexture;
CTexture CStageMaker::sm_minimapTextTexture;

int CStageMaker::m_nCurrentMapPosX = 0;
int CStageMaker::m_nCurrentMapPosY = 0;
bool CStageMaker::m_bStart = true;
bool CStageMaker::m_bMiniMapDraw = false;

List<CMiniMap> CStageMaker::m_miniMapList;



//========================================
//
//	コンストラクタ
//
//========================================
CStageMaker::CStageMaker()
{
	
}


//========================================
//
//	デストラクタ
//
//========================================
CStageMaker::~CStageMaker()
{

}

//========================================
//
//	マップタイプ判別関数
//
//========================================
bool IsLeftType(int nMapType)
{
	if (nMapType == L ||
		nMapType == LR ||
		nMapType == LT ||
		nMapType == LB ||
		nMapType == LRT ||
		nMapType == LRB ||
		nMapType == LTB ||
		nMapType == LRTB
		)
		return true;

	return false;
}
bool IsRightType(int nMapType)
{
	if (nMapType == R ||
		nMapType == LR ||
		nMapType == RT ||
		nMapType == RB ||
		nMapType == LRT ||
		nMapType == LRB ||
		nMapType == RTB ||
		nMapType == LRTB
		)
		return true;

	return false;
}
bool IsTopType(int nMapType)
{
	if (nMapType == T ||
		nMapType == LT ||
		nMapType == RT ||
		nMapType == TB ||
		nMapType == LRT ||
		nMapType == LTB ||
		nMapType == RTB ||
		nMapType == LRTB
		)
		return true;

	return false;
}
bool IsBottomType(int nMapType)
{
	if (nMapType == B ||
		nMapType == LB ||
		nMapType == RB ||
		nMapType == TB ||
		nMapType == LRB ||
		nMapType == LTB ||
		nMapType == RTB ||
		nMapType == LRTB
		)
		return true;

	return false;
}


//========================================
//
//	ランダムマップの生成
//
//========================================
void CStageMaker::CreateRendomMap()
{
	// マップデータの生成
	//m_pMapData = new SMAP_DATA[MAP_WIDTH * MAP_HEIGHT];

	// マップデータの初期化
	for (int i = 0; i < MAP_WIDTH * MAP_HEIGHT; i++)
	{
		m_pMapData[i].nMapType		= -1;
		m_pMapData[i].bClearFlag	= false;
	}

	int nCount = 0;
	bool bCount = false;

	// ランダムにマップデータを作成
	// ブロックの配置
	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			// 最大カウント
			nCount = 0;

			// 生成できるまで繰り返す
			while (++nCount < 10000)
			{
				// ランダムにマップデータを格納
				m_pMapData[(y) * MAP_WIDTH + (x)].nMapType = rand() % (MAX_MAP_TYPE + 1) - 1;

				//===== 格納した値が辻褄があっているか確認 =====
				// 配列外は除く
				// 上下左右の値が－１は空いてるので何でも入れられる

				bool bL = false;
				bool bT = false;

				// 左側に繋がるマップがある 
				if (x > 0)
				{
					// 格納されてない
					if (m_pMapData[(y)* MAP_WIDTH + (x - 1)].nMapType == -1)
					{
						bL = true;
						// ランダムで格納した値が左の要素を持っているとダメ
						if (IsLeftType(m_pMapData[(y)* MAP_WIDTH + (x)].nMapType)) continue;
					}
					// 右の要素を持っている
					else if (IsRightType(m_pMapData[(y)* MAP_WIDTH + (x - 1)].nMapType))
					{
						// 一つ前と同じ
						if (m_pMapData[(y)* MAP_WIDTH + (x - 1)].nMapType == m_pMapData[(y)* MAP_WIDTH + (x)].nMapType) continue;
						// ランダムで格納した値が左の要素を持っていないとダメ
						if (!IsLeftType(m_pMapData[(y)* MAP_WIDTH + (x)].nMapType)) continue;
					}
					// 右の要素を持っていない
					else if (!IsRightType(m_pMapData[(y)* MAP_WIDTH + (x - 1)].nMapType))
					{
						bL = true;
						// ランダムで格納した値が左の要素を持っているとダメ
						if (IsLeftType(m_pMapData[(y)* MAP_WIDTH + (x)].nMapType)) continue;
					}
				}
				// 左側にマップがない
				else
				{
					if (y != 0) bL = true;
					// ランダムで格納した値が左の要素を持っているとダメ
					if (IsLeftType(m_pMapData[(y)* MAP_WIDTH + (x)].nMapType)) continue;
				}


				// 右側に繋がるマップがある
				if (x + 1 < MAP_WIDTH)
				{
					// 格納されてない
					if (m_pMapData[(y)* MAP_WIDTH + (x + 1)].nMapType == -1)
					{
						// なんでもオーケー
					}
					// 左の要素を持っている
					else if (IsLeftType(m_pMapData[(y)* MAP_WIDTH + (x + 1)].nMapType))
					{
						// ランダムで格納した値が右の要素を持っていないとダメ
						if (!IsRightType(m_pMapData[(y)* MAP_WIDTH + (x)].nMapType)) continue;
					}
					// 左の要素を持っていない
					else if (!IsLeftType(m_pMapData[(y)* MAP_WIDTH + (x + 1)].nMapType))
					{
						// ランダムで格納した値が右の要素を持っているとダメ
						if (IsRightType(m_pMapData[(y)* MAP_WIDTH + (x)].nMapType)) continue;
					}
				}
				// 右側にマップがない
				else
				{
					// ランダムで格納した値が右の要素を持っているとダメ
					if (IsRightType(m_pMapData[(y)* MAP_WIDTH + (x)].nMapType)) continue;
				}


				// 上側に繋がるマップがある
				if (y > 0)
				{
					// 格納されてない
					if (m_pMapData[(y - 1)* MAP_WIDTH + (x)].nMapType == -1)
					{
						bT = true;
						// ランダムで格納した値が上の要素を持っているとダメ
						if (IsTopType(m_pMapData[(y)* MAP_WIDTH + (x)].nMapType)) continue;
					}
					// 下の要素を持っている
					else if (IsBottomType(m_pMapData[(y - 1)* MAP_WIDTH + (x)].nMapType))
					{
						// 一つ前と同じ
						if (m_pMapData[(y - 1)* MAP_WIDTH + (x)].nMapType == m_pMapData[(y)* MAP_WIDTH + (x)].nMapType) continue;
						// ランダムで格納した値が上の要素を持っていないとダメ
						if (!IsTopType(m_pMapData[(y)* MAP_WIDTH + (x)].nMapType)) continue;
					}
					// 下の要素を持っていない
					else if (!IsBottomType(m_pMapData[(y - 1)* MAP_WIDTH + (x)].nMapType))
					{
						bT = true;
						// ランダムで格納した値が上の要素を持っているとダメ
						if (IsTopType(m_pMapData[(y)* MAP_WIDTH + (x)].nMapType)) continue;
					}
				}
				// 上側に繋がるマップがない
				else
				{
					bT = true;
					// ランダムで格納した値が上の要素を持っているとダメ
					if (IsTopType(m_pMapData[(y)* MAP_WIDTH + (x)].nMapType)) continue;
				}


				// 下側に繋がるマップがある
				if (y + 1 < MAP_HEIGHT)
				{
					// 格納されてない
					if (m_pMapData[(y + 1)* MAP_WIDTH + (x)].nMapType == -1)
					{
						// なんでもオーケー
					}
					// 上の要素を持っている
					else if (IsTopType(m_pMapData[(y + 1)* MAP_WIDTH + (x)].nMapType))
					{
						// ランダムで格納した値が下の要素を持っていないとダメ
						if (!IsBottomType(m_pMapData[(y)* MAP_WIDTH + (x)].nMapType)) continue;
					}
					// 上の要素を持っていない
					else if (!IsTopType(m_pMapData[(y + 1)* MAP_WIDTH + (x)].nMapType))
					{
						// ランダムで格納した値が下の要素を持っているとダメ
						if (IsBottomType(m_pMapData[(y)* MAP_WIDTH + (x)].nMapType)) continue;
					}
				}
				// 下側に繋がるマップがない
				else
				{
					// ランダムで格納した値が下の要素を持っているとダメ
					if (IsBottomType(m_pMapData[(y)* MAP_WIDTH + (x)].nMapType)) continue;
				}


				// 初手で-1だったらやり直し
				if (y == 0 && x == 0)
				{
					if (m_pMapData[(y)* MAP_WIDTH + (x)].nMapType == -1) continue;
				}

				// １通マップが近くで生成されないように
				//if (x < MAP_WIDTH / 3 * 2 && y < MAP_HEIGHT / 3 * 2)
				if (x < MAP_WIDTH / 2 || y < MAP_HEIGHT / 2)
				{
					if (m_pMapData[(y)* MAP_WIDTH + (x)].nMapType == L  ||
						m_pMapData[(y)* MAP_WIDTH + (x)].nMapType == T  || 
						m_pMapData[(y)* MAP_WIDTH + (x)].nMapType == R  || 
						m_pMapData[(y)* MAP_WIDTH + (x)].nMapType == B  
						//m_pMapData[(y)* MAP_WIDTH + (x)].nMapType == LT || 
						//m_pMapData[(y)* MAP_WIDTH + (x)].nMapType == LB || 
						//m_pMapData[(y)* MAP_WIDTH + (x)].nMapType == RT  
						)
						continue;
				}

				// つながらないとこは消す
				if (bL && bT)
					m_pMapData[(y)* MAP_WIDTH + (x)].nMapType = -1;


				// 条件を満たしているので
				break;
			}

			if (nCount >= 10000) bCount = true;

		}
	}

	// ===== マップデータ生成完了 =====

	// 初期化
	m_nCurrentMapPosX = 0;
	m_nCurrentMapPosY = 0;
	m_bMiniMapDraw = false;


	if (m_pMapData[0].nMapType == L || m_pMapData[0].nMapType == LB)
	{
		CStageChangeArea::SetGotoChangeArea(L);
	}
	else if (m_pMapData[0].nMapType == B)
	{
		CStageChangeArea::SetGotoChangeArea(B);
	}


	//===== マップのチェック =====
	bool bOne = false;
	// 一通がある
	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			// 一通が一個でもある
			if (m_pMapData[(y)* MAP_WIDTH + (x)].nMapType <= B && m_pMapData[(y)* MAP_WIDTH + (x)].nMapType != -1)
			{
				bOne = true;
			}
		}
	}

	
	
	// カウントが超えてたらやり直し
	if (bCount || !bOne)
	{
		// 一個もないならやり直し
		CreateRendomMap();
	}

	// その他のチェック案
	// ステージの最低
	// 

	//===== ボス部屋作成 =====

}

//
////========================================
////
////	マップデータをもとにミニマップを生成
////
////========================================
//void CStageMaker::CreateMiniMap()
//{
//	//===== マップデータをもとにミニマップ生成 =====
//	for (int y = 0; y < MAP_HEIGHT; y++)
//	{
//		for (int x = 0; x < MAP_WIDTH; x++)
//		{
//			//if (m_pMapData[(y)* MAP_WIDTH + (x)].bClearFlag == false) continue;
//
//			int nType = m_pMapData[(y)* MAP_WIDTH + (x)].nMapType;
//
//			if (nType < 0 || nType >= MAX_MAP_TYPE) continue;
//
//			// ブロックを生成
//			CMiniMap *pMiniMap = CMiniMap::Create(Float3{ (float)96 * x - SCREEN_CENTER_X / 2, 
//				(float)96 * y - SCREEN_CENTER_Y / 2, 0 },
//				&sm_minimapTexture, m_pMapData[y * MAP_WIDTH + x].nMapType, MAX_MAP_TYPE, 1);
//
//			// リストに格納
//			m_miniMapList.AddNode(pMiniMap);
//
//			// カラー
//			pMiniMap->GetSprite()->SetColor(Float4{ 1.0f, 1.0f, 1.0f, 0.9f });
//
//			// 現在地
//			if (x == m_nCurrentMapPosX && y == m_nCurrentMapPosY)
//			{
//				pMiniMap->GetSprite()->SetColor(Float4{ 0.0f, 1.0f, 0.0f, 0.9f });
//			}
//		}
//	}
//
//}
//
////========================================
////
////	マップデータをもとにミニマップを生成
////
////========================================
//void CStageMaker::DestroyMiniMap()
//{
//	// リストを全消去
//	// 先頭リストの取得
//	List<CMiniMap>* pHead = m_miniMapList.GetHead();
//
//	// ノード無し
//	if (pHead == nullptr) return;
//
//	// オブジェクト
//	CMiniMap* pObj = nullptr;
//
//	// リスト内の一斉更新
//	List<CMiniMap> *pNode = nullptr;
//	List<CMiniMap> *pNextBack = nullptr;
//	for (pNode = pHead; pNode != nullptr; pNode = pNextBack)
//	{
//		// 次のポインタのバックアップを取る
//		pNextBack = pNode->GetNext();
//
//		// オブジェクトの更新
//		pObj = pNode->GetThis();
//
//		// オブジェクトの消去
//		pObj->Destroy();
//		m_miniMapList.DestroyNode(pNode);
//	}
//
//
//}

//========================================
//
//	ミニマップを描画
//
//========================================
void CStageMaker::MiniMapDraw()
{
	if (!m_bMiniMapDraw) return;

	// データ
	CSprite sprite;
	CTransform trans;
	float fOffSetY = 80;

	// ミニマップ背景
	trans.SetSize(Float2{ SCREEN_WIDTH, SCREEN_HEIGHT });
	sprite.SetColor(Float4{ 0.1f, 0.1f, 0.1f, 0.8f });
	sprite.Draw(&trans, nullptr, false);

	// ミニマップUI
	trans.SetSize(Float2{ 280 * 2, 200 * 2  });
	sprite.SetColor(Float4{ 1.0f, 1.0f, 1.0f, 0.9f });
	trans.SetPos(Float3{ 0, fOffSetY, 0 });
	sprite.Draw(&trans, &sm_minimapUITexture, false);

	// ミニマップTEXT 動かす
	static float fTextPosY = 0;
	static bool bUp = false;
	if (fTextPosY > 6) bUp = false;
	if (fTextPosY < -6) bUp = true;
	if (bUp) fTextPosY += 0.5f;
	else fTextPosY -= 0.5f;

	trans.SetSize(Float2{ 128 * 1.5f, 64 * 1.5f });
	sprite.SetColor(Float4{ 1.0f, 1.0f, 1.0f, 0.9f });
	trans.SetPos(Float3{ 0, -180 + fTextPosY, 0 });
	sprite.Draw(&trans, &sm_minimapTextTexture, false);


	//===== マップデータをもとにミニマップを描画 =====
	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			// 表示フラグ
			if (m_pMapData[(y)* MAP_WIDTH + (x)].bClearFlag == false) continue;

			int nType = m_pMapData[(y)* MAP_WIDTH + (x)].nMapType;

			if (nType < 0 || nType >= MAX_MAP_TYPE) continue;

			// サイズ
			trans.SetSize(Float2{ 70.0f, 70.0f });

			// 座標
			trans.SetPos(Float3{trans.GetSize().x * x - trans.GetSize().x * MAP_WIDTH / 2.0f + trans.GetSize().x / 2,
								trans.GetSize().y * y - trans.GetSize().y * MAP_HEIGHT / 2.0f + trans.GetSize().y / 2 + fOffSetY, 0 });

			// 分割数
			int nSplitX = MAX_MAP_TYPE;
			int nSplitY = 1;

			// テクスチャサイズ
			sprite.SetTexSize(Float2{ 1.0f / nSplitX, 1.0f / nSplitY });

			// テクスチャ座標
			sprite.SetTexPos(Float2{ nType % nSplitX * sprite.GetTexSize().x,
												nType / nSplitX * sprite.GetTexSize().y });
			// カラー
			sprite.SetColor(Float4{ 0.8f, 0.8f, 0.8f, 0.8f });


			// 描画
			sprite.Draw(&trans, &sm_minimapTexture, false);

			// 現在地
			if (x == m_nCurrentMapPosX && y == m_nCurrentMapPosY)
			{
				static int nCnt = 0;
				if (nCnt++ % 90 > 60) continue;
				sprite.SetColor(Float4{ 0.0f, 1.0f, 0.0f, 0.9f });
				trans.SetSize(Float2{ 10, 10 });
				sprite.Draw(&trans, nullptr, false);
			}
		}
	}


}


//========================================
//
//	マップデータをもとにステージを生成
//
//========================================
void CStageMaker::CreateStage()
{
	// 現在位置のマップのデータを取得
	int nLoadMapType = m_pMapData[m_nCurrentMapPosY * MAP_WIDTH + m_nCurrentMapPosX].nMapType;

	// 安全処理
	if (nLoadMapType < 0 || nLoadMapType >= MAX_MAP_TYPE) return;

	// 一度入ったフラグ
	m_pMapData[m_nCurrentMapPosY * MAP_WIDTH + m_nCurrentMapPosX].bClearFlag = true;

	// ロードするマップのパスを作成
	char szFileName[256];

	// スタート地点
	if (m_nCurrentMapPosX == 0 && m_nCurrentMapPosY == 0)
	{
		//BG
		std::sprintf(szFileName, FILE_PATH"map/renga/start/%d/map_bg.csv", nLoadMapType);
		CField::CreateBg(szFileName, &g_TexBG, 1, 1);
		// TILE
		std::sprintf(szFileName, FILE_PATH"map/renga/start/%d/map_tile.csv", nLoadMapType);
		CField::Create(szFileName, &g_TexTile, 11, 5);
		// OBJECT
		std::sprintf(szFileName, FILE_PATH"map/renga/start/%d/map_object.csv", nLoadMapType);
		CField::SetObject(szFileName);
		// PLAYER
		std::sprintf(szFileName, FILE_PATH"map/renga/start/%d/map_player.csv", nLoadMapType);
		// 初回
		if (m_bStart)
		{
			CStageManager::SetPlayerPos(Float3{ 96 * 4, 96 * 11, 0 });
			m_bStart = false;
		}
		else
		{
			CField::SetPlayer(szFileName, CStageChangeArea::GetGotoChangeArea());
		}
		// STAGE_CHANGE_AREA
		std::sprintf(szFileName, FILE_PATH"map/renga/start/%d/map_area.csv", nLoadMapType);
		CField::SetChangeArea(szFileName);
	}
	// ボス部屋へ行くマップ
	else if (nLoadMapType <= B && nLoadMapType >= L)
	{
		//BG
		std::sprintf(szFileName, FILE_PATH"map/renga/%d/map_bg.csv", nLoadMapType);
		CField::CreateBg(szFileName, &g_TexBG, 1, 1);
		// TILE
		std::sprintf(szFileName, FILE_PATH"map/renga/%d/map_tile.csv", nLoadMapType);
		CField::Create(szFileName, &g_TexTile, 11, 5);
		// OBJECT
		std::sprintf(szFileName, FILE_PATH"map/renga/%d/map_object.csv", nLoadMapType);
		CField::SetObject(szFileName, true);
		// ENEMY
		std::sprintf(szFileName, FILE_PATH"map/renga/%d/map_enemy.csv", nLoadMapType);
		CField::SetEnemy(szFileName);
		// PLAYER
		std::sprintf(szFileName, FILE_PATH"map/renga/%d/map_player.csv", nLoadMapType);
		CField::SetPlayer(szFileName, CStageChangeArea::GetGotoChangeArea());
		// STAGE_CHANGE_AREA
		std::sprintf(szFileName, FILE_PATH"map/renga/%d/map_area.csv", nLoadMapType);
		CField::SetChangeArea(szFileName);
	}
	else
	{
		//BG
		std::sprintf(szFileName, FILE_PATH"map/renga/%d/map_bg.csv", nLoadMapType);
		CField::CreateBg(szFileName, &g_TexBG, 1, 1);
		// TILE
		std::sprintf(szFileName, FILE_PATH"map/renga/%d/map_tile.csv", nLoadMapType);
		CField::Create(szFileName, &g_TexTile, 11, 5);
		// OBJECT
		std::sprintf(szFileName, FILE_PATH"map/renga/%d/map_object.csv", nLoadMapType);
		CField::SetObject(szFileName);
		// ENEMY
		std::sprintf(szFileName, FILE_PATH"map/renga/%d/map_enemy.csv", nLoadMapType);
		CField::SetEnemy(szFileName);
		// PLAYER
		std::sprintf(szFileName, FILE_PATH"map/renga/%d/map_player.csv", nLoadMapType);
		CField::SetPlayer(szFileName, CStageChangeArea::GetGotoChangeArea());
		// STAGE_CHANGE_AREA
		std::sprintf(szFileName, FILE_PATH"map/renga/%d/map_area.csv", nLoadMapType);
		CField::SetChangeArea(szFileName);
	}
	
}


//========================================
//
//	初期化
//
//========================================
void CStageMaker::Init()
{
	// テクスチャ
	g_TexBG.LoadTexture(FILE_PATH"map/renga/bg.png");
	g_TexTile.LoadTexture(FILE_PATH"map/renga/tile.png");
	sm_minimapTexture.LoadTexture(FILE_PATH"map/minimap.tga");
	sm_minimapUITexture.LoadTexture(FILE_PATH"map/minimap_ui.tga");
	sm_minimapTextTexture.LoadTexture(FILE_PATH"map/minimap_text.tga");
}

//========================================
//
//	終了処理
//
//========================================
void CStageMaker::Uninit()
{
	// テクスチャ
	g_TexBG.UnloadTexture();
	g_TexTile.UnloadTexture();
	sm_minimapTexture.UnloadTexture();
	sm_minimapUITexture.UnloadTexture();
	sm_minimapTextTexture.UnloadTexture();
}

//========================================
//
//	更新
//
//========================================
void CStageMaker::Update()
{
	
}


//========================================
//
//	描画
//
//========================================
void CStageMaker::Draw()
{

}

