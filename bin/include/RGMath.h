#ifndef _RGMATH_H_
#define _RGMATH_H_

#include <cmath>

namespace RGEngine
{
	namespace Math
	{		
#define RG_M_PI 3.1415926535897932f
#define RG_M_PI_DOUBLE 6.2831853071795865f
#define RG_M_PI_HALF 1.5707963267948966f
#define RG_M_PI_SQUARE 9.8696044010893586f
#define RG_M_E 2.7182818284590452f
#define RG_M_RAD_PER_DEG 0.0174532925199433f
#define RG_M_DEG_PER_RAD 57.2957795130823069f

		struct Vector;
		struct Rect;

		float DegToRad(float _degree);
		float RadToDeg(float _radian);
		int Random(int _from, int _to);
		float Random(float _from, float _to);
		float Distance(const Vector &a, const Vector &b);
		float DistanceDouble(const Vector &a, const Vector &b);
		float Sign(float x);
		float Clamp(float a, float low, float high);

		template<typename T> void Swap(T& a, T& b);
		template<typename T> T Abs(const T &a, const T &b);
		template<typename T> const T& Max(const T &a, const T &b);
		template<typename T> const T& Min(const T &a, const T &b);

		typedef unsigned long ARGB; // typedef

		struct Vector
		{
			float x, y;

			Vector(void);
			Vector(float x, float y);

			operator float*(void);
			operator const float*(void) const;

			Vector operator +(const Vector &v) const;
			Vector operator -(const Vector &v) const;
			Vector operator /(const Vector &v) const;
			Vector operator *(const Vector &v) const;

			Vector operator *(float f) const;
			Vector operator /(float f) const;

			Vector operator -(void) const;

			Vector& operator +=(const Vector &v);
			Vector& operator -=(const Vector &v);
			Vector& operator /=(const Vector &v);
			Vector& operator *=(const Vector &v);

			Vector& operator *=(float f);
			Vector& operator /=(float f);

			bool operator ==(const Vector &v) const;
			bool operator !=(const Vector &v) const;

			float Dot(const Vector &a, const Vector &b);
			float Cross(const Vector &a, const Vector &b);
			Vector Cross(const Vector &a, float s);
			Vector Cross(float s, const Vector &a);

			void Transform(float x, float y);
			void Transform(const Vector &v);

			void SetVector(const Vector &v);
			void SetVector(float x, float y);
		};
		Vector operator *(float f, const Vector &v);

		struct Dimension
		{
			float cx, cy;

			Dimension(void);
			Dimension(float cx, float cy);

			Dimension operator +(const Dimension &s) const;
			Dimension operator -(const Dimension &s) const;
			Dimension operator /(const Dimension &s) const;
			Dimension operator *(const Dimension &s) const;

			Dimension operator -(void) const;

			Dimension& operator +=(const Dimension &s);
			Dimension& operator -=(const Dimension &s);
			Dimension& operator /=(const Dimension &s);
			Dimension& operator *=(const Dimension &s);

			bool operator ==(const Dimension &s) const;
			bool operator !=(const Dimension &s) const;

			void SetDimension(const Dimension &s);
			void SetDimension(float cx, float cy);

		};

		struct Circle
		{
			Vector center;
			float radius;

			Circle(void);
			Circle(float x, float y, float radius);
			Circle(const Vector &center, float radius);

			float Area(void) const; // 넓이
			float Diameter(void) const; // 지름
			float Circumference() const; // 둘레

			bool Intersected(const Circle &c) const;
			bool Intersected(const Rect &r) const;

			void SetCircle(const Circle &c);
			void SetCircle(float x, float y, float radius);
			void SetCircle(const Vector &center, float radius);

		};

		struct Matrix
		{
			union
			{
				struct
				{
					float _11, _12, _13, _14;
					float _21, _22, _23, _24;
					float _31, _32, _33, _34;
					float _41, _42, _43, _44;
				};
				float m[4][4];
			};

			Matrix(void);
			Matrix(const float *f);
			Matrix(
				float _11, float _12, float _13, float _14,
				float _21, float _22, float _23, float _24,
				float _31, float _32, float _33, float _34,
				float _41, float _42, float _43, float _44);

			float& operator ()(int Row, int Col);
			float operator ()(int Row, int Col) const;

			operator float* (void);
			operator const float* (void) const;

			Matrix& operator +=(const Matrix &m);
			Matrix& operator -=(const Matrix &m);
			Matrix& operator *=(const Matrix &m);

			Matrix& operator *=(float f);
			Matrix& operator /=(float f);

