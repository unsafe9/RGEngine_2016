#include <chrono>
#include <random>

namespace RGEngine
{
	namespace Math
	{
		inline bool equal(const double &a, const double &b)
		{
			return abs(a - b) <= 1e-15;
		}
		inline bool equal(double &&a, double &&b)
		{
			return abs(a - b) <= 1e-15;
		}
		inline bool equal(const float &a, const float &b)
		{
			return abs(a - b) <= 1e-6f;
		}
		inline bool equal(float &&a, float &&b)
		{
			return abs(a - b) <= 1e-6f;
		}
		inline bool unequal(const double &a, const double &b)
		{
			return abs(a - b) > 1e-15;
		}
		inline bool unequal(double &&a, double &&b)
		{
			return abs(a - b) > 1e-15;
		}
		inline bool unequal(const float &a, const float &b)
		{
			return abs(a - b) > 1e-6f;
		}
		inline bool unequal(float &&a, float &&b)
		{
			return abs(a - b) > 1e-6f;
		}

		inline float DegToRad(float _degree)
		{
			return _degree * RG_M_RAD_PER_DEG;
		}
		inline float RadToDeg(float _radian)
		{
			return _radian * RG_M_DEG_PER_RAD;
		}
		inline int Random(int _from, int _to)
		{
			std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
			unsigned int seed = static_cast<unsigned int>(now.time_since_epoch().count());
			static std::default_random_engine random(seed);
			std::uniform_int_distribution<int> d(_from, _to);
			return d(random);
		}
		inline float Random(float _from, float _to)
		{
			std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
			unsigned int seed = static_cast<unsigned int>(now.time_since_epoch().count());
			static std::default_random_engine random(seed);
			std::uniform_real_distribution<float> d(_from, _to);
			return d(random);
		}

		inline float Distance(const Vector &a, const Vector &b)
		{
			return sqrt(DistanceDouble(a, b));
		}

		inline float DistanceDouble(const Vector &a, const Vector &b)
		{
			Vector d = a - b;
			return (d.x * d.x) + (d.y * d.y);
		}

		inline float Sign(float x)
		{
			return x < 0.0f ? -1.0f : 1.0f;
		}

		inline float Clamp(float a, float low, float high)
		{
			return Max(low, Min(a, high));
		}

		////////////////////////////
		//// Vector
		////////////////////////////

		inline Vector::Vector(void)
		{
			x = y = 0.0f;
		}

		inline Vector::Vector(float x, float y)
		{
			this->x = x;
			this->y = y;
		}

		inline Vector::operator float*(void)
		{
			return &x;
		}

		inline Vector::operator const float*(void) const
		{
			return const_cast<const float*>(&x);
		}

		inline Vector Vector::operator +(const Vector &v) const
		{
			return Vector(x + v.x, y + v.y);
		}

		inline Vector Vector::operator -(const Vector &v) const
		{
			return Vector(x - v.x, y - v.y);
		}

		inline Vector Vector::operator /(const Vector &v) const
		{
			return Vector(x / v.x, y / v.y);
		}

		inline Vector Vector::operator *(const Vector &v) const
		{
			return Vector(x * v.x, y * v.y);
		}

		inline Vector Vector::operator *(float f) const
		{
			return Vector(x * f, y * f);
		}

		inline Vector Vector::operator /(float f) const
		{
			float inv = 1.0f / f;
			return Vector(x * inv, y * inv);
		}

		inline Vector Vector::operator -(void) const
		{
			return Vector(-x, -y);
		}

		inline Vector& Vector::operator +=(const Vector &v)
		{
			x += v.x;
			y += v.y;
			return *this;
		}

		inline Vector& Vector::operator -=(const Vector &v)
		{
			x -= v.x;
			y -= v.y;
			return *this;
		}

		inline Vector& Vector::operator /=(const Vector &v)
		{
			x /= v.x;
			y /= v.y;
			return *this;
		}

		inline Vector& Vector::operator *=(const Vector &v)
		{
			x *= v.x;
			y *= v.y;
			return *this;
		}

		inline Vector& Vector::operator *=(float f)
		{
			x *= f;
			y *= f;
			return *this;
		}

		inline Vector& Vector::operator /=(float f)
		{
			float inv = 1.0f / f;
			x *= inv;
			y *= inv;
			return *this;
		}

