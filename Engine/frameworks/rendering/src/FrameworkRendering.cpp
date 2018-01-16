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

	//std::shared_ptr<GUILayer> layer = std::make_shared<GUILayer>("MainLayer");
	// std::shared_ptr<Button> button = std::make_shared<Button>(sf::Vector2f(300, 100), sf::Vector2f(100, 30), "MyFirstButton", true,
	// 														  ColorInfo(sf::Color(200, 200, 200, 255), sf::Color(200, 0, 0, 255), 2),
	// 														  TextInfo("./fonts/Roboto-Regular.ttf", "Press me!", 12, sf::Color(0, 0, 0, 255)));
	/*std::shared_ptr<Checkbox> checkbox = std::make_shared<Checkbox>(sf::Vector2f(640, 30), sf::Vector2f(30, 30), "MyFirstCheckbox",
																	ColorInfo(sf::Color(200, 200, 200, 255), sf::Color(0, 0, 255, 255), 2));*/
	/*std::shared_ptr<ProgressBar> progressbar = std::make_shared<ProgressBar>(sf::Vector2f(240, 500), sf::Vector2f(300, 50), "MyFirstProgressbar",
																			 ColorInfo(sf::Color(200, 200, 200, 255), sf::Color(255, 255, 255, 255), 2),
																			 TextInfo("./fonts/Roboto-Regular.ttf", "", 16, sf::Color(0, 0, 0, 255)));*/
	/*std::shared_ptr<ComboBox> combobox = std::make_shared<ComboBox>(sf::Vector2f(70, 250), sf::Vector2f(140, 30), "MyFirstComboBox",
																    ColorInfo(sf::Color(200, 200, 200, 255), sf::Color(255, 255, 0, 255), 2),
																    TextInfo("./fonts/Roboto-Regular.ttf", "", 12, sf::Color(0, 0, 0, 255)));*/
	/*std::shared_ptr<TextInput> textinput = std::make_shared<TextInput>(sf::Vector2f(400, 350), sf::Vector2f(230, 30), "MyFirstTextInput",
																	   ColorInfo(sf::Color(200, 200, 200, 255), sf::Color(255, 0, 255, 255), 2),
																	   TextInfo("./fonts/Roboto-Regular.ttf", "A default text..", 12, sf::Color(0, 0, 0, 255)));*/
	/*std::shared_ptr<Text> text = std::make_shared<Text>(sf::Vector2f(500, 30), "MyFirstText",
														TextInfo("./fonts/Roboto-Regular.ttf", "Sample text", 16, sf::Color(0, 255, 0, 255)));*/
	//std::shared_ptr<Image> img = std::make_shared<Image>(sf::Vector2f(300, 580), sf::Vector2f(), "MyFirstImage", "./images/defaultgamelogo.png");
	/*std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>(sf::Vector2f(50, 600), sf::Vector2f(), "MyFirstSprite", "./images/guitarist.png",
															  sf::Vector2f(3, 2), sf::Vector2f(103, 89));*/

	//progressbar->setFilled(50);

	/*combobox->addSelection("First item");
	combobox->addSelection("Second item");
	combobox->addSelection("LEEERRROYYYY");
	combobox->addSelection("JENKINSSSSS");
	combobox->addSelection("Very long thing over thereeeee omggg");*/

	//img->setSize(sf::Vector2f(64, 64));

	/*sprite->setAnimate(true);
	sprite->setSlowness(130);
	sprite->setSpritesAnimated({0, 2, 4});
	sprite->setSpriteIdx(1);*/
	
	// layer->add(button);
	//layer->add(checkbox);
	//layer->add(progressbar);
	//layer->add(combobox);
	//layer->add(textinput);
	//layer->add(text);
	//layer->add(img);
	//layer->add(sprite);
	//this->_handler->addLayer(layer);
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

std::string const	FrameworkRendering::getTypeFromElement(std::string const& layerId, std::string const& elemId) const
{
	if (!this->_guiHandler->layer_exists(layerId))
		throw nx::LayerNotFoundException(elemId);

	if (!this->_guiHandler->getLayerByName(layerId)->object_exists(elemId))
		throw nx::ElementNotFoundException(elemId);

	nx::gui::GUIElement *elem = this->_guiHandler->getLayerByName(layerId)->getElementByName(elemId).get();

	if (!elem)
		throw nx::NullElementException(elemId);

	return (elem->getType());
}

nx::Vector2f const	FrameworkRendering::getPosFromElement(std::string const& layerId, std::string const& elemId) const
{
	if (!this->_guiHandler->layer_exists(layerId))
		throw nx::LayerNotFoundException(elemId);

	if (!this->_guiHandler->getLayerByName(layerId)->object_exists(elemId))
		throw nx::ElementNotFoundException(elemId);

	nx::gui::GUIElement *elem = this->_guiHandler->getLayerByName(layerId)->getElementByName(elemId).get();

	if (!elem)
		throw nx::NullElementException(elemId);

	sf::Vector2f const& pos = elem->getPos();

	return (nx::Vector2f(pos.x, pos.y));
}

nx::Vector2f const	FrameworkRendering::getSizeFromElement(std::string const& layerId, std::string const& elemId) const
{
	if (!this->_guiHandler->layer_exists(layerId))
		throw nx::LayerNotFoundException(elemId);

	if (!this->_guiHandler->getLayerByName(layerId)->object_exists(elemId))
		throw nx::ElementNotFoundException(elemId);

	nx::gui::GUIElement *elem = this->_guiHandler->getLayerByName(layerId)->getElementByName(elemId).get();

	if (!elem)
		throw nx::NullElementException(elemId);

	sf::Vector2f const& size = elem->getSize();

	return (nx::Vector2f(size.x, size.y));
}


