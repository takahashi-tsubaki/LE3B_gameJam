#include "Ease.h"

double Ease::InQuad(double change, double base, double duration, double time) {	//イージングイン
	time /= duration;
	return change * time * time + base;	//changeは移動量。baseは最初の位置。durationは移動時間で、timeが現在の経過時間
}

double Ease::OutQuad(double change, double base, double duration, double time)
{	//イージングアウト
	time /= duration;
	double ans = change * (1 - (1 - time) * (1 - time) + base);
	return ans;
}

double Ease::InOutQuad(double change, double base, double duration, double time)
{	//イージングインアウト
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


