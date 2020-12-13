//=============================================================================
//
// DirectX11������ [polygon.cpp]
// Author : KOSHI USAMI
//
//=============================================================================
//
//	�J������
//
//	2020/05/31	�|���S���`��̍쐬
//	2020/06/01	3D�Ή�
//	2020/06/02	���C�e�B���O����
//	2020/06/04	�e�N�X�`������
//
//=============================================================================


//===== �C���N���[�h�� =====
#include "polygon.h"
#include "texture.h"
#include "model.h"
#include "input.h"
#include "source/camera.h"
#include "sprite.h"


//===== �}�N����` =====

//===== �\���� =====

// �萔�o�b�t�@ (�ϊ��s��)
struct ConstantMatrixBuffer
{
	DirectX::XMFLOAT4X4 mWorld;			// ���[���h�ϊ��s��
	DirectX::XMFLOAT4X4 mView;			// �r���[�ϊ��s��
	DirectX::XMFLOAT4X4 mProjection;	// �v���W�F�N�V�����ϊ��s��
	DirectX::XMFLOAT4X4 mTexture;		// UV���W�ϊ��s��
};

// �萔�o�b�t�@(�J���[)
struct ConstantColor
{
	Float4 color;
};

// ���̓��C�A�E�g
D3D11_INPUT_ELEMENT_DESC g_VertexDesc[] = {
	{
		"POSITION",						// �Z�}���e�B�b�N��
		0,								// �Z�}���e�B�b�N�ԍ�
		DXGI_FORMAT_R32G32B32_FLOAT,	// �t�H�[�}�b�g
		0,								// ���̓X���b�g�ԍ�
		0,								// �v�f����擪�܂ł̃I�t�Z�b�g�l
		D3D11_INPUT_PER_VERTEX_DATA	,	// ���̓f�[�^�̎��
		0,								// �J��Ԃ���(���_�f�[�^�̎���0)
	},
	{
		"NORMAL",						// �Z�}���e�B�b�N��
		0,								// �Z�}���e�B�b�N�ԍ�
		DXGI_FORMAT_R32G32B32_FLOAT,	// �t�H�[�}�b�g
		0,								// ���̓X���b�g�ԍ�
		D3D11_APPEND_ALIGNED_ELEMENT,	// �v�f����擪�܂ł̃I�t�Z�b�g�l(�����Ōv�Z���Ă����)
		D3D11_INPUT_PER_VERTEX_DATA	,	// ���̓f�[�^�̎��
		0,								// �J��Ԃ���(���_�f�[�^�̎���0)
	},
	{
		"TEXCOORD",						// �Z�}���e�B�b�N��
		0,								// �Z�}���e�B�b�N�ԍ�
		DXGI_FORMAT_R32G32_FLOAT,		// �t�H�[�}�b�g
		0,								// ���̓X���b�g�ԍ�
		D3D11_APPEND_ALIGNED_ELEMENT,	// �v�f����擪�܂ł̃I�t�Z�b�g�l(�����Ōv�Z���Ă����)
		D3D11_INPUT_PER_VERTEX_DATA	,	// ���̓f�[�^�̎��
		0,								// �J��Ԃ���(���_�f�[�^�̎���0)
	},
	{
		"COLOR",						// �Z�}���e�B�b�N��
		0,								// �Z�}���e�B�b�N�ԍ�
		DXGI_FORMAT_R32G32B32A32_FLOAT,	// �t�H�[�}�b�g
		0,								// ���̓X���b�g�ԍ�
		D3D11_APPEND_ALIGNED_ELEMENT,	// �v�f����擪�܂ł̃I�t�Z�b�g�l(�����Ōv�Z���Ă����)
		D3D11_INPUT_PER_VERTEX_DATA	,	// ���̓f�[�^�̎��
		0,								// �J��Ԃ���(���_�f�[�^�̎���0)
	},
};


