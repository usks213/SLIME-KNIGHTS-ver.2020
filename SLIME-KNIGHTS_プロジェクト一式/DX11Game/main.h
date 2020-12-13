//=============================================================================
//
// サンプル処理 [main.h]
// Author : KOSHI USAMI
//
//=============================================================================
#pragma once

#include <windows.h>
#include <tchar.h>
#include <mmsystem.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>
//#include <atltypes.h>	// 共有クラス
#include <time.h>
#include <iostream>


// 本来はヘッダに書かない方が良い
using namespace DirectX;

// マクロ定義
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x) {if(x){(x)->Release();x=nullptr;}}
#endif
#ifndef SAFE_DELETE
#define SAFE_DELETE(x) {if(x){delete(x);x=nullptr;}}
#endif
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(x) {if(x){delete[](x);x=nullptr;}}
#endif

#define SCREEN_WIDTH	(1280)				// ウインドウの幅
#define SCREEN_HEIGHT	(720)				// ウインドウの高さ
#define SCREEN_CENTER_X	(SCREEN_WIDTH/2)	// ウインドウの中心Ｘ座標
#define SCREEN_CENTER_Y	(SCREEN_HEIGHT/2)	// ウインドウの中心Ｙ座標

#define	NUM_VERTEX		(4)					// 頂点数
#define	NUM_POLYGON		(2)					// ポリゴン数

#define DEFAULT_OBJECT_SIZE (96)

#define FILE_PATH "rom/"


// 頂点フォーマット( 頂点座標[2D] / 反射光 / テクスチャ座標 )
typedef struct {
	XMFLOAT3 vtx;		// 頂点座標
	XMFLOAT4 diffuse;	// 拡散反射光
	XMFLOAT2 tex;		// テクスチャ座標
} VERTEX_2D;

// 頂点フォーマット
struct Vertex
{
	XMFLOAT3 pos;	// 座標
	XMFLOAT3 nor;	// 法線
	XMFLOAT2 tex;	// テクスチャ座標
	XMFLOAT4 color;	// 色
};

// Switch用
typedef XMFLOAT2 Float2;
typedef XMFLOAT3 Float3;
typedef XMFLOAT4 Float4;

// プロトタイプ宣言
HWND GetMainWnd();
HINSTANCE GetInstance();
ID3D11Device* GetDevice();
ID3D11DeviceContext* GetDeviceContext();
//=============================================================================
//	デバッグ表示フラグ
//=============================================================================
bool GetDebugFlag();
//=============================================================================
//	デバッグ表示フラグ
//=============================================================================
void SetDebugFlag(bool bFlag);