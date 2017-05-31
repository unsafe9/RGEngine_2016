#ifndef _RGDATASTREAMFILE_H_
#define _RGDATASTREAMFILE_H_

#include "RGDataStream.h"
#include <fstream>
#include <cassert>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/locking.h>

namespace RGEngine
{
	namespace DataStreams
	{
		enum FileOpenType
		{
			Read,
			Write,
			Append,
			ReadNWrite
		};

		struct FileStat
		{
			unsigned int	dev;	// ID of device containing file
			unsigned short	ino;	// inode number
			unsigned short	mode;	// protection
			short			nlink;	// number of hard links
			short			uid;	// user ID of owner
			short			gid;	// group ID of owner
			unsigned int	rdev;	// device ID (if special file)
			long			size;	// total size, in byte
			long long		atime;	// time of last access
			long long		mtime;	// time of last modification
			long long		ctime;	// created time
		};

		class File : public DataStream
		{
		private:
			FILE *m_stream;
			FileOpenType m_type;
			std::string m_path;

		public:
			File(void);
			~File() override;

			bool Open(std::string path) override;
			bool Open(std::string path, FileOpenType access);
			void Close(void) override;

			void Clear(void) override;

			bool Validate(void) const override;

			std::string GetPath(void) const override;
			int GetSize(void) const override;
			FileOpenType GetFileOpenType(void) const;
			void GetFileStat(FileStat *stat) const;
			void GetFileStat(FileStat &stat) const;

			int Write(const char *format, ...);
			int Read(const char *format, ...);
			template<typename T>
			T ReadBytes(void);
			template<typename T>
			size_t ReadBytes(T *out, size_t cnt);
			std::string ReadAll(void);
			std::string GetLine(char d = '\n');

			void SeekFromBegin(int offset);
			void SeekFromEnd(int offset);
			void SeekFromCursor(int offset);
			int Tell(void);

		};

		template<typename T>
		inline T File::ReadBytes(void)
		{
			assert(m_stream != NULL);
			T out;
			fread((void *)&out, sizeof(T), 1, m_stream);
			return std::move(out);
		}

		template<typename T>
		inline size_t File::ReadBytes(T *out, size_t cnt)
		{
			assert(m_stream != NULL);
			return fread((void *)out, sizeof(T), cnt, m_stream);
		}

	}
}

#endif // _RGDATASTREAMFILE_H_
