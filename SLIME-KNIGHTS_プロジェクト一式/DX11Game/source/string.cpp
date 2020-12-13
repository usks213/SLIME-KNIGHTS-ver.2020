//==================================================================
//									font.cpp
//	������\��
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//
//	2020/08/08	�t�H���g�N���X
//
//===================================================================


//====== �C���N���[�h�� ======
#include "string.h"
#include "../sprite.h"
#include "../texture.h"
#include "word.h"
#include "objectMgr.h"



//===== �}�N����` =====
#define FULL_FONT_SIZE_X	(8)
#define FULL_FONT_SIZE_Y	(8)
#define FULL_FONT_WIDTH	  (752)
#define FULL_FONT_HEIGHT  (752)

#define HALF_FONT_SIZE_X	(4)
#define HALF_FONT_SIZE_Y	(8)
#define HALF_FONT_WIDTH	   (64)
#define HALF_FONT_HEIGHT  (128)



//===== �v���g�^�C�v�錾 =====

//===== ���O��� =====
using namespace STRING;

//===== �O���[�o���ϐ� =====


//===== �ÓI�����o =====
CTexture CString::sm_fullFontTexture;
CTexture CString::sm_halfFontTexture;


//========================================
//
//	�R���X�g���N�^
//
//========================================
CString::CString()
{
	// �|���S���̃p�����[�^�̏�����
	m_transform;

	// �X�v���C�g�f�[�^
	m_sprite;

	// ���C���[
	m_enLayer = LAYER::STRING;

	m_bCamera = false;
	m_eOffSetX = EOFFSET_X::LEFT;
	m_eOffSetY = EOFFSET_Y::TOP;
	m_wordColor = Float4{ 1,1,1,1 };
	m_wordSize = Float2{ 50, 50 };
	m_pText = nullptr;
}