// Button

void FrameworkRendering::setStateToButton(std::string const& layerId, std::string const& buttonId, bool const state)
{
	if (!this->_guiHandler->layer_exists(layerId))
		throw nx::LayerNotFoundException(buttonId);

	if (!this->_guiHandler->getLayerByName(layerId)->object_exists(buttonId))
		throw nx::ElementNotFoundException(buttonId);

	nx::gui::Button *button = dynamic_cast<nx::gui::Button *>(this->_guiHandler->getLayerByName(layerId)->getElementByName(buttonId).get());

	if (!button)
		throw nx::NullElementException(buttonId);

	button->setState(state);
}

void FrameworkRendering::setTextToButton(std::string const& layerId, std::string const& buttonId, std::string const& text)
{
	if (!this->_guiHandler->layer_exists(layerId))
		throw nx::LayerNotFoundException(buttonId);

	if (!this->_guiHandler->getLayerByName(layerId)->object_exists(buttonId))
		throw nx::ElementNotFoundException(buttonId);

	nx::gui::Button *button = dynamic_cast<nx::gui::Button *>(this->_guiHandler->getLayerByName(layerId)->getElementByName(buttonId).get());

	if (!button)
		throw nx::NullElementException(buttonId);

	button->setText(text);
}

void FrameworkRendering::setFontSizeToButton(std::string const& layerId, std::string const& buttonId, unsigned int const fontSize)
{
	if (!this->_guiHandler->layer_exists(layerId))
		throw nx::LayerNotFoundException(buttonId);

	if (!this->_guiHandler->getLayerByName(layerId)->object_exists(buttonId))
		throw nx::ElementNotFoundException(buttonId);

	nx::gui::Button *button = dynamic_cast<nx::gui::Button *>(this->_guiHandler->getLayerByName(layerId)->getElementByName(buttonId).get());

	if (!button)
		throw nx::NullElementException(buttonId);

	button->setFontSize(fontSize);
}

void FrameworkRendering::setColorNotSelectedToButton(std::string const& layerId, std::string const& buttonId, nx::rendering::RGBa const& color)
{
	if (!this->_guiHandler->layer_exists(layerId))
		throw nx::LayerNotFoundException(buttonId);

	if (!this->_guiHandler->getLayerByName(layerId)->object_exists(buttonId))
		throw nx::ElementNotFoundException(buttonId);

	nx::gui::Button *button = dynamic_cast<nx::gui::Button *>(this->_guiHandler->getLayerByName(layerId)->getElementByName(buttonId).get());

	if (!button)
		throw nx::NullElementException(buttonId);

	button->setColorNotSelected(FrameworkRendering::RGBa_to_sfColor(color));
}

void FrameworkRendering::setColorSelectedToButton(std::string const& layerId, std::string const& buttonId, nx::rendering::RGBa const& color)
{
	if (!this->_guiHandler->layer_exists(layerId))
		throw nx::LayerNotFoundException(buttonId);

	if (!this->_guiHandler->getLayerByName(layerId)->object_exists(buttonId))
		throw nx::ElementNotFoundException(buttonId);

	nx::gui::Button *button = dynamic_cast<nx::gui::Button *>(this->_guiHandler->getLayerByName(layerId)->getElementByName(buttonId).get());

	if (!button)
		throw nx::NullElementException(buttonId);

	button->setColorSelected(FrameworkRendering::RGBa_to_sfColor(color));
}

void FrameworkRendering::setBorderColorToButton(std::string const& layerId, std::string const& buttonId, nx::rendering::RGBa const& color)
{
	if (!this->_guiHandler->layer_exists(layerId))
		throw nx::LayerNotFoundException(buttonId);

	if (!this->_guiHandler->getLayerByName(layerId)->object_exists(buttonId))
		throw nx::ElementNotFoundException(buttonId);

	nx::gui::Button *button = dynamic_cast<nx::gui::Button *>(this->_guiHandler->getLayerByName(layerId)->getElementByName(buttonId).get());

	if (!button)
		throw nx::NullElementException(buttonId);

	button->setBorderColor(FrameworkRendering::RGBa_to_sfColor(color));
}

void FrameworkRendering::setBorderThicknessToButton(std::string const& layerId, std::string const& buttonId, int const thickness)
{
	if (!this->_guiHandler->layer_exists(layerId))
		throw nx::LayerNotFoundException(buttonId);

	if (!this->_guiHandler->getLayerByName(layerId)->object_exists(buttonId))
		throw nx::ElementNotFoundException(buttonId);

	nx::gui::Button *button = dynamic_cast<nx::gui::Button *>(this->_guiHandler->getLayerByName(layerId)->getElementByName(buttonId).get());

	if (!button)
		throw nx::NullElementException(buttonId);

	button->setBorderThickness(thickness);
}

void FrameworkRendering::setPosToButton(std::string const& layerId, std::string const& buttonId, nx::Vector2f const& pos)
{
	if (!this->_guiHandler->layer_exists(layerId))
		throw nx::LayerNotFoundException(buttonId);

	if (!this->_guiHandler->getLayerByName(layerId)->object_exists(buttonId))
		throw nx::ElementNotFoundException(buttonId);

	nx::gui::Button *button = dynamic_cast<nx::gui::Button *>(this->_guiHandler->getLayerByName(layerId)->getElementByName(buttonId).get());

	if (!button)
		throw nx::NullElementException(buttonId);

	button->setPos(sf::Vector2f(pos.x, pos.y));
}

