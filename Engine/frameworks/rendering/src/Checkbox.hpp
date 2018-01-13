#ifndef CHECKBOX_HPP_
# define CHECKBOX_HPP_

# include <string>
# include "GUIElement.hpp"
# include "Nexus/log.hpp"
# include "ColorInfo.hpp"

class Checkbox : public GUIElement
{
	enum State : int
	{
		UNCHECKED = 0,
		PARTIAL = 1,
		CHECKED
	};

	State							_state;
	sf::Color						_backgroundColor;
	sf::Color						_borderColor;
	int								_borderThickness;
	sf::RectangleShape				_body;
	std::vector<sf::VertexArray>	_lines;

public:
	Checkbox(sf::Vector2f const& pos, sf::Vector2f const& size, std::string const& identifier, nx::rendering::MouseEventsContainer const& events, ColorInfo const& colorInfo);
	~Checkbox();

	// GUIElement's mouse event methods overload
	virtual void onLeftClickPressedInside(sf::Vector2i const& pos);

	// Display
	void		show(std::shared_ptr<sf::RenderWindow> const& win);

	// Setters
	void		setState(State const state);
	void		setBackgroundColor(sf::Color const& color);
	void		setBorderColor(sf::Color const& color);
	void		setBorderThickness(int const thickness);

	void		setPos(sf::Vector2f const& pos);
	void		setSize(sf::Vector2f const& size);

	// Getters
	virtual std::string const	getType() const;

	// Specific getters
	State const			getState() const;
	sf::Color const	&	getBackgroundColor() const;
	sf::Color const	&	getBorderColor() const;
	int const			getBorderThickness() const;
};

#endif /* CHECKBOX_HPP_ */