#ifndef RENDERING_FRAMEWORK_TEMPLATE_HPP_
# define RENDERING_FRAMEWORK_TEMPLATE_HPP_

#include <iostream>
#include "Nexus/frameworks/ScriptFrameworkTpl.hpp"
#include "Nexus/modules/maths.hpp"

namespace nx {

	namespace rendering {
		//
		// GUI
		//

		typedef std::vector<std::pair<std::string, nx::script::ScriptInfos> > MouseEventsContainer;

		struct RGBa {
			RGBa(const uint32_t red_, const uint32_t green_, const uint32_t blue_, const uint32_t alpha_)
			: red(red_), green(green_), blue(blue_), alpha(alpha_) {}

			RGBa(const RGBa& other)
			: red(other.red), green(other.green), blue(other.blue), alpha(other.alpha) {}

			uint32_t red;
			uint32_t green;
			uint32_t blue;
			uint32_t alpha;
		};

		struct ColorInfo {
			ColorInfo(const nx::rendering::RGBa& backgroundColor_, const nx::rendering::RGBa& borderColor_, const unsigned int borderThickness_) 
			: backgroundColor(backgroundColor_), borderColor(borderColor_), borderThickness(borderThickness_) {}
			
			ColorInfo(const nx::rendering::ColorInfo& other)
			: backgroundColor(other.backgroundColor), borderColor(other.borderColor), borderThickness(other.borderThickness) {}

			nx::rendering::RGBa	backgroundColor;
			nx::rendering::RGBa	borderColor;
			unsigned int		borderThickness;
		};

		struct TextInfo {
			TextInfo(const std::string& fontPath_, const std::string& textLabel_, const unsigned int fontSize_, const nx::rendering::RGBa& textColor_, const uint32_t textStyle_)
			: fontPath(fontPath_), textLabel(textLabel_), fontSize(fontSize_), textColor(textColor_), textStyle(textStyle_) {}

			TextInfo(const nx::rendering::TextInfo& other)
			: fontPath(other.fontPath), textLabel(other.textLabel), fontSize(other.fontSize), textColor(other.textColor), textStyle(other.textStyle) {}

			std::string			fontPath;
			std::string			textLabel;
			unsigned int		fontSize;
			nx::rendering::RGBa	textColor;
			uint32_t			textStyle;
		};

		struct GUIElementInfos {
			GUIElementInfos(const nx::Vector2f& _pos, const nx::Vector2f& _size, const std::string& _identifier, const nx::rendering::MouseEventsContainer& events_)
			: pos(_pos), size(_size), identifier(_identifier), events(events_) {}
			
			GUIElementInfos(const GUIElementInfos& other)
			: pos(other.pos), size(other.size), identifier(other.identifier), events(other.events) {}

			nx::Vector2f pos;
			nx::Vector2f size;
			std::string identifier;
			nx::rendering::MouseEventsContainer events;
		};

		struct GUIButtonInfos {
			GUIButtonInfos(bool const isPushButton_, nx::rendering::ColorInfo const& colorInfo_, nx::rendering::TextInfo const& textInfo_) : isPushButton(isPushButton_), colorInfo(colorInfo_), textInfo(textInfo_) {}
			GUIButtonInfos(const GUIButtonInfos& other) : isPushButton(other.isPushButton), colorInfo(other.colorInfo), textInfo(other.textInfo) {}

			bool isPushButton;
			nx::rendering::ColorInfo colorInfo;
			nx::rendering::TextInfo textInfo;
		};

		struct GUICheckboxInfos {
			GUICheckboxInfos(nx::rendering::ColorInfo const& colorInfo_) : colorInfo(colorInfo_) {}
			GUICheckboxInfos(GUICheckboxInfos const& other) : colorInfo(other.colorInfo) {}

			nx::rendering::ColorInfo colorInfo;
		};

		struct GUIProgressBarInfos {
			GUIProgressBarInfos(nx::rendering::ColorInfo const& colorInfo_, nx::rendering::TextInfo const& textInfo_) : colorInfo(colorInfo_), textInfo(textInfo_) {}
			GUIProgressBarInfos(const GUIProgressBarInfos& other) : colorInfo(other.colorInfo), textInfo(other.textInfo) {}

			nx::rendering::ColorInfo colorInfo;
			nx::rendering::TextInfo textInfo;
		};

		struct GUIComboBoxInfos {
			GUIComboBoxInfos(nx::rendering::ColorInfo const& colorInfo_, nx::rendering::TextInfo const& textInfo_) : colorInfo(colorInfo_), textInfo(textInfo_) {}
			GUIComboBoxInfos(const GUIComboBoxInfos& other) : colorInfo(other.colorInfo), textInfo(other.textInfo) {}

