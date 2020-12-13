//==================================================================
//								stageMaker.cpp
//	�����_���X�e�[�W���C�J�[
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//
//	2020/08/25	�X�e�[�W���C�J�[�N���X�̍쐬
//
//===================================================================


//====== �C���N���[�h�� ======
#include "stageMaker.h"
#include "block.h"
#include "camera.h"
#include "collision.h"
#include "field.h"
#include "stageChangeArea.h"
#include "string.h"
#include "stageManager.h"
#include "miniMap.h"
#include "objectMgr.h"

#include "transform.h"
#include "rigidbody.h"
#include "collision.h"


//===== �}�N����` =====



//===== �񋓌^�E�萔��` =====
enum EMAP_TYPE
{
	// 1��
	L,
	R,
	T,
	B,

	// 2��
	LR,
	LT,
	LB,
	RT,
	RB,
	TB,

	// 3��
	LRT,
	LRB,
	LTB,
	RTB,

	// 4��
	LRTB,

	MAX_MAP_TYPE,
};


//===== �O���[�o���ϐ� =====
static CTexture g_TexBG;
static CTexture g_TexTile;


//===== �ÓI�����o =====
//CStageMaker::SMAP_DATA* CStageMaker::m_pMapData = nullptr;
CStageMaker::SMAP_DATA CStageMaker::m_pMapData[MAP_HEIGHT * MAP_WIDTH];
CTexture CStageMaker::sm_minimapTexture;
CTexture CStageMaker::sm_minimapUITexture;
CTexture CStageMaker::sm_minimapTextTexture;

int CStageMaker::m_nCurrentMapPosX = 0;
int CStageMaker::m_nCurrentMapPosY = 0;
bool CStageMaker::m_bStart = true;
bool CStageMaker::m_bMiniMapDraw = false;

List<CMiniMap> CStageMaker::m_miniMapList;



//========================================
//
//	�R���X�g���N�^
//
//========================================
CStageMaker::CStageMaker()
{
	
}


//========================================
//
//	�f�X�g���N�^
//
//========================================
CStageMaker::~CStageMaker()
{

}

//========================================
//
//	�}�b�v�^�C�v���ʊ֐�
//
//========================================
bool IsLeftType(int nMapType)
{
	if (nMapType == L ||
		nMapType == LR ||
		nMapType == LT ||
		nMapType == LB ||
		nMapType == LRT ||
		nMapType == LRB ||
		nMapType == LTB ||
		nMapType == LRTB
		)
		return true;

	return false;
}
bool IsRightType(int nMapType)
{
	if (nMapType == R ||
		nMapType == LR ||
		nMapType == RT ||
		nMapType == RB ||
		nMapType == LRT ||
		nMapType == LRB ||
		nMapType == RTB ||
		nMapType == LRTB
		)
		return true;

	return false;
}
bool IsTopType(int nMapType)
{
	if (nMapType == T ||
		nMapType == LT ||
		nMapType == RT ||
		nMapType == TB ||
		nMapType == LRT ||
		nMapType == LTB ||
		nMapType == RTB ||
		nMapType == LRTB
		)
		return true;

	return false;
}
bool IsBottomType(int nMapType)
{
	if (nMapType == B ||
		nMapType == LB ||
		nMapType == RB ||
		nMapType == TB ||
		nMapType == LRB ||
		nMapType == LTB ||
		nMapType == RTB ||
		nMapType == LRTB
		)
		return true;

	return false;
}