		inline bool Vector::operator ==(const Vector &v) const
		{
			return (equal(x, v.x) && equal(y, v.y));
		}

		inline bool Vector::operator !=(const Vector &v) const
		{
			return (unequal(x, v.x) || unequal(y, v.y));
		}

		inline float Vector::Dot(const Vector &a, const Vector &b)
		{
			return a.x * b.x + a.y * b.y;
		}
		inline float Vector::Cross(const Vector &a, const Vector &b)
		{
			return a.x * b.y - a.y * b.x;
		}
		inline Vector Vector::Cross(const Vector &a, float s)
		{
			return Vector(s * a.y, -s * a.x);
		}
		inline Vector Vector::Cross(float s, const Vector &a)
		{
			return Vector(-s * a.y, s * a.x);
		}

		inline void Vector::Transform(float x, float y)
		{
			this->x += x;
			this->y += y;
		}

		inline void Vector::Transform(const Vector &v)
		{
			*this += v;
		}

		inline bool Vector::Intersected(const Vector &v) const
		{
			return *this == v;
		}
		inline bool Vector::Intersected(const Line &l) const
		{

		}
		inline bool Vector::Intersected(const Circle &c) const
		{

		}
		inline bool Vector::Intersected(const Rect &r) const
		{

		}

		inline void Vector::SetVector(const Vector &v)
		{
			*this = v;
		}
		inline void Vector::SetVector(float x, float y)
		{
			this->x = x;
			this->y = y;
		}

		inline Vector operator *(float f, const Vector &v)
		{
			return v * f;
		}

		////////////////////////////
		//// Dimension
		////////////////////////////

		inline Dimension::Dimension(void)
		{
			cx = cy = 0.0f;
		}

		inline Dimension::Dimension(float cx, float cy)
		{
			this->cx = cx;
			this->cy = cy;
		}

		inline Dimension Dimension::operator +(const Dimension &s) const
		{
			return Dimension(cx + s.cx, cy + s.cy);
		}

		inline Dimension Dimension::operator -(const Dimension &s) const
		{
			return Dimension(cx - s.cx, cy - s.cy);
		}

		inline Dimension Dimension::operator /(const Dimension &s) const
		{
			return Dimension(cx / s.cx, cy / s.cy);
		}

		inline Dimension Dimension::operator *(const Dimension &s) const
		{
			return Dimension(cx * s.cx, cy * s.cy);
		}

		inline Dimension Dimension::operator -(void) const
		{
			return Dimension(-cx, -cy);
		}


		inline Dimension& Dimension::operator +=(const Dimension &s)
		{
			cx += s.cx;
			cy += s.cy;
			return *this;
		}

		inline Dimension& Dimension::operator -=(const Dimension &s)
		{
			cx -= s.cx;
			cy -= s.cy;
			return *this;
		}

		inline Dimension& Dimension::operator /=(const Dimension &s)
		{
			cx /= s.cx;
			cy /= s.cy;
			return *this;
		}

		inline Dimension& Dimension::operator *=(const Dimension &s)
		{
			cx *= s.cx;
			cy *= s.cy;
			return *this;
		}

		inline bool Dimension::operator ==(const Dimension &s) const
		{
			return (equal(cx, s.cx) && equal(cy, s.cy));
		}

		inline bool Dimension::operator !=(const Dimension &s) const
		{
			return (unequal(cx, s.cx) || unequal(cy, s.cy));
		}

		inline void Dimension::SetDimension(const Dimension &s)
		{
			*this = s;
		}
		inline void Dimension::SetDimension(float cx, float cy)
		{
			this->cx = cx;
			this->cy = cy;
		}

		////////////////////////////
		//// Circle
		////////////////////////////

		inline Circle::Circle(void) : center(), radius(0.0f) {}
		inline Circle::Circle(float x, float y, float radius) : center(x, y), radius(radius) {}
		inline Circle::Circle(const Vector &center, float radius) : center(center), radius(radius) {}

		inline float Circle::Area(void) const
		{
			return radius * radius * RG_M_PI;
		}
		inline float Circle::Diameter(void) const
		{
			return radius * 2.0f;
		}
		inline float Circle::Circumference(void) const
		{
			return radius * RG_M_PI_DOUBLE;
		}

