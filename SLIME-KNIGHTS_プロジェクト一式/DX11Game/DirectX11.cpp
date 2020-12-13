//=============================================================================
//
// DirectX11������ [sample.cpp]
// Author : KOSHI USAMI
//
//=============================================================================
//
//	�J������
//
//	2020/05/30	DirectX11�̏�����
//
//=============================================================================

//===== �C���N���[�h�� =====
#include "DirectX11.h"
#include "polygon.h"


//===== �O���[�o���ϐ� =====

ID3D11Device*			CDirectX11::m_pDevice;				// �f�o�C�X
ID3D11DeviceContext*	CDirectX11::m_pDeviceContext;		// �f�o�C�X�R���e�L�X�g
IDXGISwapChain*			CDirectX11::m_pSwapChain;			// �X���b�v�`�F�[��
ID3D11RenderTargetView*	CDirectX11::m_pRenderTargetView;	// �����_�[�^�[�Q�b�g�r���[(�����_�����O�p�C�v���C������A�E�g�v�b�g�����s�N�Z�����)
ID3D11Texture2D*		CDirectX11::m_pDepthStencilTexture;	// �[�x/�X�e���V���o�b�t�@
ID3D11DepthStencilView*	CDirectX11::m_pDepthStencilView;	// �[�x/�X�e���V���r���[
D3D11_VIEWPORT			CDirectX11::m_Viewport;				// �r���[�|�[�g
ID3D11BlendState*		CDirectX11::m_pBlendState[MAX_BLENDSTATE];			// �u�����h �X�e�[�g


//=============================
// �R���X�g���N�^
//=============================
CDirectX11::CDirectX11()
{
	// ���\�b�h�̏�����
	m_pDevice = NULL;
	m_pDeviceContext = NULL;
	m_pSwapChain = NULL;
	m_pRenderTargetView = NULL;

	m_pDepthStencilTexture = NULL;	// �[�x/�X�e���V���o�b�t�@
	m_pDepthStencilView = NULL;		// �[�x/�X�e���V���r���[
}


//=============================
// �f�X�g���N�^
//=============================
CDirectX11::~CDirectX11()
{
	// �I������
	Release();
}


