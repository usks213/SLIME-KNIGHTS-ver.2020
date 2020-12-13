//==============================================
//								sprite.cpp
//	GM21 図形描画関連
//
//==============================================
//	author :	AT12A 05 宇佐美晃之
//==============================================
//	開発履歴
//
//	2020/05/22	図形描画関数の実装
//
//	2020/05/29	四角形描画関数にテクスチャ情報を追加
//
//	2020/07/22	スプライトクラスの作成
//
//
//===============================================

//===== インクルード部 =====
#include "sprite.h"
#include "source/camera.h"
#include "DirectX11.h"


//===== 静的メンバ =====
CShader CSprite::m_shader;
CPolygon CSprite::m_polygon;
CModel CSprite::m_model;
CTexture CSprite::m_defaultTexture;


//========================================
//
//	コンストラクタ
//
//========================================
CSprite::CSprite()
{
	// 初期化
	m_color = Float4{1.0f, 1.0f, 1.0f, 1.0f};
	m_posTexCoord = Float2{0.0f, 0.0f};
	m_sizeTexCoord = Float2{1.0f, 1.0f};

}

//========================================
//
//	デストラクタ
//
//========================================
CSprite::~CSprite()
{
	

}

//========================================
//
//	初期化
//
//========================================
void CSprite::Init()
{
	// 描画データ
	m_model.CreatePlaneModel();	// 板ポリ
	m_shader.LoadShader(CDirectX11::GetDevice(), "data/shader/VertexShader2D.cso", "data/shader/PixelShader2D.cso");
	m_polygon.Create(CDirectX11::GetDevice(), &m_model, &m_shader);
	m_defaultTexture.LoadTexture(FILE_PATH"fade.tga");
}


//========================================
//
//	描画処理
//
//========================================
void CSprite::Draw(CTransform *pTrans, CTexture *pTexture)
{
	if(pTexture && pTexture->m_pTextureResourceView)
		m_polygon.Draw(CDirectX11::GetDeviceContext(), pTrans, pTexture, this);
	else
		m_polygon.Draw(CDirectX11::GetDeviceContext(), pTrans, &m_defaultTexture, this);
}

//========================================
//
//	描画処理
//
//========================================
void CSprite::Draw(CTransform *pTrans, CTexture *pTexture, bool bCamera)
{
	if(pTexture && pTexture->m_pTextureResourceView)
		m_polygon.Draw(CDirectX11::GetDeviceContext(), pTrans, pTexture, this, bCamera);
	else
		m_polygon.Draw(CDirectX11::GetDeviceContext(), pTrans, &m_defaultTexture, this, bCamera);
}