		inline bool Circle::Intersected(const Circle &c) const
		{
			float r = radius + c.radius;
			return DistanceDouble(center, c.center) < r * r;
		}

		inline bool Circle::Intersected(const Rect &r) const
		{
			Vector nearest(
				Max(r.left, Min(center.x, r.right)),
				Max(r.top, Min(center.y, r.bottom)));
			return DistanceDouble(nearest, center) < radius * radius;
		}

		inline void Circle::SetCircle(const Circle &c)
		{
			*this = c;
		}
		inline void Circle::SetCircle(float x, float y, float radius)
		{
			center.x = x;
			center.y = y;
			this->radius = radius;
		}
		inline void Circle::SetCircle(const Vector &center, float radius)
		{
			this->center = center;
			this->radius = radius;
		}

		////////////////////////////
		//// Matrix
		////////////////////////////

		inline Matrix::Matrix(void)
		{
			memset(&_11, 0, sizeof(Matrix));
		}

		inline Matrix::Matrix(const float *pf)
		{
			memcpy(&_11, pf, sizeof(Matrix));
		}

		inline Matrix::Matrix(
			float _11, float _12, float _13, float _14,
			float _21, float _22, float _23, float _24,
			float _31, float _32, float _33, float _34,
			float _41, float _42, float _43, float _44) :
			_11(_11), _12(_12), _13(_13), _14(_14),
			_21(_21), _22(_22), _23(_23), _24(_24),
			_31(_31), _32(_32), _33(_33), _34(_34),
			_41(_41), _42(_42), _43(_43), _44(_44) {}

		inline float& Matrix::operator ()(int iRow, int iCol)
		{
			return m[iRow][iCol];
		}

		inline float Matrix::operator ()(int iRow, int iCol) const
		{
			return m[iRow][iCol];
		}

		inline Matrix::operator float*(void)
		{
			return (float*)&_11;
		}

		inline Matrix::operator const float*(void) const
		{
			return (const float*)&_11;
		}

		inline Matrix& Matrix::operator +=(const Matrix &mat)
		{
			_11 += mat._11; _12 += mat._12; _13 += mat._13; _14 += mat._14;
			_21 += mat._21; _22 += mat._22; _23 += mat._23; _24 += mat._24;
			_31 += mat._31; _32 += mat._32; _33 += mat._33; _34 += mat._34;
			_41 += mat._41; _42 += mat._42; _43 += mat._43; _44 += mat._44;
			return *this;
		}

		inline Matrix& Matrix::operator -=(const Matrix &mat)
		{
			_11 -= mat._11; _12 -= mat._12; _13 -= mat._13; _14 -= mat._14;
			_21 -= mat._21; _22 -= mat._22; _23 -= mat._23; _24 -= mat._24;
			_31 -= mat._31; _32 -= mat._32; _33 -= mat._33; _34 -= mat._34;
			_41 -= mat._41; _42 -= mat._42; _43 -= mat._43; _44 -= mat._44;
			return *this;
		}

		inline Matrix& Matrix::operator *=(const Matrix &mat)
		{
			_11 = _11 * mat._11 + _21 * mat._12 + _31 * mat._13 + _41 * mat._14;
			_12 = _12 * mat._11 + _22 * mat._12 + _32 * mat._13 + _42 * mat._14;
			_13 = _13 * mat._11 + _23 * mat._12 + _33 * mat._13 + _43 * mat._14;
			_14 = _14 * mat._11 + _24 * mat._12 + _34 * mat._13 + _44 * mat._14;
			_21 = _11 * mat._21 + _21 * mat._22 + _31 * mat._23 + _41 * mat._24;
			_22 = _12 * mat._21 + _22 * mat._22 + _32 * mat._23 + _42 * mat._24;
			_23 = _13 * mat._21 + _23 * mat._22 + _33 * mat._23 + _43 * mat._24;
			_24 = _14 * mat._21 + _24 * mat._22 + _34 * mat._23 + _44 * mat._24;
			_31 = _11 * mat._31 + _21 * mat._32 + _31 * mat._33 + _41 * mat._34;
			_32 = _12 * mat._31 + _22 * mat._32 + _32 * mat._33 + _42 * mat._34;
			_33 = _13 * mat._31 + _23 * mat._32 + _33 * mat._33 + _43 * mat._34;
			_34 = _14 * mat._31 + _24 * mat._32 + _34 * mat._33 + _44 * mat._34;
			_41 = _11 * mat._41 + _21 * mat._42 + _31 * mat._43 + _41 * mat._44;
			_42 = _12 * mat._41 + _22 * mat._42 + _32 * mat._43 + _42 * mat._44;
			_43 = _13 * mat._41 + _23 * mat._42 + _33 * mat._43 + _43 * mat._44;
			_44 = _14 * mat._41 + _24 * mat._42 + _34 * mat._43 + _44 * mat._44;
			return *this;
		}

