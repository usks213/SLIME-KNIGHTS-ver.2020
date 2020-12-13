//=============================================================================
//
// DirectX11初期化 [polygon.cpp]
// Author : KOSHI USAMI
//
//=============================================================================
//
//	開発履歴
//
//	2020/05/31	ポリゴン描画の作成
//	2020/06/01	3D対応
//	2020/06/02	ライティング実装
//	2020/06/04	テクスチャ実装
//
//=============================================================================


//===== インクルード部 =====
#include "polygon.h"
#include "texture.h"
#include "model.h"
#include "input.h"
#include "source/camera.h"
#include "sprite.h"


//===== マクロ定義 =====

//===== 構造体 =====

// 定数バッファ (変換行列)
struct ConstantMatrixBuffer
{
	DirectX::XMFLOAT4X4 mWorld;			// ワールド変換行列
	DirectX::XMFLOAT4X4 mView;			// ビュー変換行列
	DirectX::XMFLOAT4X4 mProjection;	// プロジェクション変換行列
	DirectX::XMFLOAT4X4 mTexture;		// UV座標変換行列
};

// 定数バッファ(カラー)
struct ConstantColor
{
	Float4 color;
};

// 入力レイアウト
D3D11_INPUT_ELEMENT_DESC g_VertexDesc[] = {
	{
		"POSITION",						// セマンティック名
		0,								// セマンティック番号
		DXGI_FORMAT_R32G32B32_FLOAT,	// フォーマット
		0,								// 入力スロット番号
		0,								// 要素から先頭までのオフセット値
		D3D11_INPUT_PER_VERTEX_DATA	,	// 入力データの種類
		0,								// 繰り返し回数(頂点データの時は0)
	},
	{
		"NORMAL",						// セマンティック名
		0,								// セマンティック番号
		DXGI_FORMAT_R32G32B32_FLOAT,	// フォーマット
		0,								// 入力スロット番号
		D3D11_APPEND_ALIGNED_ELEMENT,	// 要素から先頭までのオフセット値(自動で計算してくれる)
		D3D11_INPUT_PER_VERTEX_DATA	,	// 入力データの種類
		0,								// 繰り返し回数(頂点データの時は0)
	},
	{
		"TEXCOORD",						// セマンティック名
		0,								// セマンティック番号
		DXGI_FORMAT_R32G32_FLOAT,		// フォーマット
		0,								// 入力スロット番号
		D3D11_APPEND_ALIGNED_ELEMENT,	// 要素から先頭までのオフセット値(自動で計算してくれる)
		D3D11_INPUT_PER_VERTEX_DATA	,	// 入力データの種類
		0,								// 繰り返し回数(頂点データの時は0)
	},
	{
		"COLOR",						// セマンティック名
		0,								// セマンティック番号
		DXGI_FORMAT_R32G32B32A32_FLOAT,	// フォーマット
		0,								// 入力スロット番号
		D3D11_APPEND_ALIGNED_ELEMENT,	// 要素から先頭までのオフセット値(自動で計算してくれる)
		D3D11_INPUT_PER_VERTEX_DATA	,	// 入力データの種類
		0,								// 繰り返し回数(頂点データの時は0)
	},
};


//==========================
//	コンストラクタ
//==========================
CPolygon::CPolygon()
{
	// 頂点バッファの初期化
	m_pVertexBuffer	 = NULL;

	// インデックスバッファの初期化
	m_pIndexBuffer	 = NULL;

	// コンスタントバッファ(行列座標変換)の初期化
	m_pConstantMatrixBuffer = NULL;	

	// コンスタントバッファ(カラー)の初期化
	m_pConstantColorBuffer = NULL;

	// 入力レイアウトの初期化
	m_pInputLayout	 = NULL;

	// 外部データ
	m_pModel = nullptr;
	m_pShader = nullptr;

}


