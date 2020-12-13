//==================================================================
//									font.cpp
//	文字列表示
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//
//	2020/08/08	フォントクラス
//
//===================================================================


//====== インクルード部 ======
#include "string.h"
#include "../sprite.h"
#include "../texture.h"
#include "word.h"
#include "objectMgr.h"



//===== マクロ定義 =====
#define FULL_FONT_SIZE_X	(8)
#define FULL_FONT_SIZE_Y	(8)
#define FULL_FONT_WIDTH	  (752)
#define FULL_FONT_HEIGHT  (752)

#define HALF_FONT_SIZE_X	(4)
#define HALF_FONT_SIZE_Y	(8)
#define HALF_FONT_WIDTH	   (64)
#define HALF_FONT_HEIGHT  (128)



//===== プロトタイプ宣言 =====

//===== 名前空間 =====
using namespace STRING;

//===== グローバル変数 =====


//===== 静的メンバ =====
CTexture CString::sm_fullFontTexture;
CTexture CString::sm_halfFontTexture;


//========================================
//
//	コンストラクタ
//
//========================================
CString::CString()
{
	// ポリゴンのパラメータの初期化
	m_transform;

	// スプライトデータ
	m_sprite;

	// レイヤー
	m_enLayer = LAYER::STRING;

	m_bCamera = false;
	m_eOffSetX = EOFFSET_X::LEFT;
	m_eOffSetY = EOFFSET_Y::TOP;
	m_wordColor = Float4{ 1,1,1,1 };
	m_wordSize = Float2{ 50, 50 };
	m_pText = nullptr;
}

