#include "Model.h"
#include "Core/File.h"
#include <sstream>
#include <Core/Logger.h>

namespace pb
{
    Model::Model(const std::string& filename)
    {
        Load(filename);
        m_radius = CalculateRadius();
    }
    bool Model::Create(std::string filename, ...)
    {
        if (!Load(filename))
        {
            LOG("!! ERROR !! could not create model%s", filename.c_str());
            return false;
        }
        return true;
    }
    void Model::Draw(pb::Renderer& renderer, const pb::Vector2& position, float angle, const pb::Vector2& scale)
    {
        for (int i = 0; i < m_points.size() - 1; i++)
        {
            pb::Vector2 p1 = pb::Vector2::Rotate((m_points[i] * scale), angle) + position;
            pb::Vector2 p2 = pb::Vector2::Rotate((m_points[i + 1] * scale), angle) + position;

            renderer.DrawLine(p1, p2, m_color);
        }
    }
    bool Model::Load(const std::string& filename)
    {
        std::string buffer;

        if (!pow_fi::ReadFile(filename, buffer))
        {
            LOG("Error could not load file %s", filename.c_str());
            return false;
        }


        std::istringstream stream(buffer);
        //read color
        stream >> m_color;

        std::string line;
        std::getline(stream, line);

        //get number of points
        size_t numPoints = std::stoi(line);

        for (size_t i = 0; i < numPoints; i++)
        {
            Vector2 point;

            stream >> point;

            m_points.push_back(point);


        }
        return true;
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
