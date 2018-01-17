#include "FrameworkRendering.hpp"

nx::Engine* enginePtr = nullptr;

FrameworkRendering::FrameworkRendering(nx::Engine* engine)
	:
	nx::RenderingFrameworkTpl("FrameworkRendering"),
	_engine(engine),
	_win(nullptr),
	_guiHandler(nullptr),
	_graphicsHandler(nullptr)
{
	enginePtr = engine;
	nx::Log::inform("New Rendering Framework created");
}

FrameworkRendering::~FrameworkRendering()
{
	nx::Log::inform("New Rendering Framework deleted");
}

void FrameworkRendering::InitializeWindow(int width, int height, std::string titleWin)
{
	this->_win = std::make_shared<sf::RenderWindow>(sf::VideoMode(width, height), titleWin);
	this->_guiHandler = std::make_shared<nx::gui::GUIHandler>(this->_win);
	this->_graphicsHandler = std::make_shared<nx::graphics::GraphicsHandler>(this->_win);
}

void FrameworkRendering::RefreshRendering()
{
	if (this->_win && this->_guiHandler)
	{
		while (this->_win->isOpen())
		{
			// Getting input events	
			sf::Event event;

			while (this->_win->pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					this->_win->close();
				this->_guiHandler->processEvent(event);
			}
			
			// Clearing the window
			this->_win->clear(sf::Color(0, 0 , 0, 255));

			// Drawing stuff on screen
			this->_guiHandler->drawLayers();
			this->_graphicsHandler->drawElements();

			// Displaying screen
			this->_win->display();
		}
	}
}

/// TOOLS ///

sf::Color FrameworkRendering::RGBa_to_sfColor(const nx::rendering::RGBa& color)
{
	return sf::Color(color.red, color.green, color.blue, color.alpha);
}

/// EVENTS ///


bool FrameworkRendering::addLayer(const std::string& layerIdentifier)
{
	if (!_guiHandler || !_win)
		return false;

	if (this->_guiHandler->getLayers().size() > 0) {
		if (this->_guiHandler->layer_exists(layerIdentifier))
		{
			nx::Log::error(layerIdentifier + " already exists", "LAYER_DUPLICATE", 500);
			return false;
		}
	}

	this->_guiHandler->addLayer(std::make_shared<nx::gui::GUILayer>(layerIdentifier));
	return true;
}

bool FrameworkRendering::addButton(const std::string& layerId, const nx::rendering::GUIElementInfos& guiParams, const nx::rendering::GUIButtonInfos& buttonsParams)
{
	if (!this->_guiHandler->layer_exists(layerId) || this->_guiHandler->getLayerByName(layerId)->object_exists(guiParams.identifier)) {
		return (false);
	}

	std::shared_ptr<nx::gui::Button> button = std::make_shared<nx::gui::Button>(
		sf::Vector2f(guiParams.pos.x, guiParams.pos.y),
		sf::Vector2f(guiParams.size.x, guiParams.size.y),
		guiParams.identifier,
		guiParams.events,
		buttonsParams.isPushButton,
		nx::ColorInfo(
			FrameworkRendering::RGBa_to_sfColor(buttonsParams.colorInfo.backgroundColor),
			FrameworkRendering::RGBa_to_sfColor(buttonsParams.colorInfo.borderColor),
			buttonsParams.colorInfo.borderThickness),
		nx::TextInfo(
			buttonsParams.textInfo.fontPath,
			buttonsParams.textInfo.textLabel,
			buttonsParams.textInfo.fontSize,
			FrameworkRendering::RGBa_to_sfColor(buttonsParams.textInfo.textColor))
	);
	this->_guiHandler->getLayerByName(layerId)->add(button);
	std::cout << "Adding new button (" << guiParams.identifier << ") in " << layerId << std::endl;
	return (true);
}


