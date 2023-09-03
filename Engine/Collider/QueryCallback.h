#pragma once
#include "MyMath.h"

class Object3d;
class BaseCollider;

/// <summary>
/// �N�G���B�ɂ����𓾂邽�߂̍\����
/// </summary>
struct QueryHit {
	// �Փˑ���̃I�u�W�F�N�g
	Object3d* object = nullptr;
	// �Փˑ���̃R���C�_�[
	BaseCollider* coloder = nullptr;
	// �Փ˓X
	Vector3 inter;
	// �r�˃x�N�g��
	Vector3 reject;
};

class QueryCallback
{
public:
	QueryCallback() = default;
	virtual ~QueryCallback() = default;

	/// <summary>
	/// �������R�[���o�b�N
	/// </summary>
	/// <param name="info">�������</param>
	/// <returns>�N�G���[�𑱂���Ȃ�true�A�ł��؂�Ȃ�false��Ԃ�</returns>
	virtual bool OnQueryHit(const QueryHit& info) = 0;

};

