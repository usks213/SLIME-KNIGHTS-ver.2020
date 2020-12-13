//=============================================================================
//
// モデル [model.cpp]
// Author : KOSHI USAMI
//
//=============================================================================
//
//	開発履歴
//
//	2020/06/21	3Dモデル	
//
//=============================================================================

//===== インクルード部 =====
#include "model.h"


CModel::CModel()
{
	m_pVertexList = nullptr;
	m_pIndexList = nullptr;

	m_nVertexCount = 0;
	m_nIndexCount = 0;
}

CModel::~CModel()
{
	if (m_nVertexCount == 0) return;

	// バーテックスリストの解放
	if (nullptr != m_pVertexList)
	{
		delete[] m_pVertexList;
	}

	// インデックスリストの解放
	if (nullptr != m_pIndexList)
	{
		delete[] m_pIndexList;
	}

	m_pVertexList = nullptr;
	m_pIndexList = nullptr;

	m_nVertexCount = 0;
	m_nIndexCount = 0;
}

void CModel::CreateSphereModel(int nSegment)
{
	//頂点バッファ作成
	int     vcount = (nSegment + 1) * (nSegment / 2 + 1);
	m_pVertexList = new Vertex[vcount];

	for (int i = 0; i <= (nSegment / 2); ++i) {
		float irad = XM_PI * 2.0f / (float)nSegment * (float)i;
		float y = (float)cos(irad);
		float r = (float)sin(irad);
		float v = (float)i / (float)(nSegment / 2);
		for (int j = 0; j <= nSegment; ++j) {
			float jrad = XM_PI * 2.0f / (float)nSegment * (float)j;
			float x = r * (float)cos(jrad);
			float z = r * (float)sin(jrad);
			float u = (float)j / (float)nSegment;
			int   inx = i * (nSegment + 1) + j;
			m_pVertexList[inx].pos.x = x;
			m_pVertexList[inx].pos.y = y;
			m_pVertexList[inx].pos.z = z;
			m_pVertexList[inx].nor.x = x;
			m_pVertexList[inx].nor.y = y;
			m_pVertexList[inx].nor.z = z;
			m_pVertexList[inx].tex.x = u;
			m_pVertexList[inx].tex.y = v;
		}
	}
	int   icount = nSegment * 3 + nSegment * (nSegment / 2 - 1) * 6 + nSegment * 3;
	m_pIndexList = new WORD[icount];

	icount = 0;
	int i = 0;
	for (int j = 0; j < nSegment; ++j) {
		m_pIndexList[icount] = i * (nSegment + 1) + j;
		m_pIndexList[icount + 1] = (i + 1) * (nSegment + 1) + j + 1;
		m_pIndexList[icount + 2] = (i + 1) * (nSegment + 1) + j;
		icount += 3;
	}
	for (i = 1; i < nSegment / 2; ++i) {
		for (int j = 0; j < nSegment; ++j) {
			m_pIndexList[icount] = i * (nSegment + 1) + j;
			m_pIndexList[icount + 1] = i * (nSegment + 1) + j + 1;
			m_pIndexList[icount + 2] = (i + 1) * (nSegment + 1) + j;
			icount += 3;
			m_pIndexList[icount] = i * (nSegment + 1) + j + 1;
			m_pIndexList[icount + 1] = (i + 1) * (nSegment + 1) + j + 1;
			m_pIndexList[icount + 2] = (i + 1) * (nSegment + 1) + j;
			icount += 3;
		}
	}
	i = nSegment / 2;
	for (int j = 0; j < nSegment; ++j) {
		m_pIndexList[icount] = i * (nSegment + 1) + j;
		m_pIndexList[icount + 1] = (i + 1) * (nSegment + 1) + j + 1;
		m_pIndexList[icount + 2] = (i + 1) * (nSegment + 1) + j;
		icount += 3;
	}

	// 頂点・インデックスの数
	m_nVertexCount = vcount;
	m_nIndexCount = icount;
}