bool FrameworkRendering::addCheckbox(const std::string& layerId, const nx::rendering::GUIElementInfos& guiParams, const nx::rendering::GUICheckboxInfos& checkboxParams)
{
	if (!this->_guiHandler->layer_exists(layerId) || this->_guiHandler->getLayerByName(layerId)->object_exists(guiParams.identifier)) {
		return (false);
	}

	std::shared_ptr<nx::gui::Checkbox> checkbox = std::make_shared<nx::gui::Checkbox>(
		sf::Vector2f(guiParams.pos.x, guiParams.pos.y),
		sf::Vector2f(guiParams.size.x, guiParams.size.y),
		guiParams.identifier,
		guiParams.events,
		nx::ColorInfo(
			FrameworkRendering::RGBa_to_sfColor(checkboxParams.colorInfo.backgroundColor),
			FrameworkRendering::RGBa_to_sfColor(checkboxParams.colorInfo.borderColor),
			checkboxParams.colorInfo.borderThickness)
	);
	this->_guiHandler->getLayerByName(layerId)->add(checkbox);
	std::cout << "Adding new checkbox (" << guiParams.identifier << ") in " << layerId << std::endl;
	return (true);
}

bool FrameworkRendering::addProgressBar(const std::string& layerId, const nx::rendering::GUIElementInfos& guiParams, const nx::rendering::GUIProgressBarInfos& progressBarParams)
{
	if (!this->_guiHandler->layer_exists(layerId) || this->_guiHandler->getLayerByName(layerId)->object_exists(guiParams.identifier)) {
		return (false);
	}

	std::shared_ptr<nx::gui::ProgressBar> progressbar = std::make_shared<nx::gui::ProgressBar>(
		sf::Vector2f(guiParams.pos.x, guiParams.pos.y),
		sf::Vector2f(guiParams.size.x, guiParams.size.y),
		guiParams.identifier,
		guiParams.events,
		nx::ColorInfo(
			FrameworkRendering::RGBa_to_sfColor(progressBarParams.colorInfo.backgroundColor),
			FrameworkRendering::RGBa_to_sfColor(progressBarParams.colorInfo.borderColor),
			progressBarParams.colorInfo.borderThickness),
		nx::TextInfo(
			progressBarParams.textInfo.fontPath,
			progressBarParams.textInfo.textLabel,
			progressBarParams.textInfo.fontSize,
			FrameworkRendering::RGBa_to_sfColor(progressBarParams.textInfo.textColor))
		);

	this->_guiHandler->getLayerByName(layerId)->add(progressbar);
	std::cout << "Adding new progressbar (" << guiParams.identifier << ") in " << layerId << std::endl;
	return (true);
}

bool FrameworkRendering::addComboBox(const std::string& layerId, const nx::rendering::GUIElementInfos& guiParams, const nx::rendering::GUIComboBoxInfos& comboBoxParams)
{
	if (!this->_guiHandler->layer_exists(layerId) || this->_guiHandler->getLayerByName(layerId)->object_exists(guiParams.identifier)) {
		return (false);
	}

	std::shared_ptr<nx::gui::ComboBox> combobox = std::make_shared<nx::gui::ComboBox>(
		sf::Vector2f(guiParams.pos.x, guiParams.pos.y),
		sf::Vector2f(guiParams.size.x, guiParams.size.y),
		guiParams.identifier,
		guiParams.events,
		nx::ColorInfo(
			FrameworkRendering::RGBa_to_sfColor(comboBoxParams.colorInfo.backgroundColor),
			FrameworkRendering::RGBa_to_sfColor(comboBoxParams.colorInfo.borderColor),
			comboBoxParams.colorInfo.borderThickness),
		nx::TextInfo(
			comboBoxParams.textInfo.fontPath,
			comboBoxParams.textInfo.textLabel,
			comboBoxParams.textInfo.fontSize,
			FrameworkRendering::RGBa_to_sfColor(comboBoxParams.textInfo.textColor))
		);

	this->_guiHandler->getLayerByName(layerId)->add(combobox);
	std::cout << "Adding new combobox (" << guiParams.identifier << ") in " << layerId << std::endl;
	return (true);
}

