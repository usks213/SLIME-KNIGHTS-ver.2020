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
//
//===================================================================

//====== �C���N���[�h�� ======
#include "collision.h"
#include "object.h"
#include "rigidbody.h"

//===== �}�N����` =====
#define MAX_CELL (1+4+16+64)

//===== �N���X��` =====



//===== �v���g�^�C�v�錾 =====


// �ÓI�����o�̏�����
List<CCollision> CCollision::m_list;

float CCell::m_fUnit_W = 0.0f;		// �ŏ����x����Ԃ̕��P��
float CCell::m_fUnit_H = 0.0f;		// �ŏ����x����Ԃ̍��P��


//========================================
//
//	�R���X�g���N�^
//
//========================================
CCollision::CCollision()
{
	m_pObj = nullptr;
	m_pRb = nullptr;
	m_enColType = RECTANGLE;
}


//========================================
//
//	�f�X�g���N�^
//
//========================================
CCollision::~CCollision()
{

}


//========================================
//
//	������
//
//========================================
void CCollision::Init()
{
	

}

//========================================
//
//	�I������
//
//========================================
void CCollision::Uninit()
{
	// �擪���X�g�̎擾
	List<CCollision>* pHead = m_list.GetHead();

	// �m�[�h����
	if (pHead == nullptr) return;

	// �L�����N�^�[���[�N
	CCollision *pCol = nullptr;

	// ���X�g���̈�čX�V
	List<CCollision> *pNode = nullptr;
	List<CCollision> *pNextBack = nullptr;
	for (pNode = pHead; pNode != nullptr; pNode = pNextBack)
	{
		pNextBack = pNode->GetNext();

		pNode->DestroyNode(pNode);
	}
}

// �r�b�g�����֐�
DWORD BitSeparate32(DWORD n)
{
	n = (n | (n << 8)) & 0x00ff00ff;
	n = (n | (n << 4)) & 0x0f0f0f0f;
	n = (n | (n << 2)) & 0x33333333;
	return (n | (n << 1)) & 0x55555555;
}

// 2D���[�g����Ԕԍ��Z�o�֐�
WORD Get2DMortonNumber(WORD x, WORD y)
{
	return (WORD)(BitSeparate32(x) | (BitSeparate32(y) << 1));
}

// ���W�����`4���ؗv�f�ԍ��ϊ��֐�
DWORD GetPointElem(float pos_x, float pos_y)
{
	// �{���̓t�B�[���h�̑傫���Ƃ�
	return Get2DMortonNumber((WORD)(pos_x / CCell::GetUnitW()), (WORD)(pos_y / CCell::GetUnitH()));
}

