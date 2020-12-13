//==================================================================
//								effect.h
//	GM21 �G�t�F�N�g
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//	
//	2020/07/11	�G�t�F�N�g�N���X�̍쐬	
//
//===================================================================


//====== �C���N���[�h�� ======
#include "effect.h"
#include "collision.h"
#include "animator.h"
#include "objectMgr.h"
#include "animation.h"

#include "../sprite.h"
#include "../texture.h"

#ifdef _WIN64
#include "../DirectX11.h"

#endif // _WIN64


//===== �}�N����` =====


//===== �ÓI�����o =====
CTexture CEffect::sm_aTexture[EFFECT::MAX_EFFECT_NAME];

//===== ���O��� =====
using namespace EFFECT;


//========================================
//
//	�R���X�g���N�^
//
//========================================
CEffect::CEffect()
{
	// �R���W����
	//m_pCollision = CCollision::Create(this);
	// �A�j���[�^�[
	m_pAnimator = CAnimator::Create(&m_sprite, this);

	// �|���S���̃p�����[�^�̏�����
	m_transform;

	// �X�v���C�g�f�[�^
	m_sprite;

	// �e�N�X�`���f�[�^
	m_pTexture = nullptr;

	// ���C���[
	m_enLayer = LAYER::EFFECT;
}


//========================================
//
//	�f�X�g���N�^
//
//========================================
CEffect::~CEffect()
{
	// �R���W����
	//m_pCollision->Destroy();
	// �A�j���[�^�[
	m_pAnimator->Destroy();

}


//========================================
//
//	������
//
//========================================
void CEffect::Init()
{
	// �e�N�X�`���̃��[�h
	sm_aTexture[EFFECT::ENEMY_DAMAGE].LoadTexture(FILE_PATH"player/hit_effect.tga");
	sm_aTexture[EFFECT::PLAYER_DAMAGE].LoadTexture(FILE_PATH"player/player_damage.tga");
	sm_aTexture[EFFECT::DUST_L].LoadTexture(FILE_PATH"player/dust_L2.tga");
	sm_aTexture[EFFECT::DUST_R].LoadTexture(FILE_PATH"player/dust_R2.tga");
	sm_aTexture[EFFECT::SWORD_L].LoadTexture(FILE_PATH"player/sword_effect_L.tga");
	sm_aTexture[EFFECT::SWORD_R].LoadTexture(FILE_PATH"player/sword_effect_R.tga");

}

//========================================
//
//	�I������
//
//========================================
void CEffect::Uninit()
{
	// �e�N�X�`���̉��
	for (int i = 0; i < EFFECT::MAX_EFFECT_NAME; i++)
	{
		sm_aTexture[i].UnloadTexture();
	}
}

//========================================
//
//	�X�V����
//
//========================================
void CEffect::Update()
{

}

//========================================
//
//	�`�揈��
//
//========================================
void CEffect::Draw()
{
	// ���Z����
	//glBlendFunc(GL_ONE, GL_ONE);
	CDirectX11::SetBlendState(EBlendState::BS_ADDITIVE);

	// �l�p�`�̕`��
	m_sprite.Draw(&m_transform, m_pTexture);

	// �A���t�@����
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	CDirectX11::SetBlendState(EBlendState::BS_ALPHABLEND);
}

//========================================
//
//	����
//
//========================================
void CEffect::Create(EFFECT::EEFFECT_NAME enName, Float3 pos)
{
	CEffect *pEffect = CObjectManager::CreateObject<CEffect>(pos);
	Float3 vpos;

	switch (enName)
	{
	case EFFECT::ENEMY_DAMAGE:
		// �傫��
		pEffect->m_transform.SetSize(Float2{ 90 * 2.5f, 90 * 2.5f });
		// �e�N�X�`��
		pEffect->m_pTexture = &sm_aTexture[EFFECT::ENEMY_DAMAGE];
		// �A�j���[�V����
		CAnimation::Create(pEffect->m_pAnimator, "test", (unsigned int)6);
		pEffect->m_pAnimator->SetAnimation("test", 4, 6, 1);
		pEffect->m_transform.SetAngle(rand() % 360);
		vpos = pos;
		pos.x += rand() % 40 - 20;
		pos.y += rand() % 40 - 20;
		pEffect->m_transform.SetPos(pos);

		break;
	case EFFECT::PLAYER_DAMAGE:
		// �傫��
		pEffect->m_transform.SetSize(Float2{ 90 * 2, 90 * 2 });
		// �e�N�X�`��
		pEffect->m_pTexture = &sm_aTexture[EFFECT::PLAYER_DAMAGE];
		// �A�j���[�V����
		CAnimation::Create(pEffect->m_pAnimator, "test", (unsigned int)5);
		pEffect->m_pAnimator->SetAnimation("test", 5, 5, 1);
		pEffect->m_transform.SetAngle(rand() % 360);
		vpos = pos;
		pos.x += rand() % 40 - 20;
		pos.y += rand() % 40 - 20;
		pEffect->m_transform.SetPos(pos);

		break;
	case EFFECT::DUST_L:
		// �傫��
		pEffect->m_transform.SetSize(Float2{ 48, 48 });
		// �e�N�X�`��
		pEffect->m_pTexture = &sm_aTexture[EFFECT::DUST_L];
		// �A�j���[�V����
		CAnimation::Create(pEffect->m_pAnimator, "test", (unsigned int)8);
		pEffect->m_pAnimator->SetAnimation("test", 4, 8, 1);
		//pEffect->m_sprite.SetColorW(0.8f);

		break;
	case EFFECT::DUST_R:
		// �傫��
		pEffect->m_transform.SetSize(Float2{ 48, 48 });
		// �e�N�X�`��
		pEffect->m_pTexture = &sm_aTexture[EFFECT::DUST_R];
		// �A�j���[�V����
		CAnimation::Create(pEffect->m_pAnimator, "test", (unsigned int)8);
		pEffect->m_pAnimator->SetAnimation("test", 4, 8, 1);
		//pEffect->m_sprite.SetColorW(0.8f);

		break;
	case EFFECT::SWORD_L:
		// �傫��
		pEffect->m_transform.SetSize(Float2{ 96 * 2, 96 * 2 });
		// �e�N�X�`��
		pEffect->m_pTexture = &sm_aTexture[EFFECT::SWORD_L];
		// �A�j���[�V����
		CAnimation::Create(pEffect->m_pAnimator, "test", (unsigned int)4);
		pEffect->m_pAnimator->SetAnimation("test", 3, 4, 1);
		//pEffect->m_sprite.SetColorW(0.8f);

		break;
	case EFFECT::SWORD_R:
		// �傫��
		pEffect->m_transform.SetSize(Float2{ 96 * 2, 96 * 2 });
		// �e�N�X�`��
		pEffect->m_pTexture = &sm_aTexture[EFFECT::SWORD_R];
		// �A�j���[�V����
		CAnimation::Create(pEffect->m_pAnimator, "test", (unsigned int)4);
		pEffect->m_pAnimator->SetAnimation("test", 3, 4, 1);
		//pEffect->m_sprite.SetColorW(0.8f);

		break;
	case EFFECT::MAX_EFFECT_NAME:
		break;
	default:
		break;
	}

}

//========================================
//
//	������
//
//========================================
void CEffect::Destroy()
{
	CObjectManager::DestroyObject(this);

}

//========================================
//
//	�A�j���[�^�[
//
//========================================
void CEffect::OnAnimator(CAnimator *pAnimator)
{
	CObjectManager::DestroyObject(this);
}
