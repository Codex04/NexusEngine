#include "FrameworkRendering.hpp"

FrameworkRendering::FrameworkRendering(nx::Engine* engine)
	:
	nx::RenderingFrameworkTpl("FrameworkRendering"),
	_engine(engine),
	_win(nullptr),
	_handler(nullptr)
{
	nx::Log::inform("New Rendering Framework created");
}

FrameworkRendering::~FrameworkRendering()
{
	nx::Log::inform("New Rendering Framework deleted");
}

void FrameworkRendering::InitializeWindow(int width, int height, std::string titleWin)
{
	this->_win = std::make_shared<sf::RenderWindow>(sf::VideoMode(width, height), titleWin);
	this->_handler = std::make_shared<GUIHandler>(this->_win);

	std::shared_ptr<GUILayer> layer = std::make_shared<GUILayer>("MainLayer");
	std::shared_ptr<Button> button = std::make_shared<Button>(sf::Vector2f(300, 100), sf::Vector2f(100, 30), "MyFirstButton", true,
															  ColorInfo(sf::Color(200, 200, 200, 255), sf::Color(200, 0, 0, 255), 2),
															  TextInfo("./fonts/Roboto-Regular.ttf", "Press me!", 12, sf::Color(0, 0, 0, 255)));
	std::shared_ptr<Checkbox> checkbox = std::make_shared<Checkbox>(sf::Vector2f(640, 30), sf::Vector2f(30, 30), "MyFirstCheckbox",
																	ColorInfo(sf::Color(200, 200, 200, 255), sf::Color(0, 0, 255, 255), 2));
	std::shared_ptr<ProgressBar> progressbar = std::make_shared<ProgressBar>(sf::Vector2f(240, 500), sf::Vector2f(300, 50), "MyFirstProgressbar",
																			 ColorInfo(sf::Color(200, 200, 200, 255), sf::Color(255, 255, 255, 255), 2),
																			 TextInfo("./fonts/Roboto-Regular.ttf", "", 16, sf::Color(0, 0, 0, 255)));
	std::shared_ptr<ComboBox> combobox = std::make_shared<ComboBox>(sf::Vector2f(70, 250), sf::Vector2f(140, 30), "MyFirstComboBox",
																    ColorInfo(sf::Color(200, 200, 200, 255), sf::Color(255, 255, 0, 255), 2),
																    TextInfo("./fonts/Roboto-Regular.ttf", "", 12, sf::Color(0, 0, 0, 255)));
	std::shared_ptr<TextInput> textinput = std::make_shared<TextInput>(sf::Vector2f(400, 350), sf::Vector2f(230, 30), "MyFirstTextInput",
																	   ColorInfo(sf::Color(200, 200, 200, 255), sf::Color(255, 0, 255, 255), 2),
																	   TextInfo("./fonts/Roboto-Regular.ttf", "A default text..", 12, sf::Color(0, 0, 0, 255)));
	progressbar->setFilled(50);
	combobox->addSelection("First item");
	combobox->addSelection("Second item");
	combobox->addSelection("LEEERRROYYYY");
	combobox->addSelection("JENKINSSSSS");
	combobox->addSelection("Very long thing over thereeeee omggg");
	layer->add(button);
	layer->add(checkbox);
	layer->add(progressbar);
	layer->add(combobox);
	layer->add(textinput);
	this->_handler->addLayer(layer);
}

void FrameworkRendering::RefreshRendering()
{
	if (this->_win && this->_handler) 
	{
		while (this->_win->isOpen())
		{
			// Getting input events	
			sf::Event event;

			while (this->_win->pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					this->_win->close();
				this->_handler->processEvent(event);
			}
			
			// Clearing the window
			this->_win->clear(sf::Color(0, 0 , 0, 255));

			// Drawing stuff on screen
			this->_handler->drawLayers();

			// Displaying screen
			this->_win->display();
		}
	}
}