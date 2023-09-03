#include "Collision.h"
using namespace DirectX;

bool Collision::CheckSphere2Sphere(const Sphere& sphereA , const Sphere& sphereB , Vector3* inter, Vector3* reject)
{
	float dist = sqrtf(
		pow(sphereB.center.x - sphereA.center.x , 2) +
		pow(sphereB.center.y - sphereA.center.y , 2) +
		pow(sphereB.center.z - sphereA.center.z , 2)
	);

	if (dist > sphereA.radius + sphereB.radius)
	{
		return false;
	}
	*inter = sphereA.center + (sphereB.center - sphereA.center) / 2;

	//�����o���x�N�g�����Q��
	if (reject)
	{
		float rejectLen = sphereA.radius + sphereB.radius - sqrtf(dist);
		Vector3 NormDis = sphereA.center - sphereB.center;
		*reject = NormDis.nomalize();
		*reject *= rejectLen;
	}

	return true;
}

bool Collision::CheckSphere2Plane(const Sphere& sphere , const Plane& plane , Vector3* inter)
{
	//���W�n�̌��_���狅�̒��S���W�ւ̋���
	float distV = sphere.center.dot(plane.normal);

	//���ʂ̌��_���������Z���邱�ƂŁA���ʂƋ��̒��S�Ƃ̋������o��
	float dist = distV - plane.distance;

	//�����̐�Βl�����a���傫����Γ������Ă��Ȃ�
	if (fabs(dist) > sphere.radius) return false;

	//�^����_
	if (inter)
	{
		//���ʏ�̍ŋߐړ_���^����_�Ƃ���
		*inter = -dist * plane.normal + sphere.center;
	}

	return true;
}

void Collision::ClosestPtPoint2Triangle(const Vector3& point , const Triangle& triangle , Vector3* closest)
{
	// point��p0�̊O���̒��_�̈�̒��ɂ��邩�ǂ����`�F�b�N
	Vector3 p0_p1 = triangle.p1 - triangle.p0;
	Vector3 p0_p2 = triangle.p2 - triangle.p0;
	Vector3 p0_pt = point - triangle.p0;

	float d1 = p0_p1.dot(p0_pt);
	float d2 = p0_p2.dot(p0_pt);

	if (d1 <= 0.0f && d2 <= 0.0f)
	{
		// p0���ŋߖT
		*closest = triangle.p0;
		return;
	}

	// point��p1�̊O���̒��_�̈�̒��ɂ��邩�ǂ����`�F�b�N
	Vector3 p1_pt = point - triangle.p1;

	float d3 = p0_p1.dot(p1_pt);
	float d4 = p0_p2.dot(p1_pt);

	if (d3 >= 0.0f && d4 <= d3)
	{
		// p1���ŋߖT
		*closest = triangle.p1;
		return;
	}

	// point��p0_p1�̕ӗ̈�̒��ɂ��邩�ǂ����`�F�b�N���A�����point��p0_p1��ɑ΂���ˉe��Ԃ�
	float vc = d1 * d4 - d3 * d2;
	if (vc <= 0.0f && d1 >= 0.0f && d3 <= 0.0f)
	{
		float v = d1 / (d1 - d3);
		*closest = triangle.p0 + v * p0_p1;
		return;
	}

	// point��p2�̊O���̒��_�̈�̒��ɂ��邩�ǂ����`�F�b�N
	Vector3 p2_pt = point - triangle.p2;

	float d5 = p0_p1.dot(p2_pt);
	float d6 = p0_p2.dot(p2_pt);
	if (d6 >= 0.0f && d5 <= d6)
	{
		*closest = triangle.p2;
		return;
	}

	// point��p0_p2�̕ӗ̈�̒��ɂ��邩�ǂ����`�F�b�N���A�����point��p0_p2��ɑ΂���ˉe��Ԃ�
	float vb = d5 * d2 - d1 * d6;
	if (vb <= 0.0f && d2 >= 0.0f && d6 <= 0.0f)
	{
		float w = d2 / (d2 - d6);
		*closest = triangle.p0 + w * p0_p2;
		return;
	}

	// point��p1_p2�̕ӗ̈�̒��ɂ��邩�ǂ����`�F�b�N���A�����point��p1_p2��ɑ΂���ˉe��Ԃ�
	float va = d3 * d6 - d5 * d4;
	if (va <= 0.0f && (d4 - d3) >= 0.0f && (d5 - d6) >= 0.0f)
	{
		float w = (d4 - d3) / ((d4 - d3) + (d5 - d6));
		*closest = triangle.p1 + w * (triangle.p2 - triangle.p1);
		return;
	}

	float denom = 1.0f / (va + vb + vc);
	float v = vb * denom;
	float w = vc * denom;
	*closest = triangle.p0 + p0_p1 * v + p0_p2 * w;
}

