#pragma once
#pragma warning(push)
#include "fbxsdk.h"
#pragma warning(pop)


#include <d3d12.h>
#include <d3dx12.h>

#include <string>

#include "FbxModel.h"

class FbxLoader
{
private:
	//エイリアスを省略
	using string = std::string;

public://サブクラス
	struct VertexPosNormalUv
	{
		DirectX::XMFLOAT3 pos;//xyz座標
		DirectX::XMFLOAT3 normal;//法線ベクトル
		DirectX::XMFLOAT3 uv;//uv座標
	};

public:

	//モデル格納ルートパス
	static const string baseDirectory;

public:

	

	/// <summary>
	/// シングルトンインスタンスの取得
	/// </summary>
	/// <returns>インスタンス</returns>
	static FbxLoader* GetInstance();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(ID3D12Device* device);

	/// <summary>
	/// 後始末
	/// </summary>
	void Finalize();

	FbxModel* LoadModelFromFile(const string& modelname);


	void ParseNodeRecursive(FbxModel*fbxModel, FbxNode* fbxNode, Node* parent = nullptr);

	/// <summary>
	/// メッシュ読み取り
	/// </summary>
	/// <param name="fbxModel"></param>
	/// <param name="fbxNode"></param>
	void ParseMesh(FbxModel* fbxModel, FbxNode* fbxNode);

	/// <summary>
	/// 頂点読み取り
	/// </summary>
	/// <param name="fbxModel"></param>
	/// <param name="fbxNode"></param>
	void ParseMeshVertices(FbxModel* fbxModel, FbxMesh* fbxMesh);

	/// <summary>
	/// 面情報読み取り
	/// </summary>
	/// <param name="fbxModel"></param>
	/// <param name="fbxNode"></param>
	void ParseMeshFaces(FbxModel* fbxModel, FbxMesh* fbxMesh);
	/// <summary>
	/// マテリアル読み取り
	/// </summary>
	/// <param name="fbxModel"></param>
	/// <param name="fbxNode"></param>
	void ParseMaterial(FbxModel* fbxModel, FbxNode* fbxNode);

	//テクスチャ読み込み
	void LoadTexture(FbxModel* fbxModel, const std::string & fullpath);

	//ディレクトリを含んだファイルパスからファイル名を抽出する
	std::string ExtractFileName(const std::string& path);

	/// <summary>
	/// Fbxの行列をXMMatrixに変換
	/// </summary>
	/// <param name="dst"></param>
	/// <param name="src"></param>
	static void ConvertMatrixFromFbx(DirectX::XMMATRIX* dst,const FbxAMatrix& src);

	//スキニング情報の読み取り
	void ParseSkin(FbxModel* fbxModel, FbxMesh* fbxMesh);

private:
	// privateなコンストラクタ（シングルトンパターン）
	FbxLoader() = default;
	// privateなデストラクタ（シングルトンパターン）
	~FbxLoader() = default;
	// コピーコンストラクタを禁止（シングルトンパターン）
	FbxLoader(const FbxLoader& obj) = delete;
	// コピー代入演算子を禁止（シングルトンパターン）
	void operator=(const FbxLoader& obj) = delete;

	ID3D12Device* device_ = nullptr;

	FbxManager* fbxManager = nullptr;

	FbxImporter* fbxImpoter = nullptr;

	Vector4 mat;

	//テクスチャファイルがない場合の標準テクスチャファイル名
	static const string defaultTexureFileName;
	

};