//========================================
//
//	�R���X�g���N�^
//
//========================================
CString::CString(const char* pszText, Float3 pos, Float2 size, Float4 color, EOFFSET_X eOffSetX, EOFFSET_Y eOffSetY, bool bCamera)
{
	// �|���S���̃p�����[�^�̏�����
	m_transform;

	// �X�v���C�g�f�[�^
	m_sprite;

	// ���C���[
	m_enLayer = LAYER::STRING;

	m_bCamera = false;
	m_eOffSetX = EOFFSET_X::LEFT;
	m_eOffSetY = EOFFSET_Y::TOP;
	m_wordColor = Float4{ 1,1,1,1 };
	m_wordSize = Float2{ 50, 50 };
	m_pText = nullptr;


	int nFullWidthChar;	//�S�p�����̂Q�o�C�g���̃f�[�^
	int nOffset;
	int nCharPosX;
	int nCharPosY;
	int nCharCnt;
	bool bHalf = false;

	// �����N���X�|�C���g
	CWord *pWord = nullptr;
	// ���W
	Float3 wordPos = { 0.0f, 0.0f, 0.0f };
	// �e�N�X�`�����W
	Float2 texPos = { 0.0f, 0.0f };
	Float2 texSize = { 0.0f, 0.0f };
	// ������N���X�̐���
	CString *pString = this;
	pString->m_bCamera = bCamera;
	pString->m_sprite;
	pString->m_wordSize = size;
	pString->m_wordColor = color;
	pString->m_pText = pszText;

	// �I�t�Z�b�g���W
	float fOffSetX = 0;
	float fOffSetY = 0;
	pString->m_eOffSetX = eOffSetX;
	pString->m_eOffSetY = eOffSetY;

	// ������̒�������
	switch (eOffSetX)
	{
	case STRING::LEFT:
		fOffSetX = -size.x / 2 - 1;
		break;
	case STRING::CENTER_X:
		fOffSetX = strlen(pszText) / 2.0f * size.x / 2 - size.x / 2;
		break;
	case STRING::RIGHT:
		fOffSetX = strlen(pszText) * size.x / 2 - size.x / 4;
		break;
	}

	// \n�̐�����
	switch (eOffSetY)
	{
	case STRING::TOP:
		fOffSetY = -size.y / 2 - 1;
		break;
	case STRING::CENTER_Y:
		break;
	case STRING::DOWN:
		break;
	}

	// �I�t�Z�b�g���Z�b�g
	wordPos = pos;
	wordPos.x -= fOffSetX;
	wordPos.y -= fOffSetY;


	for (nCharCnt = 0; pszText[nCharCnt]; nCharCnt++)
	{
		//�S�p���ǂ����̔��f
		if ((0x7f < (unsigned char)pszText[nCharCnt] && (unsigned char)pszText[nCharCnt] < 0xa0) || 0xdf < (unsigned char)pszText[nCharCnt])
		{//�S�p������
			nFullWidthChar = ((unsigned char)pszText[nCharCnt] << 8) + (unsigned char)pszText[nCharCnt + 1];

			//----- �����R�[�h����摜�̕����̈ʒu�ɕϊ� -----
			nOffset = 0x8140;
			if (0xdf < (unsigned char)pszText[nCharCnt])	nOffset += 0x4000;

			nCharPosX = ((unsigned char)pszText[nCharCnt + 1] - (nOffset & 0x00ff)) % (FULL_FONT_WIDTH / FULL_FONT_SIZE_X + 1);
			if (0x7f < (unsigned char)pszText[nCharCnt + 1])
				if (0x9e >= (unsigned char)pszText[nCharCnt + 1])
					nCharPosX--;
			nCharPosY = (nFullWidthChar - nOffset) / (FULL_FONT_WIDTH / FULL_FONT_SIZE_Y);
			nCharPosY = ((unsigned char)pszText[nCharCnt] - (nOffset >> 8) + 1) * 2;
			if (0x9e >= (unsigned char)pszText[nCharCnt + 1])	nCharPosY--;
			nCharPosY--;

			//----- �������� -----
			// �e�N�X�`�����W
			texSize.x = 1.0f / (FULL_FONT_WIDTH / FULL_FONT_SIZE_X);
			texSize.y = 1.0f / (FULL_FONT_HEIGHT / FULL_FONT_SIZE_Y);
			texPos.x = texSize.x * nCharPosX;
			texPos.y = texSize.y * nCharPosY;

			// �n�[�t�t���O��true�̂Ƃ�
			if (bHalf) wordPos.x += size.x / 4.0f;
			bHalf = false;

			// ���[�h�̐���
			pWord = CWord::Create(wordPos, size, texPos, texSize, color, &sm_fullFontTexture);

			// ���W
			wordPos.x += size.x;

			// ���X�g�Ɋi�[
			pString->m_wordList.AddNode(pWord);


			nCharCnt++;	//�S�p�̎��̏����Ȃ̂ŕ��������������
		}
		else
		{//���p������
			//----- �����R�[�h����摜�̕����̈ʒu�ɕϊ� -----
			nCharPosX = ((unsigned char)pszText[nCharCnt] & 0x0f) % 0x10;
			nCharPosY = ((unsigned char)pszText[nCharCnt] >> 4);

			//----- �������� -----
			texSize.x = 1.0f / (HALF_FONT_WIDTH / HALF_FONT_SIZE_X);
			texSize.y = 1.0f / (HALF_FONT_HEIGHT / HALF_FONT_SIZE_Y);
			texPos.x = texSize.x * nCharPosX;
			texPos.y = texSize.y * nCharPosY;

			// �n�[�t�t���O��true�̂Ƃ�
			if (!bHalf) wordPos.x -= size.x / 4.0f;
			bHalf = true;

			// ���[�h�̐���
			pWord = CWord::Create(wordPos, Float2{ size.x / 2, size.y }, texPos, texSize, color, &sm_halfFontTexture);

			// ���W
			wordPos.x += size.x / 2.0f;

			// ���X�g�Ɋi�[
			pString->m_wordList.AddNode(pWord);
		}
	}


}


//========================================
//
//	�f�X�g���N�^
//
//========================================
CString::~CString()
{

}


//========================================
//
//	������
//
//========================================
void CString::Init()
{
	// �e�N�X�`���̃��[�h
	sm_fullFontTexture.LoadTexture(FILE_PATH"font/misaki_gothic_2nd.tga");
	sm_halfFontTexture.LoadTexture(FILE_PATH"font/misaki_gothic_2nd_4x8.tga");

}


//========================================
//
//	�I������
//
//========================================
void CString::Uninit()
{
	// �e�N�X�`���̉��
	sm_fullFontTexture.UnloadTexture();
	sm_halfFontTexture.UnloadTexture();

}


//========================================
//
//	�X�V
//
//========================================
void CString::Update()
{
	

}


//========================================
//
//	�`��
//
//========================================
void CString::Draw()
{
	List<CWord> *pHead = m_wordList.GetHead();
	if (pHead == nullptr) return;

	List<CWord> *pNode = nullptr;
	for (pNode = pHead; pNode != nullptr; pNode = pNode->GetNext())
	{
		pNode->GetThis()->Draw(m_bCamera);
	}
}


