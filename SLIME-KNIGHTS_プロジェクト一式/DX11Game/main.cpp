//=============================================================================
//
// DirectX11ベース [main.cpp]
// Author : KOSHI USAMI
//
//=============================================================================
//
//	開発履歴
//
//	2020/05/30	DirectX11の初期化
//	2020/05/31	シェーダーの作成、ポリゴンの描画の作成
//	2020/06/01	3D対応
//	2020/06/02	ライティング実装
//	2020/06/04	テクスチャ読み込みの作成
//	2020/06/14	オブジェクトを基底クラスとした
//				オブジェクト指向に変更
//	2020/06/16	入力処理実装
//	2020/06/17	フェードイン・フェードアウトの追加
//	2020/06/24	コリジョンの追加
//	2020/07/01	矩形と円の当たり判定追加
//	2020/07/08	コリジョンクラスの作成
//	2020/07/08	アニメータークラスの作成
//	2020/07/10	アニメーションクラスの作成
//	2020/07/14	フィールドクラスの作成
//	2020/07/15	リジッドボディクラス作成
//	2020/07/16	シーン管理クラス作成
//	2020/07/17	バレットクラス作成
//	2020/07/18	タイトルシーン、ゲームシーンの追加
//	2020/07/24	2D特化のベース作り、Switchとの互換性
//				トランスフォームとスプライトの作成
//	2020/07/31	レイヤー分けをクイックソートに
//	2020/08/01	当たり判定を四分木に
//	2020/08/02	キャラクターアクションクラスの作成
//				ステータスクラスの作成
//	2020/08/03	攻撃ベースクラスの作成
//	2020/08/08	文字列表示クラスの作成
//	2020/08/12	プレイヤーのイラストの実装
//	2020/08/13	プレイヤーの手の動きや遷移の制御
//	2020/08/14	ウェポンクラスの作成
//	2020/08/15	ヒットストップ
//	2020/08/18	エネミースライムの作成
//	2020/08/19	エネミーウィングの作成
//	2020/08/20	エネミーランスの作成
//	2020/08/23	ステージ管理システム
//	2020/08/25	ステージメイカークラスの作成
//	2020/08/26	ランダムステージ生成完成
//	2020/08/29	フロアクラスの作成	
//	2020/08/29	ステージレイアウトの作成	
//	2020/09/02	音を付けた（仮）
//	2020/09/03	ステージのレイアウト完成
//	2020/09/04	ミニマップ
//	2020/09/05	ボス部屋、ボス(仮)、
//	2020/09/05	チュートリアルマップ、スタートマップ、レベルアップテキスト、
//				経験値玉、UI、
//	2020/09/06	デカ羽スライム、弓スライム、ライト、ファイヤー、トゲ、キー
//	2020/09/07	リザルトUIの実装
//	2020/09/08	ボス作り直し、フィールドクラスの作り直し、ムービーUI
//	2020/09/10	操作の変更
//	2020/09/12	バレットのテクスチャを変更
//				完成！！（＼＾＿＾／）
//	2020/10/27	炎エフェクトの変更
//	2020/10/28	コンボの追加(テスト)
//	2020/11/01	コンボ・クリティカルの追加
//	2020/11/29	U22プロコン CSJA賞！！　ありがとうございます！！
//	2020/12/13	公開に向けて少し編集
//
//=============================================================================

//===== インクルード部 =====
#include "main.h"
#include "resource.h"
#include "DirectX11.h"
#include "input.h"
#include "source/sceneManager.h"
#include "Sound.h"
#include "sprite.h"
#include "source/string.h"


//-------- ライブラリのリンク
#pragma comment(lib, "winmm")
#pragma comment(lib, "imm32")
#pragma comment(lib, "d3d11")

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CLASS_NAME				_T("AppClass")					// ウインドウのクラス名
#define WINDOW_NAME				_T("SLIME KNIGHTS")				// ウインドウのキャプション名
#define FRAME_RATE		(60)

