#ifndef TEXT_HPP_
# define TEXT_HPP_

# include <string>
# include "Nexus/log.hpp"
# include "GUIElement.hpp"
# include "TextInfo.hpp"
# include "InvalidFontException.hpp"

class Text : public GUIElement
{
	sf::Font			_font;
	sf::Text			_label;

public:
	Text(sf::Vector2f const& pos, std::string const& identifier, TextInfo const& textInfo);
	~Text();

	// GUIElement's mouse event methods overload
	virtual void onMoveInside(sf::Vector2i const& pos);
	virtual void onMoveOutside(sf::Vector2i const& pos);
	virtual void onLeftClickPressedInside(sf::Vector2i const& pos);
	virtual void onLeftClickReleasedInside(sf::Vector2i const& pos);
	virtual void onRightClickPressedInside(sf::Vector2i const& pos);
	virtual void onRightClickReleasedInside(sf::Vector2i const& pos);
	virtual void onLeftClickPressedOutside(sf::Vector2i const& pos);
	virtual void onLeftClickReleasedOutside(sf::Vector2i const& pos);
	virtual void onRightClickPressedOutside(sf::Vector2i const& pos);
	virtual void onRightClickReleasedOutside(sf::Vector2i const& pos);
	virtual void keyTextEntered(char const charEntered);
	virtual void keyPressed(sf::Keyboard::Key const& keyPressed);

	// Display
	void		show(std::shared_ptr<sf::RenderWindow> const& win);

	// Setters
	void setLabel(sf::Text const& label);
	void setText(std::string const& text);
	void setFontSize(unsigned int const fontSize);

	void setPos(sf::Vector2f const& pos);
	void setSize(sf::Vector2f const& size);

	// Getters
	virtual std::string const		getType() const;

	// Specific getters
	sf::Text const &	getLabel() const;
	std::string const	getText() const;
	unsigned int const	getFontSize() const;
};

#endif /* TEXT_HPP_ */