// �����蔻��
void CCollision::Collision(List<CCollision> *pMain, List<CCollision> *pSubHead)
{
	// �擪���X�g�̎擾
	List<CCollision>* pHead = pSubHead;

	// �m�[�h����
	if (pHead == nullptr) return;

	// �L�����N�^�[���[�N
	CObject *pMainObj = pMain->GetThis()->m_pObj;
	CObject *pCol = nullptr;

	CTransform *pMainTrans = pMainObj->GetTransform();
	CTransform *pColTrans = nullptr;

	// ���X�g���̈�čX�V
	List<CCollision> *pNode = nullptr;
	List<CCollision> *pNextBack = nullptr;
	for (pNode = pHead; pNode != nullptr; pNode = pNextBack)
	{
		// ���̃|�C���^�̃o�b�N�A�b�v�����
		pNextBack = pNode->GetNext();
		// ���葤�̃f�[�^
		pCol = pNode->GetThis()->m_pObj;
		pColTrans = pCol->GetTransform();

		//===== �����Ńv���~�e�B�u�̎�ނœ����蔻��𕪂��� =====

		// ��`�Ƌ�`
		if (pMain->GetThis()->m_enColType == RECTANGLE && pNode->GetThis()->m_enColType == RECTANGLE)
		{
			if (CheckCollisionRectToRect(pMainTrans->GetPos(), pColTrans->GetPos(),
				pMainTrans->GetSize(), pColTrans->GetSize()))
			{
				// �����o��
				if (pMain->GetThis()->m_pRb != nullptr && pNode->GetThis()->m_pRb != nullptr)
				{
					// �����o������
					pMain->GetThis()->m_pRb->Extrusion(pNode->GetThis()->m_pRb);
					// ���葤�̉����o������
					pNode->GetThis()->m_pRb->Extrusion(pMain->GetThis()->m_pRb);
				}
				// �������Ă��画���̊֐����Ă�
				pMainObj->OnCollision(pNode->GetThis());
				// ���葤���Ă�
				pCol->OnCollision(pMain->GetThis());
			}
		}
		// �~�Ɖ~
		else if (pMain->GetThis()->m_enColType == CIRCLE && pNode->GetThis()->m_enColType == CIRCLE)
		{
			if (CheckCollisionCircleToCircle(pMainTrans->GetPos(), pColTrans->GetPos(), pMainTrans->GetSize().x, pColTrans->GetSize().x))
			{
				// �����o��
				if (pMain->GetThis()->m_pRb != nullptr && pNode->GetThis()->m_pRb != nullptr)
				{
					pMain->GetThis()->m_pRb->ExtrusionCircleToCircle(pNode->GetThis()->m_pRb);
				}

				// �������Ă��画���̊֐����Ă�
				pMainObj->OnCollision(pNode->GetThis());
				// ���葤���Ă�
				pCol->OnCollision(pMain->GetThis());
			}
		}
		// �~�Ƌ�`
		else if (pMain->GetThis()->m_enColType == CIRCLE && pNode->GetThis()->m_enColType == RECTANGLE)
		{
			if (CheckCollisionCircleToRect(pMainTrans->GetPos(), pColTrans->GetPos(), pMainTrans->GetSize().x, pColTrans->GetSize()))
			{
				// �����o��
				if (pMain->GetThis()->m_pRb != nullptr && pNode->GetThis()->m_pRb != nullptr)
				{
					// �����o������
					pMain->GetThis()->m_pRb->Extrusion(pNode->GetThis()->m_pRb);
					// ���葤�̉����o������
					pNode->GetThis()->m_pRb->Extrusion(pMain->GetThis()->m_pRb);
				}

				// �������Ă��画���̊֐����Ă�
				pMainObj->OnCollision(pNode->GetThis());
				// ���葤���Ă�
				pCol->OnCollision(pMain->GetThis());
			}

		}
		// ��`�Ɖ~
		else if (pMain->GetThis()->m_enColType == RECTANGLE && pNode->GetThis()->m_enColType == CIRCLE)
		{
			if (CheckCollisionCircleToRect(pColTrans->GetPos(), pMainTrans->GetPos(), pColTrans->GetSize().x, pMainTrans->GetSize()))
			{
				// �����o��
				if (pMain->GetThis()->m_pRb != nullptr && pNode->GetThis()->m_pRb != nullptr)
				{
					// �����o������
					pMain->GetThis()->m_pRb->Extrusion(pNode->GetThis()->m_pRb);
					// ���葤�̉����o������
					pNode->GetThis()->m_pRb->Extrusion(pMain->GetThis()->m_pRb);
				}

				// �������Ă��画���̊֐����Ă�
				pMainObj->OnCollision(pNode->GetThis());
				// ���葤���Ă�
				pCol->OnCollision(pMain->GetThis());
			}
		}

		// �_�Ɛ�

		// ���Ɛ�

		// �O�p

		//=========================================================

	}

}