//==========================
//	�R���X�g���N�^
//==========================
CPolygon::CPolygon()
{
	// ���_�o�b�t�@�̏�����
	m_pVertexBuffer	 = NULL;

	// �C���f�b�N�X�o�b�t�@�̏�����
	m_pIndexBuffer	 = NULL;

	// �R���X�^���g�o�b�t�@(�s����W�ϊ�)�̏�����
	m_pConstantMatrixBuffer = NULL;	

	// �R���X�^���g�o�b�t�@(�J���[)�̏�����
	m_pConstantColorBuffer = NULL;

	// ���̓��C�A�E�g�̏�����
	m_pInputLayout	 = NULL;

	// �O���f�[�^
	m_pModel = nullptr;
	m_pShader = nullptr;

}


//==========================
//	�f�X�g���N�^
//==========================
CPolygon::~CPolygon()
{
	// ���_�o�b�t�@�̉��
	if (NULL != m_pVertexBuffer)
	{
		m_pVertexBuffer->Release();
		m_pVertexBuffer = nullptr;
	}

	// �C���f�b�N�X�o�b�t�@�̉��
	if (NULL != m_pIndexBuffer)
	{
		m_pIndexBuffer->Release();
		m_pIndexBuffer = nullptr;
	}

	// �R���X�^���g�o�b�t�@(�s����W�ϊ�)�̉��
	if (NULL != m_pConstantMatrixBuffer)
	{
		m_pConstantMatrixBuffer->Release();
		m_pConstantMatrixBuffer = nullptr;
	}

	// �R���X�^���g�o�b�t�@(�J���[)�̉��
	if (NULL != m_pConstantColorBuffer)
	{
		m_pConstantColorBuffer->Release();
		m_pConstantColorBuffer = nullptr;
	}

	// ���̓��C�A�E�g�̉��
	if (NULL != m_pInputLayout)
	{
		m_pInputLayout->Release();
		m_pInputLayout = nullptr;
	}

	// �T���v���[�̉��
	if (NULL != m_pSampler)
	{
		m_pSampler->Release();
		m_pSampler = nullptr;
	}
}


