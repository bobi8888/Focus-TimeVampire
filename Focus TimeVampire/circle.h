#pragma once

//A particle of charge q moving with a velocity v in an electric field E and a magnetic field B experiences a force(in SI units[1][2]) of
// velo is distance/time, or pixels/ms?
//F=q(E+v*B)
//F = Lorentz F in Newtons 
//q = charge of particle in coulombs
//E = elec field in V/m
//v = velo of charge particle in m/s
//B = mag field in teslas

class Circle {
private:
	sf::CircleShape circle; 
	sf::Texture texture;
	sf::Clock clock;
	float movementSpeed = 0, rotationSpeed = 0;
	sf::Vector2f previousPosition;
	int spriteContactIndex = -1;
	float charge = 2;
	float velocity = 0;

	float E_electFieldStr = 2; 
	float B_magFieldStr = 2; 
	float theta_magFieldAngle = 90;
public:
	Circle(string newTexture, float movementSpeed, float rotationSpeed, float scale);
	sf::CircleShape getCircle();
	void setPosition(sf::Vector2f newPosition);
	void setMovementSpeed(float movement);
	int getSpriteContactIndex();
	void setSpriteContactIndex(int index);
	float getPositiveCharge();
	float getNegativeCharge();
	void setCharge(float);
	sf::Vector2f getPreviousPosition();
	float getVelocity();
	void setVeloity(float);
	void calculateVelocity();

	bool isAnyArrowKeyDown();
	void handlePlayerInput(sf::RenderWindow& window);

	bool hasVertexArrayCollision(sf::VertexArray vertexArray);
	bool hasSpriteCollision(sf::Sprite sprite);
	void handleScreenBoundsCollision(sf::RenderWindow& window);
	void handleVertexArrayCollision(sf::VertexArray vertexArray);

	sf::Vector2f handleRepulsion(const sf::Sprite& acceptSprite);
	void handlePlayerMovement(sf::RenderWindow& window, const sf::Sprite& acceptSprite);
};