//========================================
//
//	�X�V
//
//========================================
void CCollision::Update()
{
	// �擪���X�g�̎擾
	List<CCollision>* pHead = m_list.GetHead();

	// �m�[�h����
	if (pHead == nullptr) return;

	// ��ԃ��x���̐�
	const unsigned int uiLevel = CCell::GetUnitLevel();
	const unsigned int nMaxCell = MAX_CELL;

	// ��Ԃ̍쐬
	CCell mainCell[MAX_CELL];
	CCell subCell[MAX_CELL];
	// ���[�g���ԍ�
	DWORD Def = 0;
	DWORD wLeftTop = 0;
	DWORD wRightDown = 0;
	CTransform *pTrans;

	// ���X�g���̈�čX�V
	List<CCollision> *pNode = nullptr;
	List<CCollision> *pNextBack = nullptr;
	for (pNode = pHead; pNode != nullptr; pNode = pNode->GetNext())
	{
		// ���̃|�C���^�̃o�b�N�A�b�v�����
		//pNextBack = pNode->GetNext();

		// �����ŃJ�����O�Ȃ�AABB�ł͂���
		
		// �q�b�g�X�g�b�v
		if (pNode->GetThis()->GetObj()->GetStop()) continue;

		pTrans = pNode->GetThis()->GetObj()->GetTransform();

		// �����ŋ�Ԃ̓o�^������
		// ����ƉE�����o��
		wLeftTop = GetPointElem(pTrans->GetPos().x - pTrans->GetSize().x / 2,
								pTrans->GetPos().y - pTrans->GetSize().y / 2);
		wRightDown = GetPointElem(	pTrans->GetPos().x + pTrans->GetSize().x / 2,
									pTrans->GetPos().y + pTrans->GetSize().y / 2);
		// XOR���Ƃ�	
		Def = wLeftTop ^ wRightDown;
		unsigned int HiLevel = 0;
		unsigned int i;
		for (i = 0; i < uiLevel; i++)
		{
			DWORD Check = (Def >> (i * 2)) & 0x3;
			if (Check != 0)
				HiLevel = i + 1;
		}
		DWORD SpaceNum = wRightDown >> (HiLevel * 2);
		int nPow4 = 1;
		for (i = 0; i < uiLevel - HiLevel; i++) nPow4 *= 4;
		DWORD AddNum = (nPow4 - 1) / 3;
		SpaceNum += AddNum;	// ���ꂪ��������

		// ��ԊO�͂͂���
		if (SpaceNum > nMaxCell - 1) continue;

		// �������Ԃ̃��C�����X�g�Ɋi�[
		mainCell[SpaceNum].GetList()->AddNode(pNode->GetThis());

		// �������Ԃ̐e�̃T�u�Ɋi�[
		while (SpaceNum > 0)
		{
			SpaceNum--;
			SpaceNum /= 4;

			subCell[SpaceNum].GetList()->AddNode(pNode->GetThis());
		}

		// �����Ń_�u�����[�v�ŁA���̃L�����Ƒ�������œ����蔻������
		//pNode->GetThis()->Collision(pNode);
	}

	// �����ł��ꂼ��̋�ԓ��ł̂ɓ����蔻������
	for (int i = 0; i < nMaxCell; i++)
	{
		pHead = mainCell[i].GetList()->GetHead();
		if (pHead == nullptr) continue;

		for (pNode = pHead; pNode != nullptr; pNode = pNextBack)
		{
			pNextBack = pNode->GetNext();

			// �����蔻������
			pNode->GetThis()->Collision(pNode, pNextBack);
		}
	}

	// ���ɐe����q�ւ̓����蔻������
	for (int i = 0; i < nMaxCell; i++)
	{
		pHead = mainCell[i].GetList()->GetHead();
		if (pHead == nullptr) continue;

		for (pNode = pHead; pNode != nullptr; pNode = pNextBack)
		{
			pNextBack = pNode->GetNext();

			// �����蔻������
			pNode->GetThis()->Collision(pNode, subCell[i].GetList()->GetHead());
		}
	}

	/*for (int i = 0; i < 85; i++)
	{
		mainCell[i].ClearList();
		subCell[i].ClearList();
	}*/

}

