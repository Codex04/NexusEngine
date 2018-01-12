#include "ProgressBar.hpp"

ProgressBar::ProgressBar(sf::Vector2f const& pos, sf::Vector2f const& size, std::string const& identifier, ColorInfo const& colorInfo, TextInfo const& textInfo, bool const displayPercentage) :
	GUIElement(pos, size, identifier),
	_backgroundColor(colorInfo.backgroundColor), _borderColor(colorInfo.borderColor), _borderThickness(colorInfo.borderThickness),
	_body(sf::RectangleShape(size)), _filled(sf::RectangleShape()), _percentage(0), _font(sf::Font())
{
	this->_label = sf::Text("", this->_font, textInfo.fontSize);
	this->_label.setFillColor(textInfo.textColor);
	this->_label.setStyle(textInfo.textStyle);
	this->setFilled(0);

	this->_font.loadFromFile(textInfo.fontPath);

	this->_body.setPosition(pos);
	this->_body.setFillColor(colorInfo.backgroundColor);
	this->_body.setOutlineThickness(colorInfo.borderThickness);
	this->_body.setOutlineColor(colorInfo.borderColor);

	this->_filled.setPosition(pos);
	this->_filled.setFillColor(sf::Color(0, 255, 0, 255));

	this->setSize(sf::Vector2f(this->getSize().x + colorInfo.borderThickness, this->getSize().y + colorInfo.borderThickness));
}

ProgressBar::~ProgressBar()
{

}

// Display

void ProgressBar::show(std::shared_ptr<sf::RenderWindow> const& win)
{
	if (this->isVisible())
	{
		win->draw(this->_body);
		win->draw(this->_filled);
		win->draw(this->_label);
	}
}


// Setters

void	ProgressBar::setBackgroundColor(sf::Color const& color)
{
	this->_backgroundColor = color;
	this->_body.setFillColor(this->_backgroundColor);
}

void	ProgressBar::setBorderColor(sf::Color const& color)
{
	this->_borderColor = color;
	this->_body.setOutlineColor(this->_borderColor);
}

void	ProgressBar::setBorderThickness(int const thickness)
{
	this->_borderThickness = thickness;
	this->setSize(sf::Vector2f(this->getSize().x + thickness, this->getSize().y + thickness));
	this->_body.setOutlineThickness(this->_borderThickness);
}

void	ProgressBar::setFilled(int const percentage)
{
	if (percentage >= 0 && percentage <= 100)
	{
		this->_percentage = percentage;
		this->_filled.setSize(sf::Vector2f(this->getSize().x * (percentage / 100.0f), this->getSize().y - this->_borderThickness * 2));
		this->_label.setPosition(this->getPos().x + this->getSize().x / 2.0f - this->_label.getLocalBounds().width / 2.0f - this->_borderThickness * 2,
			this->getPos().y + this->getSize().y / 2.0f - this->_label.getLocalBounds().height / 2.0f - this->_borderThickness * 2);
		this->_label.setString(std::to_string(percentage) + "%");
	}
}

void	ProgressBar::setPos(sf::Vector2f const& pos)
{
	GUIElement::setPos(sf::Vector2f(pos.x - this->_borderThickness, pos.y - this->_borderThickness));
	this->_body.setPosition(pos);
	this->_filled.setPosition(pos);
	this->_label.setPosition(pos.x + this->getSize().x / 2.0f - this->_label.getLocalBounds().width / 2.0f - this->_borderThickness * 2,
							 pos.y + this->getSize().y / 2.0f - this->_label.getLocalBounds().height / 2.0f - this->_borderThickness * 2);
}

void	ProgressBar::setSize(sf::Vector2f const& size)
{
	GUIElement::setSize(size);
	this->_body.setSize(sf::Vector2f(this->getSize().x - this->_borderThickness * 2, this->getSize().y - this->_borderThickness * 2));
	this->_filled.setSize(sf::Vector2f(this->getSize().x * (this->_percentage / 100.0f), this->getSize().y - this->_borderThickness * 2));
	this->_label.setPosition(this->getPos().x + this->getSize().x / 2.0f - this->_label.getLocalBounds().width / 2.0f - this->_borderThickness * 2,
							 this->getPos().y + this->getSize().y / 2.0f - this->_label.getLocalBounds().height / 2.0f - this->_borderThickness * 2);
}

void	ProgressBar::setLabel(sf::Text const& label)
{
	this->_label = label;
}

// Getters

std::string	const	ProgressBar::getType() const
{
	return ("ProgressBar");
}


// Specific getters

sf::Color const	&	ProgressBar::getBackgroundColor() const
{
	return (this->_backgroundColor);
}

sf::Color const	&	ProgressBar::getBorderColor() const
{
	return (this->_borderColor);
}

int const			ProgressBar::getBorderThickness() const
{
	return (this->_borderThickness);
}

int const			ProgressBar::getFilled() const
{
	return (this->_percentage);
}

sf::Text const &	ProgressBar::getLabel() const
{
	return (this->_label);
}