//========================================
//
//	コンストラクタ
//
//========================================
CString::CString(const char* pszText, Float3 pos, Float2 size, Float4 color, EOFFSET_X eOffSetX, EOFFSET_Y eOffSetY, bool bCamera)
{
	// ポリゴンのパラメータの初期化
	m_transform;

	// スプライトデータ
	m_sprite;

	// レイヤー
	m_enLayer = LAYER::STRING;

	m_bCamera = false;
	m_eOffSetX = EOFFSET_X::LEFT;
	m_eOffSetY = EOFFSET_Y::TOP;
	m_wordColor = Float4{ 1,1,1,1 };
	m_wordSize = Float2{ 50, 50 };
	m_pText = nullptr;


	int nFullWidthChar;	//全角文字の２バイト分のデータ
	int nOffset;
	int nCharPosX;
	int nCharPosY;
	int nCharCnt;
	bool bHalf = false;

	// 文字クラスポイント
	CWord *pWord = nullptr;
	// 座標
	Float3 wordPos = { 0.0f, 0.0f, 0.0f };
	// テクスチャ座標
	Float2 texPos = { 0.0f, 0.0f };
	Float2 texSize = { 0.0f, 0.0f };
	// 文字列クラスの生成
	CString *pString = this;
	pString->m_bCamera = bCamera;
	pString->m_sprite;
	pString->m_wordSize = size;
	pString->m_wordColor = color;
	pString->m_pText = pszText;

	// オフセット座標
	float fOffSetX = 0;
	float fOffSetY = 0;
	pString->m_eOffSetX = eOffSetX;
	pString->m_eOffSetY = eOffSetY;

	// 文字列の長さから
	switch (eOffSetX)
	{
	case STRING::LEFT:
		fOffSetX = -size.x / 2 - 1;
		break;
	case STRING::CENTER_X:
		fOffSetX = strlen(pszText) / 2.0f * size.x / 2 - size.x / 2;
		break;
	case STRING::RIGHT:
		fOffSetX = strlen(pszText) * size.x / 2 - size.x / 4;
		break;
	}

	// \nの数から
	switch (eOffSetY)
	{
	case STRING::TOP:
		fOffSetY = -size.y / 2 - 1;
		break;
	case STRING::CENTER_Y:
		break;
	case STRING::DOWN:
		break;
	}

	// オフセットをセット
	wordPos = pos;
	wordPos.x -= fOffSetX;
	wordPos.y -= fOffSetY;


	for (nCharCnt = 0; pszText[nCharCnt]; nCharCnt++)
	{
		//全角かどうかの判断
		if ((0x7f < (unsigned char)pszText[nCharCnt] && (unsigned char)pszText[nCharCnt] < 0xa0) || 0xdf < (unsigned char)pszText[nCharCnt])
		{//全角だった
			nFullWidthChar = ((unsigned char)pszText[nCharCnt] << 8) + (unsigned char)pszText[nCharCnt + 1];

			//----- 文字コードから画像の文字の位置に変換 -----
			nOffset = 0x8140;
			if (0xdf < (unsigned char)pszText[nCharCnt])	nOffset += 0x4000;

			nCharPosX = ((unsigned char)pszText[nCharCnt + 1] - (nOffset & 0x00ff)) % (FULL_FONT_WIDTH / FULL_FONT_SIZE_X + 1);
			if (0x7f < (unsigned char)pszText[nCharCnt + 1])
				if (0x9e >= (unsigned char)pszText[nCharCnt + 1])
					nCharPosX--;
			nCharPosY = (nFullWidthChar - nOffset) / (FULL_FONT_WIDTH / FULL_FONT_SIZE_Y);
			nCharPosY = ((unsigned char)pszText[nCharCnt] - (nOffset >> 8) + 1) * 2;
			if (0x9e >= (unsigned char)pszText[nCharCnt + 1])	nCharPosY--;
			nCharPosY--;

			//----- 文字生成 -----
			// テクスチャ座標
			texSize.x = 1.0f / (FULL_FONT_WIDTH / FULL_FONT_SIZE_X);
			texSize.y = 1.0f / (FULL_FONT_HEIGHT / FULL_FONT_SIZE_Y);
			texPos.x = texSize.x * nCharPosX;
			texPos.y = texSize.y * nCharPosY;

			// ハーフフラグがtrueのとき
			if (bHalf) wordPos.x += size.x / 4.0f;
			bHalf = false;

			// ワードの生成
			pWord = CWord::Create(wordPos, size, texPos, texSize, color, &sm_fullFontTexture);

			// 座標
			wordPos.x += size.x;

			// リストに格納
			pString->m_wordList.AddNode(pWord);


			nCharCnt++;	//全角の時の処理なので文字をもう一つ送る
		}
		else
		{//半角だった
			//----- 文字コードから画像の文字の位置に変換 -----
			nCharPosX = ((unsigned char)pszText[nCharCnt] & 0x0f) % 0x10;
			nCharPosY = ((unsigned char)pszText[nCharCnt] >> 4);

			//----- 文字生成 -----
			texSize.x = 1.0f / (HALF_FONT_WIDTH / HALF_FONT_SIZE_X);
			texSize.y = 1.0f / (HALF_FONT_HEIGHT / HALF_FONT_SIZE_Y);
			texPos.x = texSize.x * nCharPosX;
			texPos.y = texSize.y * nCharPosY;

			// ハーフフラグがtrueのとき
			if (!bHalf) wordPos.x -= size.x / 4.0f;
			bHalf = true;

			// ワードの生成
			pWord = CWord::Create(wordPos, Float2{ size.x / 2, size.y }, texPos, texSize, color, &sm_halfFontTexture);

			// 座標
			wordPos.x += size.x / 2.0f;

			// リストに格納
			pString->m_wordList.AddNode(pWord);
		}
	}


}


//========================================
//
//	デストラクタ
//
//========================================
CString::~CString()
{

}


//========================================
//
//	初期化
//
//========================================
void CString::Init()
{
	// テクスチャのロード
	sm_fullFontTexture.LoadTexture(FILE_PATH"font/misaki_gothic_2nd.tga");
	sm_halfFontTexture.LoadTexture(FILE_PATH"font/misaki_gothic_2nd_4x8.tga");

}


//========================================
//
//	終了処理
//
//========================================
void CString::Uninit()
{
	// テクスチャの解放
	sm_fullFontTexture.UnloadTexture();
	sm_halfFontTexture.UnloadTexture();

}


//========================================
//
//	更新
//
//========================================
void CString::Update()
{
	

}


//========================================
//
//	描画
//
//========================================
void CString::Draw()
{
	List<CWord> *pHead = m_wordList.GetHead();
	if (pHead == nullptr) return;

	List<CWord> *pNode = nullptr;
	for (pNode = pHead; pNode != nullptr; pNode = pNode->GetNext())
	{
		pNode->GetThis()->Draw(m_bCamera);
	}
}


