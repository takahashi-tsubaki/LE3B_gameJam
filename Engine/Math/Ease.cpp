#include "Ease.h"

double Ease::InQuad(double change, double base, double duration, double time) {	//�C�[�W���O�C��
	time /= duration;
	return change * time * time + base;	//change�͈ړ��ʁBbase�͍ŏ��̈ʒu�Bduration�͈ړ����ԂŁAtime�����݂̌o�ߎ���
}

double Ease::OutQuad(double change, double base, double duration, double time)
{	//�C�[�W���O�A�E�g
	time /= duration;
	double ans = change * (1 - (1 - time) * (1 - time) + base);
	return ans;
}

double Ease::InOutQuad(double change, double base, double duration, double time)
{	//�C�[�W���O�C���A�E�g
	time /= duration / 2;
	if (time < 1) return change / 2 * time * time + base;
	return -change / 2 * ((--time) * (time - 2) - 1) + base;
}

void Ease::Initialize()
{
}

void Ease::Update()
{
}


