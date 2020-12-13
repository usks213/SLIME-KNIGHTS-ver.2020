//=============================================================================
//
// DirectX11初期化 [sample.cpp]
// Author : KOSHI USAMI
//
//=============================================================================
//
//	開発履歴
//
//	2020/05/30	DirectX11の初期化
//
//=============================================================================

//===== インクルード部 =====
#include "DirectX11.h"
#include "polygon.h"


//===== グローバル変数 =====

ID3D11Device*			CDirectX11::m_pDevice;				// デバイス
ID3D11DeviceContext*	CDirectX11::m_pDeviceContext;		// デバイスコンテキスト
IDXGISwapChain*			CDirectX11::m_pSwapChain;			// スワップチェーン
ID3D11RenderTargetView*	CDirectX11::m_pRenderTargetView;	// レンダーターゲットビュー(レンダリングパイプラインからアウトプットされるピクセル情報)
ID3D11Texture2D*		CDirectX11::m_pDepthStencilTexture;	// 深度/ステンシルバッファ
ID3D11DepthStencilView*	CDirectX11::m_pDepthStencilView;	// 深度/ステンシルビュー
D3D11_VIEWPORT			CDirectX11::m_Viewport;				// ビューポート
ID3D11BlendState*		CDirectX11::m_pBlendState[MAX_BLENDSTATE];			// ブレンド ステート


//=============================
// コンストラクタ
//=============================
CDirectX11::CDirectX11()
{
	// メソッドの初期化
	m_pDevice = NULL;
	m_pDeviceContext = NULL;
	m_pSwapChain = NULL;
	m_pRenderTargetView = NULL;

	m_pDepthStencilTexture = NULL;	// 深度/ステンシルバッファ
	m_pDepthStencilView = NULL;		// 深度/ステンシルビュー
}


//=============================
// デストラクタ
//=============================
CDirectX11::~CDirectX11()
{
	// 終了処理
	Release();
}


