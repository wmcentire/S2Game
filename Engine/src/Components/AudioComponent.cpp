#include "AudioComponent.h"
#include "Engine.h"
namespace pb {
	AudioComponent::~AudioComponent()
	{
		StopSound();
	}
	void AudioComponent::Initialize()
	{
		if (play_on_start)
		{
			PlaySound();
		}
	}
	void AudioComponent::Update()
	{

	}

	void AudioComponent::PlaySound()
	{
		m_channel.Stop();

		m_channel = g_audiosystem.PlayAudio(sound_name, volume, pitch, loop);
	}

	void AudioComponent::StopSound()
	{
		m_channel.Stop();
	}
	bool AudioComponent::Write(const rapidjson::Value& value) const
	{
		return true;
	}
	bool AudioComponent::Read(const rapidjson::Value& value)
	{
		READ_DATA(value, sound_name);
		READ_DATA(value, volume);
		READ_DATA(value, pitch);
		READ_DATA(value, play_on_start);
		READ_DATA(value, loop);

		g_audiosystem.AddAudio(sound_name, sound_name);

		return true;
	}
}