//========================================
//
//	生成
//
//========================================
CString* CString::Create(const char* pszText, Float3 pos, Float2 size, Float4 color, EOFFSET_X eOffSetX, EOFFSET_Y eOffSetY, bool bCamera)
{
	int nFullWidthChar;	//全角文字の２バイト分のデータ
	int nOffset;
	int nCharPosX;
	int nCharPosY;
	int nCharCnt;
	bool bHalf = false;

	// 文字クラスポイント
	CWord *pWord = nullptr;
	// 座標
	Float3 wordPos = { 0.0f, 0.0f, 0.0f };
	// テクスチャ座標
	Float2 texPos	= { 0.0f, 0.0f };
	Float2 texSize	= { 0.0f, 0.0f };
	// 文字列クラスの生成
	CString *pString = CObjectManager::CreateObject<CString>(pos);
	pString->m_bCamera = bCamera;
	pString->m_sprite;
	pString->m_wordSize = size;
	pString->m_wordColor = color;
	pString->m_pText = pszText;

	// オフセット座標
	float fOffSetX = 0;
	float fOffSetY = 0;
	pString->m_eOffSetX = eOffSetX;
	pString->m_eOffSetY = eOffSetY;

	// 文字列の長さから
	switch (eOffSetX)
	{
	case STRING::LEFT:
		fOffSetX = -size.x / 2 - 1;
		break;
	case STRING::CENTER_X:
		fOffSetX = strlen(pszText) / 2.0f * size.x / 2 - size.x / 2;
		break;
	case STRING::RIGHT:
		fOffSetX = strlen(pszText) * size.x / 2 - size.x / 4;
		break;
	}

	// \nの数から
	switch (eOffSetY)
	{
	case STRING::TOP:
		fOffSetY = -size.y / 2 - 1;
		break;
	case STRING::CENTER_Y:
		break;
	case STRING::DOWN:
		break;
	}
	
	// オフセットをセット
	wordPos = pos;
	wordPos.x -= fOffSetX;
	wordPos.y -= fOffSetY;


	for (nCharCnt = 0; pszText[nCharCnt]; nCharCnt++)
	{
		//全角かどうかの判断
		if ((0x7f < (unsigned char)pszText[nCharCnt] && (unsigned char)pszText[nCharCnt] < 0xa0) || 0xdf < (unsigned char)pszText[nCharCnt])
		{//全角だった
			nFullWidthChar = ((unsigned char)pszText[nCharCnt] << 8) + (unsigned char)pszText[nCharCnt + 1];

			//----- 文字コードから画像の文字の位置に変換 -----
			nOffset = 0x8140;
			if (0xdf < (unsigned char)pszText[nCharCnt])	nOffset += 0x4000;

			nCharPosX = ((unsigned char)pszText[nCharCnt + 1] - (nOffset & 0x00ff)) % (FULL_FONT_WIDTH / FULL_FONT_SIZE_X + 1);
			if (0x7f < (unsigned char)pszText[nCharCnt + 1])
				if (0x9e >= (unsigned char)pszText[nCharCnt + 1])
					nCharPosX--;
			nCharPosY = (nFullWidthChar - nOffset) / (FULL_FONT_WIDTH / FULL_FONT_SIZE_Y);
			nCharPosY = ((unsigned char)pszText[nCharCnt] - (nOffset >> 8) + 1) * 2;
			if (0x9e >= (unsigned char)pszText[nCharCnt + 1])	nCharPosY--;
			nCharPosY--;

			//----- 文字生成 -----
			// テクスチャ座標
			texSize.x = 1.0f / (FULL_FONT_WIDTH  / FULL_FONT_SIZE_X);
			texSize.y = 1.0f / (FULL_FONT_HEIGHT / FULL_FONT_SIZE_Y);
			texPos.x = texSize.x * nCharPosX;
			texPos.y = texSize.y * nCharPosY;

			// ハーフフラグがtrueのとき
			if(bHalf) wordPos.x += size.x / 4.0f;
			bHalf = false;

			// ワードの生成
			pWord = CWord::Create(wordPos, size, texPos, texSize, color, &sm_fullFontTexture);

			// 座標
			wordPos.x += size.x;

			// リストに格納
			pString->m_wordList.AddNode(pWord);


			nCharCnt++;	//全角の時の処理なので文字をもう一つ送る
		}
		else
		{//半角だった
			//----- 文字コードから画像の文字の位置に変換 -----
			nCharPosX = ((unsigned char)pszText[nCharCnt] & 0x0f) % 0x10;
			nCharPosY = ((unsigned char)pszText[nCharCnt] >> 4);

			//----- 文字生成 -----
			texSize.x = 1.0f / (HALF_FONT_WIDTH  / HALF_FONT_SIZE_X);
			texSize.y = 1.0f / (HALF_FONT_HEIGHT / HALF_FONT_SIZE_Y);
			texPos.x = texSize.x * nCharPosX;
			texPos.y = texSize.y * nCharPosY;

			// ハーフフラグがtrueのとき
			if (!bHalf) wordPos.x -= size.x / 4.0f;
			bHalf = true;

			// ワードの生成
			pWord = CWord::Create(wordPos, Float2{size.x / 2, size.y}, texPos, texSize, color, &sm_halfFontTexture);

			// 座標
			wordPos.x += size.x / 2.0f;

			// リストに格納
			pString->m_wordList.AddNode(pWord);
		}
	}

	return pString;
}


