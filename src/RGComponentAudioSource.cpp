#include "RGComponentAudioSource.h"

#include "RGApplication.h"

namespace RGEngine
{
	namespace Components
	{
		AudioSource::AudioSource(GameObject *gameObject) : Component(gameObject), m_channel(NULL) {}
		AudioSource::~AudioSource() {}

		Assets::Sound* AudioSource::GetSound(void) const
		{
			return m_sound;
		}

		void AudioSource::SetSound(std::string path)
		{
			if (RGAssetSound->Get(path) == NULL)
			{
				RGAssetSound->Load(path);
			}
			m_sound = RGAssetSound->Get(path);
		}

		bool AudioSource::IsPlaying(void) const
		{
			bool playing;
			m_channel->isPlaying(&playing);
			return std::move(playing);
		}

		void AudioSource::Play(void)
		{
			m_sound->Play(&m_channel);
		}
		void AudioSource::Pause(void)
		{
			m_channel->setPaused(true);
		}
		void AudioSource::Resume(void)
		{
			m_channel->setPaused(false);
		}
		void AudioSource::Stop(void)
		{
			m_channel->stop();
		}

		unsigned int AudioSource::GetPosition(void) const
		{
			unsigned int p;
			m_channel->getPosition(&p, FMOD_TIMEUNIT_MS);
			return std::move(p);
		}
		float AudioSource::GetVolume(void) const
		{
			float v;
			m_channel->getVolume(&v);
			return std::move(v);
		}
		float AudioSource::GetFrequency(void) const
		{
			float f;
			m_channel->getFrequency(&f);
			return std::move(f);
		}
		float AudioSource::GetPan(void) const
		{
			float p;
			m_channel->getPan(&p);
			return std::move(p);
		}
		bool AudioSource::GetMute(void) const
		{
			bool b;
			m_channel->getMute(&b);
			return std::move(b);
		}

		void AudioSource::SetPosition(unsigned int position)
		{
			m_channel->setPosition(position, FMOD_TIMEUNIT_MS);
		}
		void AudioSource::SetVolume(float volume)
		{
			m_channel->setVolume(volume);
		}
		void AudioSource::SetFrequency(float frequency)
		{
			m_channel->setFrequency(frequency);
		}
		void AudioSource::SetPan(float pan)
		{
			m_channel->setPan(pan);
		}
		void AudioSource::SetMute(bool b)
		{
			m_channel->setMute(b);
		}

		void AudioSource::Reset(void)
		{
			m_sound = NULL;
		}
	}
}