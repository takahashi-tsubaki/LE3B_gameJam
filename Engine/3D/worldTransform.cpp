#include "worldTransform.h"

WorldTransform::WorldTransform(Vector3 scale, Vector3 rotation, Vector3 translation)
{
	this->scale_ = scale;
	this->rotation_ = rotation;
	this->translation_ = translation;
}

void WorldTransform::initialize()
{
	scale_ = { 1 , 1 , 1 };
	rotation_ = { 0 , 0 , 0 };
	translation_ = { 0 , 0 , 0 };
	//�P�ʍs��
	matWorld_.identity();

	//�s��̍X�V
	UpdateMatWorld();
}

void WorldTransform::UpdateMatWorld()
{
	//���[���h�ϊ��s���p��
	Matrix4 affineMat, matScale, matRot, matTrans;

	affineMat.identity();
	//matScale.identity();
	matRot.identity();
	//matTrans.identity();

	//���[���h�ϊ��s��ɃX�P�[�����O,��],���s�ړ��̍s�������
	matScale = MyMath::Scale(scale_);
	matRot = MyMath::Rotate(rotation_, 6);//6�͑S���̎���K�p
	matTrans = MyMath::Move(translation_);
	//���[���h�s��ɒP�ʍs�����
	matWorld_.identity();

	//�s��̌v�Z
	matWorld_ *= matScale;
	matWorld_ *= matRot;
	matWorld_ *= matTrans;


	//�����e������ꍇ
	if (parent_) {
		//�e�̃��[���h�s��Ƃ̌v�Z���s��
		matWorld_ *= parent_->matWorld_;
	}
}
