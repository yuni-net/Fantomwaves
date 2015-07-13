#pragma once

namespace fw
{
	/*
	* ベクトル(1, 0)と、指定したベクトル(x, y)のなす角(ラジアン)を取得する ************
	*/
	float xy2radian(float x, float y);

	// 指定するxy座標が示すベクトルが単位ベクトルならこちらを使った方が効率的
	float xy2radian_unit(float x, float y);
	// *****************************************************************************
}