//========================================
//
//	����
//
//========================================
CString* CString::Create(const char* pszText, Float3 pos, Float2 size, Float4 color, EOFFSET_X eOffSetX, EOFFSET_Y eOffSetY, bool bCamera)
{
	int nFullWidthChar;	//�S�p�����̂Q�o�C�g���̃f�[�^
	int nOffset;
	int nCharPosX;
	int nCharPosY;
	int nCharCnt;
	bool bHalf = false;

	// �����N���X�|�C���g
	CWord *pWord = nullptr;
	// ���W
	Float3 wordPos = { 0.0f, 0.0f, 0.0f };
	// �e�N�X�`�����W
	Float2 texPos	= { 0.0f, 0.0f };
	Float2 texSize	= { 0.0f, 0.0f };
	// ������N���X�̐���
	CString *pString = CObjectManager::CreateObject<CString>(pos);
	pString->m_bCamera = bCamera;
	pString->m_sprite;
	pString->m_wordSize = size;
	pString->m_wordColor = color;
	pString->m_pText = pszText;

	// �I�t�Z�b�g���W
	float fOffSetX = 0;
	float fOffSetY = 0;
	pString->m_eOffSetX = eOffSetX;
	pString->m_eOffSetY = eOffSetY;

	// ������̒�������
	switch (eOffSetX)
	{
	case STRING::LEFT:
		fOffSetX = -size.x / 2 - 1;
		break;
	case STRING::CENTER_X:
		fOffSetX = strlen(pszText) / 2.0f * size.x / 2 - size.x / 2;
		break;
	case STRING::RIGHT:
		fOffSetX = strlen(pszText) * size.x / 2 - size.x / 4;
		break;
	}

	// \n�̐�����
	switch (eOffSetY)
	{
	case STRING::TOP:
		fOffSetY = -size.y / 2 - 1;
		break;
	case STRING::CENTER_Y:
		break;
	case STRING::DOWN:
		break;
	}
	
	// �I�t�Z�b�g���Z�b�g
	wordPos = pos;
	wordPos.x -= fOffSetX;
	wordPos.y -= fOffSetY;


	for (nCharCnt = 0; pszText[nCharCnt]; nCharCnt++)
	{
		//�S�p���ǂ����̔��f
		if ((0x7f < (unsigned char)pszText[nCharCnt] && (unsigned char)pszText[nCharCnt] < 0xa0) || 0xdf < (unsigned char)pszText[nCharCnt])
		{//�S�p������
			nFullWidthChar = ((unsigned char)pszText[nCharCnt] << 8) + (unsigned char)pszText[nCharCnt + 1];

			//----- �����R�[�h����摜�̕����̈ʒu�ɕϊ� -----
			nOffset = 0x8140;
			if (0xdf < (unsigned char)pszText[nCharCnt])	nOffset += 0x4000;

			nCharPosX = ((unsigned char)pszText[nCharCnt + 1] - (nOffset & 0x00ff)) % (FULL_FONT_WIDTH / FULL_FONT_SIZE_X + 1);
			if (0x7f < (unsigned char)pszText[nCharCnt + 1])
				if (0x9e >= (unsigned char)pszText[nCharCnt + 1])
					nCharPosX--;
			nCharPosY = (nFullWidthChar - nOffset) / (FULL_FONT_WIDTH / FULL_FONT_SIZE_Y);
			nCharPosY = ((unsigned char)pszText[nCharCnt] - (nOffset >> 8) + 1) * 2;
			if (0x9e >= (unsigned char)pszText[nCharCnt + 1])	nCharPosY--;
			nCharPosY--;

			//----- �������� -----
			// �e�N�X�`�����W
			texSize.x = 1.0f / (FULL_FONT_WIDTH  / FULL_FONT_SIZE_X);
			texSize.y = 1.0f / (FULL_FONT_HEIGHT / FULL_FONT_SIZE_Y);
			texPos.x = texSize.x * nCharPosX;
			texPos.y = texSize.y * nCharPosY;

			// �n�[�t�t���O��true�̂Ƃ�
			if(bHalf) wordPos.x += size.x / 4.0f;
			bHalf = false;

			// ���[�h�̐���
			pWord = CWord::Create(wordPos, size, texPos, texSize, color, &sm_fullFontTexture);

			// ���W
			wordPos.x += size.x;

			// ���X�g�Ɋi�[
			pString->m_wordList.AddNode(pWord);


			nCharCnt++;	//�S�p�̎��̏����Ȃ̂ŕ��������������
		}
		else
		{//���p������
			//----- �����R�[�h����摜�̕����̈ʒu�ɕϊ� -----
			nCharPosX = ((unsigned char)pszText[nCharCnt] & 0x0f) % 0x10;
			nCharPosY = ((unsigned char)pszText[nCharCnt] >> 4);

			//----- �������� -----
			texSize.x = 1.0f / (HALF_FONT_WIDTH  / HALF_FONT_SIZE_X);
			texSize.y = 1.0f / (HALF_FONT_HEIGHT / HALF_FONT_SIZE_Y);
			texPos.x = texSize.x * nCharPosX;
			texPos.y = texSize.y * nCharPosY;

			// �n�[�t�t���O��true�̂Ƃ�
			if (!bHalf) wordPos.x -= size.x / 4.0f;
			bHalf = true;

			// ���[�h�̐���
			pWord = CWord::Create(wordPos, Float2{size.x / 2, size.y}, texPos, texSize, color, &sm_halfFontTexture);

			// ���W
			wordPos.x += size.x / 2.0f;

			// ���X�g�Ɋi�[
			pString->m_wordList.AddNode(pWord);
		}
	}

	return pString;
}


