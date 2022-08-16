#pragma once
#include <string>
#include "Framework/Component.h"

namespace pb
{
	class AudioComponent : public Component
	{
	public:
		AudioComponent() = default;

		void Update() override;


		void PlaySound();
		void StopSound();

	public:
		std::string m_soundname;
		float pitch = 1;
		bool loop = false;
		bool playOnAwake = false;
	private:

	};
}