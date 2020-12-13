//==================================================================
//								Fire.h
//	�}�b�v�̓���
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//	
//	2020/07/09/06	�t�@�C���N���X�̍쐬	
//
//===================================================================


//====== �C���N���[�h�� ======
#include "Fire.h"
#include "collision.h"
#include "animator.h"
#include "../DirectX11.h"
#include "objectMgr.h"
#include "animation.h"
#include "light.h"


#ifdef _WIN32
#include "../Sound.h"
#endif // _WIN32

//===== �}�N����` =====
#define FIRE_SIZE_X		(41 * 0.65f)
#define FIRE_SIZE_Y		(52 * 0.65f)

//===== �ÓI�����o =====
CTexture CFire::sm_textureFire;
CTexture CFire::sm_textureBottom;


//===== �O���[�o���ϐ� =====



//========================================
//
//	�R���X�g���N�^
//
//========================================
CFire::CFire()
{
	m_pCollision = CCollision::Create(this);
	m_pAnimator = CAnimator::Create(&m_sprite, this);

	// �|���S���̃p�����[�^�̏�����
	m_transform.SetSize(Float2{ FIRE_SIZE_X * 4, FIRE_SIZE_Y * 4 });

	// �X�v���C�g�f�[�^
	m_sprite.SetColorW(0.95f);

	// ���C���[
	m_enLayer = LAYER::MAP_OBJ;

	// �A�j���[�V����
	CAnimation::Create(m_pAnimator, "fire", (unsigned int)15);
	m_pAnimator->SetAnimation("fire", 6, 17, 1);

	m_pAnimator->SetCurAnimNo(rand() % 17);
}


//========================================
//
//	�f�X�g���N�^
//
//========================================
CFire::~CFire()
{
	m_pCollision->Destroy();
	m_pAnimator->Destroy();
}


//========================================
//
//	������
//
//========================================
void CFire::Init()
{

	// �e�N�X�`���̃��[�h
	sm_textureFire.LoadTexture(FILE_PATH"object/fire4.tga");

}

//========================================
//
//	�I������
//
//========================================
void CFire::Uninit()
{
	// �e�N�X�`���̉��
	sm_textureFire.UnloadTexture();
}

//========================================
//
//	�X�V����
//
//========================================
void CFire::Update()
{


}

//========================================
//
//	�`�揈��
//
//========================================
void CFire::Draw()
{
	// �l�p�`�̕`��
	m_sprite.Draw(&m_transform, &sm_textureFire);

}

//========================================
//
//	����
//
//========================================
void CFire::Create(Float3 pos)
{
	CFire* pFire = CObjectManager::CreateObject<CFire>(pos);

	CLight::Create(&pFire->m_transform, 4.7f);
}

//========================================
//
//	������
//
//========================================
void CFire::Destroy()
{
	CObjectManager::DestroyObject(this);
}


//========================================
//
//	�R���W����
//
//========================================
void CFire::OnCollision(CCollision *pCollision)
{
	CObject* pObj = pCollision->GetObj();
	
}


//========================================
//
//	�A�j���[�^�[
//
//========================================
void CFire::OnAnimator(CAnimator *pAnimator)
{

}