		inline Matrix& Matrix::operator *=(float f)
		{
			_11 *= f; _12 *= f; _13 *= f; _14 *= f;
			_21 *= f; _22 *= f; _23 *= f; _24 *= f;
			_31 *= f; _32 *= f; _33 *= f; _34 *= f;
			_41 *= f; _42 *= f; _43 *= f; _44 *= f;
			return *this;
		}

		inline Matrix& Matrix::operator /=(float f)
		{
			float fInv = 1.0f / f;
			_11 *= fInv; _12 *= fInv; _13 *= fInv; _14 *= fInv;
			_21 *= fInv; _22 *= fInv; _23 *= fInv; _24 *= fInv;
			_31 *= fInv; _32 *= fInv; _33 *= fInv; _34 *= fInv;
			_41 *= fInv; _42 *= fInv; _43 *= fInv; _44 *= fInv;
			return *this;
		}

		inline Matrix Matrix::operator -(void) const
		{
			return Matrix(
				-_11, -_12, -_13, -_14,
				-_21, -_22, -_23, -_24,
				-_31, -_32, -_33, -_34,
				-_41, -_42, -_43, -_44);
		}

		inline Matrix Matrix::operator +(const Matrix &mat) const
		{
			return Matrix(
				_11 + mat._11, _12 + mat._12, _13 + mat._13, _14 + mat._14,
				_21 + mat._21, _22 + mat._22, _23 + mat._23, _24 + mat._24,
				_31 + mat._31, _32 + mat._32, _33 + mat._33, _34 + mat._34,
				_41 + mat._41, _42 + mat._42, _43 + mat._43, _44 + mat._44);
		}

		inline Matrix Matrix::operator -(const Matrix &mat) const
		{
			return Matrix(
				_11 - mat._11, _12 - mat._12, _13 - mat._13, _14 - mat._14,
				_21 - mat._21, _22 - mat._22, _23 - mat._23, _24 - mat._24,
				_31 - mat._31, _32 - mat._32, _33 - mat._33, _34 - mat._34,
				_41 - mat._41, _42 - mat._42, _43 - mat._43, _44 - mat._44);
		}

		inline Matrix Matrix::operator *(const Matrix &mat) const
		{
			return Matrix(
				_11 * mat._11 + _21 * mat._12 + _31 * mat._13 + _41 * mat._14,
				_12 * mat._11 + _22 * mat._12 + _32 * mat._13 + _42 * mat._14,
				_13 * mat._11 + _23 * mat._12 + _33 * mat._13 + _43 * mat._14,
				_14 * mat._11 + _24 * mat._12 + _34 * mat._13 + _44 * mat._14,
				_11 * mat._21 + _21 * mat._22 + _31 * mat._23 + _41 * mat._24,
				_12 * mat._21 + _22 * mat._22 + _32 * mat._23 + _42 * mat._24,
				_13 * mat._21 + _23 * mat._22 + _33 * mat._23 + _43 * mat._24,
				_14 * mat._21 + _24 * mat._22 + _34 * mat._23 + _44 * mat._24,
				_11 * mat._31 + _21 * mat._32 + _31 * mat._33 + _41 * mat._34,
				_12 * mat._31 + _22 * mat._32 + _32 * mat._33 + _42 * mat._34,
				_13 * mat._31 + _23 * mat._32 + _33 * mat._33 + _43 * mat._34,
				_14 * mat._31 + _24 * mat._32 + _34 * mat._33 + _44 * mat._34,
				_11 * mat._41 + _21 * mat._42 + _31 * mat._43 + _41 * mat._44,
				_12 * mat._41 + _22 * mat._42 + _32 * mat._43 + _42 * mat._44,
				_13 * mat._41 + _23 * mat._42 + _33 * mat._43 + _43 * mat._44,
				_14 * mat._41 + _24 * mat._42 + _34 * mat._43 + _44 * mat._44);
		}

