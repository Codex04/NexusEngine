#include "ConvexShape.hpp"

nx::graphics::ConvexShape::ConvexShape(sf::Vector2f const & pos, sf::Vector2f const & size, std::string const & identifier,
									   nx::ColorInfo const& colorInfo) :
	GraphicsElement(pos, sf::Vector2f(), identifier), _body(sf::ConvexShape())
{
	this->_body.setPosition(pos);
	this->_body.setFillColor(colorInfo.backgroundColor);
	this->_body.setOutlineThickness(static_cast<float>(colorInfo.borderThickness));
	this->_body.setOutlineColor(colorInfo.borderColor);
}

nx::graphics::ConvexShape::~ConvexShape()
{

}


// Display

void	nx::graphics::ConvexShape::show(std::shared_ptr<sf::RenderWindow> const & win)
{
	if (this->isVisible())
	{
		win->draw(this->_body);
	}
}


// Setters

void	nx::graphics::ConvexShape::setBackgroundColor(sf::Color const & color)
{
	this->_body.setFillColor(color);
}

void	nx::graphics::ConvexShape::setBorderColor(sf::Color const & color)
{
	this->_body.setOutlineColor(color);
}

void	nx::graphics::ConvexShape::setBorderThickness(int const thickness)
{
	this->_body.setOutlineThickness(static_cast<float>(thickness));
}

void	nx::graphics::ConvexShape::setRotation(float const angle)
{
	this->_body.setRotation(angle);
}

void	nx::graphics::ConvexShape::setPointCount(size_t const pointCount)
{
	sf::FloatRect bounds = this->_body.getLocalBounds();

	this->_body.setPointCount(pointCount);
	GraphicsElement::setSize(sf::Vector2f(bounds.width, bounds.height));
}

void	nx::graphics::ConvexShape::setPoint(size_t const index, sf::Vector2f const& point)
{
	sf::FloatRect bounds = this->_body.getLocalBounds();

	this->_body.setPoint(index, point);
	GraphicsElement::setSize(sf::Vector2f(bounds.width, bounds.height));
}

void	nx::graphics::ConvexShape::setScale(sf::Vector2f const& factor)
{
	this->_body.setScale(factor);
	GraphicsElement::setSize(sf::Vector2f(this->_body.getLocalBounds().width, this->_body.getLocalBounds().height));
}

void	nx::graphics::ConvexShape::setOrigin(sf::Vector2f const& origin)
{
	this->_body.setOrigin(origin);
}

void	nx::graphics::ConvexShape::move(sf::Vector2f const& offset)
{
	this->_body.move(offset);
}

void	nx::graphics::ConvexShape::rotate(float const angle)
{
	this->_body.rotate(angle);
}

void	nx::graphics::ConvexShape::scale(sf::Vector2f const& factor)
{
	this->_body.scale(factor);
	GraphicsElement::setSize(sf::Vector2f(this->_body.getLocalBounds().width, this->_body.getLocalBounds().height));
}

void	nx::graphics::ConvexShape::setTexture(std::string const& texturePath, bool const resetRect)
{
	if (!this->_texture.loadFromFile(texturePath))
		throw nx::InvalidImageException(texturePath);

	this->_body.setTexture(&this->_texture, resetRect);
}

void	nx::graphics::ConvexShape::setTextureRect(sf::IntRect const& rect)
{
	this->_body.setTextureRect(rect);
}

void	nx::graphics::ConvexShape::setPos(sf::Vector2f const& pos)
{
	float thickness = this->_body.getOutlineThickness();

	GraphicsElement::setPos(sf::Vector2f(pos.x - thickness, pos.y - thickness));
	this->_body.setPosition(pos);
}

void	nx::graphics::ConvexShape::setSize(sf::Vector2f const& size)
{
	//Can't modify the size
}


// Getters

std::string const	nx::graphics::ConvexShape::getType() const
{
	return ("ConvexShape");
}


// Specific getters

sf::Color const&	nx::graphics::ConvexShape::getBackgroundColor() const
{
	return (this->_body.getFillColor());
}

sf::Color const&	nx::graphics::ConvexShape::getBorderColor() const
{
	return (this->_body.getOutlineColor());
}

int const			nx::graphics::ConvexShape::getBorderThickness() const
{
	return (static_cast<int>(this->_body.getOutlineThickness()));
}

float const			nx::graphics::ConvexShape::getRotation() const
{
	return (this->_body.getRotation());
}

size_t const		nx::graphics::ConvexShape::getPointCount() const
{
	return (this->_body.getPointCount());
}

sf::Vector2f const	nx::graphics::ConvexShape::getPoint(size_t const index) const
{
	return (this->_body.getPoint(index));
}

sf::IntRect const &		nx::graphics::ConvexShape::getTextureRect() const
{
	return (this->_body.getTextureRect());
}

sf::Vector2f const &	nx::graphics::ConvexShape::getScale() const
{
	return (this->_body.getScale());
}

sf::Vector2f const &	nx::graphics::ConvexShape::getOrigin() const
{
	return (this->_body.getOrigin());
}