void FrameworkRendering::setSizeToButton(std::string const& layerId, std::string const& buttonId, nx::Vector2f const& size)
{
	if (!this->_guiHandler->layer_exists(layerId))
		throw nx::LayerNotFoundException(buttonId);

	if (!this->_guiHandler->getLayerByName(layerId)->object_exists(buttonId))
		throw nx::ElementNotFoundException(buttonId);

	nx::gui::Button *button = dynamic_cast<nx::gui::Button *>(this->_guiHandler->getLayerByName(layerId)->getElementByName(buttonId).get());

	if (!button)
		throw nx::NullElementException(buttonId);

	button->setSize(sf::Vector2f(size.x, size.y));
}

bool const					FrameworkRendering::getStateFromButton(std::string const& layerId, std::string const& buttonId) const
{
	if (!this->_guiHandler->layer_exists(layerId))
		throw nx::LayerNotFoundException(buttonId);

	if (!this->_guiHandler->getLayerByName(layerId)->object_exists(buttonId))
		throw nx::ElementNotFoundException(buttonId);

	nx::gui::Button *button = dynamic_cast<nx::gui::Button *>(this->_guiHandler->getLayerByName(layerId)->getElementByName(buttonId).get());

	if (!button)
		throw nx::NullElementException(buttonId);

	return (button->getState());
}

std::string const			FrameworkRendering::getTextFromButton(std::string const& layerId, std::string const& buttonId) const
{
	if (!this->_guiHandler->layer_exists(layerId))
		throw nx::LayerNotFoundException(buttonId);

	if (!this->_guiHandler->getLayerByName(layerId)->object_exists(buttonId))
		throw nx::ElementNotFoundException(buttonId);

	nx::gui::Button *button = dynamic_cast<nx::gui::Button *>(this->_guiHandler->getLayerByName(layerId)->getElementByName(buttonId).get());

	if (!button)
		throw nx::NullElementException(buttonId);

	return (button->getText());
}

unsigned int const			FrameworkRendering::getFontSizeFromButton(std::string const& layerId, std::string const& buttonId) const
{
	if (!this->_guiHandler->layer_exists(layerId))
		throw nx::LayerNotFoundException(buttonId);

	if (!this->_guiHandler->getLayerByName(layerId)->object_exists(buttonId))
		throw nx::ElementNotFoundException(buttonId);

	nx::gui::Button *button = dynamic_cast<nx::gui::Button *>(this->_guiHandler->getLayerByName(layerId)->getElementByName(buttonId).get());

	if (!button)
		throw nx::NullElementException(buttonId);

	return (button->getFontSize());
}

nx::rendering::RGBa const	FrameworkRendering::getColorNotSelectedFromButton(std::string const& layerId, std::string const& buttonId) const
{
	if (!this->_guiHandler->layer_exists(layerId))
		throw nx::LayerNotFoundException(buttonId);

	if (!this->_guiHandler->getLayerByName(layerId)->object_exists(buttonId))
		throw nx::ElementNotFoundException(buttonId);

	nx::gui::Button *button = dynamic_cast<nx::gui::Button *>(this->_guiHandler->getLayerByName(layerId)->getElementByName(buttonId).get());

	if (!button)
		throw nx::NullElementException(buttonId);

	sf::Color const &color = button->getColorNotSelected();

	return (nx::rendering::RGBa(color.r, color.g, color.b, color.a));
}

nx::rendering::RGBa const	FrameworkRendering::getColorSelectedFromButton(std::string const& layerId, std::string const& buttonId) const
{
	if (!this->_guiHandler->layer_exists(layerId))
		throw nx::LayerNotFoundException(buttonId);

	if (!this->_guiHandler->getLayerByName(layerId)->object_exists(buttonId))
		throw nx::ElementNotFoundException(buttonId);

	nx::gui::Button *button = dynamic_cast<nx::gui::Button *>(this->_guiHandler->getLayerByName(layerId)->getElementByName(buttonId).get());

	if (!button)
		throw nx::NullElementException(buttonId);

	sf::Color const &color = button->getColorSelected();

	return (nx::rendering::RGBa(color.r, color.g, color.b, color.a));
}

nx::rendering::RGBa const	FrameworkRendering::getBorderColorFromButton(std::string const& layerId, std::string const& buttonId) const
{
	if (!this->_guiHandler->layer_exists(layerId))
		throw nx::LayerNotFoundException(buttonId);

	if (!this->_guiHandler->getLayerByName(layerId)->object_exists(buttonId))
		throw nx::ElementNotFoundException(buttonId);

	nx::gui::Button *button = dynamic_cast<nx::gui::Button *>(this->_guiHandler->getLayerByName(layerId)->getElementByName(buttonId).get());

	if (!button)
		throw nx::NullElementException(buttonId);

	sf::Color const &color = button->getBorderColor();

	return (nx::rendering::RGBa(color.r, color.g, color.b, color.a));
}