//================================
//	�|���S������
//================================
HRESULT CPolygon::Create(ID3D11Device *pDevice, CModel *pModel, CShader *pShader)
{
	// ����p
	HRESULT hr;

	// ===== ���_�o�b�t�@�̍쐬 =====
	// ���_�o�b�t�@�Ƃ��č쐬���邽�߂̏��ݒ�
	D3D11_BUFFER_DESC vbDesc;
	ZeroMemory(&vbDesc, sizeof(vbDesc));
	//vbDesc.ByteWidth			= sizeof(g_VertexList);		// �o�b�t�@�̃T�C�Y(���_��)
	vbDesc.ByteWidth			 = sizeof(Vertex) * pModel->GetVertexCount();		// �o�b�t�@�̃T�C�Y(���_��)
	vbDesc.Usage				= D3D11_USAGE_DEFAULT;		// �g�p���@(�A�N�Z�X����)
	vbDesc.BindFlags			= D3D11_BIND_VERTEX_BUFFER;	// �o�b�t�@�̎��(���_�o�b�t�@)
	vbDesc.CPUAccessFlags		= 0;						// CPU�A�N�Z�X�ݒ�(0�ŃA�N�Z�X�s�v)
	vbDesc.MiscFlags			= 0;						// ���̑��̃I�v�V����(0�ŕs�v)
	vbDesc.StructureByteStride	= sizeof(Vertex);			// �\���̂̃T�C�Y

	// ���_�o�b�t�@�̏����l�ݒ�
	D3D11_SUBRESOURCE_DATA vrData;
	ZeroMemory(&vrData, sizeof(vrData));
	// �o�b�t�@�̏����l�ݒ�
	//vrData.pSysMem			= g_VertexList;		// �o�b�t�@������������f�[�^(�z��̐擪�A�h���X)
	vrData.pSysMem			= pModel->GetVertexList();		// �o�b�t�@������������f�[�^(�z��̐擪�A�h���X)
	// ���_�o�b�t�@�ł͎g�p���Ȃ�
	vrData.SysMemPitch		= 0;				// �������̃s�b�`(�e�N�X�`���Ŏg�p����)
	vrData.SysMemSlicePitch = 0;				// �[�x���x��(�e�N�X�`���Ŏg�p����)

	// ���_�o�b�t�@�̍쐬
	hr = pDevice->CreateBuffer(
		&vbDesc,			// �쐬����o�b�t�@���
		&vrData,			// �쐬����o�b�t�@�̏��������
		&m_pVertexBuffer);	// �쐬�����o�b�t�@��ۑ�����|�C���^
	// �G���[����
	if (FAILED(hr)) return hr;


	//===== �C���f�b�N�X�o�b�t�@�̍쐬 =====
	// �C���f�b�N�X�o�b�t�@�Ƃ��č쐬���邽�߂̏��ݒ�
	D3D11_BUFFER_DESC ibDesc;
	ZeroMemory(&ibDesc, sizeof(ibDesc));
	ibDesc.ByteWidth			= sizeof(WORD) * pModel->GetIndexCount();		// �o�b�t�@�̃T�C�Y(�C���f�b�N�X��)
	//ibDesc.ByteWidth			= sizeof(g_IndexList);		// �o�b�t�@�̃T�C�Y(�C���f�b�N�X��)
	ibDesc.Usage				= D3D11_USAGE_DEFAULT;		// �g�p���@(�A�N�Z�X����)
	ibDesc.BindFlags			= D3D11_BIND_INDEX_BUFFER;	// �o�b�t�@�̎��(�C���f�b�N�X�o�b�t�@)
	ibDesc.CPUAccessFlags		= 0;						// CPU�A�N�Z�X�ݒ�(0�ŃA�N�Z�X�s�v)
	ibDesc.MiscFlags			= 0;						// ���̑��̃I�v�V����(0�ŕs�v)
	ibDesc.StructureByteStride	= 0;						// �\���̂ł͂Ȃ��̂�0

	// �C���f�b�N�X�o�b�t�@�̏����l�ݒ�
	D3D11_SUBRESOURCE_DATA irDesc;
	ZeroMemory(&irDesc, sizeof(irDesc));
	// �o�b�t�@�̏����l�ݒ�
	irDesc.pSysMem			= pModel->GetIndexList();	// �o�b�t�@������������f�[�^(�z��̐擪�A�h���X)
	//irDesc.pSysMem			= g_IndexList;	// �o�b�t�@������������f�[�^(�z��̐擪�A�h���X)
	// �C���f�b�N�X�o�b�t�@�ł͎g�p���Ȃ�
	irDesc.SysMemPitch		= 0;			// �������̃s�b�`(�e�N�X�`���Ŏg�p����)
	irDesc.SysMemSlicePitch = 0;			// �[�x���x��(�e�N�X�`���Ŏg�p����)

	// �C���f�b�N�X�o�b�t�@�̍쐬
	hr = pDevice->CreateBuffer(
		&ibDesc,			// �쐬����o�b�t�@���
		&irDesc,			// �쐬����o�b�t�@�̏��������
		&m_pIndexBuffer);	// �쐬�����o�b�t�@��ۑ�����|�C���^
	// �G���[����
	if (FAILED(hr)) return hr;


	//===== �R���X�^���g�}�g���b�N�X�o�b�t�@�̍쐬 =====
	// �R���X�^���g�o�b�t�@�Ƃ��č쐬���邽�߂̏��ݒ�
	D3D11_BUFFER_DESC cbDesc;
	cbDesc.ByteWidth			= sizeof(ConstantMatrixBuffer);	// �o�b�t�@�T�C�Y(�ϊ��s��̐�)
	cbDesc.Usage				= D3D11_USAGE_DEFAULT;			// �g�p���@(�A�N�Z�X����)
	cbDesc.BindFlags			= D3D11_BIND_CONSTANT_BUFFER;	// �o�b�t�@�̎��(�R���X�^���g�o�b�t�@)
	cbDesc.CPUAccessFlags		= 0;							// CPU�A�N�Z�X�ݒ�(0�ŃA�N�Z�X�s�v)
	cbDesc.MiscFlags			= 0;							// ���̑��̃I�v�V����(0�ŕs�v)
	cbDesc.StructureByteStride	= 0;							// �\���̃T�C�Y(�s����g���������0�ł����삷�邱�Ƃ����؂���)
	// �R���X�^���g�o�b�t�@�̍쐬
	hr = pDevice->CreateBuffer(&cbDesc, NULL, &m_pConstantMatrixBuffer);
	// �G���[����
	if (FAILED(hr)) return hr;

	cbDesc.ByteWidth			= sizeof(ConstantColor);		// �o�b�t�@�T�C�Y(��)
	cbDesc.Usage				= D3D11_USAGE_DEFAULT;			// �g�p���@(�A�N�Z�X����)
	cbDesc.BindFlags			= D3D11_BIND_CONSTANT_BUFFER;	// �o�b�t�@�̎��(�R���X�^���g�o�b�t�@)
	cbDesc.CPUAccessFlags		= 0;							// CPU�A�N�Z�X�ݒ�(0�ŃA�N�Z�X�s�v)
	cbDesc.MiscFlags			= 0;							// ���̑��̃I�v�V����(0�ŕs�v)
	cbDesc.StructureByteStride	= 0;							// �\���̃T�C�Y(�s����g���������0�ł����삷�邱�Ƃ����؂���)
	// �R���X�^���g�o�b�t�@�̍쐬
	hr = pDevice->CreateBuffer(&cbDesc, NULL, &m_pConstantColorBuffer);
	// �G���[����
	if (FAILED(hr)) return hr;

	//===== ���C�A�E�g�̍쐬 =====
	// ���̓��C�A�E�g�̍쐬
	hr = pDevice->CreateInputLayout(
		g_VertexDesc,					// ���̓��C�A�E�g�̍\��
		_countof(g_VertexDesc),			// �\���̗v�f��
		pShader->GetVertexShaderData(),	// ���_�V�F�[�_�[�̃f�[�^
		pShader->GetVertexShaderSize(),	// ���_�V�F�[�_�[�̃T�C�Y
		&m_pInputLayout);				// �쐬�������̓��C�A�E�g�̕ۑ���
	// �G���[����
	if (FAILED(hr)) return hr;

	
	//===== �T���v���[�̍쐬 =====
	// �T���v���[�̏��ݒ�
	D3D11_SAMPLER_DESC smpDesc;
	ZeroMemory(&smpDesc, sizeof(D3D11_SAMPLER_DESC));
	//smpDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;		// �{�P����A���`���
	//smpDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;		// �{�P�Ȃ��A�j�A���X�g�l�C�o�[
	//smpDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;		// UV���W�����[�v���邩���Ȃ���
	//smpDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	//smpDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	smpDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	smpDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	smpDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	smpDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	// �T���v���[�쐬
	hr = pDevice->CreateSamplerState(&smpDesc, &m_pSampler);
	// �G���[����
	if (FAILED(hr)) return hr;

	// �|�C���^�̊i�[
	m_pModel = pModel;
	m_pShader = pShader;

	return hr;
}


