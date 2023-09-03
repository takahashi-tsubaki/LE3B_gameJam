#pragma once
#include "math.h"
#include "Vector3.h"


class Ease {	//イージングクラス定義
public:
	static double InQuad(double change, double base, double duration, double time);
	static double OutQuad(double change, double base, double duration, double time);
	static double InOutQuad(double change, double base, double duration, double time) ;
	//↓ここから下は使いません。。↓
	void Initialize();
	void Update();

private:
	int maxTime_ = 50;	//最大時間
	int time_ = 0;//経過時間
	Vector3 startVec_ = {};
	Vector3 endVec_ = {};
	double start_ = 0;
	double end_ = 0;
	bool isChange_ = false;
};