//========================================
//
//	�����蔻��
//
//========================================
void CCollision::Collision(List<CCollision> *pMain)
{
	// �擪���X�g�̎擾
	List<CCollision>* pHead = m_list.GetHead();
	List<CCollision>* pTail = m_list.GetTail();

	// �m�[�h����
	if (pHead == nullptr) return;

	// �L�����N�^�[���[�N
	CObject *pMainObj = pMain->GetThis()->m_pObj;
	CObject *pCol = nullptr;

	CTransform *pMainTrans = pMainObj->GetTransform();
	CTransform *pColTrans  = nullptr;

	// ���X�g���̈�čX�V
	List<CCollision> *pNode = nullptr;
	List<CCollision> *pNextBack = nullptr;
	for (pNode = pMain->GetNext(); pNode != nullptr; pNode = pNextBack)
	{
		// ���̃|�C���^�̃o�b�N�A�b�v�����
		pNextBack = pNode->GetNext();
		// ���葤�̃f�[�^
		pCol = pNode->GetThis()->m_pObj;
		pColTrans = pCol->GetTransform();

		//===== �����Ńv���~�e�B�u�̎�ނœ����蔻��𕪂��� =====

		// ��`�Ƌ�`
		if (pMain->GetThis()->m_enColType == RECTANGLE && pNode->GetThis()->m_enColType == RECTANGLE)
		{
			if (CheckCollisionRectToRect(pMainTrans->GetPos(), pColTrans->GetPos(),
				pMainTrans->GetSize(), pColTrans->GetSize()))
			{
				// �����o��
				if (pMain->GetThis()->m_pRb != nullptr && pNode->GetThis()->m_pRb != nullptr)
				{
					// �����o������
					pMain->GetThis()->m_pRb->Extrusion(pNode->GetThis()->m_pRb);
					// ���葤�̉����o������
					pNode->GetThis()->m_pRb->Extrusion(pMain->GetThis()->m_pRb);
				}
				// �������Ă��画���̊֐����Ă�
				pMainObj->OnCollision(pNode->GetThis());
				// ���葤���Ă�
				pCol->OnCollision(pMain->GetThis());
			}
		}
		// �~�Ɖ~
		else if(pMain->GetThis()->m_enColType == CIRCLE && pNode->GetThis()->m_enColType == CIRCLE)
		{
			if (CheckCollisionCircleToCircle(pMainTrans->GetPos(), pColTrans->GetPos(), pMainTrans->GetSize().x, pColTrans->GetSize().x))
			{
				// �����o��
				if (pMain->GetThis()->m_pRb != nullptr && pNode->GetThis()->m_pRb != nullptr)
				{
					pMain->GetThis()->m_pRb->ExtrusionCircleToCircle(pNode->GetThis()->m_pRb);
				}

				// �������Ă��画���̊֐����Ă�
				pMainObj->OnCollision(pNode->GetThis());
				// ���葤���Ă�
				pCol->OnCollision(pMain->GetThis());
			}
		}
		// �~�Ƌ�`
		else if (pMain->GetThis()->m_enColType == CIRCLE && pNode->GetThis()->m_enColType == RECTANGLE)
		{
			if (CheckCollisionCircleToRect(pMainTrans->GetPos(), pColTrans->GetPos(), pMainTrans->GetSize().x, pColTrans->GetSize()))
			{
				// �����o��
				if (pMain->GetThis()->m_pRb != nullptr && pNode->GetThis()->m_pRb != nullptr)
				{
					// �����o������
					pMain->GetThis()->m_pRb->Extrusion(pNode->GetThis()->m_pRb);
					// ���葤�̉����o������
					pNode->GetThis()->m_pRb->Extrusion(pMain->GetThis()->m_pRb);
				}

				// �������Ă��画���̊֐����Ă�
				pMainObj->OnCollision(pNode->GetThis());
				// ���葤���Ă�
				pCol->OnCollision(pMain->GetThis());
			}

		}
		// ��`�Ɖ~
		else if(pMain->GetThis()->m_enColType == RECTANGLE && pNode->GetThis()->m_enColType == CIRCLE)
		{
			if (CheckCollisionCircleToRect(pColTrans->GetPos(), pMainTrans->GetPos(), pColTrans->GetSize().x, pMainTrans->GetSize()))
			{
				// �����o��
				if (pMain->GetThis()->m_pRb != nullptr && pNode->GetThis()->m_pRb != nullptr)
				{
					// �����o������
					pMain->GetThis()->m_pRb->Extrusion(pNode->GetThis()->m_pRb);
					// ���葤�̉����o������
					pNode->GetThis()->m_pRb->Extrusion(pMain->GetThis()->m_pRb);
				}

				// �������Ă��画���̊֐����Ă�
				pMainObj->OnCollision(pNode->GetThis());
				// ���葤���Ă�
				pCol->OnCollision(pMain->GetThis());
			}
		}
		
		// �_�Ɛ�

		// ���Ɛ�

		// �O�p

		//=========================================================

	}

}


