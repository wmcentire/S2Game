#pragma once
#include "Framework/Component.h"
#include "RenderComponent.h"

namespace pb {
	class Model;
	class ModelComponent : public RenderComponent {
	public:
		ModelComponent() = default;
	public:

		// Inherited via Component
		virtual bool Write(const rapidjson::Value& value) const override;

		virtual bool Read(const rapidjson::Value& value) override;
		CLASS_DECLARATION(ModelComponent)
		virtual void Update() override;

		virtual void Draw(Renderer& renderer) override;

	public:
		std::shared_ptr<Model> m_model;
	};


}