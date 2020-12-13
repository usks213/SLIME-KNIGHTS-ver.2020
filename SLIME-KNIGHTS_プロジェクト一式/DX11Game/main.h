//=============================================================================
//
// �T���v������ [main.h]
// Author : KOSHI USAMI
//
//=============================================================================
#pragma once

#include <windows.h>
#include <tchar.h>
#include <mmsystem.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>
//#include <atltypes.h>	// ���L�N���X
#include <time.h>
#include <iostream>


// �{���̓w�b�_�ɏ����Ȃ������ǂ�
using namespace DirectX;

// �}�N����`
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x) {if(x){(x)->Release();x=nullptr;}}
#endif
#ifndef SAFE_DELETE
#define SAFE_DELETE(x) {if(x){delete(x);x=nullptr;}}
#endif
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(x) {if(x){delete[](x);x=nullptr;}}
#endif

#define SCREEN_WIDTH	(1280)				// �E�C���h�E�̕�
#define SCREEN_HEIGHT	(720)				// �E�C���h�E�̍���
#define SCREEN_CENTER_X	(SCREEN_WIDTH/2)	// �E�C���h�E�̒��S�w���W
#define SCREEN_CENTER_Y	(SCREEN_HEIGHT/2)	// �E�C���h�E�̒��S�x���W

#define	NUM_VERTEX		(4)					// ���_��
#define	NUM_POLYGON		(2)					// �|���S����

#define DEFAULT_OBJECT_SIZE (96)

#define FILE_PATH "rom/"


// ���_�t�H�[�}�b�g( ���_���W[2D] / ���ˌ� / �e�N�X�`�����W )
typedef struct {
	XMFLOAT3 vtx;		// ���_���W
	XMFLOAT4 diffuse;	// �g�U���ˌ�
	XMFLOAT2 tex;		// �e�N�X�`�����W
} VERTEX_2D;

// ���_�t�H�[�}�b�g
struct Vertex
{
	XMFLOAT3 pos;	// ���W
	XMFLOAT3 nor;	// �@��
	XMFLOAT2 tex;	// �e�N�X�`�����W
	XMFLOAT4 color;	// �F
};

// Switch�p
typedef XMFLOAT2 Float2;
typedef XMFLOAT3 Float3;
typedef XMFLOAT4 Float4;

// �v���g�^�C�v�錾
HWND GetMainWnd();
HINSTANCE GetInstance();
ID3D11Device* GetDevice();
ID3D11DeviceContext* GetDeviceContext();
//=============================================================================
//	�f�o�b�O�\���t���O
//=============================================================================
bool GetDebugFlag();
//=============================================================================
//	�f�o�b�O�\���t���O
//=============================================================================
void SetDebugFlag(bool bFlag);