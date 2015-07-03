#pragma once

namespace fw
{

	/*
	 * 32個のビットのうち何番目(0-31)のビットを立てるか引数に指定すると、
	 * そのビットが立っている状態の32bit変数データが返されます。
	 */
	unsigned long bitflag(unsigned char num);

}