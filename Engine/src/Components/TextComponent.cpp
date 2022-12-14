#include "TextComponent.h"
#include "Engine.h"

namespace pb {
    void TextComponent::Update()
    {

    }

    void TextComponent::Draw(Renderer& renderer)
    {
        g_renderer.Draw(m_texture, m_owner->m_transform, registration);
    }

    void TextComponent::SetText(const std::string& text)
    {
        if (color.r == 0 && color.g == 0 && color.b == 0 && color.a == 0) {
            color = color.black;
        }

        m_texture->CreateFromSurface(m_font->CreateSurface(text, color), g_renderer);

        bool pause = false;
    }

    bool TextComponent::Write(const rapidjson::Value& value) const
    {
        return true;
    }

    bool TextComponent::Read(const rapidjson::Value& value)
    {
        READ_DATA(value, text);
        READ_DATA(value, font_name);
        READ_DATA(value, font_size);
        READ_DATA(value, registration);
        READ_DATA(value, color);
        

        m_font = g_resources.Get<Font>(font_name, font_size);
        //if (m_font == nullptr) std::cout << "bruh\n";
        m_texture = std::make_unique<Texture>();
        //if (m_texture == nullptr) std::cout << "bruh\n";

        SetText(text);

        return true;
    }
}