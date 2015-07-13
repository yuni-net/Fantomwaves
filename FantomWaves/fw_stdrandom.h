#pragma once

#include "fw_includes.h"
#include "fw_typedef.h"

namespace fw
{
	/***
	@brief 乱数を取得します。
	@detail (min-max)の範囲の乱数を取得します。
		minとmaxに指定した値の大小が逆だった場合、どんな挙動になるのか知ったこっちゃないです。
	@return 乱数
	*/
	int stdrandom(int min, int max);

	/***
	@brief 乱数を取得します。
	@detail (min-max)の範囲の乱数を取得します。
		minとmaxに指定した値の大小が逆でも大丈夫なように内部で処理しています。
	@return 乱数
	*/
	int stdrandom_(int min, int max);

	/***
	@brief stdrandom(0, max)と等価です。
	*/
	int stdrandom(int max);

	/***
	@brief 乱数のシードを設定します。
	*/
	uint restdrandom(uint value);

	/***
	@brief 乱数のシードをtime(NULL)に設定します。
	*/
	uint restdrandom();

}
