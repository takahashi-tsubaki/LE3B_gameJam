#pragma once
#include "math.h"
#include "Vector3.h"


class Ease {	//�C�[�W���O�N���X��`
public:
	static double InQuad(double change, double base, double duration, double time);
	static double OutQuad(double change, double base, double duration, double time);
	static double InOutQuad(double change, double base, double duration, double time) ;
	//���������牺�͎g���܂���B�B��
	void Initialize();
	void Update();

private:
	int maxTime_ = 50;	//�ő厞��
	int time_ = 0;//�o�ߎ���
	Vector3 startVec_ = {};
	Vector3 endVec_ = {};
	double start_ = 0;
	double end_ = 0;
	bool isChange_ = false;
};
