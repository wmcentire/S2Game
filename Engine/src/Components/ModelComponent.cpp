#include "ModelComponent.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"
#include "Renderer/Model.h"
#include "Engine.h"
namespace pb {
    bool pb::ModelComponent::Write(const rapidjson::Value& value) const
    {
        return false;
    }

    bool pb::ModelComponent::Read(const rapidjson::Value& value)
    {
        std::string model_name;
        READ_DATA(value, model_name);

        m_model = g_resources.Get<Model>(model_name);
        return true;
    }

    void ModelComponent::Update()
    {
        //
    }
    void ModelComponent::Draw(Renderer& renderer)
    {
        m_model->Draw(renderer, m_owner->m_transform.position);
    }
}