//==========================
//	デストラクタ
//==========================
CPolygon::~CPolygon()
{
	// 頂点バッファの解放
	if (NULL != m_pVertexBuffer)
	{
		m_pVertexBuffer->Release();
		m_pVertexBuffer = nullptr;
	}

	// インデックスバッファの解放
	if (NULL != m_pIndexBuffer)
	{
		m_pIndexBuffer->Release();
		m_pIndexBuffer = nullptr;
	}

	// コンスタントバッファ(行列座標変換)の解放
	if (NULL != m_pConstantMatrixBuffer)
	{
		m_pConstantMatrixBuffer->Release();
		m_pConstantMatrixBuffer = nullptr;
	}

	// コンスタントバッファ(カラー)の解放
	if (NULL != m_pConstantColorBuffer)
	{
		m_pConstantColorBuffer->Release();
		m_pConstantColorBuffer = nullptr;
	}

	// 入力レイアウトの解放
	if (NULL != m_pInputLayout)
	{
		m_pInputLayout->Release();
		m_pInputLayout = nullptr;
	}

	// サンプラーの解放
	if (NULL != m_pSampler)
	{
		m_pSampler->Release();
		m_pSampler = nullptr;
	}
}


//================================
//	ポリゴン生成
//================================
HRESULT CPolygon::Create(ID3D11Device *pDevice, CModel *pModel, CShader *pShader)
{
	// 判定用
	HRESULT hr;

	// ===== 頂点バッファの作成 =====
	// 頂点バッファとして作成するための情報設定
	D3D11_BUFFER_DESC vbDesc;
	ZeroMemory(&vbDesc, sizeof(vbDesc));
	//vbDesc.ByteWidth			= sizeof(g_VertexList);		// バッファのサイズ(頂点数)
	vbDesc.ByteWidth			 = sizeof(Vertex) * pModel->GetVertexCount();		// バッファのサイズ(頂点数)
	vbDesc.Usage				= D3D11_USAGE_DEFAULT;		// 使用方法(アクセス許可)
	vbDesc.BindFlags			= D3D11_BIND_VERTEX_BUFFER;	// バッファの種類(頂点バッファ)
	vbDesc.CPUAccessFlags		= 0;						// CPUアクセス設定(0でアクセス不要)
	vbDesc.MiscFlags			= 0;						// その他のオプション(0で不要)
	vbDesc.StructureByteStride	= sizeof(Vertex);			// 構造体のサイズ

	// 頂点バッファの初期値設定
	D3D11_SUBRESOURCE_DATA vrData;
	ZeroMemory(&vrData, sizeof(vrData));
	// バッファの初期値設定
	//vrData.pSysMem			= g_VertexList;		// バッファを初期化するデータ(配列の先頭アドレス)
	vrData.pSysMem			= pModel->GetVertexList();		// バッファを初期化するデータ(配列の先頭アドレス)
	// 頂点バッファでは使用しない
	vrData.SysMemPitch		= 0;				// メモリのピッチ(テクスチャで使用する)
	vrData.SysMemSlicePitch = 0;				// 深度レベル(テクスチャで使用する)

	// 頂点バッファの作成
	hr = pDevice->CreateBuffer(
		&vbDesc,			// 作成するバッファ情報
		&vrData,			// 作成するバッファの初期化情報
		&m_pVertexBuffer);	// 作成したバッファを保存するポインタ
	// エラー処理
	if (FAILED(hr)) return hr;


	//===== インデックスバッファの作成 =====
	// インデックスバッファとして作成するための情報設定
	D3D11_BUFFER_DESC ibDesc;
	ZeroMemory(&ibDesc, sizeof(ibDesc));
	ibDesc.ByteWidth			= sizeof(WORD) * pModel->GetIndexCount();		// バッファのサイズ(インデックス数)
	//ibDesc.ByteWidth			= sizeof(g_IndexList);		// バッファのサイズ(インデックス数)
	ibDesc.Usage				= D3D11_USAGE_DEFAULT;		// 使用方法(アクセス許可)
	ibDesc.BindFlags			= D3D11_BIND_INDEX_BUFFER;	// バッファの種類(インデックスバッファ)
	ibDesc.CPUAccessFlags		= 0;						// CPUアクセス設定(0でアクセス不要)
	ibDesc.MiscFlags			= 0;						// その他のオプション(0で不要)
	ibDesc.StructureByteStride	= 0;						// 構造体ではないので0

	// インデックスバッファの初期値設定
	D3D11_SUBRESOURCE_DATA irDesc;
	ZeroMemory(&irDesc, sizeof(irDesc));
	// バッファの初期値設定
	irDesc.pSysMem			= pModel->GetIndexList();	// バッファを初期化するデータ(配列の先頭アドレス)
	//irDesc.pSysMem			= g_IndexList;	// バッファを初期化するデータ(配列の先頭アドレス)
	// インデックスバッファでは使用しない
	irDesc.SysMemPitch		= 0;			// メモリのピッチ(テクスチャで使用する)
	irDesc.SysMemSlicePitch = 0;			// 深度レベル(テクスチャで使用する)

	// インデックスバッファの作成
	hr = pDevice->CreateBuffer(
		&ibDesc,			// 作成するバッファ情報
		&irDesc,			// 作成するバッファの初期化情報
		&m_pIndexBuffer);	// 作成したバッファを保存するポインタ
	// エラー処理
	if (FAILED(hr)) return hr;


	//===== コンスタントマトリックスバッファの作成 =====
	// コンスタントバッファとして作成するための情報設定
	D3D11_BUFFER_DESC cbDesc;
	cbDesc.ByteWidth			= sizeof(ConstantMatrixBuffer);	// バッファサイズ(変換行列の数)
	cbDesc.Usage				= D3D11_USAGE_DEFAULT;			// 使用方法(アクセス許可)
	cbDesc.BindFlags			= D3D11_BIND_CONSTANT_BUFFER;	// バッファの種類(コンスタントバッファ)
	cbDesc.CPUAccessFlags		= 0;							// CPUアクセス設定(0でアクセス不要)
	cbDesc.MiscFlags			= 0;							// その他のオプション(0で不要)
	cbDesc.StructureByteStride	= 0;							// 構造体サイズ(行列を使うが今回は0でも動作することを実証する)
	// コンスタントバッファの作成
	hr = pDevice->CreateBuffer(&cbDesc, NULL, &m_pConstantMatrixBuffer);
	// エラー処理
	if (FAILED(hr)) return hr;

	cbDesc.ByteWidth			= sizeof(ConstantColor);		// バッファサイズ(数)
	cbDesc.Usage				= D3D11_USAGE_DEFAULT;			// 使用方法(アクセス許可)
	cbDesc.BindFlags			= D3D11_BIND_CONSTANT_BUFFER;	// バッファの種類(コンスタントバッファ)
	cbDesc.CPUAccessFlags		= 0;							// CPUアクセス設定(0でアクセス不要)
	cbDesc.MiscFlags			= 0;							// その他のオプション(0で不要)
	cbDesc.StructureByteStride	= 0;							// 構造体サイズ(行列を使うが今回は0でも動作することを実証する)
	// コンスタントバッファの作成
	hr = pDevice->CreateBuffer(&cbDesc, NULL, &m_pConstantColorBuffer);
	// エラー処理
	if (FAILED(hr)) return hr;

	//===== レイアウトの作成 =====
	// 入力レイアウトの作成
	hr = pDevice->CreateInputLayout(
		g_VertexDesc,					// 入力レイアウトの構成
		_countof(g_VertexDesc),			// 構成の要素数
		pShader->GetVertexShaderData(),	// 頂点シェーダーのデータ
		pShader->GetVertexShaderSize(),	// 頂点シェーダーのサイズ
		&m_pInputLayout);				// 作成した入力レイアウトの保存先
	// エラー処理
	if (FAILED(hr)) return hr;

	
	//===== サンプラーの作成 =====
	// サンプラーの情報設定
	D3D11_SAMPLER_DESC smpDesc;
	ZeroMemory(&smpDesc, sizeof(D3D11_SAMPLER_DESC));
	//smpDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;		// ボケる方、線形補間
	//smpDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;		// ボケない、ニアレストネイバー
	//smpDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;		// UV座標がループするかしないか
	//smpDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	//smpDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	smpDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	smpDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	smpDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	smpDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	// サンプラー作成
	hr = pDevice->CreateSamplerState(&smpDesc, &m_pSampler);
	// エラー処理
	if (FAILED(hr)) return hr;

	// ポインタの格納
	m_pModel = pModel;
	m_pShader = pShader;

	return hr;
}