//=====================================================
//
//	�`��	// �����蔻��̑傫����`�悵�Ă�����
//
//=====================================================
void CCollision::Draw()
{
	CSprite sprite;
	sprite.SetColor(Float4{ 1.0f, 1.0f, 0.0f, 0.1f });

	// �擪���X�g�̎擾
	List<CCollision>* pHead = m_list.GetHead();

	// �m�[�h����
	if (pHead == nullptr) return;

	// �L�����N�^�[���[�N
	CCollision *pCol = nullptr;

	// ���X�g���̈�čX�V
	List<CCollision> *pNode = nullptr;
	List<CCollision> *pNextBack = nullptr;
	for (pNode = pHead; pNode != nullptr; pNode = pNextBack)
	{
		pNextBack = pNode->GetNext();

		if (pNode->GetThis()->GetObj()->GetLayer() == LAYER::MAX_LAYER) continue;
		if (pNode->GetThis()->GetObj()->GetLayer() == LAYER::PLAYERATTACK) continue;
		sprite.Draw(pNode->GetThis()->GetObj()->GetTransform());
	}
}


//========================================
//
//	����
//
//========================================
CCollision* CCollision::Create(CObject *pObj, CRigidbody *pRb, ECOLLISION_TYPE enColType)
{
	CCollision *pCol = new CCollision;

	m_list.AddNode(pCol);

	pCol->m_pObj = pObj;
	pCol->m_pRb = pRb;
	pCol->m_enColType = enColType;

	return pCol;
}


//========================================
//
//	����
//
//========================================
void CCollision::Destroy()
{
	if (m_list.DestroyNode(this))
	{
		delete this;
	}
}



// ����
float Dot(Float3 vec1, Float3 vec2)
{
	float dot;

	dot = vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;

	return dot;
}

// �O��
float Cross2D(Float3 vec1, Float3 vec2)
{
	return vec1.x * vec2.y - vec1.y * vec2.x;
}