int const					FrameworkRendering::getBorderThicknessFromButton(std::string const& layerId, std::string const& buttonId) const
{
	if (!this->_guiHandler->layer_exists(layerId))
		throw nx::LayerNotFoundException(buttonId);

	if (!this->_guiHandler->getLayerByName(layerId)->object_exists(buttonId))
		throw nx::ElementNotFoundException(buttonId);

	nx::gui::Button *button = dynamic_cast<nx::gui::Button *>(this->_guiHandler->getLayerByName(layerId)->getElementByName(buttonId).get());

	if (!button)
		throw nx::NullElementException(buttonId);

	return (button->getBorderThickness());
}


//Checkbox

void		FrameworkRendering::setStateToCheckbox(std::string const& layerId, std::string const& checkboxId, nx::rendering::CheckboxState const state)
{
	if (!this->_guiHandler->layer_exists(layerId))
		throw nx::LayerNotFoundException(checkboxId);

	if (!this->_guiHandler->getLayerByName(layerId)->object_exists(checkboxId))
		throw nx::ElementNotFoundException(checkboxId);

	nx::gui::Checkbox *checkbox = dynamic_cast<nx::gui::Checkbox *>(this->_guiHandler->getLayerByName(layerId)->getElementByName(checkboxId).get());

	if (!checkbox)
		throw nx::NullElementException(checkboxId);

	checkbox->setState(static_cast<nx::gui::Checkbox::State>(state));
}

void		FrameworkRendering::setBackgroundColorToCheckbox(std::string const& layerId, std::string const& checkboxId, nx::rendering::RGBa const& color)
{
	if (!this->_guiHandler->layer_exists(layerId))
		throw nx::LayerNotFoundException(checkboxId);

	if (!this->_guiHandler->getLayerByName(layerId)->object_exists(checkboxId))
		throw nx::ElementNotFoundException(checkboxId);

	nx::gui::Checkbox *checkbox = dynamic_cast<nx::gui::Checkbox *>(this->_guiHandler->getLayerByName(layerId)->getElementByName(checkboxId).get());

	if (!checkbox)
		throw nx::NullElementException(checkboxId);

	checkbox->setBackgroundColor(FrameworkRendering::RGBa_to_sfColor(color));
}

void		FrameworkRendering::setBorderColorToCheckbox(std::string const& layerId, std::string const& checkboxId, nx::rendering::RGBa const& color)
{
	if (!this->_guiHandler->layer_exists(layerId))
		throw nx::LayerNotFoundException(checkboxId);

	if (!this->_guiHandler->getLayerByName(layerId)->object_exists(checkboxId))
		throw nx::ElementNotFoundException(checkboxId);

	nx::gui::Checkbox *checkbox = dynamic_cast<nx::gui::Checkbox *>(this->_guiHandler->getLayerByName(layerId)->getElementByName(checkboxId).get());

	if (!checkbox)
		throw nx::NullElementException(checkboxId);

	checkbox->setBorderColor(FrameworkRendering::RGBa_to_sfColor(color));
}
void		FrameworkRendering::setBorderThicknessToCheckbox(std::string const& layerId, std::string const& checkboxId, int const thickness)
{
	if (!this->_guiHandler->layer_exists(layerId))
		throw nx::LayerNotFoundException(checkboxId);

	if (!this->_guiHandler->getLayerByName(layerId)->object_exists(checkboxId))
		throw nx::ElementNotFoundException(checkboxId);

	nx::gui::Checkbox *checkbox = dynamic_cast<nx::gui::Checkbox *>(this->_guiHandler->getLayerByName(layerId)->getElementByName(checkboxId).get());

	if (!checkbox)
		throw nx::NullElementException(checkboxId);

	checkbox->setBorderThickness(thickness);
}
void		FrameworkRendering::setPosToCheckbox(std::string const& layerId, std::string const& checkboxId, nx::Vector2f const& pos)
{
	if (!this->_guiHandler->layer_exists(layerId))
		throw nx::LayerNotFoundException(checkboxId);

	if (!this->_guiHandler->getLayerByName(layerId)->object_exists(checkboxId))
		throw nx::ElementNotFoundException(checkboxId);

	nx::gui::Checkbox *checkbox = dynamic_cast<nx::gui::Checkbox *>(this->_guiHandler->getLayerByName(layerId)->getElementByName(checkboxId).get());

	if (!checkbox)
		throw nx::NullElementException(checkboxId);

	checkbox->setPos(sf::Vector2f(pos.x, pos.y));
}
void		FrameworkRendering::setSizeToCheckbox(std::string const& layerId, std::string const& checkboxId, nx::Vector2f const& size)
{
	if (!this->_guiHandler->layer_exists(layerId))
		throw nx::LayerNotFoundException(checkboxId);

	if (!this->_guiHandler->getLayerByName(layerId)->object_exists(checkboxId))
		throw nx::ElementNotFoundException(checkboxId);

	nx::gui::Checkbox *checkbox = dynamic_cast<nx::gui::Checkbox *>(this->_guiHandler->getLayerByName(layerId)->getElementByName(checkboxId).get());

	if (!checkbox)
		throw nx::NullElementException(checkboxId);

	checkbox->setSize(sf::Vector2f(size.x, size.y));
}

