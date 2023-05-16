#include "gameSprite.h"

int mouseContactIndex = -1;
bool validMouseClick = false;
sf::Vector2i mousePosition;
sf::Vector2f translatedMousePosition;
sf::Mouse mouse;

sf::Vector2f setMousePosition(sf::RenderWindow &window){
	mousePosition = sf::Mouse::getPosition(window);
	return window.mapPixelToCoords(mousePosition);
}

bool validSpriteClick(sf::Event event, sf::FloatRect globalBounds, sf::Vector2f translatedMousePosition) {
	if (event.type == sf::Event::EventType::MouseButtonPressed) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && globalBounds.contains(translatedMousePosition)) {
			return true;
		}
	}
	return false;
}