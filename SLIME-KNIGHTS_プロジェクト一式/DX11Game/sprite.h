//==============================================
//								sprite.h
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
//	2020/06/12	�l�p�`�`��֐��ɉ�]��ǉ�
//
//	2020/06/25	���_�Ŏl�p�`�`��֐�
//	
//	2020/07/22	�X�v���C�g�N���X�̍쐬
//
//===============================================

#pragma once

//====== �C���N���[�h�� ======
#include "main.h"
#include "texture.h"
#include "source/transform.h"
#include "shader.h"
#include "model.h"
#include "polygon.h"

//===== �\���̒�` =====
// ���_���
struct VERTEX_3D
{
	Float3 Position;	// ���W x, y, z
	Float4 Color;		// �F   r, g, b, a
	Float2 TexCoord;	// �e�N�X�`�����
};

class CSprite
{
public:
	CSprite();
	~CSprite();

	static void Init();
	void Draw(CTransform* pTrans, CTexture *pTexture = nullptr);
	void Draw(CTransform *pTrans, CTexture *pTexture, bool bCamera);

	// �Z�b�g�֐�
	void SetTexPos(Float2 texPos) { m_posTexCoord = texPos; }
	void SetTexSize(Float2 texSize) { m_sizeTexCoord = texSize; }
	void SetColor(Float4 color) { m_color = color; }
	void SetColorW(float w) { m_color.w = w; }
	//void SetTexture(CTexture *pTexture) { m_pTexture = pTexture; }

	// �Q�b�g�֐�
	Float2 GetTexPos() { return m_posTexCoord; }
	Float2 GetTexSize() { return m_sizeTexCoord; }
	Float4 GetColor() { return m_color; }

private:
	Float2 m_posTexCoord;		// �e�N�X�`�����W(����)0.0�`1.0
	Float2 m_sizeTexCoord;		// �e�N�X�`���T�C�Y(�E��)0.0�`1.0
	Float4 m_color;				// ���_�J���[

	// DirectX�`��f�[�^
	static CModel m_model;
	static CShader m_shader;
	static CPolygon m_polygon;
	static CTexture m_defaultTexture;
};
