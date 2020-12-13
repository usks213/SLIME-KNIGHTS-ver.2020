//==================================================================
//								experience.cpp
//	�h���b�v���邨��
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//	
//	2020/07/08/07	�}�l�[�N���X�̍쐬	
//
//===================================================================


//====== �C���N���[�h�� ======
#include "experience.h"
#include "collision.h"
#include "animator.h"
#include "rigidbody.h"
#include "../DirectX11.h"
#include "objectMgr.h"
#include "status.h"
#include "animation.h"
#include "resultUI.h"


#ifdef _WIN32
#include "../Sound.h"
#endif // _WIN32

//===== �}�N����` =====
#define EXPERIENCE_FORCE_X (8)
#define EXPERIENCE_FORCE_Y (12)
#define EXPERIENCE_SIZE		(25)

//===== �ÓI�����o =====
CTexture CExperience::sm_texture;
CTexture CExperience::sm_textureLight;


//===== �O���[�o���ϐ� =====
static CSound g_SE;
static CSound g_SE_Bound;

static int g_nSECount;
static bool g_bSEPlay;
static int g_nMoneyCount;

//========================================
//
//	�R���X�g���N�^
//
//========================================
CExperience::CExperience()
{

	m_pRigidbody = CRigidbody::Create(&m_transform, false, true, true);

	m_pCollision = CCollision::Create(this, m_pRigidbody);

	// �|���S���̃p�����[�^�̏�����
	m_transform.SetSize(Float2{ EXPERIENCE_SIZE, EXPERIENCE_SIZE });

	// �X�v���C�g�f�[�^
	m_sprite;

	// ���C���[
	m_enLayer = LAYER::EXPERIENCE;


	// ��юU��
	m_pRigidbody->SetDragX(0.001f);
	float rad = (float)(rand() % 180);
	m_pRigidbody->SetForce(Float3{	 cosf(AngleToRadian(rad)) * (rand() % EXPERIENCE_FORCE_X + 1), 
									-sinf(AngleToRadian(rad)) * (rand() % EXPERIENCE_FORCE_Y + 1), 0.0f });
	m_pRigidbody->SetGravityForce(0.3f);
	m_fForceY = EXPERIENCE_FORCE_Y;
	m_pRigidbody->SetDragX(0.005f);

	g_nMoneyCount++;
}


//========================================
//
//	�f�X�g���N�^
//
//========================================
CExperience::~CExperience()
{
	m_pCollision->Destroy();
	m_pRigidbody->Destroy();
}


//========================================
//
//	������
//
//========================================
void CExperience::Init()
{

	// �e�N�X�`���̃��[�h
	sm_texture.LoadTexture(FILE_PATH"object/experience.tga");
	sm_textureLight.LoadTexture(FILE_PATH"object/light.tga");

	// �T�E���h
	g_SE.Load(FILE_PATH"sound/experience/get.mp3");
	g_SE_Bound.Load(FILE_PATH"sound/DropNameBound.mp3");

	g_nMoneyCount = 0;
}

//========================================
//
//	�I������
//
//========================================
void CExperience::Uninit()
{
	// �e�N�X�`���̉��
	sm_texture.UnloadTexture();
	sm_textureLight.UnloadTexture();
}

//========================================
//
//	�X�V����
//
//========================================
void CExperience::Update()
{


}

//========================================
//
//	�`�揈��
//
//========================================
void CExperience::Draw()
{
	// �l�p�`�̕`��
	m_sprite.SetColor(Float4{ 1, 1, 1, 0.5f });
	m_transform.SetSize(Float2{ m_size.x, m_size.y });
	m_sprite.Draw(&m_transform, &sm_texture);


	// ���Z����
	//glBlendFunc(GL_ONE, GL_ONE);
	CDirectX11::SetBlendState(EBlendState::BS_ADDITIVE);

	// �l�p�`�̕`��
	m_sprite.SetColor(Float4{ 0, 1, 0, 0.6f });
	m_transform.SetSize(Float2{ m_size.x * 2, m_size.y * 2 });
	m_sprite.Draw(&m_transform, &sm_textureLight);
	
	// �A���t�@����
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	CDirectX11::SetBlendState(EBlendState::BS_ALPHABLEND);
	m_transform.SetSize(Float2{ m_size.x, m_size.y });


	// �T�E���h
	g_nSECount++;
	if (g_nSECount > 3 * g_nMoneyCount)
	{
		g_bSEPlay = true;
	}

}

//========================================
//
//	����
//
//========================================
void CExperience::Create(int nNum, Float3 pos)
{
	int nDigit = 0;

	while (nNum != 0)
	{
		for (int i = 0; i < nNum % 10; i++)
		{
			CExperience *pExperience = CObjectManager::CreateObject<CExperience>(pos);
			Float2 size = Float2{ EXPERIENCE_SIZE, EXPERIENCE_SIZE };
			int nExperience = 1;
			for (int j = 0; j < nDigit; j++)
			{
				size.x *= 1.5f;
				size.y *= 1.5f;
				nExperience *= 10;
			}
			pExperience->m_size = size;
			pExperience->GetTransform()->SetSize(size);
			pExperience->m_nExperience = nExperience;
			
		}

		nNum /= 10;
		nDigit++;
	}

	
}

//========================================
//
//	������
//
//========================================
void CExperience::Destroy()
{
	CObjectManager::DestroyObject(this);
	g_nMoneyCount--;
}


//========================================
//
//	�R���W����
//
//========================================
void CExperience::OnCollision(CCollision *pCollision)
{
	CObject* pObj = pCollision->GetObj();
	if (pCollision->GetRb() == nullptr) return;

	if (pObj->GetLayer() == LAYER::PLAYER)
	{
		// �v���C���[�̂��������Z
		pObj->GetStatus()->AddExperience(m_nExperience, pObj->GetTransform()->GetPos());

		// �T�E���h
		g_SE.Play(0.6f);

		// ���U���h
		CResultUI::AddExperience(m_nExperience);

		// �����̏���
		this->Destroy();
	}
	else if (pObj->GetLayer() == LAYER::FIELD || pObj->GetLayer() == LAYER::FLOOR || 
			 pObj->GetLayer() == LAYER::ENEMYBULLET)
	{
		Float3 force = m_pRigidbody->GetForce();
		if (m_fForceY < 2.0f)
		{
			force.y = 0.0f;
			force.x = 0.0f;
			m_pRigidbody->SetUseGravity(false);
		}
		else if (m_pRigidbody->GetHitDir() <= DIRECTION::LEFT)
		{
			// ���E
			force.x *= -0.8f;
			
		}
		else if(m_pRigidbody->GetHitDir() == DIRECTION::DOWN)
		{
			m_fForceY *= 0.8f;
			// ��
			force.y = m_fForceY;
		}
		else if (m_pRigidbody->GetHitDir() == DIRECTION::UP)
		{
			m_fForceY *= 0.8f;
			// ��
			force.y = -m_fForceY;
			// �T�E���h
			if (g_bSEPlay)
			{
				g_SE_Bound.Play(0.18f);
				g_bSEPlay = false;
				g_nSECount = 0;
			}
		}
	
		m_pRigidbody->SetForce(force);
	}

}


//========================================
//
//	�A�j���[�^�[
//
//========================================
void CExperience::OnAnimator(CAnimator *pAnimator)
{

}
