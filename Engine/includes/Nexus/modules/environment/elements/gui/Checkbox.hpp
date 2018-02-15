#ifndef NEXUS_ENGINE__GUI_CHECKBOX_HPP_
#define NEXUS_ENGINE__GUI_CHECKBOX_HPP_

# include "../../EnvUtils.hpp"

namespace nx
{
	namespace env
	{
		namespace gui
		{
			class Checkbox
			{
				GUIElementInfos		_elementInfos;
				GUICheckboxInfos	_checkboxInfos;

			public:
				Checkbox() {}
				Checkbox(GUIElementInfos const& elementInfos, GUICheckboxInfos const& checkboxInfos)
					: _elementInfos(elementInfos), _checkboxInfos(checkboxInfos) {}
				~Checkbox() {}

			public:
				bool isModified(){
					if (_elementInfos.getIsModified() || _checkboxInfos.getIsModified()){
						return true;
					}
					return false;
				}

				void resetModified(){
					_elementInfos.setIsModified(false);
					_checkboxInfos.setIsModified(false);
				}

				GUIElementInfos& getGuiElementInfos() { return _elementInfos; }
				GUICheckboxInfos& getGuiCheckBoxInfos() { return _checkboxInfos; }
			};
		}
	}
}

#endif /* NEXUS_ENGINE__GUI_CHECKBOX_HPP_ */