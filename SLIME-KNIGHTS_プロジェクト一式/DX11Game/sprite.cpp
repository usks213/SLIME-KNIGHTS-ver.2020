//==============================================
//								sprite.cpp
//	GM21 �}�`�`��֘A
//
//==============================================
//	author :	AT12A 05 �F�����W�V
//==============================================
//	�J������
//
//	2020/05/22	�}�`�`��֐��̎���
//
//	2020/05/29	�l�p�`�`��֐��Ƀe�N�X�`������ǉ�
//
//	2020/07/22	�X�v���C�g�N���X�̍쐬
//
//
//===============================================

//===== �C���N���[�h�� =====
#include "sprite.h"
#include "source/camera.h"
#include "DirectX11.h"


//===== �ÓI�����o =====
CShader CSprite::m_shader;
CPolygon CSprite::m_polygon;
CModel CSprite::m_model;
CTexture CSprite::m_defaultTexture;


//========================================
//
//	�R���X�g���N�^
//
//========================================
CSprite::CSprite()
{
	// ������
	m_color = Float4{1.0f, 1.0f, 1.0f, 1.0f};
	m_posTexCoord = Float2{0.0f, 0.0f};
	m_sizeTexCoord = Float2{1.0f, 1.0f};

}

//========================================
//
//	�f�X�g���N�^
//
//========================================
CSprite::~CSprite()
{
	

}

//========================================
//
//	������
//
//========================================
void CSprite::Init()
{
	// �`��f�[�^
	m_model.CreatePlaneModel();	// �|��
	m_shader.LoadShader(CDirectX11::GetDevice(), "data/shader/VertexShader2D.cso", "data/shader/PixelShader2D.cso");
	m_polygon.Create(CDirectX11::GetDevice(), &m_model, &m_shader);
	m_defaultTexture.LoadTexture(FILE_PATH"fade.tga");
}


//========================================
//
//	�`�揈��
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
//	�`�揈��
//
//========================================
void CSprite::Draw(CTransform *pTrans, CTexture *pTexture, bool bCamera)
{
	if(pTexture && pTexture->m_pTextureResourceView)
		m_polygon.Draw(CDirectX11::GetDeviceContext(), pTrans, pTexture, this, bCamera);
	else
		m_polygon.Draw(CDirectX11::GetDeviceContext(), pTrans, &m_defaultTexture, this, bCamera);
}


