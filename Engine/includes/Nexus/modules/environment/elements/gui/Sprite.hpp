#ifndef NEXUS_ENGINE__GUI_SPRITE_HPP_
#define NEXUS_ENGINE__GUI_SPRITE_HPP_

# include "../../EnvUtils.hpp"

namespace nx
{
	namespace env
	{
		namespace gui
		{
			class Sprite
			{
				GUIElementInfos		_elementInfos;
				GUISpriteInfos		_spriteInfos;

			public:
				Sprite() {}
				Sprite(GUIElementInfos const& elementInfos, GUISpriteInfos const& spriteInfos)
					: _elementInfos(elementInfos), _spriteInfos(spriteInfos) {}
				~Sprite() {}

			public:
				GUIElementInfos& getGuiElementInfos() { return _elementInfos; }
				GUISpriteInfos& getGuiSpriteInfos() { return _spriteInfos; }
			};
		}
	}
}

#endif /* NEXUS_ENGINE__GUI_SPRITE_HPP_ */