//========================================
//
//	生成
//
//========================================
CString* CString::Create()
{
	// 文字列クラスの生成
	CString *pString = CObjectManager::CreateObject<CString>();

	return pString;
}

//========================================
//
//	消去
//
//========================================
void CString::Destroy()
{
	List<CWord> *pHead = m_wordList.GetHead();
	if (pHead == nullptr) return;

	List<CWord> *pNode = nullptr;
	List<CWord> *pNextBack = nullptr;
	CWord *pWord = nullptr;
	for (pNode = pHead; pNode != nullptr; pNode = pNextBack)
	{
		pNextBack = pNode->GetNext();
		pWord = pNode->GetThis();

		if (m_wordList.DestroyNode(pNode))
		{
			delete pWord;
		}
	}

	CObjectManager::DestroyObject(this);
}


//========================================
//
//	文字列の変更
//
//========================================
void CString::SetWord(const char* pszText)
{
	if (pszText == nullptr) return;
	m_pText = pszText;

	// リストの先頭取得
	List<CWord> *pHead = m_wordList.GetHead();

	int nCharCnt;
	// 文字クラスポイント
	CWord *pWord = nullptr;
	// テクスチャ座標
	Float2 texPos = { 0.0f, 0.0f };
	Float2 texSize = { 0.0f, 0.0f };
	// リストのノード
	List<CWord> *pNode = nullptr;

	// 座標
	Float3 wordPos = { 0.0f, 0.0f, 0.0f };
	// オフセット座標
	float fOffSetX = 0;
	float fOffSetY = 0;

	// 文字列の長さから
	switch (m_eOffSetX)
	{
	case STRING::LEFT:
		fOffSetX = -m_wordSize.x / 2 - 1;
		break;
	case STRING::CENTER_X:
		fOffSetX = strlen(pszText) / 2.0f * m_wordSize.x / 2 - m_wordSize.x / 2;
		break;
	case STRING::RIGHT:
		fOffSetX = strlen(pszText) * m_wordSize.x / 2 - m_wordSize.x / 4;
		break;
	}


	// \nの数から
	switch (m_eOffSetY)
	{
	case STRING::TOP:
		fOffSetY = -m_wordSize.y / 2 - 1;
		break;
	case STRING::CENTER_Y:
		break;
	case STRING::DOWN:
		break;
	}

	// オフセットをセット
	wordPos = m_transform.GetPos();
	wordPos.x -= fOffSetX;
	wordPos.y -= fOffSetY;

	// 文字列更新
	for (pNode = pHead, nCharCnt = 0; pNode != nullptr && pszText[nCharCnt]; pNode = pNode->GetNext(), nCharCnt++)
	{
		SetWordData(pNode->GetThis(), pszText, nCharCnt, &wordPos, &m_wordSize, &m_wordColor);
	}

	// 新規生成
	if (pNode == nullptr)
	{
		for (; pszText[nCharCnt]; nCharCnt++)
		{
			pWord = CWord::Create();
			m_wordList.AddNode(pWord);
			SetWordData(pWord, pszText, nCharCnt, &wordPos, &m_wordSize, &m_wordColor);
		}
	}
	else
	{
		List<CWord> *pNextBack = nullptr;
		for ( ; pNode != nullptr; pNode = pNextBack)
		{
			pNextBack = pNode->GetNext();
			pWord = pNode->GetThis();

			if(m_wordList.DestroyNode(pNode))
				pWord->Destroy();
		}
	}

}


