#include "Model.h"
#include "Core/File.h"
#include <sstream>

namespace pb
{
    Model::Model(const std::string& filename)
    {
        Load(filename);
        m_radius = CalculateRadius();
    }
    void Model::Draw(pb::Renderer& renderer, const pb::Vector2& position, float angle, float scale)
    {
        for (int i = 0; i < m_points.size() - 1; i++)
        {
            pb::Vector2 p1 = pb::Vector2::Rotate((m_points[i] * scale), angle) + position;
            pb::Vector2 p2 = pb::Vector2::Rotate((m_points[i + 1] * scale), angle) + position;

            renderer.DrawLine(p1, p2, m_color);
        }
    }
    void Model::Load(const std::string& filename)
    {
        std::string buffer;

        pow_fi::ReadFile(filename, buffer);


        std::istringstream stream(buffer);
        stream >> m_color;


        //std::cout << "load\n";
        std::string line;
        std::getline(stream,line);

        size_t numPoints = std::stoi(line);
        for (size_t i = 0; i < numPoints; i++) {
            pb::Vector2 v;
            stream >> v;
            m_points.push_back(v);
        }
    }
    float Model::CalculateRadius()
    {
        float radius = 0;

        for (auto point : m_points) {
            point.Length();
            if (point.Length() > radius) {
                radius = point.Length();
            }
        }

        return radius;
    }
}
