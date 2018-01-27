#ifndef NEXUS_ENGINE__GUI_IMAGE_HPP_
#define NEXUS_ENGINE__GUI_IMAGE_HPP_

# include "../../EnvUtils.hpp"

namespace nx
{
	namespace env
	{
		namespace gui
		{
			class Image
			{
				GUIElementInfos		_elementInfos;
				GUIImageInfos		_imageInfos;

			public:
				Image() {}
				Image(GUIElementInfos const& elementInfos, GUIImageInfos const& imageInfos)
					: _elementInfos(elementInfos), _imageInfos(imageInfos) {}
				~Image() {}

			public:
				GUIElementInfos& getGuiElementInfos() { return _elementInfos; }
				GUIImageInfos& getGuiImageInfos() { return _imageInfos; }
			
			};
		}
	}
}

#endif /* NEXUS_ENGINE__GUI_IMAGE_HPP_ */