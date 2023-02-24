int mouseContactIndex = -1;
sf::Vector2i mousePosition;
sf::Vector2f translatedMousePosition;
sf::Mouse mouse;

sf::Vector2f setMousePosition(sf::RenderWindow &window){
	mousePosition = sf::Mouse::getPosition(window);
	return window.mapPixelToCoords(mousePosition);
}