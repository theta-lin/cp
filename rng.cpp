struct Rng
{
	uint64_t state;

	Rng(uint64_t state) : state(state)
	{
	}

	uint32_t getRaw()
	{
	    uint64_t oldstate = state;
	    state = oldstate * 6364136223846793005ULL + 1;
	    uint32_t xorshifted = ((oldstate >> 18u) ^ oldstate) >> 27u;
	    uint32_t rot = oldstate >> 59u;
	    return (xorshifted >> rot) | (xorshifted << ((-rot) & 31));
	}

	int get(int min, int max)
	{
		return min + 1ll * getRaw() % (max - min + 1);
	}
};
