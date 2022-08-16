#pragma once
#include "Math/MathUtils.h"
#include "Core/Memory.h"
#include "Math/Vector2.h"
#include "Math/Random.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"
#include "Core/File.h"
#include "Renderer/Model.h"
#include "Framework/Actor.h"
#include "Core/Time.h"
#include "Framework/Scene.h"
#include "Audio/AudioSystem.h"
#include "Renderer/Font.h"
#include "Renderer/Text.h"
#include "Renderer/Texture.h"
#include "Components/PlayerComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/AudioComponent.h"
#include "Components/PhysicsComponent.h"
#include "Components/ModelComponent.h"
#include "Resources/ResourceManager.h"
#include "Framework/Singleton.h"
#include "Framework/Factory.h"
#include <vector>
#include <memory>


namespace pb {
	extern InputSystem g_inputSystem;
	extern Time g_time;
	extern Renderer g_renderer;
	extern AudioSystem g_audiosystem;
	extern ResourceManager g_resources;

	class Engine : public Singleton<Engine> {
	public:
		void Register();
	};
}