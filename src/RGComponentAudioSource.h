#ifndef _RGCOMPONENTAUDIOSOURCE_H_
#define _RGCOMPONENTAUDIOSOURCE_H_

#include "RGComponent.h"
#include "RGAssetManager.h"

namespace RGEngine
{
	namespace Components
	{
		class AudioSource : public Component
		{
		private:
			FMOD::Channel *m_channel;
			Assets::Sound *m_sound;

		public:
			AudioSource(GameObject *gameObject);
			~AudioSource() override;

			Assets::Sound* GetSound(void) const;
			void SetSound(std::string path);

			bool IsPlaying(void) const;

			void Play(void);
			void Pause(void);
			void Resume(void);
			void Stop(void);

			unsigned int GetPosition(void) const; // millisecond
			float GetVolume(void) const;
			float GetFrequency(void) const;
			float GetPan(void) const;
			bool GetMute(void) const;

			void SetPosition(unsigned int position); // millisecond
			void SetVolume(float volume); // 0.0f ~ 1.0f
			void SetFrequency(float frequency); // Hz (can be negative)
			void SetPan(float pan); // -1.0f(left) ~ 1.0f(right)
			void SetMute(bool b);

		public:
			void Reset(void) override;
			std::type_index GetID(void) override { return typeid(AudioSource); }
			std::type_index GetFamilyID(void) override { return typeid(AudioSource); }

			static std::type_index GetStaticID(void) { return typeid(AudioSource); }
			static std::type_index GetStaticFamilyID(void) { return typeid(AudioSource); }

		public:


		};
	}
}

#endif // _RGCOMPONENTAUDIOSOURCE_H_