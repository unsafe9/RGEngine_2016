#ifndef _RGASSETSOUND_H_
#define _RGASSETSOUND_H_


#include <fmod.hpp>
// #pragma comment(lib, "fmodex_vc.lib")

#include <string>

namespace RGEngine
{
	namespace Assets
	{
		class Sound
		{
		private:
			FMOD::System *m_system;
			FMOD::Sound *m_sound;
			std::string m_path;

		public:
			Sound(FMOD::System *system);
			~Sound();

			bool Load(std::string path);
			bool Load(std::string path, int loopcount);
			void Release(void);

			bool IsLooping(void) const;

			void Play(FMOD::Channel **channel, bool paused = false);

			FMOD::System* GetSystem(void) const;
			std::string GetPath(void) const;
			unsigned int GetLength(void) const; // millisec
			int GetLoopCount(void) const;
			unsigned int GetLoopStartPoint(void) const;
			unsigned int GetLoopEndPoint(void) const;

			void SetLoop(bool b);
			void SetLoopCount(int loopcount);
			void SetLoopPoints(unsigned int loopstart, unsigned int loopend); // millisec

		};
	}
}

#endif // _RGASSETSOUND_H_