			Matrix operator -(void) const;

			Matrix operator +(const Matrix &m) const;
			Matrix operator -(const Matrix &m) const;
			Matrix operator *(const Matrix &m) const;

			Matrix operator *(float f) const;
			Matrix operator /(float f) const;

			bool operator ==(const Matrix &m) const;
			bool operator !=(const Matrix &m) const;

			Matrix& Identity(void);

			void SetMatrix(const Matrix &m);
			void SetMatrix(const float *f);
			void SetMatrix(
				float _11, float _12, float _13, float _14,
				float _21, float _22, float _23, float _24,
				float _31, float _32, float _33, float _34,
				float _41, float _42, float _43, float _44);

		};
		Matrix operator *(float f, const Matrix &m);

		struct Color
		{
			float r, g, b, a; // 0.0f ~ 1.0f

			Color(void);
			Color(float r, float g, float b);
			Color(float r, float g, float b, float a);
			Color(int r, int g, int b);
			Color(int r, int g, int b, int a);
			Color(ARGB ulcolor);

			operator ARGB(void) const;

			Color operator +(const Color &c) const;
			Color operator -(const Color &c) const;
			Color operator /(const Color &c) const;
			Color operator *(const Color &c) const;

			Color operator +(float f) const;
			Color operator -(float f) const;
			Color operator /(float f) const;
			Color operator *(float f) const;

			Color& operator +=(const Color &c);
			Color& operator -=(const Color &c);
			Color& operator /=(const Color &c);
			Color& operator *=(const Color &c);

			Color& operator +=(float f);
			Color& operator -=(float f);
			Color& operator /=(float f);
			Color& operator *=(float f);

			Color& operator =(ARGB ulcolor);

			bool operator ==(const Color &c) const;
			bool operator ==(ARGB ulcolor) const;
			bool operator !=(const Color &c) const;
			bool operator !=(ARGB ulcolor) const;

			void SetColor(const Color &c);
			void SetColor(float r, float g, float b);
			void SetColor(float r, float g, float b, float a);
			void SetColor(int r, int g, int b);
			void SetColor(int r, int g, int b, int a);
			void SetColor(ARGB ulcolor);

		};
		ARGB COLOR_RGB(int r, int g, int b); // 0 ~ 255
		ARGB COLOR_RGBA(int r, int g, int b, int a); // 0 ~ 255
		Color operator +(float f, const Color &c);
		Color operator *(float f, const Color &c);
		bool operator ==(ARGB ulcolor, const Color &c);
		bool operator !=(ARGB ulcolor, const Color &c);

		struct Rect
		{
			float left, top, right, bottom;

			Rect(void);
			Rect(float left, float top, float right, float bottom);
			Rect(const Vector &LeftTop, const Dimension &WidthHeight);
			Rect(const Vector &LeftTop, const Vector &RightBottom);
			Rect(const Vector &Pos);

			Rect operator +(const Rect &r) const;
			Rect operator -(const Rect &r) const;
			Rect operator /(const Rect &r) const;
			Rect operator *(const Rect &r) const;

			Rect operator +(const Vector &v) const;
			Rect operator -(const Vector &v) const;
			Rect operator +(const Dimension &s) const;
			Rect operator -(const Dimension &s) const;

			Rect& operator +=(const Rect &r);
			Rect& operator -=(const Rect &r);
			Rect& operator /=(const Rect &r);
			Rect& operator *=(const Rect &r);

			Rect& operator +=(const Vector &v);
			Rect& operator -=(const Vector &v);
			Rect& operator +=(const Dimension &s);
			Rect& operator -=(const Dimension &s);

			bool operator ==(const Rect &r) const;
			bool operator !=(const Rect &r) const;

			float Width(void) const;
			float Height(void) const;

			Rect& Normalize(void);
			
			bool Intersected(const Rect &r) const;
			bool Intersected(const Circle &c) const;

			void SetRect(const Rect &r);
			void SetRect(float left, float top, float right, float bottom);
			void SetRect(const Vector &LeftTop, const Dimension &WidthHeight);
			void SetRect(const Vector &LeftTop, const Vector &RightBottom);
			void SetRect(const Vector &Pos);

		};
		Rect operator +(const Vector &v, const Rect &r);
		Rect operator -(const Vector &v, const Rect &r);
		Rect operator +(const Dimension &s, const Rect &r);
		Rect operator -(const Dimension &s, const Rect &r);

}
}

#include "RGMath.inl"
#include "RGMath.hpp"

#endif // _RGMATH_H_