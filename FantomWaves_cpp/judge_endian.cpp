namespace fw
{
	bool is_big_endian()
	{
		int x = 1;
		return *reinterpret_cast<char*>(&x) == 0;
	}

	bool is_little_endian()
	{
		return !is_big_endian();
	}
}