//*****************************************************************************
// 構造体定義
//*****************************************************************************
// (なし)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
int OnCreate(HWND hWnd, LPCREATESTRUCT lpcs);
HRESULT Init(HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
HWND						g_hWnd;					// メイン ウィンドウ ハンドル
HINSTANCE					g_hInst;				// インスタンス ハンドル

ID3D11Device*				g_pDevice;				// デバイス(設定周り)
ID3D11DeviceContext*		g_pDeviceContext;		// デバイス コンテキスト(描画周り)
IDXGISwapChain*				g_pSwapChain;			// スワップチェーン(ダブルバッファリング用)
ID3D11RenderTargetView*		g_pRenderTargetView;	// フレームバッファ
UINT						g_uSyncInterval = 0;	// 垂直同期 (0:無, 1:有)
ID3D11BlendState*			g_pBlendState;			// ブレンド ステート

bool g_bDebug = false;		// デバッグ表示フラグ
int							g_nCountFPS;			// FPSカウンタ
//STRING::CString *g_pString;							// FPS文字列


//=============================================================================
// メイン関数
//=============================================================================
int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);	// 無くても良いけど、警告が出る（未使用宣言）
	UNREFERENCED_PARAMETER(lpCmdLine);		// 無くても良いけど、警告が出る（未使用宣言）

	// COMの初期化	COMコンポーネントの使用
	HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	if (FAILED(hr)) return -1;

	WNDCLASSEX wcex = {
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MAINFRM)),
		LoadCursor(nullptr, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		nullptr,
		CLASS_NAME,
		nullptr
	};
	MSG		msg;

	// インスタンス ハンドル保存
	g_hInst = hInstance;

	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	// クライアント領域サイズからウィンドウ サイズ算出
	DWORD dwStyle = WS_OVERLAPPED | WS_CAPTION
		| WS_SYSMENU | WS_BORDER | WS_MINIMIZEBOX;
	DWORD dwExStyle = 0;
	RECT rc = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	AdjustWindowRectEx(&rc, dwStyle, FALSE, dwExStyle);

	// ウィンドウの作成
	g_hWnd = CreateWindowEx(dwExStyle,
		CLASS_NAME,
		WINDOW_NAME,
		dwStyle,
		CW_USEDEFAULT,		// ウィンドウの左座標
		CW_USEDEFAULT,		// ウィンドウの上座標
		rc.right - rc.left,	// ウィンドウ横幅
		rc.bottom - rc.top,	// ウィンドウ縦幅
		nullptr,
		nullptr,
		hInstance,
		nullptr);

	// ウインドウの表示
	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);

	// DirectXの初期化(ウィンドウを作成してから行う)
	if (FAILED(Init(g_hWnd, true))) {
		return -1;
	}
	// フレームカウント初期化
	timeBeginPeriod(1);			// 分解能設定

	// FPS算出用ワーク
	DWORD dwExecLastTime = timeGetTime();
	DWORD dwFPSLastTime = timeGetTime();
	DWORD dwCurrentTime = 0;
	DWORD dwFrameCount = 0;

	// メッセージループ
	for (;;) {
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) {
				// PostQuitMessage()が呼ばれたらループ終了
				break;
			}
			else {
				// メッセージの翻訳とディスパッチ
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			// 現在時間を取得
			dwCurrentTime = timeGetTime();
			// 0.5秒ごとに
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{
				g_nCountFPS = dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / FRAME_RATE))
			{
				dwExecLastTime = dwCurrentTime;

				// 更新処理
				Update();
				// 描画処理
				Draw();
				++dwFrameCount;
			}
			//// 描画処理
			//Draw();
			//++dwFrameCount;
		}
	}

	// 終了処理
	Uninit();

	// フレームカウンタをもとに戻す
	timeEndPeriod(1);

	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, g_hInst);

	// COMの解放
	CoUninitialize();

	return (int)msg.wParam;
}

//=============================================================================
// プロシージャ
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_CREATE:					//----- ウィンドウが生成された
		return OnCreate(hWnd, (LPCREATESTRUCT)lParam);
	case WM_DESTROY:				//----- ウィンドウ破棄指示がきた
		PostQuitMessage(0);				// システムにスレッドの終了を要求
		return 0;
	case WM_KEYDOWN:				//----- キーボードが押された
		switch (wParam) {
		case VK_ESCAPE:					// [ESC]キーが押された
			PostMessage(hWnd, WM_CLOSE, 0, 0);	// [x]が押されたように振舞う
			return 0;
		}
		break;
	case WM_MENUCHAR:
		return MNC_CLOSE << 16;			// [Alt]+[Enter]時のBEEPを抑止
	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//=============================================================================
