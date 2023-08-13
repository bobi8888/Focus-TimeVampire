#pragma once

class Circle {
private:
	sf::CircleShape circle; 
	sf::Texture texture;
	float movementSpeed = 0, rotationSpeed = 0;
	sf::Vector2f previousPosition;
public:
	Circle(string newTexture, float movementSpeed, float rotationSpeed, float xScale, float yScale);
	sf::CircleShape getCircle();
	void setPosition(sf::Vector2f newPosition);
	void handlePlayerInput(sf::RenderWindow& window);
	void handlePlayerCollision(sf::VertexArray vertexArray);
	bool hasVertexArrayCollision(sf::VertexArray vertexArray);
	//void load_and_setTexture(string texture);
	//void setOrigin();
	//void setRadius();
};