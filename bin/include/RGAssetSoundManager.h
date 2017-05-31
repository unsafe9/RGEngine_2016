#ifndef _RGASSETSOUNDMANAGER_H_
#define _RGASSETSOUNDMANAGER_H_

#include "RGAssetSound.h"
#include <map>

namespace RGEngine
{
	namespace Assets
	{
		class SoundManager
		{
		private:
			std::map<std::string, Sound*> m_sounds;
			FMOD::System *m_system;
			FMOD::ChannelGroup *m_master;

		public:
			SoundManager(void);
			~SoundManager();

			bool Load(std::string path);
			bool Load(std::string path, int loopcount);

			void Release(std::string path);
			void ReleaseAll(void);

			Sound* Get(std::string path);

			float GetMasterVolume(void) const;
			bool GetMasterPaused(void) const;
			bool GetMasterMute(void) const;

			void SetMasterVolume(float volume);
			void SetMasterPaused(bool b);
			void SetMasterMute(bool b);

		};
	}
}

#endif // _RGASSETSOUNDMANAGER_H_