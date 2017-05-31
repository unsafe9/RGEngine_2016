#include "RGAssetSound.h"

#pragma comment(lib, "fmodex_vc.lib")

namespace RGEngine
{
	namespace Assets
	{
		Sound::Sound(FMOD::System *system) : m_system(system), m_sound(NULL) { }
		Sound::~Sound() { Release(); }

		bool Sound::Load(std::string path)
		{
			m_path = path;
			bool b = m_system->createSound(path.c_str(), FMOD_DEFAULT, NULL, &m_sound) == FMOD_OK;
			return b;
		}
		bool Sound::Load(std::string path, int loopcount)
		{
			m_path = path;
			if (m_system->createSound(path.c_str(), FMOD_LOOP_NORMAL, NULL, &m_sound) != FMOD_OK)
			{
				return false;
			}
			m_sound->setLoopCount(loopcount);
			return true;
		}
		void Sound::Release(void)
		{
			if (m_sound)
			{
				m_sound->release();
				m_sound = NULL;
			}
		}

		bool Sound::IsLooping(void) const
		{
			FMOD_MODE m;
			m_sound->getMode(&m);
			return m & FMOD_LOOP_NORMAL ? true : false;
		}

		void Sound::Play(FMOD::Channel **channel, bool paused)
		{
			m_system->playSound(FMOD_CHANNEL_REUSE, m_sound, paused, channel);
		}

		FMOD::System* Sound::GetSystem(void) const
		{
			return m_system;
		}
		std::string Sound::GetPath(void) const
		{
			return m_path;
		}
		unsigned int Sound::GetLength(void) const
		{
			unsigned int l;
			m_sound->getLength(&l, FMOD_TIMEUNIT_MS);
			return std::move(l);
		}
		int Sound::GetLoopCount(void) const
		{
			int c;
			m_sound->getLoopCount(&c);
			return std::move(c);
		}

		unsigned int Sound::GetLoopStartPoint(void) const
		{
			unsigned int s, e;
			m_sound->getLoopPoints(&s, FMOD_TIMEUNIT_MS, &e, FMOD_TIMEUNIT_MS);
			return s;
		}

		unsigned int Sound::GetLoopEndPoint(void) const
		{
			unsigned int s, e;
			m_sound->getLoopPoints(&s, FMOD_TIMEUNIT_MS, &e, FMOD_TIMEUNIT_MS);
			return e;
		}

		void Sound::SetLoop(bool b)
		{
			m_sound->setMode(b ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF);
		}
		void Sound::SetLoopCount(int loopcount)
		{
			m_sound->setLoopCount(loopcount);
		}
		void Sound::SetLoopPoints(unsigned int loopstart, unsigned int loopend)
		{
			m_sound->setLoopPoints(loopstart, FMOD_TIMEUNIT_MS, loopend, FMOD_TIMEUNIT_MS);
		}
	}
}