#ifndef GUIHANDLER_HPP_
# define GUIHANDLER_HPP_
    
# include <vector>
# include <memory>
# include "GUILayer.hpp"

# include "Button.hpp"
# include "Checkbox.hpp"
# include "ProgressBar.hpp"
# include "ComboBox.hpp"
# include "TextInput.hpp"
# include "Text.hpp"
//# include "Sprite.hpp"

# include "LayerNotFoundException.hpp"
    
class GUIHandler
{
    std::vector<std::shared_ptr<GUILayer>>	_guiLayers;
	std::shared_ptr<sf::RenderWindow>		_win;

public:
	GUIHandler(std::shared_ptr<sf::RenderWindow> const& win);
	~GUIHandler();

	void	addLayer(std::shared_ptr<GUILayer> elem);

	// Events
	void	processEvent(sf::Event const& event);

	// Display
	void	drawLayers();

	// Getters
	std::vector<std::shared_ptr<GUILayer>> const &	getLayers() const;
	std::vector<std::shared_ptr<GUILayer>>&			getLayers();
	std::shared_ptr<GUILayer> const &				getLayerByName(std::string const& identifier) const;
	std::shared_ptr<GUILayer>&						getLayerByName(std::string const& identifier);
	const bool 										layer_exists(const std::string&) const;
};

#endif /* GUIHANDLER_HPP_ */