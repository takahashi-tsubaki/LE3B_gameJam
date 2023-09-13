#include "Player.h"
#include "PlayerMove.h"
#include "PlayerDash.h"
#include "PlayerJump.h"

#include "ImguiManager.h"
#include "ChipPattern.h"

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

	playerM_ = Model::CreateFromOBJ("human");
	walkmodel1 = Model::CreateFromOBJ("walk1");
	walkmodel2 = Model::CreateFromOBJ("walk2");
	jumpmodel = Model::CreateFromOBJ("jump");
	jumpmodelL = Model::CreateFromOBJ("jumpL");
	dashmodel0 = Model::CreateFromOBJ("dash0");
	dashmodel1 = Model::CreateFromOBJ("dash1");
	dashmodel2 = Model::CreateFromOBJ("dash2");
	playerO_->SetModel(playerM_);

	playerO_->SetScale({ 0.5f,0.5f,0.5f });
	
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

void Player::Update(Input* input, GamePad* gamePad)
{
	int ground = OnGround;

	if (input->PushKey(DIK_D))
	{
		move.x = speed;
		playerO_->worldTransform.translation_.x += move.x;
	}
	if (input->PushKey(DIK_A))
	{
		move.x = -speed;
		playerO_->worldTransform.translation_.x += move.x;
	}


	/*Move();*/
	

	Respawn();
	CheckCollision();

	////行動マネージャーの切り替え
	//if (chipPat_ == CHIP_PATT_MOVE)
	//{
	//	actionNum = ActionNum::Move;
	//	pActManager_->SetActionNum(actionNum);
	//}
	if (chipPat_ == CHIP_PATT_DASH)
	{
		actionNum = ActionNum::Dash;
		pActManager_->SetActionNum(actionNum);
	}
	if (chipPat_ == CHIP_PATT_JUNP)
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
			pActManager_->ChangeAction(new PlayerDash(pActManager_.get(), sphere, spherePos));
		}
		else if (pActManager_->GetActionNum() == ActionNum::Jump) {
			pActManager_->ChangeAction(new PlayerJump(pActManager_.get()));
		}
		//else {}

	}

	//更...新!!
	pActManager_->ActionUpdate(input, gamePad);
	oldActionNum_ = pActManager_->GetActionNum();

	if (input->PushKey(DIK_SPACE)) { playerO_->SetModel(jumpmodelL); }
	else if (input->PushKey(DIK_A)) {
		changeModelTimer++;
		if (changeModelTimer > 24) {
			changeModelTimer = 0;
		}
		if (changeModelTimer >= 1 && changeModelTimer <= 6) {
			playerO_->SetModel(dashmodel1);
		}
		else if (changeModelTimer >= 7 && changeModelTimer <= 12) {
			playerO_->SetModel(dashmodel0);
		}
		else if (changeModelTimer >= 13 && changeModelTimer <= 18) {
			playerO_->SetModel(dashmodel2);
		}
		else if (changeModelTimer >= 19 && changeModelTimer <= 24) {
			playerO_->SetModel(dashmodel0);
		}
	}
	else if (input->PushKey(DIK_D)) {
		changeModelTimer++;
		if (changeModelTimer > 43) {
			changeModelTimer = 0;
		}


		if (changeModelTimer >= 1 && changeModelTimer <= 10) {
			playerO_->SetModel(walkmodel1);
		}
		else if (changeModelTimer >= 11 && changeModelTimer <= 21) {
			playerO_->SetModel(playerM_);
		}
		else if (changeModelTimer >= 22 && changeModelTimer <= 32) {
			playerO_->SetModel(walkmodel2);
		}
		else if (changeModelTimer >= 33 && changeModelTimer <= 43) {
			playerO_->SetModel(playerM_);
		}
	}
	else {
		playerO_->SetModel(playerM_);
	}

	ImGui::Begin("Player");
	ImGui::InputInt("ActionNumber", &actionNum);
	ImGui::InputInt("OldActionNumber", &oldActionNum_);
	ImGui::InputFloat3("Position", &playerO_->worldTransform.translation_.x);
	ImGui::InputInt("ground", &ground);
	ImGui::End();

	playerO_->Update();
}

void Player::Draw()
{
	playerO_->Draw();
}