bool FrameworkRendering::addTextInput(const std::string& layerId, const nx::rendering::GUIElementInfos& guiParams, const nx::rendering::GUITextInputInfos& textInputParams)
{
	if (!this->_guiHandler->layer_exists(layerId) || this->_guiHandler->getLayerByName(layerId)->object_exists(guiParams.identifier)) {
		return (false);
	}

	std::shared_ptr<nx::gui::TextInput> textinput = std::make_shared<nx::gui::TextInput>(
		sf::Vector2f(guiParams.pos.x, guiParams.pos.y),
		sf::Vector2f(guiParams.size.x, guiParams.size.y),
		guiParams.identifier,
		guiParams.events,
		nx::ColorInfo(
			FrameworkRendering::RGBa_to_sfColor(textInputParams.colorInfo.backgroundColor),
			FrameworkRendering::RGBa_to_sfColor(textInputParams.colorInfo.borderColor),
			textInputParams.colorInfo.borderThickness),
		nx::TextInfo(
			textInputParams.textInfo.fontPath,
			textInputParams.textInfo.textLabel,
			textInputParams.textInfo.fontSize,
			FrameworkRendering::RGBa_to_sfColor(textInputParams.textInfo.textColor))
		);

	this->_guiHandler->getLayerByName(layerId)->add(textinput);
	std::cout << "Adding new textinput (" << guiParams.identifier << ") in " << layerId << std::endl;
	return (true);
}

bool FrameworkRendering::addText(const std::string& layerId, const nx::rendering::GUIElementInfos& guiParams, const nx::rendering::GUITextInfos& textParams)
{
	if (!this->_guiHandler->layer_exists(layerId) || this->_guiHandler->getLayerByName(layerId)->object_exists(guiParams.identifier)) {
		return (false);
	}

	std::shared_ptr<nx::gui::Text> text = std::make_shared<nx::gui::Text>(
		sf::Vector2f(guiParams.pos.x, guiParams.pos.y),
		guiParams.identifier,
		guiParams.events,
		nx::TextInfo(
			textParams.textInfo.fontPath,
			textParams.textInfo.textLabel,
			textParams.textInfo.fontSize,
			FrameworkRendering::RGBa_to_sfColor(textParams.textInfo.textColor))
		);

	this->_guiHandler->getLayerByName(layerId)->add(text);
	std::cout << "Adding new text (" << guiParams.identifier << ") in " << layerId << std::endl;
	return (true);
}

bool FrameworkRendering::addImage(const std::string& layerId, const nx::rendering::GUIElementInfos& guiParams, const nx::rendering::GUIImageInfos& imageParams)
{
	if (!this->_guiHandler->layer_exists(layerId) || this->_guiHandler->getLayerByName(layerId)->object_exists(guiParams.identifier)) {
		return (false);
	}

	std::shared_ptr<nx::gui::Image> image = std::make_shared<nx::gui::Image>(
		sf::Vector2f(guiParams.pos.x, guiParams.pos.y),
		sf::Vector2f(guiParams.size.x, guiParams.size.y),
		guiParams.identifier,
		guiParams.events,
		imageParams.imagePath
		);

	this->_guiHandler->getLayerByName(layerId)->add(image);
	std::cout << "Adding new image (" << guiParams.identifier << ") in " << layerId << std::endl;
	return (true);
}

bool FrameworkRendering::addGUISprite(const std::string& layerId, const nx::rendering::GUIElementInfos& guiParams, const nx::rendering::GUISpriteInfos& spriteParams)
{
	if (!this->_guiHandler->layer_exists(layerId) || this->_guiHandler->getLayerByName(layerId)->object_exists(guiParams.identifier)) {
		return (false);
	}

	std::shared_ptr<nx::gui::Sprite> sprite = std::make_shared<nx::gui::Sprite>(
		sf::Vector2f(guiParams.pos.x, guiParams.pos.y),
		sf::Vector2f(guiParams.size.x, guiParams.size.y),
		guiParams.identifier,
		guiParams.events,
		spriteParams.spritesheetPath,
		sf::Vector2f(spriteParams.sheetGrid.x, spriteParams.sheetGrid.y),
		sf::Vector2f(spriteParams.spriteSize.x, spriteParams.spriteSize.y)
		);

	this->_guiHandler->getLayerByName(layerId)->add(sprite);
	std::cout << "Adding new guiSprite (" << guiParams.identifier << ") in " << layerId << std::endl;
	return (true);
}