nx::rendering::CheckboxState const	FrameworkRendering::getStateFromCheckbox(std::string const& layerId, std::string const& checkboxId) const
{
	if (!this->_guiHandler->layer_exists(layerId))
		throw nx::LayerNotFoundException(checkboxId);

	if (!this->_guiHandler->getLayerByName(layerId)->object_exists(checkboxId))
		throw nx::ElementNotFoundException(checkboxId);

	nx::gui::Checkbox *checkbox = dynamic_cast<nx::gui::Checkbox *>(this->_guiHandler->getLayerByName(layerId)->getElementByName(checkboxId).get());

	if (!checkbox)
		throw nx::NullElementException(checkboxId);

	return (static_cast<nx::rendering::CheckboxState>(checkbox->getState()));
}
nx::rendering::RGBa const			FrameworkRendering::getBackgroundColorFromCheckbox(std::string const& layerId, std::string const& checkboxId) const
{
	if (!this->_guiHandler->layer_exists(layerId))
		throw nx::LayerNotFoundException(checkboxId);

	if (!this->_guiHandler->getLayerByName(layerId)->object_exists(checkboxId))
		throw nx::ElementNotFoundException(checkboxId);

	nx::gui::Checkbox *checkbox = dynamic_cast<nx::gui::Checkbox *>(this->_guiHandler->getLayerByName(layerId)->getElementByName(checkboxId).get());

	if (!checkbox)
		throw nx::NullElementException(checkboxId);

	sf::Color const &color = checkbox->getBackgroundColor();

	return (nx::rendering::RGBa(color.r, color.g, color.b, color.a));
}
nx::rendering::RGBa const			FrameworkRendering::getBorderColorFromCheckbox(std::string const& layerId, std::string const& checkboxId) const
{
	if (!this->_guiHandler->layer_exists(layerId))
		throw nx::LayerNotFoundException(checkboxId);

	if (!this->_guiHandler->getLayerByName(layerId)->object_exists(checkboxId))
		throw nx::ElementNotFoundException(checkboxId);

	nx::gui::Checkbox *checkbox = dynamic_cast<nx::gui::Checkbox *>(this->_guiHandler->getLayerByName(layerId)->getElementByName(checkboxId).get());

	if (!checkbox)
		throw nx::NullElementException(checkboxId);

	sf::Color const &color = checkbox->getBorderColor();

	return (nx::rendering::RGBa(color.r, color.g, color.b, color.a));
}
int const							FrameworkRendering::getBorderThicknessFromCheckbox(std::string const& layerId, std::string const& checkboxId) const
{
	if (!this->_guiHandler->layer_exists(layerId))
		throw nx::LayerNotFoundException(checkboxId);

	if (!this->_guiHandler->getLayerByName(layerId)->object_exists(checkboxId))
		throw nx::ElementNotFoundException(checkboxId);

	nx::gui::Checkbox *checkbox = dynamic_cast<nx::gui::Checkbox *>(this->_guiHandler->getLayerByName(layerId)->getElementByName(checkboxId).get());

	if (!checkbox)
		throw nx::NullElementException(checkboxId);

	return (checkbox->getBorderThickness());
}


//CircleShape

void	FrameworkRendering::setBackgroundColorToCircleShape(std::string const& circleShapeId, nx::rendering::RGBa const& color)
{
	if (!this->_graphicsHandler->object_exists(circleShapeId))
		throw nx::ElementNotFoundException(circleShapeId);

	nx::graphics::CircleShape *circleShape = dynamic_cast<nx::graphics::CircleShape *>(this->_graphicsHandler->getElementByName(circleShapeId).get());

	if (!circleShape)
		throw nx::NullElementException(circleShapeId);

	circleShape->setBackgroundColor(FrameworkRendering::RGBa_to_sfColor(color));
}

void	FrameworkRendering::setBorderColorToCircleShape(std::string const& circleShapeId, nx::rendering::RGBa const& color)
{
	if (!this->_graphicsHandler->object_exists(circleShapeId))
		throw nx::ElementNotFoundException(circleShapeId);

	nx::graphics::CircleShape *circleShape = dynamic_cast<nx::graphics::CircleShape *>(this->_graphicsHandler->getElementByName(circleShapeId).get());

	if (!circleShape)
		throw nx::NullElementException(circleShapeId);

	circleShape->setBorderColor(FrameworkRendering::RGBa_to_sfColor(color));
}

void	FrameworkRendering::setBorderThicknessToCircleShape(std::string const& circleShapeId, int const thickness)
{
	if (!this->_graphicsHandler->object_exists(circleShapeId))
		throw nx::ElementNotFoundException(circleShapeId);

	nx::graphics::CircleShape *circleShape = dynamic_cast<nx::graphics::CircleShape *>(this->_graphicsHandler->getElementByName(circleShapeId).get());

	if (!circleShape)
		throw nx::NullElementException(circleShapeId);

	circleShape->setBorderThickness(thickness);
}

void	FrameworkRendering::setRotationToCircleShape(std::string const& circleShapeId, float const angle)
{
	if (!this->_graphicsHandler->object_exists(circleShapeId))
		throw nx::ElementNotFoundException(circleShapeId);

	nx::graphics::CircleShape *circleShape = dynamic_cast<nx::graphics::CircleShape *>(this->_graphicsHandler->getElementByName(circleShapeId).get());

	if (!circleShape)
		throw nx::NullElementException(circleShapeId);

	circleShape->setRotation(angle);
}

void	FrameworkRendering::setRadiusToCircleShape(std::string const& circleShapeId, float const radius)
{
	if (!this->_graphicsHandler->object_exists(circleShapeId))
		throw nx::ElementNotFoundException(circleShapeId);

	nx::graphics::CircleShape *circleShape = dynamic_cast<nx::graphics::CircleShape *>(this->_graphicsHandler->getElementByName(circleShapeId).get());

	if (!circleShape)
		throw nx::NullElementException(circleShapeId);

	circleShape->setRadius(radius);
}

