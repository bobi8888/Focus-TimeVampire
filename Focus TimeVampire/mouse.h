
sf::Vector2i mousePosition;
sf::Vector2f translatedMousePosition;
sf::Mouse mouse;

sf::Vector2f setMousePosition(sf::RenderWindow &window){
	mousePosition = sf::Mouse::getPosition(window);
	return window.mapPixelToCoords(mousePosition);
}
bool isSpriteClicked(sf::Vector2f translatedMousePosition, const sf::Sprite &sprite, sf::Event event) {
	
	if (sprite.getGlobalBounds().contains(translatedMousePosition)){
		if (event.type = sf::Event::MouseButtonPressed){
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
				return true;
			}
		}
	}else{
		return false;
	}
}