//==================================================================
//								object.h
//	GM21 �I�u�W�F�N�g�֘A
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//
//	2020/06/03	�t�@�C���������ăI�u�W�F�N�g�P�ʂŃ\�[�X�ɂ���
//	2020/06/14	�I�u�W�F�N�g�����N���X��
//	2020/06/18	�t�����h�֐����X�^�e�B�b�N�̊֐��ɕύX
//	2020/08/15	�q�b�g�X�g�b�v����������
//
//===================================================================

#pragma once

//====== �C���N���[�h�� ======
#include "../main.h"
#include "transform.h"
#include "../sprite.h"
#include "../texture.h"


//===== �}�N����` =====

// ���C���[
namespace LAYER
{
	enum LAYER
	{
		BG,
		FIELD,
		FLOOR,
		MAP_OBJ,
		ENEMY,
		WEAPON,
		PLAYER,
		ENEMYBULLET,
		PLAYERBULLET,
		ENEMYATTACK,
		PLAYERATTACK,
		EXPERIENCE,
		EFFECT,
		UI,
		STRING,
		RESULT_UI,
		FADE,
		MAX_LAYER,
	};
}


//===== �N���X��` =====

// �O��`
class CCollision;
class CAnimator;
class CRigidbody;
class CStatus;

class CObject
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	 CObject();
	virtual ~CObject();
	// ���z�֐�
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void LateUpdate() { return; }

	// ���̃I�u�W�F�N�g�ɓ����������ɌĂ΂��֐�
	virtual void OnCollision(CCollision *pCollision) { return; }		// �L�����N�^�[�Ɏ�������
	// �A�j���[�V�����I�����ɌĂяo�����֐�
	virtual void OnAnimator(CAnimator *pAnimator) { return; }

	// �ÓI�֐�

	// �Q�b�g�֐�
	int GetLayer() { return m_enLayer; }
	//CTexture* GetTexture() { return m_pTexture; }
	CTransform* GetTransform() { return &m_transform; }
	CSprite* GetSprite() { return &m_sprite; }
	// �Z�b�g�֐�
	//void SetTexture(CTexture* tex) { m_pTexture = tex; }
	virtual CStatus* GetStatus() { return nullptr; }
	bool GetStop() { return m_bStop; }
	void SetStop(bool bFlag) { m_bStop = bFlag;; }

protected:

	// �`��f�[�^
	CTransform m_transform;
	// �X�v���C�g�f�[�^
	CSprite m_sprite;

	// ���C���[
	LAYER::LAYER m_enLayer;		// ���C���[�ԍ�
	bool m_bStop;
private:
	friend class CObjectManager;
	bool m_bDestroy;
};

