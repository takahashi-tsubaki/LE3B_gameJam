#pragma once
#include "BaseCollider.h"
#include "CollisionPrimitive.h"

class MeshCollider:public BaseCollider
{
public:
	MeshCollider()
	{
		shapeType = COLLISIONSHAPE_MESH;
	}

	//�O�p�`�̔z����\�z����
	void ConstructTriangles(Mesh* model);

	//�X�V����
	void Update() override;

	//���Ƃ̓����蔻��
	bool CheckCollisionSphere(const Sphere& sphere , Vector3* inter = nullptr, Vector3* reject = nullptr);

	//���C�Ƃ̓����蔻��
	bool CheckCollisionRay(const Ray& ray , float* distance = nullptr , Vector3* inter = nullptr);

private:
	std::vector<Triangle> triangles;

	//���[���h�s��̋t�s��
	Matrix4 objectMatWorld;

};

