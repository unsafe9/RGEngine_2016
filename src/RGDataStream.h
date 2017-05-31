#ifndef _RGDATASTREAM_H_
#define _RGDATASTREAM_H_

#include <fstream>
#include <cassert>

namespace RGEngine
{
	class DataStream
	{
	public:
		DataStream(void) {}
		virtual ~DataStream() {}

		virtual bool Open(std::string path) = 0 {}
		virtual void Close(void) = 0 {}

		virtual void Clear(void) = 0 {}

		virtual bool Validate(void) const = 0 {}

		virtual std::string GetPath(void) const = 0 {}
		virtual int GetSize(void) const = 0 {}

	};


}

#endif // _RGDATASTREAM_H_
