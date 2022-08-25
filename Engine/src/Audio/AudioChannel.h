#pragma once

namespace FMOD
{
	class Channel;
}

namespace pb
{
	class AudioChannel
	{
	public:
		AudioChannel() {}
		AudioChannel(FMOD::Channel* channel) { m_channel = channel; }

		bool IsPlaying();
		void Stop();

		float GetPitch();
		float GetVolume();
		
		void SetPitch(float pitch);
		void SetVolume(float volume);
		

	private:
		FMOD::Channel* m_channel = nullptr;
		float pitch = 0;
		float volume = 0;
	};
}