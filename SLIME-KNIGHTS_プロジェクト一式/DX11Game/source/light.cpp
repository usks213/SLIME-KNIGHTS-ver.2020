//==================================================================
//								light.h
//	�}�b�v�̃��C�g	
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//	
//	2020/09/06	���C�g�N���X�̍쐬
//
//===================================================================


//====== �C���N���[�h�� ======
#include "light.h"

#include "collision.h"
#include "objectMgr.h"


#include "../texture.h"
#include "../sprite.h"

#ifdef _WIN64
#include "../DirectX11.h"

#endif // _WIN64

//===== �}�N����` =====



//===== ���O��� =====


CTexture CLight::sm_texture;
bool CLight::m_bBoss = false;


//========================================
//
//	�R���X�g���N�^
//
//========================================
CLight::CLight()
{
	// �R���W����
	m_pCollision = CCollision::Create(this, nullptr);

	// �|���S���̃p�����[�^�̏�����
	m_transform.SetSize(Float2{ 500, 500 });

	// �X�v���C�g�f�[�^
	m_sprite.SetColor(Float4{ 0.74f, 0.25f, 0.01f, 0.6f });
	if (m_bBoss)
	{
		m_sprite.SetColor(Float4{ 0.4f, 0.02f, 0.53f, 0.6f });
	}

	// ���C���[
	m_enLayer = LAYER::EFFECT;

	// �e
	m_pParent = nullptr;

}


//========================================
//
//	�f�X�g���N�^
//
//========================================
CLight::~CLight()
{
	// �R���W����
	m_pCollision->Destroy();
}

//========================================
//
//	������
//
//========================================
void CLight::Init()
{
	// �e�N�X�`���̃��[�h
	sm_texture.LoadTexture(FILE_PATH"object/light.tga");

}

//========================================
//
//	�I������
//
//========================================
void CLight::Uninit()
{
	// �e�N�X�`���̉��
	sm_texture.UnloadTexture();
}

//========================================
//
//	�X�V����
//
//========================================
void CLight::Update()
{
	
}

//========================================
//
//	�X�V����
//
//========================================
void CLight::LateUpdate()
{
	if (m_pParent == nullptr) return;
	Float3 pos = m_pParent->GetPos();

	m_transform.SetPos(pos);

	// �傫����ς���
	float size = m_transform.GetSizeX();
	if (m_fBaseSize * 1.07f < size)
	{
		m_bExpansion = false;
	}
	if (m_fBaseSize * 0.93f > size)
	{
		m_bExpansion = true;
	}

	if (m_bExpansion)
	{
		size *= 1.004f;
	}
	else
	{
		size *= 0.996f;
	}

	m_transform.SetSize(Float2{ size, size });
}

//========================================
//
//	�`�揈��
//
//========================================
void CLight::Draw()
{
	// ���Z����
//	glBlendFunc(GL_ONE, GL_ONE);
	CDirectX11::SetBlendState(EBlendState::BS_ADDITIVE);

	// �l�p�`�̕`��
	m_sprite.Draw(&m_transform, &sm_texture);

	// �A���t�@����
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	CDirectX11::SetBlendState(EBlendState::BS_ALPHABLEND);

}

//========================================
//
//	����
//
//========================================
CLight* CLight::Create(CTransform *pParent, float fScale)
{
	CLight *pLight = CObjectManager::CreateObject<CLight>();

	pLight->m_pParent = pParent;
	pLight->m_transform = *pParent;
	Float2 size = pLight->m_transform.GetSize();
	size.x *= fScale;
	size.y = size.x;
	pLight->m_fBaseSize = size.x;
	pLight->m_transform.SetSize(size);

	return pLight;
}

//========================================
//
//	����
//
//========================================
void CLight::Destroy()
{
	CObjectManager::DestroyObject(this);

}

//========================================
//
//	�����蔻��
//
//========================================
void CLight::OnCollision(CCollision *pCollision) 
{
	CObject* pObj = pCollision->GetObj();

	if (pObj->GetLayer() == LAYER::PLAYER)
	{
	}
}