void Player::CheckCollision()
{

#pragma region jimennitatu
	if (!OnGround/* && pActManager_->GetActionNum() != ActionNum::Jump*/)
	{
		//sitamuki
		const float fallacc = -0.05f;
		const float fallVY = -0.5f;
		//kasoku
		fallV.y = max(fallV.y + fallacc, fallVY);
		playerO_->worldTransform.translation_.x += fallV.x;
		playerO_->worldTransform.translation_.y += fallV.y;
		playerO_->worldTransform.translation_.z += fallV.z;
	}
#pragma endregion

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
			//if (sphere[i]->GetCollisionInfo().collider->GetAttribute() == COLLISION_ATTR_LAND)
			//{
			//	isHit = true;
			//	playerO_->worldTransform.translation_.x += callback.move.x;
			//	playerO_->worldTransform.translation_.y += callback.move.y;
			//	playerO_->worldTransform.translation_.z += callback.move.z;
			//	break;
			//}
			if (sphere[i]->GetCollisionInfo().collider->GetAttribute() == COLLISION_ATTR_GOAL)
			{
				isHit = true;
				playerO_->worldTransform.translation_.x += callback.move.x;
				playerO_->worldTransform.translation_.y += callback.move.y;
				playerO_->worldTransform.translation_.z += callback.move.z;
				isGoal_ = true;
				break;
			}
			if (sphere[i]->GetCollisionInfo().collider->GetAttribute() == COLLISION_ATTR_WALL)
			{
				isHit = true;
				playerO_->worldTransform.translation_.x += callback.move.x;
				//playerO_->worldTransform.translation_.y += callback.move.y;
				playerO_->worldTransform.translation_.z += callback.move.z;
				break;
			}
		}

		Ray ray;
		ray.start = sphere[i]->center;
		ray.start.y += sphere[i]->GetRadius();
		ray.dir = { 0,-1,0 };
		RaycastHit rayCastHit;
		if (OnGround)
		{
			const float adsDistance = 0.2f;
			if (sphere[i]->GetIsHit() == true)
			{
				if (CollisionManager::GetInstance()->Raycast(ray, COLLISION_ATTR_LAND,
					&rayCastHit, sphere[i]->GetRadius() * 1.8f + adsDistance))
				{
					OnGround = true;
					playerO_->worldTransform.translation_.y -= (rayCastHit.distance - sphere[i]->GetRadius() * 1.8f);
				}
			}

			else
			{
				OnGround = false;
				fallV = {};
			}
		}
		else if (fallV.y <= 0.0f)
		{
			if (CollisionManager::GetInstance()->Raycast(ray, COLLISION_ATTR_LAND,
				&rayCastHit, sphere[i]->GetRadius() * 1.8f))
			{
				OnGround = true;
				playerO_->worldTransform.translation_.y -= (rayCastHit.distance - sphere[i]->GetRadius() * 1.8f);

			}
		}

	}
#pragma endregion



	for (int i = 0; i < SPHERE_COLISSION_NUM; i++) {

		spherePos[i] = playerO_->GetPosition();
		sphere[i]->Update();
	}



}

void Player::ResetParam(int startplayerPos)
{		
	startplayerPos_ = startplayerPos;
	if (startplayerPos == 1)
	{
		playerO_->worldTransform.translation_ = { 462,10,50 };
	}
	if (startplayerPos == 2)
	{
		playerO_->worldTransform.translation_ = { 0,10,50 };
	}
	if (startplayerPos == 3)
	{
		playerO_->worldTransform.translation_ = { 190,10,50 };
	}
	//playerO_->worldTransform.translation_ = { 0,0,50 };
	actionNum = 1;
	oldActionNum_ = 0;	//アクション前フレーム保存変数
	isGoal_ = false;
	isHit = false;
}

void Player::Move()
{
	move  = { speed,0,0};
	playerO_->worldTransform.translation_ += move;
}

void Player::Respawn()
{
	/*if (playerO_->worldTransform.translation_.y <= -20.0f)
	{
		playerO_->worldTransform.translation_ = { 0,30,50 };
	}*/
	if (startplayerPos_ == 1&& playerO_->worldTransform.translation_.y <= -20.0f)
	{
		playerO_->worldTransform.translation_ = { 462,30,50 };
	}
	if (startplayerPos_ == 2&& playerO_->worldTransform.translation_.y <= -20.0f)
	{
		playerO_->worldTransform.translation_ = { 0,30,50 };
	}
	if (startplayerPos_ == 3&& playerO_->worldTransform.translation_.y <= -20.0f)
	{
		playerO_->worldTransform.translation_ = { 190,30,50 };
	}
}
