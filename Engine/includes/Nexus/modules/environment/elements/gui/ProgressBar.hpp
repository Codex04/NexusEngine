#ifndef NEXUS_ENGINE__GUI_PROGRESSBAR_HPP_
#define NEXUS_ENGINE__GUI_PROGRESSBAR_HPP_

# include "../../EnvUtils.hpp"

namespace nx
{
	namespace env
	{
		namespace gui
		{
			class ProgressBar
			{
				GUIElementInfos		_elementInfos;
				GUIProgressBarInfos	_progressBarInfos;

			public:
				ProgressBar() {}
				ProgressBar(GUIElementInfos const& elementInfos, GUIProgressBarInfos const& progressBarInfos)
					: _elementInfos(elementInfos), _progressBarInfos(progressBarInfos) {}
				~ProgressBar() {}

			public:
				GUIElementInfos& getGuiElementInfos() { return _elementInfos; }
				GUIProgressBarInfos& getGuiProgressBarInfos() { return _progressBarInfos; }
			};
		}
	}
}

#endif /* NEXUS_ENGINE__GUI_PROGRESSBAR_HPP_ */