//==============================
//	�|���S���̕`��
//==============================
void CPolygon::Draw(ID3D11DeviceContext *pDeviceContext, CTransform *pTrans, CTexture *pTexture, CSprite *pSpr, bool bCamera)
{
	// �g�����_�V�F�[�_�[���w��
	pDeviceContext->VSSetShader(
		m_pShader->GetVertexShader(),	// �ݒ肷�钸�_�V�F�[�_�[
		NULL,						// ID3D11ClassInstance�̃|�C���^�̔z��
		0);							// �z��̗v�f��

	// �g���s�N�Z���V�F�[�_�[���w��
	pDeviceContext->PSSetShader(
		m_pShader->GetPixelShader(),	// �ݒ肷��s�N�Z���V�F�[�_�[
		NULL,						// ID3D11ClassInstance�̃|�C���^�̔z��
		0);							// �z��̗v�f��

	// ���_�o�b�t�@
	UINT stride = sizeof(Vertex);	// 1���_�̃T�C�Y�̔z��
	UINT offset = 0;				// ���_�o�b�t�@�̊J�n�ʒu�����炷�I�t�Z�b�g�̔z��
	// ���_�o�b�t�@���w��
	pDeviceContext->IASetVertexBuffers(
		0,					// ���̓X���b�g�̊J�n�ԍ�
		1,					// ���_�o�b�t�@�̐�
		&m_pVertexBuffer,	// ���_�o�b�t�@�̔z��
		&stride,			// 1���_�̃T�C�Y�̔z��
		&offset);			// ���_�o�b�t�@�̊J�n�ʒu�����炷�I�t�Z�b�g�̔z��
	
	// �C���f�b�N�X�o�b�t�@���w��
	pDeviceContext->IASetIndexBuffer(
		m_pIndexBuffer,			// �ݒ肷��C���f�b�N�X�o�b�t�@
		DXGI_FORMAT_R16_UINT,	// �C���f�b�N�X�̃T�C�Y�t�H�[�}�b�g(WORD�^)
		0);						// �o�b�t�@�̊J�n�I�t�Z�b�g

	// ���̓��C�A�E�g���w��
	pDeviceContext->IASetInputLayout(m_pInputLayout);	// �ݒ肷����̓��C�A�E�g

	// �e�N�X�`���̎w��
	if (pTexture != nullptr && pTexture->m_pTextureResourceView != nullptr)
	{
		pDeviceContext->PSSetShaderResources(0, 1, &pTexture->m_pTextureResourceView);
		pDeviceContext->PSSetSamplers(0, 1, &m_pSampler);
	}

	// ���[���h�}�g���N�X�ݒ� (�ϊ��s��̐�)
	DirectX::XMMATRIX worldMatrix;
	// �g�k
	if (bCamera)
	{
		worldMatrix = DirectX::XMMatrixScaling(pTrans->GetSize().x  * CCamera::GetScale(),
			pTrans->GetSize().y  * CCamera::GetScale(), 1.0f);
	}
	else
	{
		worldMatrix = DirectX::XMMatrixScaling(pTrans->GetSize().x,
			pTrans->GetSize().y, 1.0f);
	}
	// ��]
	worldMatrix *= DirectX::XMMatrixRotationRollPitchYaw(AngleToRadian(180.0f), 0.0f, AngleToRadian(pTrans->GetAngle()));
	//worldMatrix *= DirectX::XMMatrixRotationRollPitchYaw(trans.rot.x, trans.rot.y, trans.rot.z);
	// �ړ�
	Float3 CameraPos = CCamera::GetCameraPos();
	if (bCamera)
	{
		// �J�������W
		worldMatrix *= DirectX::XMMatrixTranslation((pTrans->GetPos().x - CameraPos.x) * CCamera::GetScale() + SCREEN_CENTER_X,
			(pTrans->GetPos().y - CameraPos.y)  * CCamera::GetScale() + SCREEN_CENTER_Y,
			pTrans->GetPos().z);
	}
	else
	{
		worldMatrix *= DirectX::XMMatrixTranslation(pTrans->GetPos().x + SCREEN_CENTER_X,
			pTrans->GetPos().y + SCREEN_CENTER_Y, pTrans->GetPos().z);
	}

	// �r���[�}�g���b�N�X�̐ݒ�
	//XMMATRIX viewMatrix = XMMatrixLookAtLH(CCamera::GetEyePos(), CCamera::GetFocusPos(), CCamera::GetUpVec());	// ��̏������ƂɃr���[�ϊ��s���ݒ�

	// �J�����s��
	DirectX::XMMATRIX viewMatrix =
		DirectX::XMMatrixOrthographicOffCenterLH(0, static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT), 0, -1, 1);


	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	float	 fov		= XMConvertToRadians(70.0f);							// ����p
	float	 aspect		= (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;			// �X�N���[���̃A�X�y�N�g��
	float	 nearZ		= 0.1f;													// �N���b�s���O�̍ŒZ����
	float	 farZ		= 10000.0f;												// �N���b�s���O�̍Œ�����
	XMMATRIX projMatrix = XMMatrixPerspectiveFovLH(fov, aspect, nearZ, farZ);	// ��̏������ƂɃv���W�F�N�V�����ϊ��s���ݒ�
	
	// �e�N�X�`���}�g���b�N�X�̐ݒ�
	// �g�k
	XMMATRIX texMatrix = XMMatrixScaling(pSpr->GetTexSize().x, pSpr->GetTexSize().y, 0.0f);
	// �ړ�
	texMatrix *= XMMatrixTranslation(pSpr->GetTexPos().x, pSpr->GetTexPos().y, 0.0f);

	// �X�V����R���X�^���g�}�g���b�N�X�o�b�t�@�̍쐬
	ConstantMatrixBuffer cmb;
	XMStoreFloat4x4(&cmb.mWorld, XMMatrixTranspose(worldMatrix));		// ���[���h�}�g���b�N�X
	XMStoreFloat4x4(&cmb.mView, XMMatrixTranspose(viewMatrix));			// �r���[�}�g���b�N�X
	XMStoreFloat4x4(&cmb.mProjection, XMMatrixTranspose(projMatrix));	// �v���W�F�N�V�����}�g���b�N�X
	XMStoreFloat4x4(&cmb.mTexture, XMMatrixTranspose(texMatrix));		// �e�N�X�`���}�g���b�N�X

	// �R���X�^���g�}�g���b�N�X�o�b�t�@�X�V
	pDeviceContext->UpdateSubresource(
		m_pConstantMatrixBuffer,	// �X�V�Ώۂ̃o�b�t�@
		0,					// �C���f�b�N�X(0)
		NULL,				// �X�V�͈�(nullptr)
		&cmb,				// ���f�f�[�^
		0,					// �f�[�^��1�s�̃T�C�Y(0)
		0);					// 1�[�x�X���C�X�̃T�C�Y(0)

	// ���_�V�F�[�_�[�̃R���X�^���g�o�b�t�@��ݒ�
	pDeviceContext->VSSetConstantBuffers(
		0,						// �o�b�t�@�̊J�n�ԍ�
		1,						// �o�b�t�@�̐�
		&m_pConstantMatrixBuffer);	// �ݒ肷��R���X�^���g�o�b�t�@

	// �J���[�R���X�^���g�o�b�t�@
	ConstantColor cc;
	cc.color = pSpr->GetColor();

	// �R���X�^���g�}�g���b�N�X�o�b�t�@�X�V
	pDeviceContext->UpdateSubresource(
		m_pConstantColorBuffer,	// �X�V�Ώۂ̃o�b�t�@
		0,					// �C���f�b�N�X(0)
		NULL,				// �X�V�͈�(nullptr)
		&cc,				// ���f�f�[�^
		0,					// �f�[�^��1�s�̃T�C�Y(0)
		0);					// 1�[�x�X���C�X�̃T�C�Y(0)

	// �s�N�Z���V�F�[�_�[�̃R���X�^���g�o�b�t�@��ݒ�
	pDeviceContext->PSSetConstantBuffers(
		0,						// �o�b�t�@�̊J�n�ԍ�
		1,						// �o�b�t�@�̐�
		&m_pConstantColorBuffer);	// �ݒ肷��R���X�^���g�o�b�t�@

	// �v���~�e�B�u�̌`����w��
	pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);	// �v���~�e�B�u�̎��

	// �C���f�b�N�X�o�b�t�@�ɂ��`��
	pDeviceContext->DrawIndexed(
		m_pModel->GetIndexCount(),			// �`�悷�钸�_�̐�
		0,								// �`��Ŏg���ŏ��̃C���f�b�N�X�ԍ�
		0);								// ���_�o�b�t�@�̍ŏ��̈ʒu

	//pDeviceContext->Draw(3, 0);
}