//=========================================
//	DirectX �������֐�
//=========================================
HRESULT CDirectX11::Create(HWND hwnd)
{
	HRESULT hr;

	// �L���Ƀ����^�C�����C���[
	UINT flags = 0;
#ifdef _DEBUG
	flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif // _DEBUG
	
	// �@�\���x����z��Ŏw��
	D3D_FEATURE_LEVEL pFeatureLevel[] = { D3D_FEATURE_LEVEL_11_1, D3D_FEATURE_LEVEL_11_0, };
	// �쐬���ꂽ�f�o�C�X�̋@�\���x�����󂯎��ϐ�
	D3D_FEATURE_LEVEL featureLevel;

	// �N���C�A���g�̈�̃T�C�Y���v�Z���邽�� (���N�^���O��)
	//CRect rect;
	// �X���b�v�`�F�[���̐���
	DXGI_SWAP_CHAIN_DESC scDesc;

	// �N���C�A���g�̈���擾
	//::GetClientRect(hwnd, &rect);

	// �X���b�v�`�F�[���̏�����
	ZeroMemory(&scDesc, sizeof(scDesc));
	scDesc.BufferCount			= 1;				// �X���b�v�`�F�[���̃o�b�t�@��
	scDesc.BufferDesc.Width		= SCREEN_WIDTH;		// �X���b�v�`�F�[���̃o�b�t�@�T�C�Y(����)
	scDesc.BufferDesc.Height	= SCREEN_HEIGHT;	// �X���b�v�`�F�[���̃o�b�t�@�T�C�Y(�c��)
	scDesc.BufferDesc.Format	= DXGI_FORMAT_R8G8B8A8_UNORM;			// �X���b�v�`�F�[���̃o�b�t�@�t�H�[�}�b�g
	scDesc.BufferDesc.RefreshRate.Numerator	  = 60;						// ���t���b�V�����[�g�̕���
	scDesc.BufferDesc.RefreshRate.Denominator =  1;						// ���t���b�V�����[�g�̕��q
	scDesc.BufferUsage			= DXGI_USAGE_RENDER_TARGET_OUTPUT;		// �o�b�t�@�������_�[�^�[�Q�b�g�Ƃ��Ďg�p
	scDesc.OutputWindow			= hwnd;				// �E�B���h�E�n���h��
	scDesc.SampleDesc.Count		= 1;				// �}���`�T���v�����O�̃s�N�Z���P�ʂ̐�
	scDesc.SampleDesc.Quality	= 0;				// �}���`�T���v�����O�̕i��
	scDesc.Windowed				= TRUE;				// �E�B���h�E���[�h

	// �f�o�C�X�ƃX���b�v�`�F�[���̐����A������
	hr = D3D11CreateDeviceAndSwapChain(
		NULL,						// �A�_�v�^�[�̃|�C���^�BNULL���ƋK��̃A�_�v�^
		D3D_DRIVER_TYPE_HARDWARE,	// �n�[�h�E�F�A���g��D3D_DRIVER_TYPE_HARDWARE���w��
		NULL,						// DeviceType���n�[�h�E�F�A�̏ꍇ��NULL
		flags,						// �L���ɂ��郉���^�C�����C���[
		pFeatureLevel,				// �쐬�������݂�@�\���x���̏������w�肷��z��
		_countof(pFeatureLevel),	// �쐬�������݂�@�\���x���̏������w�肷��z��̐�(����)
		D3D11_SDK_VERSION,			// D3D11_SDK_VERSION���w��
		&scDesc,					// �X���b�v�`�F�[���̏������p�����[�^�[
		&m_pSwapChain,				// �쐬�����X���b�v�`�F�[��
		&m_pDevice,					// �쐬�����f�o�C�X
		&featureLevel,				// �쐬�����f�o�C�X�̋@�\���x��
		&m_pDeviceContext			// �쐬�����f�o�C�X�R���e�L�X�g
	);
	// �G���[����
	if (FAILED(hr)) return hr;


	// �o�b�N�o�b�t�@�̐���
	// �o�b�N�o�b�t�@�̃|�C���^
	ID3D11Texture2D* pBackBuffer;

	// �X���b�v�`�F�[���̃o�b�t�@�̂P���擾(�`��p�̃������m��)
	hr = m_pSwapChain->GetBuffer(
		0,							// �o�b�t�@�̃C���f�b�N�X(��{��0)						
		__uuidof(ID3D11Texture2D),	// �擾����o�b�t�@�̃C���^�[�t�F�[�XID
		(LPVOID*)&pBackBuffer		// �o�b�t�@�̎擾��
	);
	// �G���[����
	if (FAILED(hr)) return hr;

	// �����_�[�^�[�Q�b�g�r���[�̐���
	hr = m_pDevice->CreateRenderTargetView(
		pBackBuffer,			// �쐬����o�b�t�@�̃��\�[�X
		NULL,					// �쐬����View�̐ݒ���e�f�[�^�̎w��(NULL�Ńf�t�H���g�ݒ�)
		&m_pRenderTargetView);	// �쐬���ꂽRenderTargetView�̊i�[��
	// �G���[����
	if (FAILED(hr)) return hr;

	// Target�̎擾���I������̂Ńe�N�X�`�����\�[�X(�o�b�N�o�b�t�@)�̉��
	pBackBuffer->Release();		
	


	// �[�x�X�e���V���o�b�t�@�p�̃e�N�X�`�����\�[�X���쐬
	D3D11_TEXTURE2D_DESC txDesc;
	// �[�x�X�e���V���o�b�t�@�̏�����
	ZeroMemory(&txDesc, sizeof(txDesc));
	txDesc.Width				= SCREEN_WIDTH;		// �o�b�N�o�b�t�@�Ɠ����T�C�Y���w��(�o�b�t�@�̉���)
	txDesc.Height				= SCREEN_HEIGHT;	// �o�b�N�o�b�t�@�Ɠ����T�C�Y���w��(�o�b�t�@�̏c��)
	txDesc.MipLevels			= 1;				// �~�b�v�}�b�v�̃��x���w��
	txDesc.ArraySize			= 1;				// �e�N�X�`���z��̃T�C�Y�w��
	txDesc.Format				= DXGI_FORMAT_D24_UNORM_S8_UINT;	// �e�N�X�`���̃t�H�[�}�b�g(DXGI_FORMAT_D24_UNORM_S8_UINT)���g����Depth24bit Stencil8bit
	txDesc.SampleDesc.Count		= 1;				// �}���`�T���v�����O�̃s�N�Z���P�ʂ̐�(DepthStencil�o�b�t�@�ł͎g��Ȃ�)
	txDesc.SampleDesc.Quality	= 0;				// �}���`�T���v�����O�̕i��(DepthStencil�o�b�t�@�ł͎g��Ȃ�)
	txDesc.Usage				= D3D11_USAGE_DEFAULT;				// �e�N�X�`���̎g�p���@(�f�t�H���g)
	txDesc.BindFlags			= D3D11_BIND_DEPTH_STENCIL;			// Bind�ݒ��Depth,Stencil�ɐݒ�
	txDesc.CPUAccessFlags		= 0;				// ���\�[�X�ւ�CPU�̃A�N�Z�X�����ɂ��Ă̐ݒ� (�f�t�H���g��0�H)
	txDesc.MiscFlags			= 0;				// ���\�[�X�I�v�V�����̃t���O(�f�t�H���g��0�H)

	// Texture_Desc�̏��Ńe�N�X�`�����쐬
	hr = m_pDevice->CreateTexture2D(
		&txDesc,					// �쐬����e�N�X�`���̏ڍ׏��
		NULL,						// �e�N�X�`���̏��ɕt������f�[�^�w��(�ǂݍ��񂾉摜�f�[�^���w�肵����)
		&m_pDepthStencilTexture);	// �쐬���ꂽTexture�f�[�^���i�[���邽�߂̃|�C���^
	// �G���[����
	if (FAILED(hr)) return hr;

	// �[�x�X�e���V���r���[�̍쐬
	D3D11_DEPTH_STENCIL_VIEW_DESC dsDesc;
	// �[�x�X�e���V���r���[�̏�����
	ZeroMemory(&dsDesc, sizeof(dsDesc));
	dsDesc.Format = txDesc.Format;							// View�̃t�H�[�}�b�g(Texture�̂��̂��g�p)
	dsDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;	// DSV���������ł����Texture�̎�ނ�ݒ肷��l
	dsDesc.Texture2D.MipSlice = 0;							// �ŏ��Ɏg�p����~�b�v�}�b�v�̃��x�����w��

	// CreateTexture2D��Dsv_Desc����Depth��Stencil�o�b�t�@�����
	//hr = m_pDevice->CreateDepthStencilView(
	//	m_pDepthStencilTexture,		// DSV�Ƃ��Ďg�p�����Texture
	//	&dsDesc,					// DSV�̐ݒ�
	//	&m_pDepthStencilView);		// ID3D11DepthStencilView�̏o�͐�
	//// �G���[����
	//if (FAILED(hr)) return hr;

	// �e�^�[�Q�b�g�r���[�������_�[�^�[�Q�b�g�ɐݒ�
	m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);


	//�r���[�|�[�g�ݒ�
	m_Viewport.TopLeftX = 0;
	m_Viewport.TopLeftY = 0;
	m_Viewport.Width = (FLOAT)SCREEN_WIDTH;
	m_Viewport.Height = (FLOAT)SCREEN_HEIGHT;
	m_Viewport.MinDepth = 0.0f;
	m_Viewport.MaxDepth = 1.0f;

	// �r���[�|�[�g���Z�b�g
	m_pDeviceContext->RSSetViewports(1, &m_Viewport);


	// ���X�^���C�Y�ݒ�
	D3D11_RASTERIZER_DESC rd;
	ZeroMemory(&rd, sizeof(rd));
	rd.CullMode = D3D11_CULL_NONE;	// �J�����O���s��Ȃ�
	rd.FillMode = D3D11_FILL_SOLID;	// �|���S����h��Ԃ�
	ID3D11RasterizerState* pRs = nullptr;
	m_pDevice->CreateRasterizerState(&rd, &pRs);
	m_pDeviceContext->RSSetState(pRs);
	SAFE_RELEASE(pRs);
	// �u�����h �X�e�[�g����
	D3D11_BLEND_DESC BlendDesc;
	ZeroMemory(&BlendDesc, sizeof(BlendDesc));
	BlendDesc.AlphaToCoverageEnable = FALSE;
	BlendDesc.IndependentBlendEnable = FALSE;
	BlendDesc.RenderTarget[0].BlendEnable = FALSE;
	BlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	BlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	BlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	BlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	BlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	// �����������Ȃ�
	m_pDevice->CreateBlendState(&BlendDesc, &m_pBlendState[0]);
	// ����������
	BlendDesc.RenderTarget[0].BlendEnable = TRUE;
	m_pDevice->CreateBlendState(&BlendDesc, &m_pBlendState[1]);
	// ���Z����
	BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	m_pDevice->CreateBlendState(&BlendDesc, &m_pBlendState[2]);
	// ���Z����
	BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_REV_SUBTRACT;
	m_pDevice->CreateBlendState(&BlendDesc, &m_pBlendState[3]);

	// �u�����h�X�e�C�g�̃Z�b�g
	SetBlendState(BS_ALPHABLEND);

	return hr;
}


