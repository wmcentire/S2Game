#pragma once
#include "Renderer.h"
#include <vector>
#include <iostream>

namespace pb {
    class Model
    {
    public:
        Model() = default;
        Model(const std::string& filename);
        Model(const std::vector<pb::Vector2>& points, const pb::Color& color) :
            m_points{ points },
            m_color{ color }
        {
            //std::vector<int> ints{1,2,3,4};
            //std::vector<int> cints{ints};
        }

        void Draw(pb::Renderer& renderer, const pb::Vector2& position, float angle, float scale);
        void Load(const std::string& filename);
        float CalculateRadius();

        float GetRadius() { return m_radius; }
    private:
        pb::Color m_color {0,0,0,0};
        std::vector<pb::Vector2> m_points;

        float m_radius = 0;
    };
}