bool FrameworkRendering::addGraphicsSprite(const nx::rendering::GraphicsElementInfos& graphicsParams, const nx::rendering::GraphicsSpriteInfos& spriteParams)
{
	if (this->_graphicsHandler->object_exists(graphicsParams.identifier)) {
		return (false);
	}

	std::shared_ptr<nx::graphics::Sprite> sprite = std::make_shared<nx::graphics::Sprite>(
		sf::Vector2f(graphicsParams.pos.x, graphicsParams.pos.y),
		sf::Vector2f(graphicsParams.size.x, graphicsParams.size.y),
		graphicsParams.identifier,
		graphicsParams.events,
		spriteParams.spritesheetPath,
		sf::Vector2f(spriteParams.sheetGrid.x, spriteParams.sheetGrid.y),
		sf::Vector2f(spriteParams.spriteSize.x, spriteParams.spriteSize.y)
		);

	this->_graphicsHandler->addElement(sprite);
	std::cout << "Adding new graphicsSprite (" << graphicsParams.identifier << ")" << std::endl;
	return (true);
}

bool FrameworkRendering::addGraphicsCirleShape(const nx::rendering::GraphicsElementInfos& graphicsParams, const nx::rendering::GraphicsCircleInfos& circleShapeParams)
{
	if (this->_graphicsHandler->object_exists(graphicsParams.identifier)) {
		return (false);
	}
	
	std::shared_ptr<nx::graphics::CircleShape> circle = std::make_shared<nx::graphics::CircleShape>(
		sf::Vector2f(graphicsParams.pos.x, graphicsParams.pos.y),
		sf::Vector2f(graphicsParams.size.x, graphicsParams.size.y),
		graphicsParams.identifier,
		graphicsParams.events,
		circleShapeParams.radius,
		nx::ColorInfo(
			FrameworkRendering::RGBa_to_sfColor(circleShapeParams.colorInfo.backgroundColor),
			FrameworkRendering::RGBa_to_sfColor(circleShapeParams.colorInfo.borderColor),
			circleShapeParams.colorInfo.borderThickness)
		);

	this->_graphicsHandler->addElement(circle);
	std::cout << "Adding new graphicsCircle (" << graphicsParams.identifier << ")" << std::endl;
	return (true);
}

bool FrameworkRendering::addGraphicsRectShape(const nx::rendering::GraphicsElementInfos& graphicsParams, const nx::rendering::GraphicsRectInfos& rectShapeParams)
{
	if (this->_graphicsHandler->object_exists(graphicsParams.identifier)) {
		return (false);
	}

	std::shared_ptr<nx::graphics::RectShape> rect = std::make_shared<nx::graphics::RectShape>(
		sf::Vector2f(graphicsParams.pos.x, graphicsParams.pos.y),
		sf::Vector2f(graphicsParams.size.x, graphicsParams.size.y),
		graphicsParams.identifier,
		graphicsParams.events,
		nx::ColorInfo(
			FrameworkRendering::RGBa_to_sfColor(rectShapeParams.colorInfo.backgroundColor),
			FrameworkRendering::RGBa_to_sfColor(rectShapeParams.colorInfo.borderColor),
			rectShapeParams.colorInfo.borderThickness)
		);

	this->_graphicsHandler->addElement(rect);
	std::cout << "Adding new graphicsRect (" << graphicsParams.identifier << ")" << std::endl;
	return (true);
}

bool FrameworkRendering::addGraphicsConvexShape(const nx::rendering::GraphicsElementInfos& graphicsParams, const nx::rendering::GraphicsConvexInfos& convexShapeParams)
{
	if (this->_graphicsHandler->object_exists(graphicsParams.identifier)) {
		return (false);
	}

	std::shared_ptr<nx::graphics::ConvexShape> convex = std::make_shared<nx::graphics::ConvexShape>(
		sf::Vector2f(graphicsParams.pos.x, graphicsParams.pos.y),
		sf::Vector2f(graphicsParams.size.x, graphicsParams.size.y),
		graphicsParams.identifier,
		graphicsParams.events,
		nx::ColorInfo(
			FrameworkRendering::RGBa_to_sfColor(convexShapeParams.colorInfo.backgroundColor),
			FrameworkRendering::RGBa_to_sfColor(convexShapeParams.colorInfo.borderColor),
			convexShapeParams.colorInfo.borderThickness)
		);

	this->_graphicsHandler->addElement(convex);
	std::cout << "Adding new graphicsConvex (" << graphicsParams.identifier << ")" << std::endl;
	return (true);
}