//========================================
//
//	�����_���}�b�v�̐���
//
//========================================
void CStageMaker::CreateRendomMap()
{
	// �}�b�v�f�[�^�̐���
	//m_pMapData = new SMAP_DATA[MAP_WIDTH * MAP_HEIGHT];

	// �}�b�v�f�[�^�̏�����
	for (int i = 0; i < MAP_WIDTH * MAP_HEIGHT; i++)
	{
		m_pMapData[i].nMapType		= -1;
		m_pMapData[i].bClearFlag	= false;
	}

	int nCount = 0;
	bool bCount = false;

	// �����_���Ƀ}�b�v�f�[�^���쐬
	// �u���b�N�̔z�u
	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			// �ő�J�E���g
			nCount = 0;

			// �����ł���܂ŌJ��Ԃ�
			while (++nCount < 10000)
			{
				// �����_���Ƀ}�b�v�f�[�^���i�[
				m_pMapData[(y) * MAP_WIDTH + (x)].nMapType = rand() % (MAX_MAP_TYPE + 1) - 1;

				//===== �i�[�����l�����낪�����Ă��邩�m�F =====
				// �z��O�͏���
				// �㉺���E�̒l���|�P�͋󂢂Ă�̂ŉ��ł��������

				bool bL = false;
				bool bT = false;

				// �����Ɍq����}�b�v������ 
				if (x > 0)
				{
					// �i�[����ĂȂ�
					if (m_pMapData[(y)* MAP_WIDTH + (x - 1)].nMapType == -1)
					{
						bL = true;
						// �����_���Ŋi�[�����l�����̗v�f�������Ă���ƃ_��
						if (IsLeftType(m_pMapData[(y)* MAP_WIDTH + (x)].nMapType)) continue;
					}
					// �E�̗v�f�������Ă���
					else if (IsRightType(m_pMapData[(y)* MAP_WIDTH + (x - 1)].nMapType))
					{
						// ��O�Ɠ���
						if (m_pMapData[(y)* MAP_WIDTH + (x - 1)].nMapType == m_pMapData[(y)* MAP_WIDTH + (x)].nMapType) continue;
						// �����_���Ŋi�[�����l�����̗v�f�������Ă��Ȃ��ƃ_��
						if (!IsLeftType(m_pMapData[(y)* MAP_WIDTH + (x)].nMapType)) continue;
					}
					// �E�̗v�f�������Ă��Ȃ�
					else if (!IsRightType(m_pMapData[(y)* MAP_WIDTH + (x - 1)].nMapType))
					{
						bL = true;
						// �����_���Ŋi�[�����l�����̗v�f�������Ă���ƃ_��
						if (IsLeftType(m_pMapData[(y)* MAP_WIDTH + (x)].nMapType)) continue;
					}
				}
				// �����Ƀ}�b�v���Ȃ�
				else
				{
					if (y != 0) bL = true;
					// �����_���Ŋi�[�����l�����̗v�f�������Ă���ƃ_��
					if (IsLeftType(m_pMapData[(y)* MAP_WIDTH + (x)].nMapType)) continue;
				}


				// �E���Ɍq����}�b�v������
				if (x + 1 < MAP_WIDTH)
				{
					// �i�[����ĂȂ�
					if (m_pMapData[(y)* MAP_WIDTH + (x + 1)].nMapType == -1)
					{
						// �Ȃ�ł��I�[�P�[
					}
					// ���̗v�f�������Ă���
					else if (IsLeftType(m_pMapData[(y)* MAP_WIDTH + (x + 1)].nMapType))
					{
						// �����_���Ŋi�[�����l���E�̗v�f�������Ă��Ȃ��ƃ_��
						if (!IsRightType(m_pMapData[(y)* MAP_WIDTH + (x)].nMapType)) continue;
					}
					// ���̗v�f�������Ă��Ȃ�
					else if (!IsLeftType(m_pMapData[(y)* MAP_WIDTH + (x + 1)].nMapType))
					{
						// �����_���Ŋi�[�����l���E�̗v�f�������Ă���ƃ_��
						if (IsRightType(m_pMapData[(y)* MAP_WIDTH + (x)].nMapType)) continue;
					}
				}
				// �E���Ƀ}�b�v���Ȃ�
				else
				{
					// �����_���Ŋi�[�����l���E�̗v�f�������Ă���ƃ_��
					if (IsRightType(m_pMapData[(y)* MAP_WIDTH + (x)].nMapType)) continue;
				}


				// �㑤�Ɍq����}�b�v������
				if (y > 0)
				{
					// �i�[����ĂȂ�
					if (m_pMapData[(y - 1)* MAP_WIDTH + (x)].nMapType == -1)
					{
						bT = true;
						// �����_���Ŋi�[�����l����̗v�f�������Ă���ƃ_��
						if (IsTopType(m_pMapData[(y)* MAP_WIDTH + (x)].nMapType)) continue;
					}
					// ���̗v�f�������Ă���
					else if (IsBottomType(m_pMapData[(y - 1)* MAP_WIDTH + (x)].nMapType))
					{
						// ��O�Ɠ���
						if (m_pMapData[(y - 1)* MAP_WIDTH + (x)].nMapType == m_pMapData[(y)* MAP_WIDTH + (x)].nMapType) continue;
						// �����_���Ŋi�[�����l����̗v�f�������Ă��Ȃ��ƃ_��
						if (!IsTopType(m_pMapData[(y)* MAP_WIDTH + (x)].nMapType)) continue;
					}
					// ���̗v�f�������Ă��Ȃ�
					else if (!IsBottomType(m_pMapData[(y - 1)* MAP_WIDTH + (x)].nMapType))
					{
						bT = true;
						// �����_���Ŋi�[�����l����̗v�f�������Ă���ƃ_��
						if (IsTopType(m_pMapData[(y)* MAP_WIDTH + (x)].nMapType)) continue;
					}
				}
				// �㑤�Ɍq����}�b�v���Ȃ�
				else
				{
					bT = true;
					// �����_���Ŋi�[�����l����̗v�f�������Ă���ƃ_��
					if (IsTopType(m_pMapData[(y)* MAP_WIDTH + (x)].nMapType)) continue;
				}


				// �����Ɍq����}�b�v������
				if (y + 1 < MAP_HEIGHT)
				{
					// �i�[����ĂȂ�
					if (m_pMapData[(y + 1)* MAP_WIDTH + (x)].nMapType == -1)
					{
						// �Ȃ�ł��I�[�P�[
					}
					// ��̗v�f�������Ă���
					else if (IsTopType(m_pMapData[(y + 1)* MAP_WIDTH + (x)].nMapType))
					{
						// �����_���Ŋi�[�����l�����̗v�f�������Ă��Ȃ��ƃ_��
						if (!IsBottomType(m_pMapData[(y)* MAP_WIDTH + (x)].nMapType)) continue;
					}
					// ��̗v�f�������Ă��Ȃ�
					else if (!IsTopType(m_pMapData[(y + 1)* MAP_WIDTH + (x)].nMapType))
					{
						// �����_���Ŋi�[�����l�����̗v�f�������Ă���ƃ_��
						if (IsBottomType(m_pMapData[(y)* MAP_WIDTH + (x)].nMapType)) continue;
					}
				}
				// �����Ɍq����}�b�v���Ȃ�
				else
				{
					// �����_���Ŋi�[�����l�����̗v�f�������Ă���ƃ_��
					if (IsBottomType(m_pMapData[(y)* MAP_WIDTH + (x)].nMapType)) continue;
				}


				// �����-1���������蒼��
				if (y == 0 && x == 0)
				{
					if (m_pMapData[(y)* MAP_WIDTH + (x)].nMapType == -1) continue;
				}

				// �P�ʃ}�b�v���߂��Ő�������Ȃ��悤��
				//if (x < MAP_WIDTH / 3 * 2 && y < MAP_HEIGHT / 3 * 2)
				if (x < MAP_WIDTH / 2 || y < MAP_HEIGHT / 2)
				{
					if (m_pMapData[(y)* MAP_WIDTH + (x)].nMapType == L  ||
						m_pMapData[(y)* MAP_WIDTH + (x)].nMapType == T  || 
						m_pMapData[(y)* MAP_WIDTH + (x)].nMapType == R  || 
						m_pMapData[(y)* MAP_WIDTH + (x)].nMapType == B  
						//m_pMapData[(y)* MAP_WIDTH + (x)].nMapType == LT || 
						//m_pMapData[(y)* MAP_WIDTH + (x)].nMapType == LB || 
						//m_pMapData[(y)* MAP_WIDTH + (x)].nMapType == RT  
						)
						continue;
				}

				// �Ȃ���Ȃ��Ƃ��͏���
				if (bL && bT)
					m_pMapData[(y)* MAP_WIDTH + (x)].nMapType = -1;


				// �����𖞂����Ă���̂�
				break;
			}

			if (nCount >= 10000) bCount = true;

		}
	}

	// ===== �}�b�v�f�[�^�������� =====

	// ������
	m_nCurrentMapPosX = 0;
	m_nCurrentMapPosY = 0;
	m_bMiniMapDraw = false;


	if (m_pMapData[0].nMapType == L || m_pMapData[0].nMapType == LB)
	{
		CStageChangeArea::SetGotoChangeArea(L);
	}
	else if (m_pMapData[0].nMapType == B)
	{
		CStageChangeArea::SetGotoChangeArea(B);
	}


	//===== �}�b�v�̃`�F�b�N =====
	bool bOne = false;
	// ��ʂ�����
	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			// ��ʂ���ł�����
			if (m_pMapData[(y)* MAP_WIDTH + (x)].nMapType <= B && m_pMapData[(y)* MAP_WIDTH + (x)].nMapType != -1)
			{
				bOne = true;
			}
		}
	}

	
	
	// �J�E���g�������Ă����蒼��
	if (bCount || !bOne)
	{
		// ����Ȃ��Ȃ��蒼��
		CreateRendomMap();
	}

	// ���̑��̃`�F�b�N��
	// �X�e�[�W�̍Œ�
	// 

	//===== �{�X�����쐬 =====

}