void	FrameworkRendering::setPosToCircleShape(std::string const& circleShapeId, nx::Vector2f const& pos)
{
	if (!this->_graphicsHandler->object_exists(circleShapeId))
		throw nx::ElementNotFoundException(circleShapeId);

	nx::graphics::CircleShape *circleShape = dynamic_cast<nx::graphics::CircleShape *>(this->_graphicsHandler->getElementByName(circleShapeId).get());

	if (!circleShape)
		throw nx::NullElementException(circleShapeId);

	circleShape->setPos(sf::Vector2f(pos.x, pos.y));
}

void	FrameworkRendering::setSizeToCircleShape(std::string const& circleShapeId, nx::Vector2f const& size)
{
	if (!this->_graphicsHandler->object_exists(circleShapeId))
		throw nx::ElementNotFoundException(circleShapeId);

	nx::graphics::CircleShape *circleShape = dynamic_cast<nx::graphics::CircleShape *>(this->_graphicsHandler->getElementByName(circleShapeId).get());

	if (!circleShape)
		throw nx::NullElementException(circleShapeId);

	circleShape->setSize(sf::Vector2f(size.x, size.y));
}

nx::rendering::RGBa const	FrameworkRendering::getBackgroundColorFromCircleShape(std::string const& circleShapeId) const
{
	if (!this->_graphicsHandler->object_exists(circleShapeId))
		throw nx::ElementNotFoundException(circleShapeId);

	nx::graphics::CircleShape *circleShape = dynamic_cast<nx::graphics::CircleShape *>(this->_graphicsHandler->getElementByName(circleShapeId).get());

	if (!circleShape)
		throw nx::NullElementException(circleShapeId);

	sf::Color const &color = circleShape->getBackgroundColor();

	return (nx::rendering::RGBa(color.r, color.g, color.b, color.a));
}

nx::rendering::RGBa const	FrameworkRendering::getBorderColorFromCircleShape(std::string const& circleShapeId) const
{
	if (!this->_graphicsHandler->object_exists(circleShapeId))
		throw nx::ElementNotFoundException(circleShapeId);

	nx::graphics::CircleShape *circleShape = dynamic_cast<nx::graphics::CircleShape *>(this->_graphicsHandler->getElementByName(circleShapeId).get());

	if (!circleShape)
		throw nx::NullElementException(circleShapeId);

	sf::Color const &color = circleShape->getBorderColor();

	return (nx::rendering::RGBa(color.r, color.g, color.b, color.a));
}

int const					FrameworkRendering::getBorderThicknessFromCircleShape(std::string const& circleShapeId) const
{
	if (!this->_graphicsHandler->object_exists(circleShapeId))
		throw nx::ElementNotFoundException(circleShapeId);

	nx::graphics::CircleShape *circleShape = dynamic_cast<nx::graphics::CircleShape *>(this->_graphicsHandler->getElementByName(circleShapeId).get());

	if (!circleShape)
		throw nx::NullElementException(circleShapeId);

	return (circleShape->getBorderThickness());
}

float const					FrameworkRendering::getRotationFromCircleShape(std::string const& circleShapeId) const
{
	if (!this->_graphicsHandler->object_exists(circleShapeId))
		throw nx::ElementNotFoundException(circleShapeId);

	nx::graphics::CircleShape *circleShape = dynamic_cast<nx::graphics::CircleShape *>(this->_graphicsHandler->getElementByName(circleShapeId).get());

	if (!circleShape)
		throw nx::NullElementException(circleShapeId);

	return (circleShape->getRotation());
}

float const					FrameworkRendering::getRadiusFromCircleShape(std::string const& circleShapeId) const
{
	if (!this->_graphicsHandler->object_exists(circleShapeId))
		throw nx::ElementNotFoundException(circleShapeId);

	nx::graphics::CircleShape *circleShape = dynamic_cast<nx::graphics::CircleShape *>(this->_graphicsHandler->getElementByName(circleShapeId).get());

	if (!circleShape)
		throw nx::NullElementException(circleShapeId);

	return (circleShape->getRadius());
}


//ComboBox

void	FrameworkRendering::setBackgroundColorToComboBox(std::string const& layerId, std::string const& comboBoxId, nx::rendering::RGBa const& color)
{
	if (!this->_guiHandler->layer_exists(layerId))
		throw nx::LayerNotFoundException(comboBoxId);

	if (!this->_guiHandler->getLayerByName(layerId)->object_exists(comboBoxId))
		throw nx::ElementNotFoundException(comboBoxId);

	nx::gui::ComboBox *comboBox = dynamic_cast<nx::gui::ComboBox *>(this->_guiHandler->getLayerByName(layerId)->getElementByName(comboBoxId).get());

	if (!comboBox)
		throw nx::NullElementException(comboBoxId);

	comboBox->setBackgroundColor(FrameworkRendering::RGBa_to_sfColor(color));
}

void	FrameworkRendering::setBorderColorToComboBox(std::string const& layerId, std::string const& comboBoxId, nx::rendering::RGBa const& color)
{
	if (!this->_guiHandler->layer_exists(layerId))
		throw nx::LayerNotFoundException(comboBoxId);

	if (!this->_guiHandler->getLayerByName(layerId)->object_exists(comboBoxId))
		throw nx::ElementNotFoundException(comboBoxId);

	nx::gui::ComboBox *comboBox = dynamic_cast<nx::gui::ComboBox *>(this->_guiHandler->getLayerByName(layerId)->getElementByName(comboBoxId).get());

	if (!comboBox)
		throw nx::NullElementException(comboBoxId);

	comboBox->setBorderColor(FrameworkRendering::RGBa_to_sfColor(color));
}

