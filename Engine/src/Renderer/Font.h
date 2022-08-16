#pragma once
#include "Resources/Resource.h"
#include <string>

struct _TTF_Font;

namespace pb
{
	class Font : public Resource
	{
	public:
		Font() = default;
		Font(const std::string& filename, int fontSize);
		~Font();

		bool Create(std::string filename, ...) override;
		void Load(const std::string& filename, int fontSize);



		friend class Text;

	private:
		_TTF_Font* m_ttfFont = nullptr;
	};
}