//
////========================================
////
////	�}�b�v�f�[�^�����ƂɃ~�j�}�b�v�𐶐�
////
////========================================
//void CStageMaker::CreateMiniMap()
//{
//	//===== �}�b�v�f�[�^�����ƂɃ~�j�}�b�v���� =====
//	for (int y = 0; y < MAP_HEIGHT; y++)
//	{
//		for (int x = 0; x < MAP_WIDTH; x++)
//		{
//			//if (m_pMapData[(y)* MAP_WIDTH + (x)].bClearFlag == false) continue;
//
//			int nType = m_pMapData[(y)* MAP_WIDTH + (x)].nMapType;
//
//			if (nType < 0 || nType >= MAX_MAP_TYPE) continue;
//
//			// �u���b�N�𐶐�
//			CMiniMap *pMiniMap = CMiniMap::Create(Float3{ (float)96 * x - SCREEN_CENTER_X / 2, 
//				(float)96 * y - SCREEN_CENTER_Y / 2, 0 },
//				&sm_minimapTexture, m_pMapData[y * MAP_WIDTH + x].nMapType, MAX_MAP_TYPE, 1);
//
//			// ���X�g�Ɋi�[
//			m_miniMapList.AddNode(pMiniMap);
//
//			// �J���[
//			pMiniMap->GetSprite()->SetColor(Float4{ 1.0f, 1.0f, 1.0f, 0.9f });
//
//			// ���ݒn
//			if (x == m_nCurrentMapPosX && y == m_nCurrentMapPosY)
//			{
//				pMiniMap->GetSprite()->SetColor(Float4{ 0.0f, 1.0f, 0.0f, 0.9f });
//			}
//		}
//	}
//
//}
//
////========================================
////
////	�}�b�v�f�[�^�����ƂɃ~�j�}�b�v�𐶐�
////
////========================================
//void CStageMaker::DestroyMiniMap()
//{
//	// ���X�g��S����
//	// �擪���X�g�̎擾
//	List<CMiniMap>* pHead = m_miniMapList.GetHead();
//
//	// �m�[�h����
//	if (pHead == nullptr) return;
//
//	// �I�u�W�F�N�g
//	CMiniMap* pObj = nullptr;
//
//	// ���X�g���̈�čX�V
//	List<CMiniMap> *pNode = nullptr;
//	List<CMiniMap> *pNextBack = nullptr;
//	for (pNode = pHead; pNode != nullptr; pNode = pNextBack)
//	{
//		// ���̃|�C���^�̃o�b�N�A�b�v�����
//		pNextBack = pNode->GetNext();
//
//		// �I�u�W�F�N�g�̍X�V
//		pObj = pNode->GetThis();
//
//		// �I�u�W�F�N�g�̏���
//		pObj->Destroy();
//		m_miniMapList.DestroyNode(pNode);
//	}
//
//
//}