//========================================
//
//	格納文字列のデータ更新
//
//========================================
void CString::SetWordData(CWord *pWord, const char *pszText, int nCharCnt, Float3 *pPos, Float2 *pSize, Float4 *pColor)
{
	int nFullWidthChar;	//全角文字の２バイト分のデータ
	int nOffset;
	int nCharPosX;
	int nCharPosY;
	static bool bHalf = false;

	// テクスチャ座標
	Float2 texPos = { 0.0f, 0.0f };
	Float2 texSize = { 0.0f, 0.0f };

	//全角かどうかの判断
	if ((0x7f < (unsigned char)pszText[nCharCnt] && (unsigned char)pszText[nCharCnt] < 0xa0) || 0xdf < (unsigned char)pszText[nCharCnt])
	{//全角だった
		nFullWidthChar = ((unsigned char)pszText[nCharCnt] << 8) + (unsigned char)pszText[nCharCnt + 1];

		//----- 文字コードから画像の文字の位置に変換 -----
		nOffset = 0x8140;
		if (0xdf < (unsigned char)pszText[nCharCnt])	nOffset += 0x4000;

		nCharPosX = ((unsigned char)pszText[nCharCnt + 1] - (nOffset & 0x00ff)) % (FULL_FONT_WIDTH / FULL_FONT_SIZE_X + 1);
		if (0x7f < (unsigned char)pszText[nCharCnt + 1])
			if (0x9e >= (unsigned char)pszText[nCharCnt + 1])
				nCharPosX--;
		nCharPosY = (nFullWidthChar - nOffset) / (FULL_FONT_WIDTH / FULL_FONT_SIZE_Y);
		nCharPosY = ((unsigned char)pszText[nCharCnt] - (nOffset >> 8) + 1) * 2;
		if (0x9e >= (unsigned char)pszText[nCharCnt + 1])	nCharPosY--;
		nCharPosY--;

		//----- 文字生成 -----
		// テクスチャ座標
		texSize.x = 1.0f / (FULL_FONT_WIDTH / FULL_FONT_SIZE_X);
		texSize.y = 1.0f / (FULL_FONT_HEIGHT / FULL_FONT_SIZE_Y);
		texPos.x = texSize.x * nCharPosX;
		texPos.y = texSize.y * nCharPosY;

		// ハーフフラグがtrueのとき
		if (bHalf) pPos->x += pSize->x / 4.0f;
		bHalf = false;

		// 更新
		pWord->GetSprite()->SetTexPos(texPos);
		pWord->GetSprite()->SetTexSize(texSize);
		pWord->GetSprite()->SetColor(*pColor);
		pWord->GetTrans()->SetPos(*pPos);
		pWord->GetTrans()->SetSize(*pSize);
		pWord->SetTexture(&sm_halfFontTexture);

		// 座標
		pPos->x += pSize->x;

		nCharCnt++;	//全角の時の処理なので文字をもう一つ送る
	}
	else
	{//半角だった
		//----- 文字コードから画像の文字の位置に変換 -----
		nCharPosX = ((unsigned char)pszText[nCharCnt] & 0x0f) % 0x10;
		nCharPosY = ((unsigned char)pszText[nCharCnt] >> 4);

		//----- 文字生成 -----
		texSize.x = 1.0f / (HALF_FONT_WIDTH / HALF_FONT_SIZE_X);
		texSize.y = 1.0f / (HALF_FONT_HEIGHT / HALF_FONT_SIZE_Y);
		texPos.x = texSize.x * nCharPosX;
		texPos.y = texSize.y * nCharPosY;

		// ハーフフラグがtrueのとき
		if (!bHalf) pPos->x -= pSize->x / 4.0f;
		bHalf = true;

		// 更新
		pWord->GetSprite()->SetTexPos(texPos);
		pWord->GetSprite()->SetTexSize(texSize);
		pWord->GetSprite()->SetColor(*pColor);
		pWord->GetTrans()->SetPos(*pPos);
		pWord->GetTrans()->SetSize(Float2{pSize->x / 2, pSize->y});
		pWord->SetTexture(&sm_halfFontTexture);

		// 座標
		pPos->x += pSize->x / 2.0f;
	}
}