// �x�N�g���̒���
float Length(Float3 vec)
{
	return sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

// �x�N�g���̐��K��
Float3 Normalize(Float3 vec)
{
	float mag = Length(vec);
	vec.x /= mag;
	vec.y /= mag;
	vec.z /= mag;

	return vec;
}


// �����̏Փ�
bool CheckCollisionLine(Float3 pos1, Float3 pos2, Float3 pos3, Float3 pos4, Float3* outPos, float *outT1) 
{

	Float3 v = { pos3.x - pos1.x, pos3.y - pos1.y, 0.0f };
	// �x�N�g��
	Float3 vec1 = { pos2.x - pos1.x, pos2.y - pos1.y, 0.0f };
	Float3 vec2 = { pos4.x - pos3.x, pos4.y - pos3.y, 0.0f };

	float Crs_v1_v2 = Cross2D(vec1, vec2);
	if (Crs_v1_v2 == 0.0f) {
		// ���s���
		return false;
	}

	float Crs_v_v1 = Cross2D(v, vec1);
	float Crs_v_v2 = Cross2D(v, vec2);

	float t1 = Crs_v_v2 / Crs_v1_v2;
	float t2 = Crs_v_v1 / Crs_v1_v2;

	if(outT1)
		*outT1 = t2;

	const float eps = 0.00001f;
	if (t1 + eps < 0 || t1 - eps > 1 || t2 + eps < 0 || t2 - eps > 1) {
		// �������Ă��Ȃ�
		return false;
	}

	if (outPos)
	{
		//*outPos = seg1.s + seg1.v * t1;
		outPos->x = pos1.x + vec1.x * t1;
		outPos->y = pos1.y + vec1.y * t1;
		outPos->z = 0;
	}
	return true;
}



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
bool CheckCollisionRectToRect(Float3 centerPos1, Float3 centerPos2, Float2 size1, Float2 size2)
{
	Float2 halfSize1 = Float2{ size1.x / 2.0f, size1.y / 2.0f };
	Float2 halfSize2 = Float2{ size2.x / 2.0f, size2.y / 2.0f };

	if ((centerPos2.x - halfSize2.x < centerPos1.x + halfSize1.x) &&		// 2�̍��[ < 1�̉E�[
		(centerPos1.x - halfSize1.x < centerPos2.x + halfSize2.x ))		// 1�̍��[ < 2�̉E�[
	{
		if ((centerPos2.y - halfSize2.y < centerPos1.y + halfSize1.y) &&		// 2�̏�[ < 1�̉��[
			(centerPos1.y - halfSize1.y < centerPos2.y + halfSize2.y))		// 1�̏�[ < 2�̉��[
		{
			return true;
		}
	}



	return false;
}




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
bool CheckCollisionCircleToCircle(Float3 centerPos1, Float3 centerPos2, float radius1, float radius2)
{
	float fX = centerPos1.x - centerPos2.x;
	float fY = centerPos1.y - centerPos2.y;
	float fR = radius1 + radius2;

	if (fX * fX + fY * fY		// (�~1�̒��S���WX - �~2�̒��S���WX)��2�� + (�~1�̒��S���WY - �~2�̒��S���WY)��2��
		<= fR * fR)				// (�~1�̔��a+�~2�̔��a)��2��
	{
		return true;
	}

	return false;
}


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
bool CheckCollisionCircleToRect(Float3 centerPos1, Float3 centerPos2, float radius1, Float2 size2)
{
	// �~
	float x = centerPos1.x;
	float y = centerPos1.y;
	float radius = radius1;

	// ��`
	float L = centerPos2.x - size2.x / 2.0f;
	float R = centerPos2.x + size2.x / 2.0f;
	float T = centerPos2.y - size2.y / 2.0f;
	float B = centerPos2.y + size2.y / 2.0f;


	if (L - radius > x || R + radius < x || T - radius > y || B + radius < y) {//��`�̗̈攻��1
		return false;
	}
	if (L > x && T > y && !((L - x) * (L - x) + (T - y) * (T - y) < radius * radius)) {//����̓����蔻��
		return false;
	}
	if (R < x && T > y && !((R - x) * (R - x) + (T - y) * (T - y) < radius * radius)) {//�E��̓����蔻��
		return false;
	}
	if (L > x && B < y && !((L - x) * (L - x) + (B - y) * (B - y) < radius * radius)) {//�����̓����蔻��
		return false;
	}
	if (R < x && B < y && !((R - x) * (R - x) + (B - y) * (B - y) < radius * radius)) {//�E���̓����蔻��
		return false;
	}
	return true;//���ׂĂ̏������O�ꂽ�Ƃ��ɓ������Ă���
}