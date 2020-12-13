//==================================================================
//									font.h
//	������\��
//
//==================================================================
//	author :	AT12A 05 �F�����W�V
//==================================================================
//	�J������
//
//	2020/08/08	������\���N���X�̍쐬
//
//===================================================================

#pragma once

//====== �C���N���[�h�� ======
#include "../main.h"
#include "object.h"
#include "List.h"
#include "word.h"


//===== �}�N����` =====
namespace STRING
{
	enum EOFFSET_X
	{
		LEFT,
		CENTER_X,
		RIGHT,

		MAX_OFFSET_X,
	};
	enum EOFFSET_Y
	{
		TOP,
		CENTER_Y,
		DOWN,

		MAX_OFFSET_Y,
	};

	//===== �N���X��` =====

	class CString : public CObject
	{
	public:
		CString();
		CString(const char* pszText, Float3 pos, Float2 size, Float4 color,
			EOFFSET_X eOffSetX = LEFT, EOFFSET_Y eOffSetY = TOP, bool bCamera = false);
		~CString();
		virtual void Update();
		virtual void Draw();

		static void Init();
		static void Uninit();

		static CString* Create(	const char* pszText, Float3 pos, Float2 size, Float4 color, 
								EOFFSET_X eOffSetX = LEFT, EOFFSET_Y eOffSetY = TOP, bool bCamera = false);
		static CString* Create();
		void Destroy();

		// �Z�b�g�֐�
		void SetWord(const char* pszText);
		void SetPos(Float3 pos) {
			m_transform.SetPos(pos);
			SetWord(m_pText);
		}
		void SetSize(Float2 size) {
			m_wordSize = size;
			SetWord(m_pText);
		}
		void SetColor(Float4 color) {
			m_wordColor = color;
			SetWord(m_pText);
		}
		void SetOffSet(EOFFSET_X eOffSetX, EOFFSET_Y eOffSetY) {
			m_eOffSetX = eOffSetX;
			m_eOffSetY = eOffSetY;
			SetWord(m_pText);
		}
		void SetCamera(bool bCamera) {
			m_bCamera = bCamera;
			SetWord(m_pText);
		}
		void SetLayer(LAYER::LAYER eLayer) { m_enLayer = eLayer; }

	private:
		static CTexture sm_fullFontTexture;		// �t���t�H���g�e�N�X�`��
		static CTexture sm_halfFontTexture;		// �n�[�t�t�H���g�e�N�X�`��

		// �����f�[�^
		List<CWord> m_wordList;				// �������X�g
		EOFFSET_X m_eOffSetX;				// �E�񂹍���
		EOFFSET_Y m_eOffSetY;				// ��񂹉���
		bool m_bCamera;
		Float2 m_wordSize;
		Float4 m_wordColor;
		const char* m_pText;

		// ������w�i�F���g����悤��


		static void SetWordData(CWord *pWord, const char *pszText, int nCharCnt, Float3 *pPos, Float2 *pSize, Float4 *pColor);
	};
}