#include "RGAssetSoundManager.h"

namespace RGEngine
{
	namespace Assets
	{
		SoundManager::SoundManager(void)
		{
			FMOD::System_Create(&m_system);
			m_system->init(1024, FMOD_INIT_NORMAL, NULL);
			m_system->getMasterChannelGroup(&m_master);
		}
		SoundManager::~SoundManager()
		{
			ReleaseAll();
			if (m_system)
			{
				m_system->close();
				m_system->release();
			}
		}
		bool SoundManager::Load(std::string path)
		{
			if (m_sounds[path] != NULL)
			{
				return true;
			}
			Sound *s = new Sound(m_system);
			bool res = s->Load(path);
			m_sounds[path] = s;
			return std::move(res);
		}
		bool SoundManager::Load(std::string path, int loopcount)
		{
			if (m_sounds[path] != NULL)
			{
				return true;
			}
			Sound *s = new Sound(m_system);
			bool res = s->Load(path, loopcount);
			m_sounds[path] = s;
			return std::move(res);
		}
		void SoundManager::Release(std::string path)
		{
			m_sounds.at(path)->Release();
			m_sounds.erase(path);
		}
		void SoundManager::ReleaseAll(void)
		{
			for (auto &i : m_sounds)
			{
				(i.second)->Release();
			}
			m_sounds.clear();
		}
		Sound* SoundManager::Get(std::string path)
		{
			return m_sounds[path];
		}

		float SoundManager::GetMasterVolume(void) const
		{
			float v = 0.0f;
			m_master->getVolume(&v);
			return v;
		}
		bool SoundManager::GetMasterPaused(void) const
		{
			bool b = false;
			m_master->getPaused(&b);
			return b;
		}
		bool SoundManager::GetMasterMute(void) const
		{
			bool b = false;
			m_master->getMute(&b);
			return b;
		}

		void SoundManager::SetMasterVolume(float volume)
		{
			m_master->setVolume(volume);
		}
		void SoundManager::SetMasterPaused(bool b)
		{
			m_master->setPaused(b);
		}
		void SoundManager::SetMasterMute(bool b)
		{
			m_master->setMute(b);
		}

	}
}