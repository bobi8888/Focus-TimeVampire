#pragma once

class Circle {
private:
	sf::CircleShape circle; 
	sf::Texture texture;
	float movementSpeed = 0, rotationSpeed = 0;
	sf::Vector2f previousPosition;
	int spriteContactIndex = -1;

public:
	Circle(string newTexture, float movementSpeed, float rotationSpeed, float scale);
	sf::CircleShape getCircle();
	void setPosition(sf::Vector2f newPosition);
	void setMovementSpeed(float movement);
	int getSpriteContactIndex();
	void setSpriteContactIndex(int index);

	bool isAnyArrowKeyDown();
	void handlePlayerInput(sf::RenderWindow& window);

	bool hasVertexArrayCollision(sf::VertexArray vertexArray);
	bool hasSpriteCollision(sf::Sprite sprite);
	void handleScreenBoundsCollision(sf::RenderWindow& window);
	void handleVertexArrayCollision(sf::VertexArray vertexArray);

	sf::Vector2f handleRepulsion(const sf::Sprite& acceptSprite);
	void handlePlayerMovement(sf::RenderWindow& window, const sf::Sprite& acceptSprite);
};