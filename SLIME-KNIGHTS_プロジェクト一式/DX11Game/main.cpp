//=============================================================================
//
// DirectX11�x�[�X [main.cpp]
// Author : KOSHI USAMI
//
//=============================================================================
//
//	�J������
//
//	2020/05/30	DirectX11�̏�����
//	2020/05/31	�V�F�[�_�[�̍쐬�A�|���S���̕`��̍쐬
//	2020/06/01	3D�Ή�
//	2020/06/02	���C�e�B���O����
//	2020/06/04	�e�N�X�`���ǂݍ��݂̍쐬
//	2020/06/14	�I�u�W�F�N�g�����N���X�Ƃ���
//				�I�u�W�F�N�g�w���ɕύX
//	2020/06/16	���͏�������
//	2020/06/17	�t�F�[�h�C���E�t�F�[�h�A�E�g�̒ǉ�
//	2020/06/24	�R���W�����̒ǉ�
//	2020/07/01	��`�Ɖ~�̓����蔻��ǉ�
//	2020/07/08	�R���W�����N���X�̍쐬
//	2020/07/08	�A�j���[�^�[�N���X�̍쐬
//	2020/07/10	�A�j���[�V�����N���X�̍쐬
//	2020/07/14	�t�B�[���h�N���X�̍쐬
//	2020/07/15	���W�b�h�{�f�B�N���X�쐬
//	2020/07/16	�V�[���Ǘ��N���X�쐬
//	2020/07/17	�o���b�g�N���X�쐬
//	2020/07/18	�^�C�g���V�[���A�Q�[���V�[���̒ǉ�
//	2020/07/24	2D�����̃x�[�X���ASwitch�Ƃ̌݊���
//				�g�����X�t�H�[���ƃX�v���C�g�̍쐬
//	2020/07/31	���C���[�������N�C�b�N�\�[�g��
//	2020/08/01	�����蔻����l���؂�
//	2020/08/02	�L�����N�^�[�A�N�V�����N���X�̍쐬
//				�X�e�[�^�X�N���X�̍쐬
//	2020/08/03	�U���x�[�X�N���X�̍쐬
//	2020/08/08	������\���N���X�̍쐬
//	2020/08/12	�v���C���[�̃C���X�g�̎���
//	2020/08/13	�v���C���[�̎�̓�����J�ڂ̐���
//	2020/08/14	�E�F�|���N���X�̍쐬
//	2020/08/15	�q�b�g�X�g�b�v
//	2020/08/18	�G�l�~�[�X���C���̍쐬
//	2020/08/19	�G�l�~�[�E�B���O�̍쐬
//	2020/08/20	�G�l�~�[�����X�̍쐬
//	2020/08/23	�X�e�[�W�Ǘ��V�X�e��
//	2020/08/25	�X�e�[�W���C�J�[�N���X�̍쐬
//	2020/08/26	�����_���X�e�[�W��������
//	2020/08/29	�t���A�N���X�̍쐬	
//	2020/08/29	�X�e�[�W���C�A�E�g�̍쐬	
//	2020/09/02	����t�����i���j
//	2020/09/03	�X�e�[�W�̃��C�A�E�g����
//	2020/09/04	�~�j�}�b�v
//	2020/09/05	�{�X�����A�{�X(��)�A
//	2020/09/05	�`���[�g���A���}�b�v�A�X�^�[�g�}�b�v�A���x���A�b�v�e�L�X�g�A
//				�o���l�ʁAUI�A
//	2020/09/06	�f�J�H�X���C���A�|�X���C���A���C�g�A�t�@�C���[�A�g�Q�A�L�[
//	2020/09/07	���U���gUI�̎���
//	2020/09/08	�{�X��蒼���A�t�B�[���h�N���X�̍�蒼���A���[�r�[UI
//	2020/09/10	����̕ύX
//	2020/09/12	�o���b�g�̃e�N�X�`����ύX
//				�����I�I�i�_�O�Q�O�^�j
//	2020/10/27	���G�t�F�N�g�̕ύX
//	2020/10/28	�R���{�̒ǉ�(�e�X�g)
//	2020/11/01	�R���{�E�N���e�B�J���̒ǉ�
//	2020/11/29	U22�v���R�� CSJA�܁I�I�@���肪�Ƃ��������܂��I�I
//	2020/12/13	���J�Ɍ����ď����ҏW
//
//=============================================================================

//===== �C���N���[�h�� =====
#include "main.h"
#include "resource.h"
#include "DirectX11.h"
#include "input.h"
#include "source/sceneManager.h"
#include "Sound.h"
#include "sprite.h"
#include "source/string.h"


