//=============================================================================
//
// モデル [model.h]
// Author : KOSHI USAMI
//
//=============================================================================
//
//	開発履歴
//
//	2020/06/21	3Dモデル	
//
//=============================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

//===== インクルード部 =====
#include "main.h"


//====== クラス定義 =====
class CModel
{
public:
	CModel();
	~CModel();
	void CreateSphereModel(int nSegment);
	void CreateCubeModel();
	void CreatePlaneModel();
	void DestroyModel();

	// ゲット関数
	Vertex* GetVertexList() { return m_pVertexList; }
	WORD* GetIndexList() { return m_pIndexList; }
	int GetVertexCount() { return m_nVertexCount; }
	int GetIndexCount() { return m_nIndexCount; }

private:
	Vertex*	m_pVertexList;
	WORD*	m_pIndexList;
	int m_nVertexCount;
	int m_nIndexCount;
};


#endif // !_MODEL_H_