		inline Matrix Matrix::operator *(float f) const
		{
			return Matrix(
				_11 * f, _12 * f, _13 * f, _14 * f,
				_21 * f, _22 * f, _23 * f, _24 * f,
				_31 * f, _32 * f, _33 * f, _34 * f,
				_41 * f, _42 * f, _43 * f, _44 * f);
		}

		inline Matrix Matrix::operator /(float f) const
		{
			float inv = 1.0f / f;
			return Matrix(
				_11 * inv, _12 * inv, _13 * inv, _14 * inv,
				_21 * inv, _22 * inv, _23 * inv, _24 * inv,
				_31 * inv, _32 * inv, _33 * inv, _34 * inv,
				_41 * inv, _42 * inv, _43 * inv, _44 * inv);
		}

		inline bool Matrix::operator ==(const Matrix &mat) const
		{
			return 0 == memcmp(this, &mat, sizeof(Matrix));
		}

		inline bool Matrix::operator !=(const Matrix &mat) const
		{
			return 0 != memcmp(this, &mat, sizeof(Matrix));
		}

		inline Matrix& Matrix::Identity(void)
		{
			_11 = 1.0f; _12 = 0.0f; _13 = 0.0f; _14 = 0.0f;
			_21 = 0.0f; _22 = 1.0f; _23 = 0.0f; _24 = 0.0f;
			_31 = 0.0f; _32 = 0.0f; _33 = 1.0f; _34 = 0.0f;
			_41 = 0.0f; _42 = 0.0f; _43 = 0.0f; _44 = 1.0f;
			return *this;
		}

		inline void Matrix::SetMatrix(const Matrix &m)
		{
			*this = m;
		}
		inline void Matrix::SetMatrix(const float *pf)
		{
			memcpy(&_11, pf, sizeof(Matrix));
		}
		inline void Matrix::SetMatrix(
			float _11, float _12, float _13, float _14,
			float _21, float _22, float _23, float _24,
			float _31, float _32, float _33, float _34,
			float _41, float _42, float _43, float _44)
		{
			this->_11 = _11; this->_12 = _12; this->_13 = _13; this->_14 = _14;
			this->_21 = _21; this->_22 = _22; this->_23 = _23; this->_24 = _24;
			this->_31 = _31; this->_32 = _32; this->_33 = _33; this->_34 = _34;
			this->_41 = _41; this->_42 = _42; this->_43 = _43; this->_44 = _44;
		}

		inline Matrix operator *(float f, const Matrix &mat)
		{
			return mat * f;
		}

		////////////////////////////
		//// Color
		////////////////////////////

		inline Color::Color(void) :
			r(1.0f), g(1.0f), b(1.0f), a(1.0f) {}

		inline Color::Color(float r, float g, float b) :
			r(r), g(g), b(b), a(1.0f) {}

		inline Color::Color(float r, float g, float b, float a) :
			r(r), g(g), b(b), a(a) {}

		inline Color::Color(int r, int g, int b) : a(1.0f)
		{
			float div = 1.0f / 255.0f;
			this->r = div * (float)r;
			this->g = div * (float)g;
			this->b = div * (float)b;
		}

		inline Color::Color(int r, int g, int b, int a)
		{
			float div = 1.0f / 255.0f;
			this->r = div * (float)r;
			this->g = div * (float)g;
			this->b = div * (float)b;
			this->a = div * (float)a;
		}

		inline Color::Color(ARGB ulcolor)
		{
			float div = 1.0f / 255.0f;
			r = div * (float)(unsigned char)(ulcolor >> 16);
			g = div * (float)(unsigned char)(ulcolor >> 8);
			b = div * (float)(unsigned char)ulcolor;
			a = div * (float)(unsigned char)(ulcolor >> 24);
		}

