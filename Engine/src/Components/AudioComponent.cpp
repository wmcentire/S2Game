#include "AudioComponent.h"
#include "Engine.h"
namespace pb {
	void AudioComponent::Update()
	{

	}

	void AudioComponent::PlaySound()
	{
		pb::g_audiosystem.PlayAudio(m_soundname);
	}

	void AudioComponent::StopSound()
	{

	}
}