//-------- ���C�u�����̃����N
#pragma comment(lib, "winmm")
#pragma comment(lib, "imm32")
#pragma comment(lib, "d3d11")

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CLASS_NAME				_T("AppClass")					// �E�C���h�E�̃N���X��
#define WINDOW_NAME				_T("SLIME KNIGHTS")				// �E�C���h�E�̃L���v�V������
#define FRAME_RATE		(60)

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
// (�Ȃ�)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
int OnCreate(HWND hWnd, LPCREATESTRUCT lpcs);
HRESULT Init(HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
HWND						g_hWnd;					// ���C�� �E�B���h�E �n���h��
HINSTANCE					g_hInst;				// �C���X�^���X �n���h��

ID3D11Device*				g_pDevice;				// �f�o�C�X(�ݒ����)
ID3D11DeviceContext*		g_pDeviceContext;		// �f�o�C�X �R���e�L�X�g(�`�����)
IDXGISwapChain*				g_pSwapChain;			// �X���b�v�`�F�[��(�_�u���o�b�t�@�����O�p)
ID3D11RenderTargetView*		g_pRenderTargetView;	// �t���[���o�b�t�@
UINT						g_uSyncInterval = 0;	// �������� (0:��, 1:�L)
ID3D11BlendState*			g_pBlendState;			// �u�����h �X�e�[�g

bool g_bDebug = false;		// �f�o�b�O�\���t���O
int							g_nCountFPS;			// FPS�J�E���^
//STRING::CString *g_pString;							// FPS������


//=============================================================================
// ���C���֐�
//=============================================================================
int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);	// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j
	UNREFERENCED_PARAMETER(lpCmdLine);		// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j

	// COM�̏�����	COM�R���|�[�l���g�̎g�p
	HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	if (FAILED(hr)) return -1;

	WNDCLASSEX wcex = {
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MAINFRM)),
		LoadCursor(nullptr, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		nullptr,
		CLASS_NAME,
		nullptr
	};
	MSG		msg;

	// �C���X�^���X �n���h���ۑ�
	g_hInst = hInstance;

	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �N���C�A���g�̈�T�C�Y����E�B���h�E �T�C�Y�Z�o
	DWORD dwStyle = WS_OVERLAPPED | WS_CAPTION
		| WS_SYSMENU | WS_BORDER | WS_MINIMIZEBOX;
	DWORD dwExStyle = 0;
	RECT rc = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	AdjustWindowRectEx(&rc, dwStyle, FALSE, dwExStyle);

	// �E�B���h�E�̍쐬
	g_hWnd = CreateWindowEx(dwExStyle,
		CLASS_NAME,
		WINDOW_NAME,
		dwStyle,
		CW_USEDEFAULT,		// �E�B���h�E�̍����W
		CW_USEDEFAULT,		// �E�B���h�E�̏���W
		rc.right - rc.left,	// �E�B���h�E����
		rc.bottom - rc.top,	// �E�B���h�E�c��
		nullptr,
		nullptr,
		hInstance,
		nullptr);

	// �E�C���h�E�̕\��
	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);

	// DirectX�̏�����(�E�B���h�E���쐬���Ă���s��)
	if (FAILED(Init(g_hWnd, true))) {
		return -1;
	}
	// �t���[���J�E���g������
	timeBeginPeriod(1);			// ����\�ݒ�

	// FPS�Z�o�p���[�N
	DWORD dwExecLastTime = timeGetTime();
	DWORD dwFPSLastTime = timeGetTime();
	DWORD dwCurrentTime = 0;
	DWORD dwFrameCount = 0;

	// ���b�Z�[�W���[�v
	for (;;) {
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) {
				// PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
				break;
			}
			else {
				// ���b�Z�[�W�̖|��ƃf�B�X�p�b�`
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			// ���ݎ��Ԃ��擾
			dwCurrentTime = timeGetTime();
			// 0.5�b���Ƃ�
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{
				g_nCountFPS = dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / FRAME_RATE))
			{
				dwExecLastTime = dwCurrentTime;

				// �X�V����
				Update();
				// �`�揈��
				Draw();
				++dwFrameCount;
			}
			//// �`�揈��
			//Draw();
			//++dwFrameCount;
		}
	}

	// �I������
	Uninit();

	// �t���[���J�E���^�����Ƃɖ߂�
	timeEndPeriod(1);

	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, g_hInst);

	// COM�̉��
	CoUninitialize();

	return (int)msg.wParam;
}

//=============================================================================
// �v���V�[�W��
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_CREATE:					//----- �E�B���h�E���������ꂽ
		return OnCreate(hWnd, (LPCREATESTRUCT)lParam);
	case WM_DESTROY:				//----- �E�B���h�E�j���w��������
		PostQuitMessage(0);				// �V�X�e���ɃX���b�h�̏I����v��
		return 0;
	case WM_KEYDOWN:				//----- �L�[�{�[�h�������ꂽ
		switch (wParam) {
		case VK_ESCAPE:					// [ESC]�L�[�������ꂽ
			PostMessage(hWnd, WM_CLOSE, 0, 0);	// [x]�������ꂽ�悤�ɐU����
			return 0;
		}
		break;
	case WM_MENUCHAR:
		return MNC_CLOSE << 16;			// [Alt]+[Enter]����BEEP��}�~
	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//=============================================================================
