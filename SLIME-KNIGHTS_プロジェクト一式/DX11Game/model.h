//=============================================================================
//
// ���f�� [model.h]
// Author : KOSHI USAMI
//
//=============================================================================
//
//	�J������
//
//	2020/06/21	3D���f��	
//
//=============================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

//===== �C���N���[�h�� =====
#include "main.h"


//====== �N���X��` =====
class CModel
{
public:
	CModel();
	~CModel();
	void CreateSphereModel(int nSegment);
	void CreateCubeModel();
	void CreatePlaneModel();
	void DestroyModel();

	// �Q�b�g�֐�
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
