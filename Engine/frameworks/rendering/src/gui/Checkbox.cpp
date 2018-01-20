#include "Checkbox.hpp"

nx::gui::Checkbox::Checkbox(sf::Vector2f const& pos, sf::Vector2f const& size, std::string const& identifier, nx::rendering::MouseEventsContainer const& events, ColorInfo const& colorInfo) :
	GUIElement(pos, size, identifier, events), _state(State::UNCHECKED),
	_backgroundColor(colorInfo.backgroundColor), _borderColor(colorInfo.borderColor), _borderThickness(colorInfo.borderThickness),
	_body(sf::RectangleShape(size))
{
	this->_body.setPosition(pos);
	this->_body.setFillColor(colorInfo.backgroundColor);
	this->_body.setOutlineThickness(static_cast<float>(colorInfo.borderThickness));
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

	GUIElement::setSize(sf::Vector2f(this->_body.getLocalBounds().width, this->_body.getLocalBounds().height));
}

nx::gui::Checkbox::~Checkbox()
{

}


// GUIElement's mouse event methods overload

void nx::gui::Checkbox::onLeftClickPressedInside(sf::Vector2i const& pos)
{
	this->dispatchMouseEvent(pos, "onLeftClickPressedInside");

	//Will be called when a left-click is inside the element
	if (this->_state != State::UNCHECKED)
		this->_state = State::UNCHECKED;
	else
		this->_state = State::CHECKED;
}

// Display

void nx::gui::Checkbox::show(std::shared_ptr<sf::RenderWindow> const& win)
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
void	nx::gui::Checkbox::setState(State const state)
{
	this->_state = state;
}

void	nx::gui::Checkbox::setBackgroundColor(sf::Color const& color)
{
	this->_backgroundColor = color;
	this->_body.setFillColor(this->_backgroundColor);
}

void	nx::gui::Checkbox::setBorderColor(sf::Color const& color)
{
	this->_borderColor = color;
	this->_body.setOutlineColor(this->_borderColor);
	for (auto it : this->_lines)
	{
		it[0].color = this->_borderColor;
		it[1].color = this->_borderColor;
	}
}

void	nx::gui::Checkbox::setBorderThickness(int const thickness)
{
	this->_borderThickness = thickness;
	this->_body.setOutlineThickness(static_cast<float>(this->_borderThickness));
	GUIElement::setSize(sf::Vector2f(this->_body.getLocalBounds().width, this->_body.getLocalBounds().height));
}

void	nx::gui::Checkbox::setPos(sf::Vector2f const& pos)
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

void	nx::gui::Checkbox::setSize(sf::Vector2f const& size)
{
	this->_body.setSize(sf::Vector2f(size.x - this->_borderThickness * 2, size.y - this->_borderThickness * 2));
	GUIElement::setSize(sf::Vector2f(this->_body.getLocalBounds().width, this->_body.getLocalBounds().height));

	if (!this->_lines.empty())
	{
		this->_lines[0][1].position = sf::Vector2f(this->getPos().x + this->getSize().x - this->_borderThickness,
												   this->getPos().y + this->getSize().y - this->_borderThickness);
		this->_lines[1][1].position = sf::Vector2f(this->getPos().x - this->_borderThickness, this->getPos().y + size.y - this->_borderThickness);
		this->_lines[2][1].position = sf::Vector2f(this->getPos().x + (size.x - this->_borderThickness) * 0.9f, this->getPos().y + (size.y - this->_borderThickness) / 2.0f);
	}
}

// Getters

std::string	const	nx::gui::Checkbox::getType() const
{
	return ("Checkbox");
}


// Specific getters

nx::gui::Checkbox::State const nx::gui::Checkbox::getState() const
{
	return (this->_state);
}

sf::Color const	&	nx::gui::Checkbox::getBackgroundColor() const
{
	return (this->_backgroundColor);
}

sf::Color const	&	nx::gui::Checkbox::getBorderColor() const
{
	return (this->_borderColor);
}

int const			nx::gui::Checkbox::getBorderThickness() const
{
	return (this->_borderThickness);
}