bool Collision::CheckSphere2Triangle(const Sphere& sphere , const Triangle& triangle , Vector3* inter)
{
	Vector3 p;
	//���̒��S�ɑ΂���ړ_�ł���O�p�`��ɂ���_p��������
	ClosestPtPoint2Triangle(sphere.center , triangle , &p);
	//�_p�Ƌ��̒��S�̍����x�N�g��
	Vector3 v = p - sphere.center;
	//�����̓������߂�
	float powDist = powf(v.length() , 2);

	if (powDist > powf(sphere.radius , 2))
	{
		return false;
	}

	if (inter)
	{
		*inter = p;
	}

	return true;
}

bool Collision::CheckRay2Plane(const Ray& ray , const Plane& plane , float* distance , Vector3* inter)
{
	//�덷�z���p�̔����Ȓl
	const float epsilon = 1.0e-5f;
	//�ʖ@���ƃ��C�̕����x�N�g���̓���
	float d1 = plane.normal.dot(ray.dir);
	//���ʂɂ͓�����Ȃ�
	if (d1 > -epsilon)
	{
		return false;
	}

	//�ʖ@���ƃ��C�̎��_���W�̓���
	float d2 = plane.normal.dot(ray.start);
	//�n�_�ƕ��ʂ̋���(���ʂ̖@������)
	float dist = d2 - plane.distance;
	//�n�_�ƕ��ʂ̋���(���C����)
	float t = dist / -d1;
	//��_�����_�����ɂ���̂œ�����Ȃ�
	if (t < 0)
	{
		return false;
	}

	//��������������
	if (distance)
	{
		*distance = t;
	}

	//��_���v�Z
	if (inter)
	{
		*inter = ray.start + t * ray.dir;
	}

	return true;
}

bool Collision::CheckRay2Triangle(const Ray& ray , const Triangle& triangle , float* distance , Vector3* inter)
{
	//�O�p�`������Ă��镽�ʂ��Z�o
	Plane plane;
	Vector3 interPlane;
	plane.normal = triangle.normal;
	plane.distance = triangle.normal.dot(triangle.p0);

	//���C�ƕ��ʂ��������Ă��Ȃ���Γ������Ă��Ȃ�
	if (!CheckRay2Plane(ray , plane , distance , &interPlane))
	{
		return false;
	}

	//���C�ƕ��ʂ��������Ă����̂ŁA�����ƌ�_���������܂ꂽ
	//���C�ƕ��ʂ̌�_���O�p�`�̓����ɂ��邩����
	const float epsilon = 1.0e-5f;//�덷�z���p�̔����Ȓl
	Vector3 m;

	//��p0_p1�ɂ���
	Vector3 pt_p0 = triangle.p0 - interPlane;
	Vector3 p0_p1 = triangle.p1 - triangle.p0;
	m = pt_p0.cross(p0_p1);
	//�ӂ̊O���ł���Γ������Ă��Ȃ��̂Ŕ����ł��؂�
	if (m.dot(triangle.normal) < -epsilon)
	{
		return false;
	}

	//��p1_p2�ɂ���
	Vector3 pt_p1 = triangle.p1 - interPlane;
	Vector3 p1_p2 = triangle.p2 - triangle.p1;
	m = pt_p1.cross(p1_p2);
	//�ӂ̊O���ł���Γ������Ă��Ȃ��̂Ŕ����ł��؂�
	if (m.dot(triangle.normal) < -epsilon)
	{
		return false;
	}

	//��p2_p0�ɂ���
	Vector3 pt_p2 = triangle.p2 - interPlane;
	Vector3 p2_p0 = triangle.p0 - triangle.p2;
	m = pt_p2.cross(p2_p0);
	//�ӂ̊O���ł���Γ������Ă��Ȃ��̂Ŕ����ł��؂�
	if (m.dot(triangle.normal) < -epsilon)
	{
		return false;
	}

	if (inter)
	{
		*inter = interPlane;
	}

	return true;
}

bool Collision::CheckRay2Sphere(const Ray& ray , const Sphere& sphere , float* distance , Vector3* inter)
{
	Vector3 m = ray.start - sphere.center;
	float b = m.dot(ray.dir);
	float c = m.dot(m) - powf(sphere.radius , 2);

	//���C�̎n�_�����̊O�ɂ���(c>0)�A���C�������痣��Ă���������w���Ă���ꍇ(b>0)�A������Ȃ�
	if (c > 0.0f && b > 0.0f)
	{
		return false;
	}

	float discr = b * b - c;
	//���̔��ʎ��̓��C�������O��Ă��邱�ƂɈ�v
	if (discr < 0.0f)
	{
		return false;
	}

	//���C�Ƌ��͌������Ă���
	//��������ꍇ�̍ŏ��̒lt���v�Z
	float t = -b - sqrtf(discr);
	//t�����ł���ꍇ�A���C�͋��̓�������J�n���Ă���̂�t���[���ɃN�����v
	if (t < 0)
	{
		t = 0.0f;
	}

	if (distance)
	{
		*distance = t;
	}

	if (inter)
	{
		*inter = ray.start + t * ray.dir;
	}

	return true;
}