//=========================================
//	DirectX 初期化関数
//=========================================
HRESULT CDirectX11::Create(HWND hwnd)
{
	HRESULT hr;

	// 有効にランタイムレイヤー
	UINT flags = 0;
#ifdef _DEBUG
	flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif // _DEBUG
	
	// 機能レベルを配列で指定
	D3D_FEATURE_LEVEL pFeatureLevel[] = { D3D_FEATURE_LEVEL_11_1, D3D_FEATURE_LEVEL_11_0, };
	// 作成されたデバイスの機能レベルを受け取る変数
	D3D_FEATURE_LEVEL featureLevel;

	// クライアント領域のサイズを計算するため (レクタングル)
	//CRect rect;
	// スワップチェーンの生成
	DXGI_SWAP_CHAIN_DESC scDesc;

	// クライアント領域を取得
	//::GetClientRect(hwnd, &rect);

	// スワップチェーンの初期化
	ZeroMemory(&scDesc, sizeof(scDesc));
	scDesc.BufferCount			= 1;				// スワップチェーンのバッファ数
	scDesc.BufferDesc.Width		= SCREEN_WIDTH;		// スワップチェーンのバッファサイズ(横幅)
	scDesc.BufferDesc.Height	= SCREEN_HEIGHT;	// スワップチェーンのバッファサイズ(縦幅)
	scDesc.BufferDesc.Format	= DXGI_FORMAT_R8G8B8A8_UNORM;			// スワップチェーンのバッファフォーマット
	scDesc.BufferDesc.RefreshRate.Numerator	  = 60;						// リフレッシュレートの分母
	scDesc.BufferDesc.RefreshRate.Denominator =  1;						// リフレッシュレートの分子
	scDesc.BufferUsage			= DXGI_USAGE_RENDER_TARGET_OUTPUT;		// バッファをレンダーターゲットとして使用
	scDesc.OutputWindow			= hwnd;				// ウィンドウハンドル
	scDesc.SampleDesc.Count		= 1;				// マルチサンプリングのピクセル単位の数
	scDesc.SampleDesc.Quality	= 0;				// マルチサンプリングの品質
	scDesc.Windowed				= TRUE;				// ウィンドウモード

	// デバイスとスワップチェーンの生成、初期化
	hr = D3D11CreateDeviceAndSwapChain(
		NULL,						// アダプターのポインタ。NULLだと規定のアダプタ
		D3D_DRIVER_TYPE_HARDWARE,	// ハードウェアを使うD3D_DRIVER_TYPE_HARDWAREを指定
		NULL,						// DeviceTypeがハードウェアの場合はNULL
		flags,						// 有効にするランタイムレイヤー
		pFeatureLevel,				// 作成を試しみる機能レベルの順序を指定する配列
		_countof(pFeatureLevel),	// 作成を試しみる機能レベルの順序を指定する配列の数(長さ)
		D3D11_SDK_VERSION,			// D3D11_SDK_VERSIONを指定
		&scDesc,					// スワップチェーンの初期化パラメーター
		&m_pSwapChain,				// 作成されるスワップチェーン
		&m_pDevice,					// 作成されるデバイス
		&featureLevel,				// 作成されるデバイスの機能レベル
		&m_pDeviceContext			// 作成されるデバイスコンテキスト
	);
	// エラー処理
	if (FAILED(hr)) return hr;


	// バックバッファの生成
	// バックバッファのポインタ
	ID3D11Texture2D* pBackBuffer;

	// スワップチェーンのバッファの１つを取得(描画用のメモリ確保)
	hr = m_pSwapChain->GetBuffer(
		0,							// バッファのインデックス(基本は0)						
		__uuidof(ID3D11Texture2D),	// 取得するバッファのインターフェースID
		(LPVOID*)&pBackBuffer		// バッファの取得先
	);
	// エラー処理
	if (FAILED(hr)) return hr;

	// レンダーターゲットビューの生成
	hr = m_pDevice->CreateRenderTargetView(
		pBackBuffer,			// 作成するバッファのリソース
		NULL,					// 作成するViewの設定内容データの指定(NULLでデフォルト設定)
		&m_pRenderTargetView);	// 作成されたRenderTargetViewの格納先
	// エラー処理
	if (FAILED(hr)) return hr;

	// Targetの取得が終わったのでテクスチャリソース(バックバッファ)の解放
	pBackBuffer->Release();		
	


	// 深度ステンシルバッファ用のテクスチャリソースを作成
	D3D11_TEXTURE2D_DESC txDesc;
	// 深度ステンシルバッファの初期化
	ZeroMemory(&txDesc, sizeof(txDesc));
	txDesc.Width				= SCREEN_WIDTH;		// バックバッファと同じサイズを指定(バッファの横幅)
	txDesc.Height				= SCREEN_HEIGHT;	// バックバッファと同じサイズを指定(バッファの縦幅)
	txDesc.MipLevels			= 1;				// ミップマップのレベル指定
	txDesc.ArraySize			= 1;				// テクスチャ配列のサイズ指定
	txDesc.Format				= DXGI_FORMAT_D24_UNORM_S8_UINT;	// テクスチャのフォーマット(DXGI_FORMAT_D24_UNORM_S8_UINT)を使うとDepth24bit Stencil8bit
	txDesc.SampleDesc.Count		= 1;				// マルチサンプリングのピクセル単位の数(DepthStencilバッファでは使わない)
	txDesc.SampleDesc.Quality	= 0;				// マルチサンプリングの品質(DepthStencilバッファでは使わない)
	txDesc.Usage				= D3D11_USAGE_DEFAULT;				// テクスチャの使用方法(デフォルト)
	txDesc.BindFlags			= D3D11_BIND_DEPTH_STENCIL;			// Bind設定はDepth,Stencilに設定
	txDesc.CPUAccessFlags		= 0;				// リソースへのCPUのアクセス権限についての設定 (デフォルトは0？)
	txDesc.MiscFlags			= 0;				// リソースオプションのフラグ(デフォルトは0？)

	// Texture_Descの情報でテクスチャを作成
	hr = m_pDevice->CreateTexture2D(
		&txDesc,					// 作成するテクスチャの詳細情報
		NULL,						// テクスチャの情報に付加するデータ指定(読み込んだ画像データを指定したり)
		&m_pDepthStencilTexture);	// 作成されたTextureデータを格納するためのポインタ
	// エラー処理
	if (FAILED(hr)) return hr;

	// 深度ステンシルビューの作成
	D3D11_DEPTH_STENCIL_VIEW_DESC dsDesc;
	// 深度ステンシルビューの初期化
	ZeroMemory(&dsDesc, sizeof(dsDesc));
	dsDesc.Format = txDesc.Format;							// Viewのフォーマット(Textureのものを使用)
	dsDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;	// DSVが何次元であるとTextureの種類を設定する値
	dsDesc.Texture2D.MipSlice = 0;							// 最初に使用するミップマップのレベルを指定

	// CreateTexture2DとDsv_DescからDepthとStencilバッファを作る
	//hr = m_pDevice->CreateDepthStencilView(
	//	m_pDepthStencilTexture,		// DSVとして使用されるTexture
	//	&dsDesc,					// DSVの設定
	//	&m_pDepthStencilView);		// ID3D11DepthStencilViewの出力先
	//// エラー処理
	//if (FAILED(hr)) return hr;

	// 各ターゲットビューをレンダーターゲットに設定
	m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);


	//ビューポート設定
	m_Viewport.TopLeftX = 0;
	m_Viewport.TopLeftY = 0;
	m_Viewport.Width = (FLOAT)SCREEN_WIDTH;
	m_Viewport.Height = (FLOAT)SCREEN_HEIGHT;
	m_Viewport.MinDepth = 0.0f;
	m_Viewport.MaxDepth = 1.0f;

	// ビューポートをセット
	m_pDeviceContext->RSSetViewports(1, &m_Viewport);


	// ラスタライズ設定
	D3D11_RASTERIZER_DESC rd;
	ZeroMemory(&rd, sizeof(rd));
	rd.CullMode = D3D11_CULL_NONE;	// カリングを行わない
	rd.FillMode = D3D11_FILL_SOLID;	// ポリゴンを塗りつぶす
	ID3D11RasterizerState* pRs = nullptr;
	m_pDevice->CreateRasterizerState(&rd, &pRs);
	m_pDeviceContext->RSSetState(pRs);
	SAFE_RELEASE(pRs);
	// ブレンド ステート生成
	D3D11_BLEND_DESC BlendDesc;
	ZeroMemory(&BlendDesc, sizeof(BlendDesc));
	BlendDesc.AlphaToCoverageEnable = FALSE;
	BlendDesc.IndependentBlendEnable = FALSE;
	BlendDesc.RenderTarget[0].BlendEnable = FALSE;
	BlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	BlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	BlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	BlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	BlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	// 半透明合成なし
	m_pDevice->CreateBlendState(&BlendDesc, &m_pBlendState[0]);
	// 半透明合成
	BlendDesc.RenderTarget[0].BlendEnable = TRUE;
	m_pDevice->CreateBlendState(&BlendDesc, &m_pBlendState[1]);
	// 加算合成
	BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	m_pDevice->CreateBlendState(&BlendDesc, &m_pBlendState[2]);
	// 減算合成
	BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_REV_SUBTRACT;
	m_pDevice->CreateBlendState(&BlendDesc, &m_pBlendState[3]);

	// ブレンドステイトのセット
	SetBlendState(BS_ALPHABLEND);

	return hr;
}


