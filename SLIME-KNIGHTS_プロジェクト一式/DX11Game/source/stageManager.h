//==================================================================
//								stageManager.h
//	�X�e�[�W�Ǘ�
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//
//	2020/08/23	�X�e�[�W�Ǘ��N���X�쐬
//
//===================================================================

#pragma once

//====== �C���N���[�h�� ======
#include "../main.h"
#include "stage.h"
#include "player.h"
#include "transform.h"
#include "../Sound.h"
#include "resultUI.h"


//===== �񋓌^ =====
namespace BGM
{
	enum EMAP_BGM
	{
		START_MAP,

		RENGA_RANDOM,
		RENGA_BOSS,

		MAX_MAP_BGM,
	};
}


//===== �N���X��` =====
class CStageManager
{
public:
	CStageManager();
	~CStageManager();

	// �l�又��
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	// �X�e�[�W�̃Z�b�g
	static void SetNextStage(CStage *pNextStage);
	static void SetTimerNextStage(CStage *pNextStage, int nTimerFrame, void(*pFadeOutEvent)() = SetStageChange);
	static void SetStageChange();
	
	// �v���C���[
	static void SetRestart();
	static void SetPlayerPos(Float3 pos) {
		if (m_pMainPlayer) {
			//m_pMainPlayer->GetTransform()->SetPos(pos);
			m_pMainPlayer->SetReStartPos(pos);
		}
	}
	static CPlayer* GetMainPlayer() { return m_pMainPlayer; }

	// �X�e�[�W�f�[�^
	static void SetStageLevel(int nLevel) { m_nStageLevel = nLevel; }
	static void AddStageLevel() { m_nStageLevel++; }
	static int GetStageLevel() { return m_nStageLevel; }
	static void SetTutorialClear(bool bFlag) { m_bTutorialClear = bFlag; }

	// BGM
	static void SetBGM(BGM::EMAP_BGM eBGM, float fVolume = 0.5f);
	static void StopBGM() {
		for(int i = 0; i < BGM::MAX_MAP_BGM; i++)
		sm_aBGM[i].Stop(); 
	}
	static void PlayBGM() { sm_aBGM[m_eCurBGM].Play(0.5f); }
	static int GetGameTime() { return m_nGameTime; }
	static void CreateResult() { m_pResultUI = CResultUI::Create(); }

private:
	static CStage* m_pCurrentStage;
	static CStage* m_pNextStage;
	static CPlayer* m_pMainPlayer;
	static int m_nTimer;

	// �X�e�[�W�̊K�w
	static int m_nStageLevel;
	static bool m_bTutorialClear;

	// BGM
	static CSound sm_aBGM[BGM::MAX_MAP_BGM];
	static BGM::EMAP_BGM m_eCurBGM;

	static CResultUI* m_pResultUI;
	static int m_nGameTime;
};