//=============================
// DirectX �I���֐�
//=============================
void CDirectX11::Release()
{
	//===== �e���\�[�X�̏I������ =====

	// �f�o�C�X�R���e�L�X�g�̃N���A
	if (m_pDeviceContext)	m_pDeviceContext->ClearState();

	// �[�x�X�e���V���o�b�t�@�r���[�̉��
	if (NULL != m_pDepthStencilView)
	{
		m_pDepthStencilView->Release();
		m_pDepthStencilView = NULL;
	}

	// �[�x�X�e���V���o�b�t�@�̉��
	if (NULL != m_pDepthStencilTexture)
	{
		m_pDepthStencilTexture->Release();
		m_pDepthStencilTexture = NULL;
	}

	// �����_�[�^�[�Q�b�g�r���[�̉��
	if (NULL != m_pRenderTargetView)
	{
		m_pRenderTargetView->Release();
		m_pRenderTargetView = NULL;
	}

	// �X���b�v�`�F�[���̉��
	if (NULL != m_pSwapChain)
	{
		m_pSwapChain->Release();
		m_pSwapChain = NULL;
	}

	// �f�o�C�X�R���e�L�X�g�̉��
	if (NULL != m_pDeviceContext)
	{
		m_pDeviceContext->Release();
		m_pDeviceContext = NULL;
	}

	// �f�o�C�X�̉��
	if (NULL != m_pDevice)
	{
		m_pDevice->Release();
		m_pDevice = NULL;
	}
}