//==============================
//	ポリゴンの描画
//==============================
void CPolygon::Draw(ID3D11DeviceContext *pDeviceContext, CTransform *pTrans, CTexture *pTexture, CSprite *pSpr, bool bCamera)
{
	// 使う頂点シェーダーを指定
	pDeviceContext->VSSetShader(
		m_pShader->GetVertexShader(),	// 設定する頂点シェーダー
		NULL,						// ID3D11ClassInstanceのポインタの配列
		0);							// 配列の要素数

	// 使うピクセルシェーダーを指定
	pDeviceContext->PSSetShader(
		m_pShader->GetPixelShader(),	// 設定するピクセルシェーダー
		NULL,						// ID3D11ClassInstanceのポインタの配列
		0);							// 配列の要素数

	// 頂点バッファ
	UINT stride = sizeof(Vertex);	// 1頂点のサイズの配列
	UINT offset = 0;				// 頂点バッファの開始位置をずらすオフセットの配列
	// 頂点バッファを指定
	pDeviceContext->IASetVertexBuffers(
		0,					// 入力スロットの開始番号
		1,					// 頂点バッファの数
		&m_pVertexBuffer,	// 頂点バッファの配列
		&stride,			// 1頂点のサイズの配列
		&offset);			// 頂点バッファの開始位置をずらすオフセットの配列
	
	// インデックスバッファを指定
	pDeviceContext->IASetIndexBuffer(
		m_pIndexBuffer,			// 設定するインデックスバッファ
		DXGI_FORMAT_R16_UINT,	// インデックスのサイズフォーマット(WORD型)
		0);						// バッファの開始オフセット

	// 入力レイアウトを指定
	pDeviceContext->IASetInputLayout(m_pInputLayout);	// 設定する入力レイアウト

	// テクスチャの指定
	if (pTexture != nullptr && pTexture->m_pTextureResourceView != nullptr)
	{
		pDeviceContext->PSSetShaderResources(0, 1, &pTexture->m_pTextureResourceView);
		pDeviceContext->PSSetSamplers(0, 1, &m_pSampler);
	}

	// ワールドマトリクス設定 (変換行列の積)
	DirectX::XMMATRIX worldMatrix;
	// 拡縮
	if (bCamera)
	{
		worldMatrix = DirectX::XMMatrixScaling(pTrans->GetSize().x  * CCamera::GetScale(),
			pTrans->GetSize().y  * CCamera::GetScale(), 1.0f);
	}
	else
	{
		worldMatrix = DirectX::XMMatrixScaling(pTrans->GetSize().x,
			pTrans->GetSize().y, 1.0f);
	}
	// 回転
	worldMatrix *= DirectX::XMMatrixRotationRollPitchYaw(AngleToRadian(180.0f), 0.0f, AngleToRadian(pTrans->GetAngle()));
	//worldMatrix *= DirectX::XMMatrixRotationRollPitchYaw(trans.rot.x, trans.rot.y, trans.rot.z);
	// 移動
	Float3 CameraPos = CCamera::GetCameraPos();
	if (bCamera)
	{
		// カメラ座標
		worldMatrix *= DirectX::XMMatrixTranslation((pTrans->GetPos().x - CameraPos.x) * CCamera::GetScale() + SCREEN_CENTER_X,
			(pTrans->GetPos().y - CameraPos.y)  * CCamera::GetScale() + SCREEN_CENTER_Y,
			pTrans->GetPos().z);
	}
	else
	{
		worldMatrix *= DirectX::XMMatrixTranslation(pTrans->GetPos().x + SCREEN_CENTER_X,
			pTrans->GetPos().y + SCREEN_CENTER_Y, pTrans->GetPos().z);
	}

	// ビューマトリックスの設定
	//XMMATRIX viewMatrix = XMMatrixLookAtLH(CCamera::GetEyePos(), CCamera::GetFocusPos(), CCamera::GetUpVec());	// 上の情報をもとにビュー変換行列を設定

	// カメラ行列
	DirectX::XMMATRIX viewMatrix =
		DirectX::XMMatrixOrthographicOffCenterLH(0, static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT), 0, -1, 1);


	// プロジェクションマトリックスの設定
	float	 fov		= XMConvertToRadians(70.0f);							// 視野角
	float	 aspect		= (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;			// スクリーンのアスペクト比
	float	 nearZ		= 0.1f;													// クリッピングの最短距離
	float	 farZ		= 10000.0f;												// クリッピングの最長距離
	XMMATRIX projMatrix = XMMatrixPerspectiveFovLH(fov, aspect, nearZ, farZ);	// 上の情報をもとにプロジェクション変換行列を設定
	
	// テクスチャマトリックスの設定
	// 拡縮
	XMMATRIX texMatrix = XMMatrixScaling(pSpr->GetTexSize().x, pSpr->GetTexSize().y, 0.0f);
	// 移動
	texMatrix *= XMMatrixTranslation(pSpr->GetTexPos().x, pSpr->GetTexPos().y, 0.0f);

	// 更新するコンスタントマトリックスバッファの作成
	ConstantMatrixBuffer cmb;
	XMStoreFloat4x4(&cmb.mWorld, XMMatrixTranspose(worldMatrix));		// ワールドマトリックス
	XMStoreFloat4x4(&cmb.mView, XMMatrixTranspose(viewMatrix));			// ビューマトリックス
	XMStoreFloat4x4(&cmb.mProjection, XMMatrixTranspose(projMatrix));	// プロジェクションマトリックス
	XMStoreFloat4x4(&cmb.mTexture, XMMatrixTranspose(texMatrix));		// テクスチャマトリックス

	// コンスタントマトリックスバッファ更新
	pDeviceContext->UpdateSubresource(
		m_pConstantMatrixBuffer,	// 更新対象のバッファ
		0,					// インデックス(0)
		NULL,				// 更新範囲(nullptr)
		&cmb,				// 反映データ
		0,					// データの1行のサイズ(0)
		0);					// 1深度スライスのサイズ(0)

	// 頂点シェーダーのコンスタントバッファを設定
	pDeviceContext->VSSetConstantBuffers(
		0,						// バッファの開始番号
		1,						// バッファの数
		&m_pConstantMatrixBuffer);	// 設定するコンスタントバッファ

	// カラーコンスタントバッファ
	ConstantColor cc;
	cc.color = pSpr->GetColor();

	// コンスタントマトリックスバッファ更新
	pDeviceContext->UpdateSubresource(
		m_pConstantColorBuffer,	// 更新対象のバッファ
		0,					// インデックス(0)
		NULL,				// 更新範囲(nullptr)
		&cc,				// 反映データ
		0,					// データの1行のサイズ(0)
		0);					// 1深度スライスのサイズ(0)

	// ピクセルシェーダーのコンスタントバッファを設定
	pDeviceContext->PSSetConstantBuffers(
		0,						// バッファの開始番号
		1,						// バッファの数
		&m_pConstantColorBuffer);	// 設定するコンスタントバッファ

	// プリミティブの形状を指定
	pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);	// プリミティブの種類

	// インデックスバッファによる描画
	pDeviceContext->DrawIndexed(
		m_pModel->GetIndexCount(),			// 描画する頂点の数
		0,								// 描画で使う最初のインデックス番号
		0);								// 頂点バッファの最初の位置

	//pDeviceContext->Draw(3, 0);
}