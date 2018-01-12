#include "Checkbox.hpp"

Checkbox::Checkbox(sf::Vector2f const& pos, sf::Vector2f const& size, std::string const& identifier, ColorInfo const& colorInfo) :
	GUIElement(pos, size, identifier), _state(State::UNCHECKED),
	_backgroundColor(colorInfo.backgroundColor), _borderColor(colorInfo.borderColor), _borderThickness(colorInfo.borderThickness),
	_body(sf::RectangleShape(size))
{
	this->_body.setPosition(pos);
	this->_body.setFillColor(colorInfo.backgroundColor);
	this->_body.setOutlineThickness(colorInfo.borderThickness);
	this->_body.setOutlineColor(colorInfo.borderColor);

	sf::VertexArray half1(sf::LinesStrip, 2);
	sf::VertexArray half2(sf::LinesStrip, 2);
	sf::VertexArray partial(sf::LinesStrip, 2);

	half1[0].position = pos;
	half1[0].color = this->_borderColor;
	half1[1].position = sf::Vector2f(pos.x + size.x - this->_borderThickness,
									 pos.y + size.y - this->_borderThickness);
	half1[1].color = this->_borderColor;

	half2[0].position = sf::Vector2f(pos.x + size.x - this->_borderThickness, pos.y);
	half2[0].color = this->_borderColor;
	half2[1].position = sf::Vector2f(pos.x - this->_borderThickness, pos.y + size.y - this->_borderThickness);
	half2[1].color = this->_borderColor;

	partial[0].position = sf::Vector2f(pos.x + (size.x - this->_borderThickness) * 0.1f,
									   pos.y + (size.y - this->_borderThickness) / 2.0f);
	partial[0].color = this->_borderColor;
	partial[1].position = sf::Vector2f(pos.x + (size.x - this->_borderThickness) * 0.9f, 
									   pos.y + (size.y - this->_borderThickness) / 2.0f);
	partial[1].color = this->_borderColor;

	this->_lines.push_back(half1);
	this->_lines.push_back(half2);
	this->_lines.push_back(partial);

	this->setSize(sf::Vector2f(this->getSize().x + colorInfo.borderThickness, this->getSize().y + colorInfo.borderThickness));
}

Checkbox::~Checkbox()
{

}


// GUIElement's mouse event methods overload
void Checkbox::onLeftClickPressedInside(sf::Vector2i const& pos)
{
	this->dispatchMouseEvent(pos, "onLeftClickPressedInside");

	//Will be called when a left-click is inside the element
	nx::Log::inform("Left-click pressed inside the checkbox '" + this->getIdentifier() + "'");
	if (this->_state != State::UNCHECKED)
		this->_state = State::UNCHECKED;
	else
		this->_state = State::CHECKED;
}

// Display

void Checkbox::show(std::shared_ptr<sf::RenderWindow> const& win)
{
	if (this->isVisible())
	{
		win->draw(this->_body);
		if (this->_state == State::CHECKED)
		{
			win->draw(this->_lines[0]);
			win->draw(this->_lines[1]);
		}
		else if (this->_state == State::PARTIAL)
			win->draw(this->_lines[2]);
	}
}


// Setters
void	Checkbox::setState(State const state)
{
	this->_state = state;
}

void	Checkbox::setBackgroundColor(sf::Color const& color)
{
	this->_backgroundColor = color;
	this->_body.setFillColor(this->_backgroundColor);
}

void	Checkbox::setBorderColor(sf::Color const& color)
{
	this->_borderColor = color;
	this->_body.setOutlineColor(this->_borderColor);
	for (auto it : this->_lines)
	{
		it[0].color = this->_borderColor;
		it[1].color = this->_borderColor;
	}
}

void	Checkbox::setBorderThickness(int const thickness)
{
	this->_borderThickness = thickness;
	this->setSize(sf::Vector2f(this->getSize().x + thickness, this->getSize().y + thickness));
	this->_body.setOutlineThickness(this->_borderThickness);
}

void	Checkbox::setPos(sf::Vector2f const& pos)
{
	GUIElement::setPos(sf::Vector2f(pos.x - this->_borderThickness, pos.y - this->_borderThickness));
	this->_body.setPosition(this->getPos());

	this->_lines[0][0].position = pos;
	this->_lines[0][1].position = sf::Vector2f(pos.x + this->getSize().x - this->_borderThickness,
											   pos.y + this->getSize().y - this->_borderThickness);

	this->_lines[1][0].position = sf::Vector2f(pos.x + this->getSize().x - this->_borderThickness, pos.y);
	this->_lines[1][1].position = sf::Vector2f(pos.x - this->_borderThickness, pos.y + this->getSize().y - this->_borderThickness);

	this->_lines[2][0].position = sf::Vector2f(pos.x + (this->getSize().x - this->_borderThickness) * 0.1f,
											   pos.y + (this->getSize().y - this->_borderThickness) / 2.0f);
	this->_lines[2][1].position = sf::Vector2f(pos.x + (this->getSize().x - this->_borderThickness) * 0.9f,
											   pos.y + (this->getSize().y - this->_borderThickness) / 2.0f);
}

void	Checkbox::setSize(sf::Vector2f const& size)
{
	GUIElement::setSize(size);
	this->_body.setSize(sf::Vector2f(this->getSize().x - this->_borderThickness * 2, this->getSize().y - this->_borderThickness * 2));

	if (!this->_lines.empty())
	{
		this->_lines[0][1].position = sf::Vector2f(this->getPos().x + this->getSize().x - this->_borderThickness,
												   this->getPos().y + this->getSize().y - this->_borderThickness);
		this->_lines[1][1].position = sf::Vector2f(this->getPos().x - this->_borderThickness, this->getPos().y + size.y - this->_borderThickness);
		this->_lines[2][1].position = sf::Vector2f(this->getPos().x + (size.x - this->_borderThickness) * 0.9f, this->getPos().y + (size.y - this->_borderThickness) / 2.0f);
	}
}

// Getters

std::string	const	Checkbox::getType() const
{
	return ("Checkbox");
}


// Specific getters

Checkbox::State const Checkbox::getState() const
{
	return (this->_state);
}

sf::Color const	&	Checkbox::getBackgroundColor() const
{
	return (this->_backgroundColor);
}

sf::Color const	&	Checkbox::getBorderColor() const
{
	return (this->_borderColor);
}

int const			Checkbox::getBorderThickness() const
{
	return (this->_borderThickness);
}