//=============================
// DirectX 終了関数
//=============================
void CDirectX11::Release()
{
	//===== 各リソースの終了処理 =====

	// デバイスコンテキストのクリア
	if (m_pDeviceContext)	m_pDeviceContext->ClearState();

	// 深度ステンシルバッファビューの解放
	if (NULL != m_pDepthStencilView)
	{
		m_pDepthStencilView->Release();
		m_pDepthStencilView = NULL;
	}

	// 深度ステンシルバッファの解放
	if (NULL != m_pDepthStencilTexture)
	{
		m_pDepthStencilTexture->Release();
		m_pDepthStencilTexture = NULL;
	}

	// レンダーターゲットビューの解放
	if (NULL != m_pRenderTargetView)
	{
		m_pRenderTargetView->Release();
		m_pRenderTargetView = NULL;
	}

	// スワップチェーンの解放
	if (NULL != m_pSwapChain)
	{
		m_pSwapChain->Release();
		m_pSwapChain = NULL;
	}

	// デバイスコンテキストの解放
	if (NULL != m_pDeviceContext)
	{
		m_pDeviceContext->Release();
		m_pDeviceContext = NULL;
	}

	// デバイスの解放
	if (NULL != m_pDevice)
	{
		m_pDevice->Release();
		m_pDevice = NULL;
	}
}


//===========================
//	DirectX 描画開始関数
//===========================
void CDirectX11::StartRender()
{
	// 安全処理
	if (NULL == m_pDevice) return;
	if (NULL == m_pDeviceContext) return;
	if (NULL == m_pRenderTargetView) return;

	// バックバッファをクリアする色
	float clearColor[4] = { 0.117647f, 0.254902f, 0.352941f, 1.0f };
	// バックバッファのクリア
	m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetView, clearColor);
	// 深度ステンシルバッファのクリア
	//m_pDeviceContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	// ============ TODO: ここに描画処理を記述.================
	
	//g_polygon.Draw(m_pDeviceContext, &g_shader);

	// ========================================================
}

//===========================
//	DirectX 描画開始関数
//===========================
void CDirectX11::EndRender()
{
	// 安全処理
	if (NULL == m_pSwapChain) return;

	// バックバッファとフロントバッファの入れ替え
	m_pSwapChain->Present(1, 0);
}

//=======================================
//
//	ブレンドステイトのセット
//
//=======================================
void CDirectX11::SetBlendState(int nBlendState)
{
	if (nBlendState >= 0 && nBlendState < MAX_BLENDSTATE)
	{
		float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
		m_pDeviceContext->OMSetBlendState(m_pBlendState[nBlendState], blendFactor, 0xffffffff);
	}
}