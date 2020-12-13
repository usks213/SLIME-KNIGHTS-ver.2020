//==================================================================
//									font.h
//	文字列表示
//
//==================================================================
//	author :	AT12A 05 宇佐美晃之
//==================================================================
//	開発履歴
//
//	2020/08/08	文字列表示クラスの作成
//
//===================================================================

#pragma once

//====== インクルード部 ======
#include "../main.h"
#include "object.h"
#include "List.h"
#include "word.h"


//===== マクロ定義 =====
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

	//===== クラス定義 =====

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

		// セット関数
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
		static CTexture sm_fullFontTexture;		// フルフォントテクスチャ
		static CTexture sm_halfFontTexture;		// ハーフフォントテクスチャ

		// 文字データ
		List<CWord> m_wordList;				// 文字リスト
		EOFFSET_X m_eOffSetX;				// 右寄せ左寄せ
		EOFFSET_Y m_eOffSetY;				// 上寄せ下寄せ
		bool m_bCamera;
		Float2 m_wordSize;
		Float4 m_wordColor;
		const char* m_pText;

		// 文字列背景色を使えるように


		static void SetWordData(CWord *pWord, const char *pszText, int nCharCnt, Float3 *pPos, Float2 *pSize, Float4 *pColor);
	};
}