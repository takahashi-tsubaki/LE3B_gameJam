#include "SphereCollider.h"

void SphereCollider::Update()
{
	if (object3d)
	{
		//���[���h�s�񂩂���W�𒊏o
		const Matrix4& matWorld = object3d->GetMatWorld();

		//���̃����o�ϐ����X�V
		Sphere::center =
		{
			matWorld.m[3][0] + offset.x ,
			matWorld.m[3][1] + offset.y ,
			matWorld.m[3][2] + offset.z
		};
	}
	else if (basisPos)
	{
		Sphere::center = *basisPos + offset;
	}
	else
	{
		Sphere::center = {0 , 0 , 0};
	}


	Sphere::radius = radius_;

	isHit = false;
}