void CModel::CreateCubeModel()
{
	static Vertex g_pVertexList[]{
		// 後
	{ XMFLOAT3(-0.5f,  0.5f, -0.5f), XMFLOAT3( 0.0f,  0.0f, -1.0f), XMFLOAT2(1.0f,  0.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
	{ XMFLOAT3( 0.5f,  0.5f, -0.5f), XMFLOAT3( 0.0f,  0.0f, -1.0f), XMFLOAT2(0.0f,  1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
	{ XMFLOAT3(-0.5f, -0.5f, -0.5f), XMFLOAT3( 0.0f,  0.0f, -1.0f), XMFLOAT2(0.0f,  0.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
	{ XMFLOAT3( 0.5f, -0.5f, -0.5f), XMFLOAT3( 0.0f,  0.0f, -1.0f), XMFLOAT2(1.0f,  1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
		// 前
	{ XMFLOAT3(-0.5f,  0.5f,  0.5f), XMFLOAT3( 0.0f,  0.0f,  1.0f), XMFLOAT2(1.0f,  0.0f), XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f) },
	{ XMFLOAT3(-0.5f, -0.5f,  0.5f), XMFLOAT3( 0.0f,  0.0f,  1.0f), XMFLOAT2(0.0f,  1.0f), XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f) },
	{ XMFLOAT3( 0.5f,  0.5f,  0.5f), XMFLOAT3( 0.0f,  0.0f,  1.0f), XMFLOAT2(0.0f,  0.0f), XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f) },
	{ XMFLOAT3( 0.5f, -0.5f,  0.5f), XMFLOAT3( 0.0f,  0.0f,  1.0f), XMFLOAT2(1.0f,  1.0f), XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f) },
		// 左
	{ XMFLOAT3(-0.5f,  0.5f,  0.5f), XMFLOAT3(-1.0f,  0.0f,  0.0f), XMFLOAT2(1.0f,  1.0f), XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f) },
	{ XMFLOAT3(-0.5f,  0.5f, -0.5f), XMFLOAT3(-1.0f,  0.0f,  0.0f), XMFLOAT2(0.0f,  1.0f), XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f) },
	{ XMFLOAT3(-0.5f, -0.5f,  0.5f), XMFLOAT3(-1.0f,  0.0f,  0.0f), XMFLOAT2(1.0f,  0.0f), XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f) },
	{ XMFLOAT3(-0.5f, -0.5f, -0.5f), XMFLOAT3(-1.0f,  0.0f,  0.0f), XMFLOAT2(0.0f,  0.0f), XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f) },
		// 右
	{ XMFLOAT3( 0.5f,  0.5f,  0.5f), XMFLOAT3( 1.0f,  0.0f,  0.0f), XMFLOAT2(0.0f,  0.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
	{ XMFLOAT3( 0.5f, -0.5f,  0.5f), XMFLOAT3( 1.0f,  0.0f,  0.0f), XMFLOAT2(1.0f,  0.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
	{ XMFLOAT3( 0.5f,  0.5f, -0.5f), XMFLOAT3( 1.0f,  0.0f,  0.0f), XMFLOAT2(0.0f,  1.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
	{ XMFLOAT3( 0.5f, -0.5f, -0.5f), XMFLOAT3( 1.0f,  0.0f,  0.0f), XMFLOAT2(1.0f,  1.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
		// 上
	{ XMFLOAT3(-0.5f,  0.5f,  0.5f), XMFLOAT3( 0.0f,  1.0f,  0.0f), XMFLOAT2(0.0f,  0.0f), XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f) },
	{ XMFLOAT3( 0.5f,  0.5f,  0.5f), XMFLOAT3( 0.0f,  1.0f,  0.0f), XMFLOAT2(1.0f,  0.0f), XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f) },
	{ XMFLOAT3(-0.5f,  0.5f, -0.5f), XMFLOAT3( 0.0f,  1.0f,  0.0f), XMFLOAT2(0.0f,  1.0f), XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f) },
	{ XMFLOAT3( 0.5f,  0.5f, -0.5f), XMFLOAT3( 0.0f,  1.0f,  0.0f), XMFLOAT2(1.0f,  1.0f), XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f) },
		// 下
	{ XMFLOAT3(-0.5f, -0.5f,  0.5f), XMFLOAT3( 0.0f, -1.0f,  0.0f), XMFLOAT2(1.0f,  0.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
	{ XMFLOAT3(-0.5f, -0.5f, -0.5f), XMFLOAT3( 0.0f, -1.0f,  0.0f), XMFLOAT2(0.0f,  1.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
	{ XMFLOAT3( 0.5f, -0.5f,  0.5f), XMFLOAT3( 0.0f, -1.0f,  0.0f), XMFLOAT2(0.0f,  0.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
	{ XMFLOAT3( 0.5f, -0.5f, -0.5f), XMFLOAT3( 0.0f, -1.0f,  0.0f), XMFLOAT2(1.0f,  1.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
};
	m_pVertexList = g_pVertexList;
	m_nVertexCount = 24;

	static WORD g_pIndexList[]{
	 0,  1,  2,     3,  2,  1,
	 4,  5,  6,     7,  6,  5,
	 8,  9, 10,    11, 10,  9,
	12, 13, 14,    15, 14, 13,
	16, 17, 18,    19, 18, 17,
	20, 21, 22,    23, 22, 21,
};
	m_pIndexList = g_pIndexList;
	m_nIndexCount = 36;

}


void CModel::CreatePlaneModel()
{
	// 頂点バッファ
	m_pVertexList = new Vertex[4];

	// 頂点座標
	m_pVertexList[0].pos = XMFLOAT3{ -0.5f,  0.5f, 0 };	// 左上
	m_pVertexList[1].pos = XMFLOAT3{  0.5f,  0.5f, 0 };	// 右上
	m_pVertexList[2].pos = XMFLOAT3{ -0.5f, -0.5f, 0 };	// 左下
	m_pVertexList[3].pos = XMFLOAT3{  0.5f, -0.5f, 0 };	// 右下

	// 法線
	m_pVertexList[0].nor = XMFLOAT3{ 0.0f,  0.0f, -1.0f };	// 左上
	m_pVertexList[1].nor = XMFLOAT3{ 0.0f,  0.0f, -1.0f };	// 右上
	m_pVertexList[2].nor = XMFLOAT3{ 0.0f,  0.0f, -1.0f };	// 左下
	m_pVertexList[3].nor = XMFLOAT3{ 0.5f,  0.0f, -1.0f };	// 右下

	// UV座標
	m_pVertexList[0].tex = XMFLOAT2{  0.0f,  0.0f};	// 左上
	m_pVertexList[1].tex = XMFLOAT2{  1.0f,  0.0f};	// 右上
	m_pVertexList[2].tex = XMFLOAT2{  0.0f,  1.0f};	// 左下
	m_pVertexList[3].tex = XMFLOAT2{  1.0f,  1.0f};	// 右下

	// 頂点カラー
	m_pVertexList[0].color = XMFLOAT4{ 1.0f, 1.0f, 1.0f, 1.0f };	// 左上
	m_pVertexList[1].color = XMFLOAT4{ 1.0f, 1.0f, 1.0f, 1.0f };	// 右上
	m_pVertexList[2].color = XMFLOAT4{ 1.0f, 1.0f, 1.0f, 1.0f };	// 左下
	m_pVertexList[3].color = XMFLOAT4{ 1.0f, 1.0f, 1.0f, 1.0f };	// 右下

	// インデックスバッファ
	m_pIndexList = new WORD[6];

	//インデックス情報
	m_pIndexList[0] = 0;
	m_pIndexList[1] = 1;
	m_pIndexList[2] = 2;
	m_pIndexList[3] = 1;
	m_pIndexList[4] = 2;
	m_pIndexList[5] = 3;

	// バーテックスカウント
	m_nVertexCount = 4;

	// インデックスカウント
	m_nIndexCount = 6;
	
}

void CModel::DestroyModel()
{

}
