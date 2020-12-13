//==================================================================
//									collision.h
//	�R���W����
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//
//	2020/06/24	�R���W����
//	2020/07/03	CCollision�N���X�̍쐬
//
//===================================================================
#pragma once

//====== �C���N���[�h�� ======
#include "../main.h"
#include "List.h"

//===== �}�N����` =====

enum ECOLLISION_TYPE
{
	RECTANGLE,
	CIRCLE,

	MAX_COLLISION_TYPE,
};

//===== �N���X��` =====
class CObject;
class CRigidbody;

// �����F �ėp�^�ɂ���
class CCollision
{
public:
	CCollision();
	~CCollision();
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	static void Collision(List<CCollision> *pMain);
	static void Collision(List<CCollision> *pMain, List<CCollision> *pSubHead);

	// �����E����
	static CCollision* Create(CObject *pObj, CRigidbody *pRb = nullptr, ECOLLISION_TYPE enColType = RECTANGLE);
	void Destroy();

	// �Q�b�g�֐�
	CObject* GetObj() { return m_pObj; }
	CRigidbody* GetRb() { return m_pRb; }

private:
	static List<CCollision> m_list;
	CObject *m_pObj;
	CRigidbody *m_pRb;

	ECOLLISION_TYPE m_enColType;
};

// �l���؋��
class CCell
{
public:
	CCell()
	{

	}
	~CCell()
	{
		List<CCollision> *pHead = m_list.GetHead();

		if (pHead == nullptr) return;

		List<CCollision> *pNode = nullptr;
		List<CCollision> *pNextBack = nullptr;

		for (pNode = pHead; pNode != nullptr; pNode = pNextBack)
		{
			pNextBack = pNode->GetNext();

			m_list.DestroyNode(pNode);
		}
	}

	void ClearList()
	{
		List<CCollision> *pHead = m_list.GetHead();

		if (pHead == nullptr) return;

		List<CCollision> *pNode = nullptr;
		List<CCollision> *pNextBack = nullptr;

		for (pNode = pHead; pNode != nullptr; pNode = pNextBack)
		{
			pNextBack = pNode->GetNext();

			m_list.DestroyNode(pNode);
		}
	}

	List<CCollision>* GetList() { return &m_list; }

	static void SetMapSize(float width, float height)
	{
		m_fUnit_W = width  / (float)(1 << (m_uiLevel - 1));
		m_fUnit_H = height / (float)(1 << (m_uiLevel - 1));
	}

	static float GetUnitW() { return m_fUnit_W; }
	static float GetUnitH() { return m_fUnit_H; }
	static unsigned int GetUnitLevel() { return m_uiLevel; }

private:
	List<CCollision> m_list;
	static float m_fUnit_W;		// �ŏ����x����Ԃ̕��P��
	static float m_fUnit_H;		// �ŏ����x����Ԃ̍��P��
	static const unsigned int m_uiLevel = 3;			// �ŉ��ʃ��x��
};


//===== �v���g�^�C�v�錾 =====
float Dot(Float3 vec1, Float3 vec2);
float Cross2D(Float3 vec1, Float3 vec2);
float Length(Float3 vec);
Float3 Normalize(Float3 vec);

// �������m�̓����蔻�� ���K���Ȃ�? (���_��0���獶�㎞�v���)
//bool CheckLineToLine(Float3 pos1, Float3 pos2, Float3 pos3, Float3 pos4, Float3 *pCrossPos);

// �������m�̓����蔻�� ���K���Ȃ�? (���_��0���獶�㎞�v���)
bool CheckCollisionLine(Float3 pos1, Float3 pos2, Float3 pos3, Float3 pos4, Float3* outPos = nullptr, float *outT1 = nullptr);

//*******************************
//
//	��`�Ƌ�`�̓����蔻��
//	
//	����:
//		��`�P�̒��S���W
//		��`�Q�̒��S���W
//		��`�P�̃T�C�Y
//		��`�Q�̃T�C�Y
//
//	�߂�l
//		false�F�ڐG���Ă��Ȃ�
//		true�F�ڐG���Ă���
//
//*******************************
bool CheckCollisionRectToRect(Float3 centerPos1, Float3 centerPos2, Float2 size1, Float2 size2);

//*******************************
//
//	�~�Ɖ~�̓����蔻��
//	
//	����:
//		�~�P�̒��S���W
//		�~�Q�̒��S���W
//		�~�P�̔��a
//		�~�Q�̔��a
//
//	�߂�l
//		false�F�ڐG���Ă��Ȃ�
//		true�F�ڐG���Ă���
//
//*******************************
bool CheckCollisionCircleToCircle(Float3 centerPos1, Float3 centerPos2, float radius1, float radius2);

//*******************************
//
//	�~�Ƌ�`�̓����蔻��
//	
//	����:
//		�~�P�̒��S���W
//		��`�Q�̒��S���W
//		�~�P�̔��a
//		��`�Q�̑傫��
//
//	�߂�l
//		false�F�ڐG���Ă��Ȃ�
//		true�F�ڐG���Ă���
//
//*******************************
bool CheckCollisionCircleToRect(Float3 centerPos1, Float3 centerPos2, float radius1, Float2 size2);