//========================================
//
//	�~�j�}�b�v��`��
//
//========================================
void CStageMaker::MiniMapDraw()
{
	if (!m_bMiniMapDraw) return;

	// �f�[�^
	CSprite sprite;
	CTransform trans;
	float fOffSetY = 80;

	// �~�j�}�b�v�w�i
	trans.SetSize(Float2{ SCREEN_WIDTH, SCREEN_HEIGHT });
	sprite.SetColor(Float4{ 0.1f, 0.1f, 0.1f, 0.8f });
	sprite.Draw(&trans, nullptr, false);

	// �~�j�}�b�vUI
	trans.SetSize(Float2{ 280 * 2, 200 * 2  });
	sprite.SetColor(Float4{ 1.0f, 1.0f, 1.0f, 0.9f });
	trans.SetPos(Float3{ 0, fOffSetY, 0 });
	sprite.Draw(&trans, &sm_minimapUITexture, false);

	// �~�j�}�b�vTEXT ������
	static float fTextPosY = 0;
	static bool bUp = false;
	if (fTextPosY > 6) bUp = false;
	if (fTextPosY < -6) bUp = true;
	if (bUp) fTextPosY += 0.5f;
	else fTextPosY -= 0.5f;

	trans.SetSize(Float2{ 128 * 1.5f, 64 * 1.5f });
	sprite.SetColor(Float4{ 1.0f, 1.0f, 1.0f, 0.9f });
	trans.SetPos(Float3{ 0, -180 + fTextPosY, 0 });
	sprite.Draw(&trans, &sm_minimapTextTexture, false);


	//===== �}�b�v�f�[�^�����ƂɃ~�j�}�b�v��`�� =====
	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			// �\���t���O
			if (m_pMapData[(y)* MAP_WIDTH + (x)].bClearFlag == false) continue;

			int nType = m_pMapData[(y)* MAP_WIDTH + (x)].nMapType;

			if (nType < 0 || nType >= MAX_MAP_TYPE) continue;

			// �T�C�Y
			trans.SetSize(Float2{ 70.0f, 70.0f });

			// ���W
			trans.SetPos(Float3{trans.GetSize().x * x - trans.GetSize().x * MAP_WIDTH / 2.0f + trans.GetSize().x / 2,
								trans.GetSize().y * y - trans.GetSize().y * MAP_HEIGHT / 2.0f + trans.GetSize().y / 2 + fOffSetY, 0 });

			// ������
			int nSplitX = MAX_MAP_TYPE;
			int nSplitY = 1;

			// �e�N�X�`���T�C�Y
			sprite.SetTexSize(Float2{ 1.0f / nSplitX, 1.0f / nSplitY });

			// �e�N�X�`�����W
			sprite.SetTexPos(Float2{ nType % nSplitX * sprite.GetTexSize().x,
												nType / nSplitX * sprite.GetTexSize().y });
			// �J���[
			sprite.SetColor(Float4{ 0.8f, 0.8f, 0.8f, 0.8f });


			// �`��
			sprite.Draw(&trans, &sm_minimapTexture, false);

			// ���ݒn
			if (x == m_nCurrentMapPosX && y == m_nCurrentMapPosY)
			{
				static int nCnt = 0;
				if (nCnt++ % 90 > 60) continue;
				sprite.SetColor(Float4{ 0.0f, 1.0f, 0.0f, 0.9f });
				trans.SetSize(Float2{ 10, 10 });
				sprite.Draw(&trans, nullptr, false);
			}
		}
	}


}