// WM_CREATEメッセージハンドラ
//=============================================================================
int OnCreate(HWND hWnd, LPCREATESTRUCT lpcs)
{
	// クライアント領域サイズをSCREEN_WIDTH×SCREEN_HEIGHTに再設定.
	RECT rcClnt;
	GetClientRect(hWnd, &rcClnt);
	rcClnt.right -= rcClnt.left;
	rcClnt.bottom -= rcClnt.top;
	if (rcClnt.right != SCREEN_WIDTH || rcClnt.bottom != SCREEN_HEIGHT) {
		RECT rcWnd;
		GetWindowRect(hWnd, &rcWnd);
		SIZE sizeWnd;
		sizeWnd.cx = (rcWnd.right - rcWnd.left) - rcClnt.right + SCREEN_WIDTH;
		sizeWnd.cy = (rcWnd.bottom - rcWnd.top) - rcClnt.bottom + SCREEN_HEIGHT;
		SetWindowPos(hWnd, nullptr, 0, 0, sizeWnd.cx, sizeWnd.cy, SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER);
	}

	// IME無効化
	ImmAssociateContext(hWnd, nullptr);

	return 0;	// -1を返すとCreateWindow(Ex)が失敗する.
}


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Init(HWND hWnd, BOOL bWindow)
{
	HRESULT hr = S_OK;;

	// 乱数
	srand(time(NULL));

	// DirectX11の初期化
	hr = CDirectX11::Create(hWnd);
	// エラー処理
	if (FAILED(hr)) return hr;

	// 入力処理初期化
	hr = InitInput();
	// エラー処理
	if (FAILED(hr)) return hr;

	// サウンドの初期化
	hr = CSound::InitSound();
	// エラー処理
	if (FAILED(hr)) return hr;

	// スプライトの初期化
	CSprite::Init();

	// シーンの初期化
	//hr = CSceneManager::Init();
	CSceneManager::Init();
	// エラー処理
	if (FAILED(hr)) return hr;

	// FPS表示フレーム
	/*char szFPS[30];
	std::sprintf(szFPS, "FPS = %d", g_nCountFPS);
	g_pString = STRING::CString::Create(szFPS, Float3{ -SCREEN_CENTER_X, -SCREEN_CENTER_Y / 3 * 1.5f, 0 }, Float2{ 50, 50 }, Float4{ 0,1,0,1 });
	g_pString->SetLayer(LAYER::MAX_LAYER);*/

	return hr;
}


//=============================================================================
// 終了処理
//=============================================================================
void Uninit(void)
{
	
	// シーンの終了処理
	CSceneManager::Uninit();

	// サウンドの終了処理
	CSound::UninitSound();

	// 入力終了処理
	UninitInput();

	// Direct11の終了処理
	CDirectX11::Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void Update(void)
{
	// TODO: ここに更新処理を記述.

	// 入力更新処理
	UpdateInput();

	// シーンの更新処理
	CSceneManager::Update();

	//// FPS表示
	//char szFPS[20];
	//std::sprintf(szFPS, "FPS = %d", g_nCountFPS);
	//g_pString->SetWord(szFPS);

	// デバッグ表示
#ifdef _WIN32
	if (GetKeyTrigger(VK_O))
		g_bDebug ^= 1;
#endif // _WIN32

}


//=============================================================================
// 描画処理
//=============================================================================
void Draw(void)
{
	// DirectX11の描画開始処理
	CDirectX11::StartRender();

	// ============ TODO: ここに描画処理を記述.================

	// シーンの描画処理
	CSceneManager::Draw();
	//FPS
	/*if (g_pString)
	{
		g_pString->Destroy();
		g_pString = nullptr;
	}*/


	// ========================================================

	// DirectX11の描画終了処理
	CDirectX11::EndRender();
}


//=============================================================================
//	ウィンドウハンドル
//=============================================================================
HWND GetMainWnd()
{
	return g_hWnd;
}


//=============================================================================
//	デバッグ表示フラグ
//=============================================================================
bool GetDebugFlag()
{
	return g_bDebug;
}

//=============================================================================
//	デバッグ表示フラグ
//=============================================================================
void SetDebugFlag(bool bFlag)
{
	g_bDebug = bFlag;
}
