#pragma once

#include "CollisionTypes.h"
#include "Object3d.h"
#include "CollisionInfo.h"


//�R���C�_�[���N���X
class BaseCollider
{
public:
	friend class CollisionManager;

public:
	BaseCollider() = default;
	//���z�f�X�g���N�^
	virtual ~BaseCollider() = default;

	inline void SetObject3d(Object3d* object)
	{
		this->object3d = object;
	}

	inline Object3d* GetObject3d()
	{
		return object3d;
	}

	//�X�V
	virtual void Update() = 0;
	//�`��^�C�v�擾
	inline CollisionShapeType GetShapeType()
	{
		return shapeType;
	}

	inline void OnCollision(const CollisionInfo& info)
	{
		isHit = true;
		this->info = info;
	}

	inline void SetAttribute(unsigned short attribute)
	{
		this->attribute = attribute;
	}

	unsigned short GetAttribute() {
		return this->attribute;
	}

	inline void AddAttribute(unsigned short attribute)
	{
		this->attribute |= attribute;
	}

	inline void RemoveAttribute(unsigned short attribute)
	{
		this->attribute &= !attribute;
	}

	inline bool GetIsHit()
	{
		return isHit;
	}

	inline CollisionInfo GetCollisionInfo()
	{
		return info;
	}

protected:
	Object3d* object3d = nullptr;
	
	bool isHit = false;

	CollisionInfo info = {
		nullptr ,
		nullptr ,
		{0 , 0 , 0}
	};
	
	//�`��^�C�v
	CollisionShapeType shapeType = SHAPE_UNKNOWN;
	//�����蔻�葮��
	unsigned short attribute = 0b1111111111111111;
};