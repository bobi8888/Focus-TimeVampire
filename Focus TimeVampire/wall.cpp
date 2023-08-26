#include "utils.h"
#include "wall.h"

Wall::Wall(float centerX, float centerY, bool isHorizontal, float thick, float len) {
	centerPosition = sf::Vector2f(centerX, centerY);
	horiztonal = isHorizontal;
	thickness = thick;
	length = len;

	sf::VertexArray newVertexArray(sf::Quads, 5);
	if (!isHorizontal) { 
		newVertexArray[0].position = sf::Vector2f(centerX - thick/2, centerY - length/2);
		newVertexArray[1].position = sf::Vector2f(centerX + thick/2, centerY - length/2);
		newVertexArray[2].position = sf::Vector2f(centerX + thick/2, centerY + length/2);
		newVertexArray[3].position = sf::Vector2f(centerX - thick/2, centerY + length/2);
		newVertexArray[4].position = sf::Vector2f(centerX - thick / 2, centerY - length / 2);

	}
	else {
		newVertexArray[0].position = sf::Vector2f(centerX - length / 2, centerY - thick / 2);
		newVertexArray[1].position = sf::Vector2f(centerX + length / 2, centerY - thick / 2);
		newVertexArray[2].position = sf::Vector2f(centerX + length / 2, centerY + thick / 2);
		newVertexArray[3].position = sf::Vector2f(centerX - length / 2, centerY + thick / 2);
		newVertexArray[4].position = sf::Vector2f(centerX - length / 2, centerY - thick / 2);
	}

	newVertexArray[0].color = sf::Color::Green;
	newVertexArray[1].color = sf::Color::Magenta;
	newVertexArray[2].color = sf::Color::Cyan;
	newVertexArray[3].color = sf::Color::Blue;

	vertexArray = newVertexArray;
}

sf::VertexArray Wall::getVertexArray() {
	return vertexArray;
}