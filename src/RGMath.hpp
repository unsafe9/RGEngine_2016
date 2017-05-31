namespace RGEngine
{
	namespace Math
	{
		template<typename T> 
		inline T Abs(const T &a, const T &b)
		{
			return a > static_cast<T>(0) ? a : -a;
		}

		template<typename T>
		inline void Swap(T& a, T& b)
		{
			T tmp = a;
			a = b;
			b = tmp;
		}
		template<typename T>
		inline const T& Max(const T &a, const T &b)
		{
			return a > b ? a : b;
		}

		template<typename T>
		inline const T& Min(const T &a, const T &b)
		{
			return a > b ? b : a;
		}
	}
}