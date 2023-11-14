#pragma once

class Wall{
private:
	sf::Vector2f centerPosition;
	//bool horiztonal;
	float length = 0, height = 0;
	float angle = 0, radians = 0, oppo = 0, adj = 0, scaleFactor = 0;
	sf::Vector2f bisectOrigin;
	sf::Vector2f bisectEnd;

	sf::VertexArray vertexArray;
	sf::VertexArray collisionArray;
	float collisionX1 = 0, collisionX2 = 0, collisionY1 = 0, collisionY2 = 0;

	sf::Vector2f zeroPosition;
	sf::Vector2f firstPosition;
	sf::Vector2f secondPosition;
	sf::Vector2f thirdPosition;
	sf::Vector2f forthPosition;
	sf::Transform rotation;
	sf::Transform transform;

public:
	Wall(float centerX, float centerY, float len, float hi, float ang);
	sf::VertexArray getVertexArray();
	sf::Vector2f getCollisionArrayCorners(int corner);
	sf::Vector2f getBisectOrigin();
	sf::Vector2f getBisectEnd();
	sf::Vector2f getCorners(int position);
	sf::Transform getTransform();
	float getAngle();
	float getHeight();
	void setFourCorners(sf::Vector2f zero, sf::Vector2f one, sf::Vector2f two, sf::Vector2f three);
	float getCollisionX1();
	float getCollisionX2();
	float getCollisionY1();
	float getCollisionY2();
};