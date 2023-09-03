#pragma once
#include "CollisionPrimitive.h"
#include "RaycastHit.h"
#include "QueryCallback.h"

#include <forward_list>
#include <d3d12.h>

class BaseCollider;

class CollisionManager
{
public:
	static CollisionManager* GetInstance();

	//�����o�֐�
public:
	//�R���C�_�[�̒ǉ�
	inline void AddCollider(BaseCollider* collider)
	{
		colliders.push_front(collider);
	}

	//�R���C�_�[�̍폜
	inline void RemoveCollider(BaseCollider* collider)
	{
		colliders.remove(collider);
	}

	void CheckAllCollisions();
	bool Raycast(const Ray& ray , unsigned short attribute, RaycastHit* hitInfo = nullptr , float maxDistance = D3D12_FLOAT32_MAX);
	bool Raycast(const Ray& ray , RaycastHit* hitInfo = nullptr , float maxDistance = D3D12_FLOAT32_MAX);

	/// <summary>
	/// ���ɂ��ՓˑS����
	/// </summary>
	/// <param name="sphere">��</param>
	/// <param name="callback">�Փˎ��R�[���o�b�N</param>
	/// <param name="attribute">�Ώۂ̑���</param>
	void QuerySphere(const Sphere& sphere, QueryCallback* callback, unsigned short attribute = (unsigned short)0xffff);

private:
	CollisionManager() = default;
	CollisionManager(const CollisionManager&) = delete;
	~CollisionManager() = default;
	CollisionManager& operator= (const CollisionManager&) = delete;

	//�R���C�_�[�̃��X�g
	std::forward_list<BaseCollider*> colliders;

};