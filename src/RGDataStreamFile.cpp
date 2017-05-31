#include "RGDataStreamFile.h"

#include <cstdarg>

namespace RGEngine
{
	namespace DataStreams
	{
		File::File(void) : m_stream(NULL), m_type(FileOpenType::Read) {}

		File::~File() { Clear(); }

		bool File::Open(std::string path)
		{
			return Open(path, FileOpenType::ReadNWrite);
		}

		bool File::Open(std::string path, FileOpenType access)
		{
			assert(m_stream == NULL);

			m_path = path;
			m_type = access;
			switch (m_type)
			{
			case FileOpenType::Read:
				fopen_s(&m_stream, m_path.c_str(), "r");
				break;

			case FileOpenType::Write:
				fopen_s(&m_stream, m_path.c_str(), "w");
				break;

			case FileOpenType::Append:
				fopen_s(&m_stream, m_path.c_str(), "a");
				break;

			case FileOpenType::ReadNWrite:
				fopen_s(&m_stream, m_path.c_str(), "r+");
				break;

			}
			return m_stream != NULL;
		}

		void File::Close(void)
		{
			fclose(m_stream);
			m_stream = NULL;
		}

		void File::Clear(void)
		{
			Close();
			m_type = FileOpenType::Read;
			m_path.clear();
		}
		
		bool File::Validate(void) const
		{
			return m_stream && !feof(m_stream);
		}

		std::string File::GetPath(void) const
		{
			assert(m_stream != NULL);
			return m_path;
		}
		FileOpenType File::GetFileOpenType(void) const
		{
			assert(m_stream != NULL);
			return m_type;
		}
		void File::GetFileStat(FileStat *stat) const
		{
			assert(m_stream != NULL);
			fstat(_fileno(m_stream), (struct stat *)stat);
		}
		void File::GetFileStat(FileStat &stat) const
		{
			assert(m_stream != NULL);
			fstat(_fileno(m_stream), (struct stat *)&stat);
		}
		int File::GetSize(void) const
		{
			assert(m_stream != NULL);
			
			struct stat stat_buf;
			int rc = fstat(_fileno(m_stream), &stat_buf);
			return rc == 0 ? stat_buf.st_size : -1;
		}
		
		int File::Write(const char *format, ...)
		{
			assert(m_stream != NULL);

			va_list arg;
			va_start(arg, format);
			int res = vfprintf(m_stream, format, arg);
			va_end(arg);
			return std::move(res);
		}

		int File::Read(const char *format, ...)
		{
			assert(m_stream != NULL);

			va_list arg;
			va_start(arg, format);
			int res = vfscanf(m_stream, format, arg);
			va_end(arg);
			return std::move(res);
		}

		std::string File::ReadAll(void)
		{
			assert(m_stream != NULL);

			fseek(m_stream, 0, SEEK_END);
			size_t size = ftell(m_stream);
			rewind(m_stream);

			char *buf = new char[size];
			fread(buf, sizeof(char), size, m_stream);
			std::string res(buf);
			delete[] buf;
			return std::move(res);
		}

		std::string File::GetLine(char d)
		{
			assert(m_stream != NULL);

			std::string temp;
			char c;
			for (;;)
			{
				c = static_cast<char>(fgetc(m_stream));
				if (feof(m_stream) || c == d)
				{
					break;
				}
				temp += c;
			}
			return std::move(temp);
		}

		void File::SeekFromBegin(int offset)
		{
			assert(m_stream != NULL);
			fseek(m_stream, offset, SEEK_SET);
		}
		void File::SeekFromEnd(int offset)
		{
			assert(m_stream != NULL);
			fseek(m_stream, offset, SEEK_END);
		}
		void File::SeekFromCursor(int offset)
		{
			assert(m_stream != NULL);
			fseek(m_stream, offset, SEEK_CUR);
		}
		int File::Tell(void)
		{
			assert(m_stream != NULL);
			return ftell(m_stream);
		}
	}
}