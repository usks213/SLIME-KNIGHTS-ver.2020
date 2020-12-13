//==================================================================
//									animation.h
//	�A�j���[�V����
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//
//	2020/07/10	�A�j���[�V�����N���X�쐬
//
//===================================================================
#pragma once

//====== �C���N���[�h�� ======
#include "../main.h"
#include <stdarg.h>


//===== �}�N����` =====


//===== �N���X��` =====
class CAnimator;

// �����F �ėp�^�ɂ���
class CAnimation
{
public:
	CAnimation();
	~CAnimation();
	// �����E����
	static CAnimation* Create(CAnimator* pAnimator, const char *pszName, int nMaxFrame, ...);
	static CAnimation* Create(CAnimator* pAnimator, const char *pszName, unsigned int nMaxFrame);
	void Destroy();
	// �Q�b�g�֐�
	const char* GetName() { return m_pszName; }
	int* GetAnimNoArray() { return m_pAnimNoArray; }
	int GetArraySize() { return m_nArraySize; }
	CAnimator* GetAnimator() { return m_pAnimator; }
private:
	int* m_pAnimNoArray;
	int m_nArraySize;
	const char *m_pszName;
	CAnimator *m_pAnimator;
};