//========================================
//
//	����
//
//========================================
CString* CString::Create()
{
	// ������N���X�̐���
	CString *pString = CObjectManager::CreateObject<CString>();

	return pString;
}

//========================================
//
//	����
//
//========================================
void CString::Destroy()
{
	List<CWord> *pHead = m_wordList.GetHead();
	if (pHead == nullptr) return;

	List<CWord> *pNode = nullptr;
	List<CWord> *pNextBack = nullptr;
	CWord *pWord = nullptr;
	for (pNode = pHead; pNode != nullptr; pNode = pNextBack)
	{
		pNextBack = pNode->GetNext();
		pWord = pNode->GetThis();

		if (m_wordList.DestroyNode(pNode))
		{
			delete pWord;
		}
	}

	CObjectManager::DestroyObject(this);
}


//========================================
//
//	������̕ύX
//
//========================================
void CString::SetWord(const char* pszText)
{
	if (pszText == nullptr) return;
	m_pText = pszText;

	// ���X�g�̐擪�擾
	List<CWord> *pHead = m_wordList.GetHead();

	int nCharCnt;
	// �����N���X�|�C���g
	CWord *pWord = nullptr;
	// �e�N�X�`�����W
	Float2 texPos = { 0.0f, 0.0f };
	Float2 texSize = { 0.0f, 0.0f };
	// ���X�g�̃m�[�h
	List<CWord> *pNode = nullptr;

	// ���W
	Float3 wordPos = { 0.0f, 0.0f, 0.0f };
	// �I�t�Z�b�g���W
	float fOffSetX = 0;
	float fOffSetY = 0;

	// ������̒�������
	switch (m_eOffSetX)
	{
	case STRING::LEFT:
		fOffSetX = -m_wordSize.x / 2 - 1;
		break;
	case STRING::CENTER_X:
		fOffSetX = strlen(pszText) / 2.0f * m_wordSize.x / 2 - m_wordSize.x / 2;
		break;
	case STRING::RIGHT:
		fOffSetX = strlen(pszText) * m_wordSize.x / 2 - m_wordSize.x / 4;
		break;
	}


	// \n�̐�����
	switch (m_eOffSetY)
	{
	case STRING::TOP:
		fOffSetY = -m_wordSize.y / 2 - 1;
		break;
	case STRING::CENTER_Y:
		break;
	case STRING::DOWN:
		break;
	}

	// �I�t�Z�b�g���Z�b�g
	wordPos = m_transform.GetPos();
	wordPos.x -= fOffSetX;
	wordPos.y -= fOffSetY;

	// ������X�V
	for (pNode = pHead, nCharCnt = 0; pNode != nullptr && pszText[nCharCnt]; pNode = pNode->GetNext(), nCharCnt++)
	{
		SetWordData(pNode->GetThis(), pszText, nCharCnt, &wordPos, &m_wordSize, &m_wordColor);
	}

	// �V�K����
	if (pNode == nullptr)
	{
		for (; pszText[nCharCnt]; nCharCnt++)
		{
			pWord = CWord::Create();
			m_wordList.AddNode(pWord);
			SetWordData(pWord, pszText, nCharCnt, &wordPos, &m_wordSize, &m_wordColor);
		}
	}
	else
	{
		List<CWord> *pNextBack = nullptr;
		for ( ; pNode != nullptr; pNode = pNextBack)
		{
			pNextBack = pNode->GetNext();
			pWord = pNode->GetThis();

			if(m_wordList.DestroyNode(pNode))
				pWord->Destroy();
		}
	}

}


