#include "GUIElement.hpp"

GUIElement::GUIElement(sf::Vector2f const& pos, sf::Vector2f const& size, std::string const& identifier) :
	_pos(pos), _size(size), _identifier(identifier), _isVisible(true)
{

}
GUIElement::~GUIElement()
{

}


// Mouse events

void	GUIElement::onMoveInside(sf::Vector2i const& pos)
{

}

void	GUIElement::onMoveOutside(sf::Vector2i const& pos)
{

}

void	GUIElement::onLeftClickPressedInside(sf::Vector2i const& pos)
{

}

void	GUIElement::onLeftClickReleasedInside(sf::Vector2i const& pos)
{

}

void	GUIElement::onRightClickPressedInside(sf::Vector2i const& pos)
{

}

void	GUIElement::onRightClickReleasedInside(sf::Vector2i const& pos)
{

}

void	GUIElement::onLeftClickPressedOutside(sf::Vector2i const& pos)
{

}

void	GUIElement::onLeftClickReleasedOutside(sf::Vector2i const& pos)
{

}

void	GUIElement::onRightClickPressedOutside(sf::Vector2i const& pos)
{

}

void	GUIElement::onRightClickReleasedOutside(sf::Vector2i const& pos)
{

}

void	GUIElement::keyTextEntered(char const charEntered)
{

}

void	GUIElement::keyPressed(sf::Keyboard::Key const& keyPressed)
{

}


// Setters

void	GUIElement::setPos(sf::Vector2f const& pos)
{
	this->_pos = pos;
}

void	GUIElement::setSize(sf::Vector2f const& size)
{
	this->_size = size;
}

void	GUIElement::setVisible(bool const state)
{
	this->_isVisible = state;
}

// Getters

sf::Vector2f const &	GUIElement::getPos() const
{
	return (this->_pos);
}

sf::Vector2f const &	GUIElement::getSize() const
{
	return (this->_size);
}

std::string	const &		GUIElement::getIdentifier() const
{
	return (this->_identifier);
}

bool					GUIElement::isVisible() const
{
	return (this->_isVisible);
}