			nx::rendering::ColorInfo colorInfo;
			nx::rendering::TextInfo textInfo;
		};

		struct GUITextInputInfos {
			GUITextInputInfos(nx::rendering::ColorInfo const& colorInfo_, nx::rendering::TextInfo const& textInfo_) : colorInfo(colorInfo_), textInfo(textInfo_) {}
			GUITextInputInfos(const GUITextInputInfos& other) : colorInfo(other.colorInfo), textInfo(other.textInfo) {}

			nx::rendering::ColorInfo colorInfo;
			nx::rendering::TextInfo textInfo;
		};

		struct GUITextInfos {
			GUITextInfos(nx::rendering::TextInfo const& textInfo_) : textInfo(textInfo_) {}
			GUITextInfos(const GUITextInfos& other) : textInfo(other.textInfo) {}

			nx::rendering::TextInfo textInfo;
		};

		struct GUIImageInfos {
			GUIImageInfos(std::string const& imagePath_) : imagePath(imagePath_) {}
			GUIImageInfos(const GUIImageInfos& other) : imagePath(other.imagePath) {}

			std::string imagePath;
		};

		struct GUISpriteInfos {
			GUISpriteInfos(std::string const& spritesheetPath_, nx::Vector2f const& sheetGrid_, nx::Vector2f const& spriteSize_) : spritesheetPath(spritesheetPath_), sheetGrid(sheetGrid_), spriteSize(spriteSize_) {}
			GUISpriteInfos(const GUISpriteInfos& other) : spritesheetPath(other.spritesheetPath), sheetGrid(other.sheetGrid), spriteSize(other.spriteSize) {}

			std::string spritesheetPath;
			nx::Vector2f sheetGrid;
			nx::Vector2f spriteSize;
		};


		struct GraphicsElementInfos {
			GraphicsElementInfos(const nx::Vector2f& _pos, const nx::Vector2f& _size, const std::string& _identifier, const nx::rendering::MouseEventsContainer& events_)
				: pos(_pos), size(_size), identifier(_identifier), events(events_) {}

			GraphicsElementInfos(const GUIElementInfos& other)
				: pos(other.pos), size(other.size), identifier(other.identifier), events(other.events) {}

			nx::Vector2f pos;
			nx::Vector2f size;
			std::string identifier;
			nx::rendering::MouseEventsContainer events;
		};

		struct GraphicsSpriteInfos {
			GraphicsSpriteInfos(std::string const& spritesheetPath_, nx::Vector2f const& sheetGrid_, nx::Vector2f const& spriteSize_) : spritesheetPath(spritesheetPath_), sheetGrid(sheetGrid_), spriteSize(spriteSize_) {}
			GraphicsSpriteInfos(const GUISpriteInfos& other) : spritesheetPath(other.spritesheetPath), sheetGrid(other.sheetGrid), spriteSize(other.spriteSize) {}

			std::string spritesheetPath;
			nx::Vector2f sheetGrid;
			nx::Vector2f spriteSize;
		};

		struct GraphicsCircleInfos {
			GraphicsCircleInfos(float const radius_, nx::rendering::ColorInfo const& colorInfo_) : radius(radius_), colorInfo(colorInfo_) {}
			GraphicsCircleInfos(const GraphicsCircleInfos& other) : colorInfo(other.colorInfo) {}

			float radius;
			nx::rendering::ColorInfo colorInfo;
		};

		struct GraphicsRectInfos {
			GraphicsRectInfos(nx::rendering::ColorInfo const& colorInfo_) : colorInfo(colorInfo_) {}
			GraphicsRectInfos(const GraphicsRectInfos& other) : colorInfo(other.colorInfo) {}

			nx::rendering::ColorInfo colorInfo;
		};

		struct GraphicsConvexInfos {
			GraphicsConvexInfos(nx::rendering::ColorInfo const& colorInfo_) : colorInfo(colorInfo_) {}
			GraphicsConvexInfos(const GraphicsConvexInfos& other) : colorInfo(other.colorInfo) {}

			nx::rendering::ColorInfo colorInfo;
		};
	}

	class RenderingFrameworkTpl
	{
	protected:
		const std::string 		_name;

	public:
		// This method must be implemented this way
		RenderingFrameworkTpl(const std::string & name) : _name(name) {};
		// This method must be implemented this way
		virtual ~RenderingFrameworkTpl() {};
		// This method must be implemented this way
		const std::string& getName(void) const {return this->_name;}