		inline Color::operator ARGB(void) const
		{
			ARGB dwR = r >= 1.0f ? 0xff : r <= 0.0f ? 0x00 : (ARGB)(r * 255.0f + 0.5f);
			ARGB dwG = g >= 1.0f ? 0xff : g <= 0.0f ? 0x00 : (ARGB)(g * 255.0f + 0.5f);
			ARGB dwB = b >= 1.0f ? 0xff : b <= 0.0f ? 0x00 : (ARGB)(b * 255.0f + 0.5f);
			ARGB dwA = a >= 1.0f ? 0xff : a <= 0.0f ? 0x00 : (ARGB)(a * 255.0f + 0.5f);

			return (dwA << 24) | (dwR << 16) | (dwG << 8) | dwB;
		}

		inline Color Color::operator +(const Color &c) const
		{
			return Color(r + c.r, g + c.g, b + c.b, a + c.a);
		}

		inline Color Color::operator -(const Color &c) const
		{
			return Color(r - c.r, g - c.g, b - c.b, a - c.a);
		}

		inline Color Color::operator /(const Color &c) const
		{
			return Color(r / c.r, g / c.g, b / c.b, a / c.a);
		}

		inline Color Color::operator *(const Color &c) const
		{
			return Color(r * c.r, g * c.g, b * c.b, a * c.a);
		}

		inline Color Color::operator +(float f) const
		{
			return Color(r + f, g + f, b + f, a + f);
		}

		inline Color Color::operator -(float f) const
		{
			return Color(r - f, g - f, b - f, a - f);
		}

		inline Color Color::operator /(float f) const
		{
			float inv = 1.0f / f;
			return Color(r * f, g * f, b * f, a * f);
		}

		inline Color Color::operator *(float f) const
		{
			return Color(r * f, g * f, b * f, a * f);
		}

		inline Color& Color::operator +=(const Color &c)
		{
			r += c.r;
			g += c.g;
			b += c.b;
			a += c.a;
			return *this;
		}

		inline Color& Color::operator -=(const Color &c)
		{
			r -= c.r;
			g -= c.g;
			b -= c.b;
			a -= c.a;
			return *this;
		}

		inline Color& Color::operator /=(const Color &c)
		{
			r /= c.r;
			g /= c.g;
			b /= c.b;
			a /= c.a;
			return *this;
		}

		inline Color& Color::operator *=(const Color &c)
		{
			r *= c.r;
			g *= c.g;
			b *= c.b;
			a *= c.a;
			return *this;
		}

		inline Color& Color::operator +=(float f)
		{
			r += f;
			g += f;
			b += f;
			a += f;
			return *this;
		}

		inline Color& Color::operator -=(float f)
		{
			r -= f;
			g -= f;
			b -= f;
			a -= f;
			return *this;
		}

		inline Color& Color::operator /=(float f)
		{
			float inv = 1.0f / f;
			r *= inv;
			g *= inv;
			b *= inv;
			a *= inv;
			return *this;
		}

		inline Color& Color::operator *=(float f)
		{
			r *= f;
			g *= f;
			b *= f;
			a *= f;
			return *this;
		}

		inline Color& Color::operator =(ARGB ulcolor)
		{
			float div = 1.0f / 255.0f;
			a = div * (float)(unsigned char)(ulcolor >> 24);
			r = div * (float)(unsigned char)(ulcolor >> 16);
			g = div * (float)(unsigned char)(ulcolor >> 8);
			b = div * (float)(unsigned char)(ulcolor >> 0);
			return *this;
		}

		inline bool Color::operator ==(const Color &c) const
		{
			return equal(r, c.r) && equal(g, c.g) && equal(b, c.b) && equal(a, c.a);
		}

		inline bool Color::operator ==(ARGB ulcolor) const
		{
			return
				(unsigned char)(a * 255.0f) == (unsigned char)(ulcolor >> 24) &&
				(unsigned char)(r * 255.0f) == (unsigned char)(ulcolor >> 16) &&
				(unsigned char)(g * 255.0f) == (unsigned char)(ulcolor >> 8) &&
				(unsigned char)(b * 255.0f) == (unsigned char)(ulcolor >> 0);
		}

		inline bool Color::operator !=(const Color &c) const
		{
			return unequal(r, c.r) || unequal(g, c.g) || unequal(b, c.b) || unequal(a, c.a);
		}