//========================================
//
//	�}�b�v�f�[�^�����ƂɃX�e�[�W�𐶐�
//
//========================================
void CStageMaker::CreateStage()
{
	// ���݈ʒu�̃}�b�v�̃f�[�^���擾
	int nLoadMapType = m_pMapData[m_nCurrentMapPosY * MAP_WIDTH + m_nCurrentMapPosX].nMapType;

	// ���S����
	if (nLoadMapType < 0 || nLoadMapType >= MAX_MAP_TYPE) return;

	// ��x�������t���O
	m_pMapData[m_nCurrentMapPosY * MAP_WIDTH + m_nCurrentMapPosX].bClearFlag = true;

	// ���[�h����}�b�v�̃p�X���쐬
	char szFileName[256];

	// �X�^�[�g�n�_
	if (m_nCurrentMapPosX == 0 && m_nCurrentMapPosY == 0)
	{
		//BG
		std::sprintf(szFileName, FILE_PATH"map/renga/start/%d/map_bg.csv", nLoadMapType);
		CField::CreateBg(szFileName, &g_TexBG, 1, 1);
		// TILE
		std::sprintf(szFileName, FILE_PATH"map/renga/start/%d/map_tile.csv", nLoadMapType);
		CField::Create(szFileName, &g_TexTile, 11, 5);
		// OBJECT
		std::sprintf(szFileName, FILE_PATH"map/renga/start/%d/map_object.csv", nLoadMapType);
		CField::SetObject(szFileName);
		// PLAYER
		std::sprintf(szFileName, FILE_PATH"map/renga/start/%d/map_player.csv", nLoadMapType);
		// ����
		if (m_bStart)
		{
			CStageManager::SetPlayerPos(Float3{ 96 * 4, 96 * 11, 0 });
			m_bStart = false;
		}
		else
		{
			CField::SetPlayer(szFileName, CStageChangeArea::GetGotoChangeArea());
		}
		// STAGE_CHANGE_AREA
		std::sprintf(szFileName, FILE_PATH"map/renga/start/%d/map_area.csv", nLoadMapType);
		CField::SetChangeArea(szFileName);
	}
	// �{�X�����֍s���}�b�v
	else if (nLoadMapType <= B && nLoadMapType >= L)
	{
		//BG
		std::sprintf(szFileName, FILE_PATH"map/renga/%d/map_bg.csv", nLoadMapType);
		CField::CreateBg(szFileName, &g_TexBG, 1, 1);
		// TILE
		std::sprintf(szFileName, FILE_PATH"map/renga/%d/map_tile.csv", nLoadMapType);
		CField::Create(szFileName, &g_TexTile, 11, 5);
		// OBJECT
		std::sprintf(szFileName, FILE_PATH"map/renga/%d/map_object.csv", nLoadMapType);
		CField::SetObject(szFileName, true);
		// ENEMY
		std::sprintf(szFileName, FILE_PATH"map/renga/%d/map_enemy.csv", nLoadMapType);
		CField::SetEnemy(szFileName);
		// PLAYER
		std::sprintf(szFileName, FILE_PATH"map/renga/%d/map_player.csv", nLoadMapType);
		CField::SetPlayer(szFileName, CStageChangeArea::GetGotoChangeArea());
		// STAGE_CHANGE_AREA
		std::sprintf(szFileName, FILE_PATH"map/renga/%d/map_area.csv", nLoadMapType);
		CField::SetChangeArea(szFileName);
	}
	else
	{
		//BG
		std::sprintf(szFileName, FILE_PATH"map/renga/%d/map_bg.csv", nLoadMapType);
		CField::CreateBg(szFileName, &g_TexBG, 1, 1);
		// TILE
		std::sprintf(szFileName, FILE_PATH"map/renga/%d/map_tile.csv", nLoadMapType);
		CField::Create(szFileName, &g_TexTile, 11, 5);
		// OBJECT
		std::sprintf(szFileName, FILE_PATH"map/renga/%d/map_object.csv", nLoadMapType);
		CField::SetObject(szFileName);
		// ENEMY
		std::sprintf(szFileName, FILE_PATH"map/renga/%d/map_enemy.csv", nLoadMapType);
		CField::SetEnemy(szFileName);
		// PLAYER
		std::sprintf(szFileName, FILE_PATH"map/renga/%d/map_player.csv", nLoadMapType);
		CField::SetPlayer(szFileName, CStageChangeArea::GetGotoChangeArea());
		// STAGE_CHANGE_AREA
		std::sprintf(szFileName, FILE_PATH"map/renga/%d/map_area.csv", nLoadMapType);
		CField::SetChangeArea(szFileName);
	}
	
}


//========================================
//
//	������
//
//========================================
void CStageMaker::Init()
{
	// �e�N�X�`��
	g_TexBG.LoadTexture(FILE_PATH"map/renga/bg.png");
	g_TexTile.LoadTexture(FILE_PATH"map/renga/tile.png");
	sm_minimapTexture.LoadTexture(FILE_PATH"map/minimap.tga");
	sm_minimapUITexture.LoadTexture(FILE_PATH"map/minimap_ui.tga");
	sm_minimapTextTexture.LoadTexture(FILE_PATH"map/minimap_text.tga");
}

//========================================
//
//	�I������
//
//========================================
void CStageMaker::Uninit()
{
	// �e�N�X�`��
	g_TexBG.UnloadTexture();
	g_TexTile.UnloadTexture();
	sm_minimapTexture.UnloadTexture();
	sm_minimapUITexture.UnloadTexture();
	sm_minimapTextTexture.UnloadTexture();
}

//========================================
//
//	�X�V
//
//========================================
void CStageMaker::Update()
{
	
}


//========================================
//
//	�`��
//
//========================================
void CStageMaker::Draw()
{

}

