#pragma once

namespace fw
{
	// 初期化必須！
	// 取得した値が全てゼロになる場合は初期化されていない証拠
	// 複数回初期化しても問題無い
	unsigned long xrandom();
	void xrandom_init(unsigned long seed);

}