#include "AudioChannel.h"
#include "fmod.hpp"

namespace pb {
	bool AudioChannel::IsPlaying()
	{
		if (m_channel == nullptr) return false;

		bool isPlaying;
		m_channel->isPlaying(&isPlaying);
		

		return isPlaying;
	}
	void AudioChannel::Stop()
	{
		if (IsPlaying()) m_channel->stop();
	}
	float AudioChannel::GetPitch()
	{
		float pitch = 0;
		if (IsPlaying()) m_channel->getPitch(&pitch);

		return pitch;
	}
	float AudioChannel::GetVolume()
	{
		float volume = 0;
		if (IsPlaying()) m_channel->getVolume(&volume);

		return volume;
	}
	void AudioChannel::SetPitch(float pitch)
	{
		if (IsPlaying()) m_channel->setPitch(pitch);
	}
	void AudioChannel::SetVolume(float volume)
	{
		if (IsPlaying()) m_channel->setVolume(volume);
	}
}