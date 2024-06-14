#ifndef RANDOM_UTIL_HPP
#define RANDOM_UTIL_HPP

#include <chrono>
#include <string>
#include <type_traits>
#include <random>

class RandomUtil
{
public:

	static RandomUtil& instance()
	{
		static RandomUtil ins;
		return ins;
	}

	~RandomUtil() = default;

	template<typename T>
	T generateInRange(T min, T max)
	{
		std::uniform_int_distribution<> distrib(min, max);

		return distrib(r);
	}

	float generateInRange(float min, float max)
	{
		std::uniform_real_distribution<> distrib(min, max);

		return distrib(r);
	}

	double generateInRange(double min, double max)
	{
		std::uniform_real_distribution<> distrib(min, max);

		return distrib(r);
	}

private:
	RandomUtil()
	{
		auto now_ms = std::chrono::time_point_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now());
		long long cc = 0;
		memcpy(&cc, &now_ms, sizeof(long long));
    	r = std::ranlux24_base(cc);
	}

	std::ranlux24_base r;
};

#endif // !RANDOM_UTIL_HPP