//========================================
//
//	�i�[������̃f�[�^�X�V
//
//========================================
void CString::SetWordData(CWord *pWord, const char *pszText, int nCharCnt, Float3 *pPos, Float2 *pSize, Float4 *pColor)
{
	int nFullWidthChar;	//�S�p�����̂Q�o�C�g���̃f�[�^
	int nOffset;
	int nCharPosX;
	int nCharPosY;
	static bool bHalf = false;

	// �e�N�X�`�����W
	Float2 texPos = { 0.0f, 0.0f };
	Float2 texSize = { 0.0f, 0.0f };

	//�S�p���ǂ����̔��f
	if ((0x7f < (unsigned char)pszText[nCharCnt] && (unsigned char)pszText[nCharCnt] < 0xa0) || 0xdf < (unsigned char)pszText[nCharCnt])
	{//�S�p������
		nFullWidthChar = ((unsigned char)pszText[nCharCnt] << 8) + (unsigned char)pszText[nCharCnt + 1];

		//----- �����R�[�h����摜�̕����̈ʒu�ɕϊ� -----
		nOffset = 0x8140;
		if (0xdf < (unsigned char)pszText[nCharCnt])	nOffset += 0x4000;

		nCharPosX = ((unsigned char)pszText[nCharCnt + 1] - (nOffset & 0x00ff)) % (FULL_FONT_WIDTH / FULL_FONT_SIZE_X + 1);
		if (0x7f < (unsigned char)pszText[nCharCnt + 1])
			if (0x9e >= (unsigned char)pszText[nCharCnt + 1])
				nCharPosX--;
		nCharPosY = (nFullWidthChar - nOffset) / (FULL_FONT_WIDTH / FULL_FONT_SIZE_Y);
		nCharPosY = ((unsigned char)pszText[nCharCnt] - (nOffset >> 8) + 1) * 2;
		if (0x9e >= (unsigned char)pszText[nCharCnt + 1])	nCharPosY--;
		nCharPosY--;

		//----- �������� -----
		// �e�N�X�`�����W
		texSize.x = 1.0f / (FULL_FONT_WIDTH / FULL_FONT_SIZE_X);
		texSize.y = 1.0f / (FULL_FONT_HEIGHT / FULL_FONT_SIZE_Y);
		texPos.x = texSize.x * nCharPosX;
		texPos.y = texSize.y * nCharPosY;

		// �n�[�t�t���O��true�̂Ƃ�
		if (bHalf) pPos->x += pSize->x / 4.0f;
		bHalf = false;

		// �X�V
		pWord->GetSprite()->SetTexPos(texPos);
		pWord->GetSprite()->SetTexSize(texSize);
		pWord->GetSprite()->SetColor(*pColor);
		pWord->GetTrans()->SetPos(*pPos);
		pWord->GetTrans()->SetSize(*pSize);
		pWord->SetTexture(&sm_halfFontTexture);

		// ���W
		pPos->x += pSize->x;

		nCharCnt++;	//�S�p�̎��̏����Ȃ̂ŕ��������������
	}
	else
	{//���p������
		//----- �����R�[�h����摜�̕����̈ʒu�ɕϊ� -----
		nCharPosX = ((unsigned char)pszText[nCharCnt] & 0x0f) % 0x10;
		nCharPosY = ((unsigned char)pszText[nCharCnt] >> 4);

		//----- �������� -----
		texSize.x = 1.0f / (HALF_FONT_WIDTH / HALF_FONT_SIZE_X);
		texSize.y = 1.0f / (HALF_FONT_HEIGHT / HALF_FONT_SIZE_Y);
		texPos.x = texSize.x * nCharPosX;
		texPos.y = texSize.y * nCharPosY;

		// �n�[�t�t���O��true�̂Ƃ�
		if (!bHalf) pPos->x -= pSize->x / 4.0f;
		bHalf = true;

		// �X�V
		pWord->GetSprite()->SetTexPos(texPos);
		pWord->GetSprite()->SetTexSize(texSize);
		pWord->GetSprite()->SetColor(*pColor);
		pWord->GetTrans()->SetPos(*pPos);
		pWord->GetTrans()->SetSize(Float2{pSize->x / 2, pSize->y});
		pWord->SetTexture(&sm_halfFontTexture);

		// ���W
		pPos->x += pSize->x / 2.0f;
	}
}

