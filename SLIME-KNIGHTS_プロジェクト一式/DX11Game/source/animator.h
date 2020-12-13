//==================================================================
//									animator.h
//	�A�j���[�^�[
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//
//	2020/07/08	�A�j���[�^�[�N���X�쐬
//
//===================================================================
#pragma once

//====== �C���N���[�h�� ======
#include "../main.h"
#include "List.h"

//===== �}�N����` =====


//===== �N���X��` =====
class CSprite;
class CObject;
class CAnimation;

// �����F �ėp�^�ɂ���
class CAnimator
{
public:
	CAnimator();
	~CAnimator();
	static void Init();
	static void Uninit();
	static void Update();

	// �����E����
	static CAnimator* Create(CSprite *pSpr, CObject* pObj);
	void Destroy();

	// �Q�b�g�֐�
	CSprite* GetSpr() { return m_pSpr; }

	// �A�j���[�V�������X�g�Ǘ�
	void AddAnimation(CAnimation *pAnim) { m_animationList.AddNode(pAnim); }
	void DestroyAnimation(CAnimation *pAnim) { m_animationList.DestroyNode(pAnim); }
	void SetAnimation(const char *pszName);
	void SetAnimation(const char *pszName, int nSpeed);
	void SetAnimation(const char *pszName, int nSpeed, int nSplitX, int nSplitY);

	// �Q�b�g�֐�
	CAnimation* GetCurrentAnimation() { return m_pCurrentAnimation; }

	// �Z�b�g�֐�
	void SetStop(bool bStop) { m_bStop = bStop; }

	void SetCurAnimNo(int nAnimNo) { m_nCurrentAnimNo = nAnimNo; }

private:
	static List<CAnimator> m_list;
	List<CAnimation> m_animationList;
	CSprite *m_pSpr;
	CObject *m_pObj;

	// �A�j���[�V�����̕ϐ�
	int m_nSpeed;
	int m_nSplitX;
	int m_nSplitY;
	int m_nFrame;
	int m_nCurrentAnimNo;
	CAnimation *m_pCurrentAnimation;
	bool m_bStop;
};