		inline bool Color::operator !=(ARGB ulcolor) const
		{
			return
				(unsigned char)(a * 255.0f) != (unsigned char)(ulcolor >> 24) ||
				(unsigned char)(r * 255.0f) != (unsigned char)(ulcolor >> 16) ||
				(unsigned char)(g * 255.0f) != (unsigned char)(ulcolor >> 8) ||
				(unsigned char)(b * 255.0f) != (unsigned char)(ulcolor >> 0);
		}

		inline void Color::SetColor(const Color &c)
		{
			a = c.a;
			r = c.r;
			g = c.g;
			b = c.b;
		}
		inline void Color::SetColor(float r, float g, float b)
		{
			this->r = r;
			this->g = g;
			this->b = b;
		}
		inline void Color::SetColor(float r, float g, float b, float a)
		{
			this->r = r;
			this->g = g;
			this->b = b;
			this->a = a;
		}
		inline void Color::SetColor(int r, int g, int b)
		{
			float div = 1.0f / 255.0f;
			this->r = div * r;
			this->g = div * g;
			this->b = div * b;
		}
		inline void Color::SetColor(int r, int g, int b, int a)
		{
			float div = 1.0f / 255.0f;
			this->r = div * (float)r;
			this->g = div * (float)g;
			this->b = div * (float)b;
			this->a = div * (float)a;
		}
		inline void Color::SetColor(ARGB ulcolor)
		{
			float div = 1.0f / 255.0f;
			a = div * (float)(unsigned char)(ulcolor >> 24);
			r = div * (float)(unsigned char)(ulcolor >> 16);
			g = div * (float)(unsigned char)(ulcolor >> 8);
			b = div * (float)(unsigned char)(ulcolor >> 0);
		}

		inline ARGB COLOR_RGB(int r, int g, int b)
		{
			return COLOR_RGBA(0xff, r, g, b);
		}
		inline ARGB COLOR_RGBA(int r, int g, int b, int a)
		{
			return (ARGB)(((a & 0xff) << 24) | ((r & 0xff) << 16) | ((g & 0xff) << 8) | (b & 0xff));
		}
		inline Color operator +(float f, const Color &c)
		{
			return c + f;
		}
		inline Color operator *(float f, const Color &c)
		{
			return c * f;
		}
		inline bool operator ==(ARGB ulcolor, const Color &c)
		{
			return c == ulcolor;
		}
		inline bool operator !=(ARGB ulcolor, const Color &c)
		{
			return c != ulcolor;
		}

		////////////////////////////
		//// Rect
		////////////////////////////

		inline Rect::Rect(void)
		{
			left = top = right = bottom = 0.0f;
		}

		inline Rect::Rect(float left, float top, float right, float bottom)
		{
			this->left = left;
			this->top = top;
			this->right = right;
			this->bottom = bottom;
		}

		inline Rect::Rect(const Vector &LeftTop, const Dimension &WidthHeight)
		{
			left = LeftTop.x;
			top = LeftTop.y;
			right = left + WidthHeight.cx;
			bottom = top + WidthHeight.cy;
		}

		inline Rect::Rect(const Vector &LeftTop, const Vector &RightBottom)
		{
			left = LeftTop.x;
			top = LeftTop.y;
			right = RightBottom.x;
			bottom = RightBottom.y;
		}

		inline Rect::Rect(const Vector &Pos)
		{
			left = right = Pos.x;
			top = bottom = Pos.y;
		}

		inline Rect Rect::operator +(const Rect &r) const
		{
			return Rect(left + r.left, top + r.top, right + r.right, bottom + r.bottom);
		}

		inline Rect Rect::operator -(const Rect &r) const
		{
			return Rect(left - r.left, top - r.top, right - r.right, bottom - r.bottom);
		}

		inline Rect Rect::operator /(const Rect &r) const
		{
			return Rect(left / r.left, top / r.top, right / r.right, bottom / r.bottom);
		}

		inline Rect Rect::operator *(const Rect &r) const
		{
			return Rect(left * r.left, top * r.top, right * r.right, bottom * r.bottom);
		}

		inline Rect Rect::operator +(const Vector &v) const
		{
			return Rect(left + v.x, top + v.y, right + v.x, bottom + v.y);
		}

