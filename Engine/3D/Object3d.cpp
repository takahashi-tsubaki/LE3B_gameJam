#include "Object3d.h"
#include <d3dcompiler.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;
using namespace Microsoft::WRL;
using namespace std;

/// <summary>
/// �ÓI�����o�ϐ��̎���
/// </summary>
ID3D12Device* Object3d::device_ = nullptr;
ID3D12GraphicsCommandList* Object3d::sCommandList = nullptr;
Object3d::PipelineSet Object3d::pipelineSet;
Camera* Object3d::sCamera_ = nullptr;
Light* Object3d::light_ = nullptr;

void Object3d::StaticInitialize(ID3D12Device* device, Camera* camera) {
	// nullptr�`�F�b�N
	assert(device);

	device_ = device;
	sCamera_ = camera;

	// �O���t�B�b�N�p�C�v���C���̐���
	CreateGraphicsPipeline();

	// ���f���̐ÓI������
	Model::StaticInitialize(device);
}

void Object3d::CreateGraphicsPipeline() {
	HRESULT result = S_FALSE;
	ComPtr<ID3DBlob> vsBlob;    // ���_�V�F�[�_�I�u�W�F�N�g
	ComPtr<ID3DBlob> psBlob;    // �s�N�Z���V�F�[�_�I�u�W�F�N�g
	ComPtr<ID3DBlob> errorBlob; // �G���[�I�u�W�F�N�g

	// ���_�V�F�[�_�̓ǂݍ��݂ƃR���p�C��
	result = D3DCompileFromFile(
	  L"Resources/shaders/OBJVertexShader.hlsl",
	  nullptr,
	  D3D_COMPILE_STANDARD_FILE_INCLUDE,
	  "main", "vs_5_0", 
	  D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
	  0, &vsBlob, &errorBlob);

	if (FAILED(result)) {
		// errorBlob����G���[���e��string�^�ɃR�s�[
		std::string errstr;
		errstr.resize(errorBlob->GetBufferSize());

		std::copy_n(
		  (char*)errorBlob->GetBufferPointer(), errorBlob->GetBufferSize(), errstr.begin());
		errstr += "\n";
		// �G���[���e���o�̓E�B���h�E�ɕ\��
		OutputDebugStringA(errstr.c_str());
		exit(1);
	}

	// �s�N�Z���V�F�[�_�̓ǂݍ��݂ƃR���p�C��
	result = D3DCompileFromFile(
	  L"Resources/shaders/OBJPixelShader.hlsl",
	  nullptr,
	  D3D_COMPILE_STANDARD_FILE_INCLUDE,
	  "main", "ps_5_0",
	  D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
	  0, &psBlob, &errorBlob);

	if (FAILED(result)) {
		// errorBlob����G���[���e��string�^�ɃR�s�[
		std::string errstr;
		errstr.resize(errorBlob->GetBufferSize());

		std::copy_n(
		  (char*)errorBlob->GetBufferPointer(), errorBlob->GetBufferSize(), errstr.begin());
		errstr += "\n";
		// �G���[���e���o�̓E�B���h�E�ɕ\��
		OutputDebugStringA(errstr.c_str());
		exit(1);
	}

	// ���_���C�A�E�g
	D3D12_INPUT_ELEMENT_DESC inputLayout[] = {
	  {// xy���W(1�s�ŏ������ق������₷��)
	   "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT,
	   D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
	  {// �@���x�N�g��(1�s�ŏ������ق������₷��)
	   "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT,
	   D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
	  {// uv���W(1�s�ŏ������ق������₷��)
	   "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, D3D12_APPEND_ALIGNED_ELEMENT,
	   D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
	};

	// �O���t�B�b�N�X�p�C�v���C���̗����ݒ�
	D3D12_GRAPHICS_PIPELINE_STATE_DESC gpipeline{};
	gpipeline.VS = CD3DX12_SHADER_BYTECODE(vsBlob.Get());
	gpipeline.PS = CD3DX12_SHADER_BYTECODE(psBlob.Get());

	// �T���v���}�X�N
	gpipeline.SampleMask = D3D12_DEFAULT_SAMPLE_MASK; // �W���ݒ�
	// ���X�^���C�U�X�e�[�g
	gpipeline.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	// �f�v�X�X�e���V���X�e�[�g
	gpipeline.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);

	// �����_�[�^�[�Q�b�g�̃u�����h�ݒ�
	D3D12_RENDER_TARGET_BLEND_DESC blenddesc{};
	blenddesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL; // RBGA�S�Ẵ`�����l����`��
	blenddesc.BlendEnable = true;
	blenddesc.BlendOp = D3D12_BLEND_OP_ADD;
	blenddesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;
	blenddesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;

	blenddesc.BlendOpAlpha = D3D12_BLEND_OP_ADD;
	blenddesc.SrcBlendAlpha = D3D12_BLEND_ONE;
	blenddesc.DestBlendAlpha = D3D12_BLEND_ZERO;

	// �u�����h�X�e�[�g�̐ݒ�
	gpipeline.BlendState.RenderTarget[0] = blenddesc;

	// �[�x�o�b�t�@�̃t�H�[�}�b�g
	gpipeline.DSVFormat = DXGI_FORMAT_D32_FLOAT;

	// ���_���C�A�E�g�̐ݒ�
	gpipeline.InputLayout.pInputElementDescs = inputLayout;
	gpipeline.InputLayout.NumElements = _countof(inputLayout);

	// �}�`�̌`��ݒ�i�O�p�`�j
	gpipeline.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

	gpipeline.NumRenderTargets = 1;                            // �`��Ώۂ�1��
	gpipeline.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB; // 0�`255�w���RGBA
	gpipeline.SampleDesc.Count = 1; // 1�s�N�Z���ɂ�1��T���v�����O

	// �f�X�N���v�^�����W
	CD3DX12_DESCRIPTOR_RANGE descRangeSRV;
	descRangeSRV.Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0); // t0 ���W�X�^

	// ���[�g�p�����[�^
	CD3DX12_ROOT_PARAMETER rootparams[4];
	rootparams[0].InitAsConstantBufferView(0, 0, D3D12_SHADER_VISIBILITY_ALL);
	rootparams[1].InitAsConstantBufferView(1, 0, D3D12_SHADER_VISIBILITY_ALL);
	rootparams[2].InitAsDescriptorTable(1, &descRangeSRV, D3D12_SHADER_VISIBILITY_ALL);
	rootparams[3].InitAsConstantBufferView(2, 0, D3D12_SHADER_VISIBILITY_ALL);

	// �X�^�e�B�b�N�T���v���[
	CD3DX12_STATIC_SAMPLER_DESC samplerDesc = CD3DX12_STATIC_SAMPLER_DESC(0);

	// ���[�g�V�O�l�`���̐ݒ�
	CD3DX12_VERSIONED_ROOT_SIGNATURE_DESC rootSignatureDesc;
	rootSignatureDesc.Init_1_0(
	  _countof(rootparams), rootparams, 1, &samplerDesc,
	  D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

	ComPtr<ID3DBlob> rootSigBlob;
	// �o�[�W������������̃V���A���C�Y
	result = D3DX12SerializeVersionedRootSignature(
	  &rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0, &rootSigBlob, &errorBlob);
	// ���[�g�V�O�l�`���̐���
	result = device_->CreateRootSignature(
	  0, rootSigBlob->GetBufferPointer(), rootSigBlob->GetBufferSize(),
	  IID_PPV_ARGS(&pipelineSet.rootsignature));
	assert(SUCCEEDED(result));

	gpipeline.pRootSignature = pipelineSet.rootsignature.Get();

	// �O���t�B�b�N�X�p�C�v���C���̐���
	result =
	  device_->CreateGraphicsPipelineState(&gpipeline, IID_PPV_ARGS(&pipelineSet.pipelinestate));
	assert(SUCCEEDED(result));
}

void Object3d::PreDraw(ID3D12GraphicsCommandList* commandList) {
	// PreDraw��PostDraw���y�A�ŌĂ΂�Ă��Ȃ���΃G���[
	assert(sCommandList == nullptr);

	// �R�}���h���X�g���Z�b�g
	sCommandList = commandList;

	// �v���~�e�B�u�`���ݒ�
	commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void Object3d::PostDraw() {
	// �R�}���h���X�g������
	sCommandList = nullptr;
}

Object3d* Object3d::Create() {
	// 3D�I�u�W�F�N�g�̃C���X�^���X�𐶐�
	Object3d* object3d = new Object3d();
	if (object3d == nullptr) {
		return nullptr;
	}

	// ������
	if (!object3d->Initialize()) {
		delete object3d;
		assert(0);
		return nullptr;
	}

	return object3d;
}

bool Object3d::Initialize() {
	// nullptr�`�F�b�N
	assert(device_);

	// �q�[�v�v���p�e�B
	CD3DX12_HEAP_PROPERTIES heapProps = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	// ���\�[�X�ݒ�
	CD3DX12_RESOURCE_DESC resourceDesc =
	  CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferDataB0) + 0xff) & ~0xff);

	HRESULT result;
	// �萔�o�b�t�@�̐���
	result = device_->CreateCommittedResource(
	  &heapProps, D3D12_HEAP_FLAG_NONE, &resourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
	  IID_PPV_ARGS(&constBuffB0));
	assert(SUCCEEDED(result));

	// �萔�o�b�t�@�̃}�b�s���O
	result = constBuffB0->Map(0, nullptr, (void**)&constMap);
	assert(SUCCEEDED(result));

	return true;
}