//===========================
//	DirectX �`��J�n�֐�
//===========================
void CDirectX11::StartRender()
{
	// ���S����
	if (NULL == m_pDevice) return;
	if (NULL == m_pDeviceContext) return;
	if (NULL == m_pRenderTargetView) return;

	// �o�b�N�o�b�t�@���N���A����F
	float clearColor[4] = { 0.117647f, 0.254902f, 0.352941f, 1.0f };
	// �o�b�N�o�b�t�@�̃N���A
	m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetView, clearColor);
	// �[�x�X�e���V���o�b�t�@�̃N���A
	//m_pDeviceContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	// ============ TODO: �����ɕ`�揈�����L�q.================
	
	//g_polygon.Draw(m_pDeviceContext, &g_shader);

	// ========================================================
}

//===========================
//	DirectX �`��J�n�֐�
//===========================
void CDirectX11::EndRender()
{
	// ���S����
	if (NULL == m_pSwapChain) return;

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	m_pSwapChain->Present(1, 0);
}

//=======================================
//
//	�u�����h�X�e�C�g�̃Z�b�g
//
//=======================================
void CDirectX11::SetBlendState(int nBlendState)
{
	if (nBlendState >= 0 && nBlendState < MAX_BLENDSTATE)
	{
		float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
		m_pDeviceContext->OMSetBlendState(m_pBlendState[nBlendState], blendFactor, 0xffffffff);
	}
}