void	FrameworkRendering::setBorderThicknessToComboBox(std::string const& layerId, std::string const& comboBoxId, int const thickness)
{
	if (!this->_guiHandler->layer_exists(layerId))
		throw nx::LayerNotFoundException(comboBoxId);

	if (!this->_guiHandler->getLayerByName(layerId)->object_exists(comboBoxId))
		throw nx::ElementNotFoundException(comboBoxId);

	nx::gui::ComboBox *comboBox = dynamic_cast<nx::gui::ComboBox *>(this->_guiHandler->getLayerByName(layerId)->getElementByName(comboBoxId).get());

	if (!comboBox)
		throw nx::NullElementException(comboBoxId);

	comboBox->setBorderThickness(thickness);
}

void	FrameworkRendering::setFontSizeToComboBox(std::string const& layerId, std::string const& comboBoxId, unsigned int const fontSize)
{
	if (!this->_guiHandler->layer_exists(layerId))
		throw nx::LayerNotFoundException(comboBoxId);

	if (!this->_guiHandler->getLayerByName(layerId)->object_exists(comboBoxId))
		throw nx::ElementNotFoundException(comboBoxId);

	nx::gui::ComboBox *comboBox = dynamic_cast<nx::gui::ComboBox *>(this->_guiHandler->getLayerByName(layerId)->getElementByName(comboBoxId).get());

	if (!comboBox)
		throw nx::NullElementException(comboBoxId);

	comboBox->setFontSize(fontSize);
}

void	FrameworkRendering::addSelectionToComboBox(std::string const& layerId, std::string const& comboBoxId, std::string const& selection)
{
	if (!this->_guiHandler->layer_exists(layerId))
		throw nx::LayerNotFoundException(comboBoxId);

	if (!this->_guiHandler->getLayerByName(layerId)->object_exists(comboBoxId))
		throw nx::ElementNotFoundException(comboBoxId);

	nx::gui::ComboBox *comboBox = dynamic_cast<nx::gui::ComboBox *>(this->_guiHandler->getLayerByName(layerId)->getElementByName(comboBoxId).get());

	if (!comboBox)
		throw nx::NullElementException(comboBoxId);

	comboBox->addSelection(selection);
}

void	FrameworkRendering::removeSelectionToComboBox(std::string const& layerId, std::string const& comboBoxId, std::string const& selection, uint16_t const nbTimes)
{
	if (!this->_guiHandler->layer_exists(layerId))
		throw nx::LayerNotFoundException(comboBoxId);

	if (!this->_guiHandler->getLayerByName(layerId)->object_exists(comboBoxId))
		throw nx::ElementNotFoundException(comboBoxId);

	nx::gui::ComboBox *comboBox = dynamic_cast<nx::gui::ComboBox *>(this->_guiHandler->getLayerByName(layerId)->getElementByName(comboBoxId).get());

	if (!comboBox)
		throw nx::NullElementException(comboBoxId);

	comboBox->removeSelection(selection, nbTimes);
}

void	FrameworkRendering::removeSelectionToComboBox(std::string const& layerId, std::string const& comboBoxId, uint16_t const idx, uint16_t const nbTimes)
{
	if (!this->_guiHandler->layer_exists(layerId))
		throw nx::LayerNotFoundException(comboBoxId);

	if (!this->_guiHandler->getLayerByName(layerId)->object_exists(comboBoxId))
		throw nx::ElementNotFoundException(comboBoxId);

	nx::gui::ComboBox *comboBox = dynamic_cast<nx::gui::ComboBox *>(this->_guiHandler->getLayerByName(layerId)->getElementByName(comboBoxId).get());

	if (!comboBox)
		throw nx::NullElementException(comboBoxId);

	comboBox->removeSelection(idx, nbTimes);
}

void	FrameworkRendering::clearSelectionsToComboBox(std::string const& layerId, std::string const& comboBoxId)
{
	if (!this->_guiHandler->layer_exists(layerId))
		throw nx::LayerNotFoundException(comboBoxId);

	if (!this->_guiHandler->getLayerByName(layerId)->object_exists(comboBoxId))
		throw nx::ElementNotFoundException(comboBoxId);

	nx::gui::ComboBox *comboBox = dynamic_cast<nx::gui::ComboBox *>(this->_guiHandler->getLayerByName(layerId)->getElementByName(comboBoxId).get());

	if (!comboBox)
		throw nx::NullElementException(comboBoxId);

	comboBox->clearSelections();
}

void	FrameworkRendering::setPosToComboBox(std::string const& layerId, std::string const& comboBoxId, nx::Vector2f const& pos)
{
	if (!this->_guiHandler->layer_exists(layerId))
		throw nx::LayerNotFoundException(comboBoxId);

	if (!this->_guiHandler->getLayerByName(layerId)->object_exists(comboBoxId))
		throw nx::ElementNotFoundException(comboBoxId);

	nx::gui::ComboBox *comboBox = dynamic_cast<nx::gui::ComboBox *>(this->_guiHandler->getLayerByName(layerId)->getElementByName(comboBoxId).get());

	if (!comboBox)
		throw nx::NullElementException(comboBoxId);

	comboBox->setPos(sf::Vector2f(pos.x, pos.y));
}

