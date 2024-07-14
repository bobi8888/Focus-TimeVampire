#pragma once
class MovementVector {
private:
	sf::Vector2f previousCoord;
	sf::Vector2f currentCoord;
	float direction;
	int quadrant;

public:
	float getDirection;
	void setQuadrant(sf::CircleShape circle);



};