		inline Rect Rect::operator -(const Vector &v) const
		{
			return Rect(left - v.x, top - v.y, right - v.x, bottom - v.y);
		}

		inline Rect Rect::operator +(const Dimension &s) const
		{
			return Rect(left, top, right + s.cx, bottom + s.cy);
		}

		inline Rect Rect::operator -(const Dimension &s) const
		{
			return Rect(left, top, right - s.cx, bottom - s.cy);
		}

		inline Rect& Rect::operator +=(const Rect &r)
		{
			left += r.left;
			top += r.top;
			right += r.right;
			bottom += r.bottom;
			return *this;
		}

		inline Rect& Rect::operator -=(const Rect &r)
		{
			left -= r.left;
			top -= r.top;
			right -= r.right;
			bottom -= r.bottom;
			return *this;
		}

		inline Rect& Rect::operator /=(const Rect &r)
		{
			left /= r.left;
			top /= r.top;
			right /= r.right;
			bottom /= r.bottom;
			return *this;
		}

		inline Rect& Rect::operator *=(const Rect &r)
		{
			left *= r.left;
			top *= r.top;
			right *= r.right;
			bottom *= r.bottom;
			return *this;
		}

		inline Rect& Rect::operator +=(const Vector &v)
		{
			left += v.x;
			top += v.y;
			right += v.x;
			bottom += v.y;
			return *this;
		}

		inline Rect& Rect::operator -=(const Vector &v)
		{
			left -= v.x;
			top -= v.y;
			right -= v.x;
			bottom -= v.y;
			return *this;
		}

		inline Rect& Rect::operator +=(const Dimension &s)
		{
			right += s.cx;
			bottom += s.cy;
			return *this;
		}

		inline Rect& Rect::operator -=(const Dimension &s)
		{
			right -= s.cx;
			bottom -= s.cy;
			return *this;
		}

		inline bool Rect::operator ==(const Rect &r) const
		{
			return (equal(left, r.left) && equal(top, r.top) && equal(right, r.right) && equal(bottom, r.bottom));
		}

		inline bool Rect::operator !=(const Rect &r) const
		{
			return (unequal(left, r.left) || unequal(top, r.top) || unequal(right, r.right) || unequal(bottom, r.bottom));
		}

		inline float Rect::Width(void) const
		{
			return right - left;
		}

		inline float Rect::Height(void) const
		{
			return bottom - top;
		}

		inline Rect& Rect::Normalize(void)
		{
			float tmp;
			if (right < left)
			{
				tmp = right;
				right = left;
				left = tmp;
			}
			if (bottom < top)
			{
				tmp = bottom;
				bottom = top;
				top = tmp;
			}
			return *this;
		}

		inline bool Rect::Intersected(const Rect &r) const
		{
			return
				left < r.right &&
				right > r.left &&
				top < r.bottom &&
				bottom > r.top;
		}

		inline bool Rect::Intersected(const Circle &c) const
		{
			return c.Intersected(*this);
		}

		inline void Rect::SetRect(const Rect &r)
		{
			*this = r;
		}
		inline void Rect::SetRect(float left, float top, float right, float bottom)
		{
			this->left = left;
			this->top = top;
			this->right = right;
			this->bottom = bottom;
		}
		inline void Rect::SetRect(const Vector &LeftTop, const Dimension &WidthHeight)
		{
			left = LeftTop.x;
			top = LeftTop.y;
			right = left + WidthHeight.cx;
			bottom = top + WidthHeight.cy;
		}
		inline void Rect::SetRect(const Vector &LeftTop, const Vector &RightBottom)
		{
			left = LeftTop.x;
			top = LeftTop.y;
			right = RightBottom.x;
			bottom = RightBottom.y;
		}
		inline void Rect::SetRect(const Vector &Pos)
		{
			left = right = Pos.x;
			top = bottom = Pos.y;
		}

		inline Rect operator +(const Vector &v, const Rect &r)
		{
			return r + v;
		}
		inline Rect operator -(const Vector &v, const Rect &r)
		{
			return r + v;
		}
		inline Rect operator +(const Dimension &s, const Rect &r)
		{
			return r + s;
		}
		inline Rect operator -(const Dimension &s, const Rect &r)
		{
			return r + s;
		}

	}
}