		// Framework Methods (must be virtual pure)
		virtual void InitializeWindow(int width, int height, std::string titleWin) = 0;
		virtual void RefreshRendering() = 0;
		// GUI ELEMENTS
		virtual bool addLayer(const std::string&) = 0;
		virtual bool addButton(const std::string&, const nx::rendering::GUIElementInfos&, const nx::rendering::GUIButtonInfos&) = 0;
		virtual bool addCheckbox(const std::string&, const nx::rendering::GUIElementInfos&, const nx::rendering::GUICheckboxInfos&) = 0;
		virtual bool addProgressBar(const std::string&, const nx::rendering::GUIElementInfos&, const nx::rendering::GUIProgressBarInfos&) = 0;
		virtual bool addComboBox(const std::string&, const nx::rendering::GUIElementInfos&, const nx::rendering::GUIComboBoxInfos&) = 0;
		virtual bool addTextInput(const std::string&, const nx::rendering::GUIElementInfos&, const nx::rendering::GUITextInputInfos&) = 0;
		virtual bool addText(const std::string&, const nx::rendering::GUIElementInfos&, const nx::rendering::GUITextInfos&) = 0;
		virtual bool addImage(const std::string&, const nx::rendering::GUIElementInfos&, const nx::rendering::GUIImageInfos&) = 0;
		virtual bool addGUISprite(const std::string&, const nx::rendering::GUIElementInfos&, const nx::rendering::GUISpriteInfos&) = 0;

		virtual bool addGraphicsSprite(const nx::rendering::GraphicsElementInfos& graphicsParams, const nx::rendering::GraphicsSpriteInfos& spriteParams) = 0;
		virtual bool addGraphicsCirleShape(const nx::rendering::GraphicsElementInfos& graphicsParams, const nx::rendering::GraphicsCircleInfos& circleShapeParams) = 0;
		virtual bool addGraphicsRectShape(const nx::rendering::GraphicsElementInfos& graphicsParams, const nx::rendering::GraphicsRectInfos& rectShapeParams) = 0;
		virtual bool addGraphicsConvexShape(const nx::rendering::GraphicsElementInfos& graphicsParams, const nx::rendering::GraphicsConvexInfos& convexShapeParams) = 0;

		virtual std::string const	getTypeFromElement(std::string const& layerId, std::string const& elemId) const = 0;

		//Button
		virtual void setStateToButton(std::string const& layerId, std::string const& buttonId, bool const state) = 0;
		virtual void setTextToButton(std::string const& layerId, std::string const& buttonId, std::string const& text) = 0;
		virtual void setFontSizeToButton(std::string const& layerId, std::string const& buttonId, unsigned int const fontSize) = 0;
		virtual void setColorNotSelectedToButton(std::string const& layerId, std::string const& buttonId, nx::rendering::RGBa const& color) = 0;
		virtual void setColorSelectedToButton(std::string const& layerId, std::string const& buttonId, nx::rendering::RGBa const& color) = 0;
		virtual void setBorderColorToButton(std::string const& layerId, std::string const& buttonId, nx::rendering::RGBa const& color) = 0;
		virtual void setBorderThicknessToButton(std::string const& layerId, std::string const& buttonId, int const thickness) = 0;
		virtual void setPosToButton(std::string const& layerId, std::string const& buttonId, nx::Vector2f const& pos) = 0;
		virtual void setSizeToButton(std::string const& layerId, std::string const& buttonId, nx::Vector2f const& size) = 0;

		virtual bool const					getStateFromButton(std::string const& layerId, std::string const& buttonId) const = 0;
		virtual std::string const			getTextFromButton(std::string const& layerId, std::string const& buttonId) const = 0;
		virtual unsigned int const			getFontSizeFromButton(std::string const& layerId, std::string const& buttonId) const = 0;
		virtual nx::rendering::RGBa const &	getColorNotSelectedFromButton(std::string const& layerId, std::string const& buttonId) const = 0;
		virtual nx::rendering::RGBa const &	getColorSelectedFromButton(std::string const& layerId, std::string const& buttonId) const = 0;
		virtual nx::rendering::RGBa const &	getBorderColorFromButton(std::string const& layerId, std::string const& buttonId) const = 0;
		virtual int const					getBorderThicknessFromButton(std::string const& layerId, std::string const& buttonId) const = 0;
	};	
}

#endif /* RENDERING_FRAMEWORK_TEMPLATE_HPP_*/