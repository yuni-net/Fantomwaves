#include <math.h>
#include <fw_xy2radian.h>

namespace fw
{
	float xy2radian(float x, float y)
	{
		float dx = x;
		float dy = y;

		float d2 = x*x + y*y;

		if (d2 == 0.0f || d2 == -0.0f)
		{
			return 0.0f;
		}

		if (fabsf(d2 - 1.0f) >= 0.0000001f)
		{
			// 斜辺の二乗が1でないということは斜辺も1でない
			// つまり単位ベクトルではない
			float d = powf(d2, 0.5f);	// √d2
			dx = dx / d;
			dy = dy / d;
		}

		return xy2radian_unit(dx, dy);
	}

	float xy2radian_unit(float x, float y)
	{
		float radian = acosf(x);

		if (y < 0.0f)
		{
			radian = 0.0f - radian;	// 符号反転
		}

		return radian;
	}
}