// WM_CREATE���b�Z�[�W�n���h��
//=============================================================================
int OnCreate(HWND hWnd, LPCREATESTRUCT lpcs)
{
	// �N���C�A���g�̈�T�C�Y��SCREEN_WIDTH�~SCREEN_HEIGHT�ɍĐݒ�.
	RECT rcClnt;
	GetClientRect(hWnd, &rcClnt);
	rcClnt.right -= rcClnt.left;
	rcClnt.bottom -= rcClnt.top;
	if (rcClnt.right != SCREEN_WIDTH || rcClnt.bottom != SCREEN_HEIGHT) {
		RECT rcWnd;
		GetWindowRect(hWnd, &rcWnd);
		SIZE sizeWnd;
		sizeWnd.cx = (rcWnd.right - rcWnd.left) - rcClnt.right + SCREEN_WIDTH;
		sizeWnd.cy = (rcWnd.bottom - rcWnd.top) - rcClnt.bottom + SCREEN_HEIGHT;
		SetWindowPos(hWnd, nullptr, 0, 0, sizeWnd.cx, sizeWnd.cy, SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER);
	}

	// IME������
	ImmAssociateContext(hWnd, nullptr);

	return 0;	// -1��Ԃ���CreateWindow(Ex)�����s����.
}


//=============================================================================
// ����������
//=============================================================================
HRESULT Init(HWND hWnd, BOOL bWindow)
{
	HRESULT hr = S_OK;;

	// ����
	srand(time(NULL));

	// DirectX11�̏�����
	hr = CDirectX11::Create(hWnd);
	// �G���[����
	if (FAILED(hr)) return hr;

	// ���͏���������
	hr = InitInput();
	// �G���[����
	if (FAILED(hr)) return hr;

	// �T�E���h�̏�����
	hr = CSound::InitSound();
	// �G���[����
	if (FAILED(hr)) return hr;

	// �X�v���C�g�̏�����
	CSprite::Init();

	// �V�[���̏�����
	//hr = CSceneManager::Init();
	CSceneManager::Init();
	// �G���[����
	if (FAILED(hr)) return hr;

	// FPS�\���t���[��
	/*char szFPS[30];
	std::sprintf(szFPS, "FPS = %d", g_nCountFPS);
	g_pString = STRING::CString::Create(szFPS, Float3{ -SCREEN_CENTER_X, -SCREEN_CENTER_Y / 3 * 1.5f, 0 }, Float2{ 50, 50 }, Float4{ 0,1,0,1 });
	g_pString->SetLayer(LAYER::MAX_LAYER);*/

	return hr;
}


//=============================================================================
// �I������
//=============================================================================
void Uninit(void)
{
	
	// �V�[���̏I������
	CSceneManager::Uninit();

	// �T�E���h�̏I������
	CSound::UninitSound();

	// ���͏I������
	UninitInput();

	// Direct11�̏I������
	CDirectX11::Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void Update(void)
{
	// TODO: �����ɍX�V�������L�q.

	// ���͍X�V����
	UpdateInput();

	// �V�[���̍X�V����
	CSceneManager::Update();

	//// FPS�\��
	//char szFPS[20];
	//std::sprintf(szFPS, "FPS = %d", g_nCountFPS);
	//g_pString->SetWord(szFPS);

	// �f�o�b�O�\��
#ifdef _WIN32
	if (GetKeyTrigger(VK_O))
		g_bDebug ^= 1;
#endif // _WIN32

}


//=============================================================================
// �`�揈��
//=============================================================================
void Draw(void)
{
	// DirectX11�̕`��J�n����
	CDirectX11::StartRender();

	// ============ TODO: �����ɕ`�揈�����L�q.================

	// �V�[���̕`�揈��
	CSceneManager::Draw();
	//FPS
	/*if (g_pString)
	{
		g_pString->Destroy();
		g_pString = nullptr;
	}*/


	// ========================================================

	// DirectX11�̕`��I������
	CDirectX11::EndRender();
}


//=============================================================================
//	�E�B���h�E�n���h��
//=============================================================================
HWND GetMainWnd()
{
	return g_hWnd;
}


//=============================================================================
//	�f�o�b�O�\���t���O
//=============================================================================
bool GetDebugFlag()
{
	return g_bDebug;
}

//=============================================================================
//	�f�o�b�O�\���t���O
//=============================================================================
void SetDebugFlag(bool bFlag)
{
	g_bDebug = bFlag;
}
