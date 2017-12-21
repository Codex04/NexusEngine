#ifndef GUIELEMENT_HPP_
# define GUIELEMENT_HPP_

# include <SFML/Graphics.hpp>
# include <memory>

class GUIElement
{
	sf::Vector2f							_pos;
	sf::Vector2f							_size;
	std::string								_identifier;
	bool									_isVisible;

public:
	GUIElement(sf::Vector2f pos, sf::Vector2f size, std::string const& identifier);
	~GUIElement();

	// Mouse events
	virtual void onEnter();
	virtual void onLeave();
	virtual void onClick();

	// Display
	virtual void show(std::shared_ptr<sf::RenderWindow> const& win) = 0;

	// Setters
	void						setVisible(bool const state);

	// Getters
	sf::Vector2f const &										getPos() const;
	sf::Vector2f const &										getSize() const;
	std::string	const &											getIdentifier() const;
	bool														isVisible() const;
	virtual std::string	const									getType() const = 0;
};

#endif /* GUIELEMENT_HPP_ */