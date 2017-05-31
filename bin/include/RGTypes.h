#ifndef _RGTYPES_H_
#define _RGTYPES_H_

namespace RGEngine
{
	namespace Types
	{
		struct Point
		{
			long x, y;
			Point(void) : x(0L), y(0L) {}
			Point(long x, long y) : x(x), y(y) {}
			Point& operator +=(const Point &p) { x += p.x, y += p.y; return *this; }
			Point& operator -=(const Point &p) { x -= p.x, y -= p.y; return *this; }
			Point operator +(const Point &p) const { return Point(x + p.x, y + p.y); }
			Point operator -(const Point &p) const { return Point(x - p.x, y - p.y); }
			void Translate(long x, long y) { this->x += x, this->y += y; }
			void Translate(const Point &p) { x += p.x, y += p.y; }
			void SetPoint(const Point &p) { *this = p; }
			void SetPoint(long x, long y) { this->x = x, this->y = y; }
		};

		struct Size
		{
			long cx, cy;
			Size(void) : cx(0L), cy(0L) {}
			Size(long cx, long cy) : cx(cx), cy(cy) {}
			Size& operator +=(const Size &s) { cx += s.cx, cy += s.cy; return *this; }
			Size& operator -=(const Size &s) { cx -= s.cx, cy -= s.cy; return *this; }
			Size operator +(const Size &s) const { return Size(cx + s.cx, cy + s.cy); }
			Size operator -(const Size &s) const { return Size(cx - s.cx, cy - s.cy); }
			void SetSize(const Size &s) { *this = s; }
			void SetSize(long cx, long cy) { this->cx = cx, this->cy = cy; }
		};
		struct Rect
		{
			long left, top, right, bottom;

			Rect(void) { left = top = right = bottom = 0L; }
			Rect(long left, long top, long right, long bottom) : left(left), top(top), right(right), bottom(bottom) {}
			long Width(void) { return right - left; }
			long Height(void) { return bottom - top; }
			void SetRect(const Rect &r) { *this = r; }
			void SetRect(long _left, long _top, long _right, long _bottom) { left = _left; top = _top; right = _right; bottom = _bottom; }

		};
	}
	
}

#endif // _RGTYPES_H_