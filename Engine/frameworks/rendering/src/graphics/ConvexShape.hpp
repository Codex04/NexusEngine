#ifndef NX_GRAPHICS_CONVEXSHAPE_HPP_
# define NX_GRAPHICS_CONVEXSHAPE_HPP_

# include <string>
# include <numeric>
# include "Nexus/log.hpp"
# include "GraphicsElement.hpp"
# include "../ColorInfo.hpp"
# include "../InvalidImageException.hpp"

namespace nx
{
	namespace graphics
	{
		class ConvexShape : public GraphicsElement
		{
			sf::ConvexShape	_body;
			sf::Texture		_texture;

		public:
			ConvexShape(sf::Vector2f const & pos, sf::Vector2f const & size, std::string const & identifier,
						nx::rendering::MouseEventsContainer const & events, nx::ColorInfo const& colorInfo);
			~ConvexShape();

			// Display
			void	show(std::shared_ptr<sf::RenderWindow> const& win);

			// Setters
			void	setBackgroundColor(sf::Color const& color);
			void	setBorderColor(sf::Color const& color);
			void	setBorderThickness(int const thickness);
			void	setRotation(float const angle);
			void	setPointCount(size_t const pointCount);
			void	setPoint(size_t const index, sf::Vector2f const& point);
			void	setScale(sf::Vector2f const& factor);
			void	setOrigin(sf::Vector2f const& origin);
			void	move(sf::Vector2f const& offset);
			void	rotate(float const angle);
			void	scale(sf::Vector2f const& factor);
			void	setTexture(std::string const& texturePath, bool const resetRect = false);
			void	setTextureRect(sf::IntRect const& rect);

			void	setPos(sf::Vector2f const& pos);
			void	setSize(sf::Vector2f const& size);

			// Getters
			virtual std::string const	getType() const;

			// Specific getters
			sf::Color const&	getBackgroundColor() const;
			sf::Color const&	getBorderColor() const;
			int const			getBorderThickness() const;
			float const			getRotation() const;
			size_t const		getPointCount() const;
			sf::Vector2f const	getPoint(size_t const index) const;
			sf::IntRect const &		getTextureRect() const;
			sf::Vector2f const &	getScale() const;
			sf::Vector2f const &	getOrigin() const;
		};
	}
}

#endif /* NX_GRAPHICS_CONVEXSHAPE_HPP_ */