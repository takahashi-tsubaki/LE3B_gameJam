#include "Player.h"
#include "PlayerMove.h"
#include "PlayerDash.h"
#include "PlayerJump.h"

#include "ImguiManager.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::Initialize(DirectXCommon* dxCommon)
{
	dxCommon_ = dxCommon;
	//デバイスのセット
	FbxObject3d::SetDevice(dxCommon_->GetDevice());
	//グラフィックスパイプライン生成
	FbxObject3d::CreateGraphicsPipeline();
	////敵のFbx読み込み
	//playerFbxM_.reset(FbxLoader::GetInstance()->LoadModelFromFile("boss_prot4"));
	//playerFbxO_ = std::make_unique<FbxObject3d>();
	//playerFbxO_->Initialize();
	//playerFbxO_->SetModel(playerFbxM_.get());

	playerO_ = Object3d::Create();

	playerM_= Model::CreateFromOBJ("human");
	playerO_->SetModel(playerM_);

	playerO_->SetScale({ 0.5f,0.5f,0.5f });
	//////FBX当たり判定初期化
	//for (int i = 0; i < SPHERE_COLISSION_NUM; i++)
	//{
	//	sphere[i] = new SphereCollider;
	//	CollisionManager::GetInstance()->AddCollider(sphere[i]);
	//	spherePos[i] = playerFbxO_.get()->bonesMat[i].GetWorldPos();
	//	sphere[i]->SetBasisPos(&spherePos[i]);
	//	sphere[i]->SetRadius(1.0f);
	//	sphere[i]->SetAttribute(COLLISION_ATTR_PLAYERS);
	//	sphere[i]->Update();
	////	//test
	////	coliderPosTest_[i] = Object3d::Create();
	////	coliderPosTest_[i]->SetModel(hpModel_.get());
	////	coliderPosTest_[i]->SetPosition(sphere[i]->center);
	////	coliderPosTest_[i]->SetScale({ sphere[i]->GetRadius(),sphere[i]->GetRadius() ,sphere[i]->GetRadius() });
	////	coliderPosTest_[i]->SetRotate({ 0,0,0 });
	////	coliderPosTest_[i]->Update();

	//}

	sphere.resize(SPHERE_COLISSION_NUM);
	spherePos.resize(SPHERE_COLISSION_NUM);
	for (int i = 0; i < SPHERE_COLISSION_NUM; i++)
	{
		sphere[i] = new SphereCollider;
		CollisionManager::GetInstance()->AddCollider(sphere[i]);
		spherePos[i] = playerO_->GetPosition();
		sphere[i]->SetBasisPos(&spherePos[i]);
		sphere[i]->SetRadius(1.0f);
		sphere[i]->SetAttribute(COLLISION_ATTR_PLAYERS);
		sphere[i]->Update();
	}


	//行動マネージャー
	pActManager_ = std::make_unique<PlayerActionManager>();
	//pActManager_->ColliderInitialize(&sphere, SPHERE_COLISSION_NUM);
	pActManager_->ActionInitialize(playerO_);
}

void Player::Update(Input* input,GamePad* gamePad)
{
	playerO_->Update();
	//行動マネージャーの切り替え
	if (input->TriggerKey(DIK_1))
	{
		actionNum = ActionNum::Move;
		pActManager_->SetActionNum(actionNum);
	}
	if (input->TriggerKey(DIK_2))
	{
		actionNum = ActionNum::Dash;
		pActManager_->SetActionNum(actionNum);
	}
	if (input->TriggerKey(DIK_3))
	{
		actionNum = ActionNum::Jump;
		pActManager_->SetActionNum(actionNum);
	}
	//前フレームとAction_Numが違ったら行動代入
	if (oldActionNum_ != pActManager_->GetActionNum()) {
		if (pActManager_->GetActionNum() == ActionNum::Move) {
			pActManager_->ChangeAction(new PlayerMove(pActManager_.get()));
		}
		else if (pActManager_->GetActionNum() == ActionNum::Dash) {
			pActManager_->ChangeAction(new PlayerDash(pActManager_.get()));
		}
		else if (pActManager_->GetActionNum() == ActionNum::Jump) {
			pActManager_->ChangeAction(new PlayerJump(pActManager_.get()));
		}
		//else {}

	}
	//更...新!!
	pActManager_->ActionUpdate(input,gamePad);
	oldActionNum_ = pActManager_->GetActionNum();

	ImGui::Begin("Player");
	ImGui::InputInt("ActionNumber", &actionNum);
	ImGui::InputInt("OldActionNumber", &oldActionNum_);
	ImGui::InputFloat3("Position", &playerO_->worldTransform.translation_.x);
	ImGui::End();
}

void Player::Draw()
{
	playerO_->Draw();
}

void Player::CheckCollision()
{
#pragma region オブジェクト同士の押し出し処理
	class PlayerQueryCallBack : public QueryCallback
	{
	public:
		PlayerQueryCallBack(Sphere* sphere) : sphere(sphere) {};

		bool OnQueryHit(const QueryHit& info)
		{
			rejectDir = info.reject;
			rejectDir.nomalize();

			//上方向と排斥方向の角度差のコサイン値
			float cos = rejectDir.dot(up);

			//
			const float threshold = cosf(XMConvertToRadians(30.0f));
			//角度差によって天井または地面と判定される場合を除いて
			if (-threshold < cos && cos < threshold)
			{
				//押し出す
				sphere->center += info.reject;
				move += info.reject;
			}
			return true;
		}
		void SphereQuery();

		//ワールドの上方向
		const Vector3 up = { 0,1,0 };
		//排斥方向
		Vector3 rejectDir;
		//クエリーに使用する球
		Sphere* sphere = nullptr;
		//排斥による移動量
		Vector3 move = {};

	};


	for (int i = 0; i < SPHERE_COLISSION_NUM; i++)
	{
		PlayerQueryCallBack callback(sphere[i]);

		//球と地形の交差を全探索する
		CollisionManager::GetInstance()->QuerySphere(*sphere[i], &callback);

		if (sphere[i]->GetIsHit() == true)
		{
			////当たったものの属性が敵だった時
			//if (sphere[i]->GetCollisionInfo().collider->GetAttribute() == COLLISION_ATTR_ENEMYS)
			//{
			//	playerO_->worldTransform.translation_.x += callback.move.x;
			//	playerO_->worldTransform.translation_.y += callback.move.y;
			//	playerO_->worldTransform.translation_.z += callback.move.z;
			//	break;
			//}
		}

	}
#pragma endregion 
}