void Object3d::Update() {
	assert(sCamera_);

	HRESULT result;
	UpdateMatrix();
	//XMMATRIX matScale, matRot, matTrans;

	//// �X�P�[���A��]�A���s�ړ��s��̌v�Z
	//matScale = XMMatrixScaling(scale.x, scale.y, scale.z);
	//matRot = XMMatrixIdentity();
	//matRot *= XMMatrixRotationZ(XMConvertToRadians(rotation.z));
	//matRot *= XMMatrixRotationX(XMConvertToRadians(rotation.x));
	//matRot *= XMMatrixRotationY(XMConvertToRadians(rotation.y));
	//matTrans = XMMatrixTranslation(position.x, position.y, position.z);

	//// ���[���h�s��̍���
	//matWorld = XMMatrixIdentity(); // �ό`�����Z�b�g
	//matWorld *= matScale;          // ���[���h�s��ɃX�P�[�����O�𔽉f
	//matWorld *= matRot;            // ���[���h�s��ɉ�]�𔽉f
	//matWorld *= matTrans;          // ���[���h�s��ɕ��s�ړ��𔽉f



	//if (isBillboard) {
	//	const XMMATRIX& matBillboard = sCamera_->GetBillboardMatrix();

	//	matWorld = XMMatrixIdentity();
	//	matWorld *= matScale; // ���[���h�s��ɃX�P�[�����O�𔽉f
	//	matWorld *= matRot;   // ���[���h�s��ɉ�]�𔽉f
	//	matWorld *= matBillboard;
	//	matWorld *= matTrans; // ���[���h�s��ɕ��s�ړ��𔽉f
	//}

	/*const XMMATRIX& matViewProjection = sCamera_->GetViewProjectionMatrix();
	const XMFLOAT3& cameraPos = sCamera_->GetEye();*/

	XMVECTOR CameraVec = { 10000.0f,10000.0f,10000.0f/*camera_->GetEye().x - worldTransform.translation_.x + 2.0f,camera_->GetEye().x - worldTransform.translation_.y + 2.0f,camera_->GetEye().x - worldTransform.translation_.z*/ };

	CameraVec = XMVector3Normalize(CameraVec);


	
	result = constBuffB0->Map(0, nullptr, (void**)&constMap);
	//constMap->color = color;
	Matrix4 myMat = worldTransform.matWorld_;
	myMat *= sCamera_->GetViewProjectionMatrix();	// �s��̍��� 
	constMap->mat = myMat;
	constMap->color = color_;
	constBuffB0->Unmap(0, nullptr);

	//// �萔�o�b�t�@�փf�[�^�]��
	//constMap->viewproj = matViewProjection;
	//constMap->world = matWorld;
	//constMap->cameraPos = cameraPos;
	//constMap->color = this->color;
}

void Object3d::UpdateMatrix()
{
	worldTransform.UpdateMatWorld();
	// �e�I�u�W�F�N�g�������
	if (parent != nullptr) {
		// �e�I�u�W�F�N�g�̃��[���h�s����|����
		matWorld *= parent->matWorld;
	}
}

void Object3d::Draw() {
	// nullptr�`�F�b�N
	assert(device_);
	assert(sCommandList);

	// ���f���̊��蓖�Ă��Ȃ���Ε`�悵�Ȃ�
	if (model_ == nullptr) {
		return;
	}

	// �p�C�v���C���X�e�[�g�̐ݒ�
	sCommandList->SetPipelineState(pipelineSet.pipelinestate.Get());
	// ���[�g�V�O�l�`���̐ݒ�
	sCommandList->SetGraphicsRootSignature(pipelineSet.rootsignature.Get());
	// �萔�o�b�t�@�r���[���Z�b�g
	sCommandList->SetGraphicsRootConstantBufferView(0, constBuffB0->GetGPUVirtualAddress());

	light_->Draw(sCommandList,3);
	// ���f���`��
	model_->Draw(sCommandList);
	
}