void	FrameworkRendering::setSizeToComboBox(std::string const& layerId, std::string const& comboBoxId, nx::Vector2f const& size)
{
	if (!this->_guiHandler->layer_exists(layerId))
		throw nx::LayerNotFoundException(comboBoxId);

	if (!this->_guiHandler->getLayerByName(layerId)->object_exists(comboBoxId))
		throw nx::ElementNotFoundException(comboBoxId);

	nx::gui::ComboBox *comboBox = dynamic_cast<nx::gui::ComboBox *>(this->_guiHandler->getLayerByName(layerId)->getElementByName(comboBoxId).get());

	if (!comboBox)
		throw nx::NullElementException(comboBoxId);

	comboBox->setSize(sf::Vector2f(size.x, size.y));
}

nx::rendering::RGBa const	FrameworkRendering::getBackgroundColorFromComboBox(std::string const& layerId, std::string const& comboBoxId) const
{
	if (!this->_guiHandler->layer_exists(layerId))
		throw nx::LayerNotFoundException(comboBoxId);

	if (!this->_guiHandler->getLayerByName(layerId)->object_exists(comboBoxId))
		throw nx::ElementNotFoundException(comboBoxId);

	nx::gui::ComboBox *comboBox = dynamic_cast<nx::gui::ComboBox *>(this->_guiHandler->getLayerByName(layerId)->getElementByName(comboBoxId).get());

	if (!comboBox)
		throw nx::NullElementException(comboBoxId);

	sf::Color const &color = comboBox->getBackgroundColor();

	return (nx::rendering::RGBa(color.r, color.g, color.b, color.a));
}

nx::rendering::RGBa const	FrameworkRendering::getBorderColorFromComboBox(std::string const& layerId, std::string const& comboBoxId) const
{
	if (!this->_guiHandler->layer_exists(layerId))
		throw nx::LayerNotFoundException(comboBoxId);

	if (!this->_guiHandler->getLayerByName(layerId)->object_exists(comboBoxId))
		throw nx::ElementNotFoundException(comboBoxId);

	nx::gui::ComboBox *comboBox = dynamic_cast<nx::gui::ComboBox *>(this->_guiHandler->getLayerByName(layerId)->getElementByName(comboBoxId).get());

	if (!comboBox)
		throw nx::NullElementException(comboBoxId);

	sf::Color const &color = comboBox->getBorderColor();

	return (nx::rendering::RGBa(color.r, color.g, color.b, color.a));
}

int const					FrameworkRendering::getBorderThicknessFromComboBox(std::string const& layerId, std::string const& comboBoxId) const
{
	if (!this->_guiHandler->layer_exists(layerId))
		throw nx::LayerNotFoundException(comboBoxId);

	if (!this->_guiHandler->getLayerByName(layerId)->object_exists(comboBoxId))
		throw nx::ElementNotFoundException(comboBoxId);

	nx::gui::ComboBox *comboBox = dynamic_cast<nx::gui::ComboBox *>(this->_guiHandler->getLayerByName(layerId)->getElementByName(comboBoxId).get());

	if (!comboBox)
		throw nx::NullElementException(comboBoxId);

	return (comboBox->getBorderThickness());
}

unsigned int const			FrameworkRendering::getFontSizeFromComboBox(std::string const& layerId, std::string const& comboBoxId) const
{
	if (!this->_guiHandler->layer_exists(layerId))
		throw nx::LayerNotFoundException(comboBoxId);

	if (!this->_guiHandler->getLayerByName(layerId)->object_exists(comboBoxId))
		throw nx::ElementNotFoundException(comboBoxId);

	nx::gui::ComboBox *comboBox = dynamic_cast<nx::gui::ComboBox *>(this->_guiHandler->getLayerByName(layerId)->getElementByName(comboBoxId).get());

	if (!comboBox)
		throw nx::NullElementException(comboBoxId);

	return (comboBox->getFontSize());
}

std::string const			FrameworkRendering::getSelectedFromComboBox(std::string const& layerId, std::string const& comboBoxId) const
{
	if (!this->_guiHandler->layer_exists(layerId))
		throw nx::LayerNotFoundException(comboBoxId);

	if (!this->_guiHandler->getLayerByName(layerId)->object_exists(comboBoxId))
		throw nx::ElementNotFoundException(comboBoxId);

	nx::gui::ComboBox *comboBox = dynamic_cast<nx::gui::ComboBox *>(this->_guiHandler->getLayerByName(layerId)->getElementByName(comboBoxId).get());

	if (!comboBox)
		throw nx::NullElementException(comboBoxId);

	return (comboBox->getSelected());
}

uint16_t const				FrameworkRendering::getIdxSelectedFromComboBox(std::string const& layerId, std::string const& comboBoxId) const
{
	if (!this->_guiHandler->layer_exists(layerId))
		throw nx::LayerNotFoundException(comboBoxId);

	if (!this->_guiHandler->getLayerByName(layerId)->object_exists(comboBoxId))
		throw nx::ElementNotFoundException(comboBoxId);

	nx::gui::ComboBox *comboBox = dynamic_cast<nx::gui::ComboBox *>(this->_guiHandler->getLayerByName(layerId)->getElementByName(comboBoxId).get());

	if (!comboBox)
		throw nx::NullElementException(comboBoxId);

	return (comboBox->getIdxSelected());
}