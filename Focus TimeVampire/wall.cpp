#include "utils.h"
#include "wall.h"

Wall::Wall(float centerX, float centerY, float len, float hi, float ang) {
	centerPosition = sf::Vector2f(centerX, centerY);
	length = len;
	height = hi;
	scaleFactor = height / 2 / length;
	angle = ang;
	radians = angle * 0.01745329252;
	oppo = sin(radians) * length;
	adj = cos(radians) * length;
	bisectOrigin = sf::Vector2f(centerX - (length / 2), centerY);
	bisectEnd = sf::Vector2f(bisectOrigin.x + adj, centerY - oppo);
	

	zeroPosition = sf::Vector2f(centerX - length / 2, centerY + height / 2);
	firstPosition = sf::Vector2f(centerX - length / 2, centerY - height / 2);
	secondPosition = sf::Vector2f(centerX + length / 2, centerY - height / 2);
	thirdPosition = sf::Vector2f(centerX + length / 2, centerY + height / 2);

	//zeroPosition = sf::Vector2f(bisectOrigin.x - sin(radians) * height / 2, bisectOrigin.y - cos(radians) * height / 2);
	//firstPosition = sf::Vector2f(bisectEnd.x - oppo * scaleFactor, bisectEnd.y - adj * scaleFactor);
	//secondPosition = sf::Vector2f(bisectEnd.x + oppo * scaleFactor, bisectEnd.y + adj * scaleFactor);
	//thirdPosition = sf::Vector2f(bisectOrigin.x + sin(radians) * height / 2, bisectOrigin.y + cos(radians) * height / 2);

	sf::VertexArray newVertexArray(sf::Quads, 5);
	newVertexArray[0].position = zeroPosition;
	newVertexArray[1].position = firstPosition;
	newVertexArray[2].position = secondPosition;
	newVertexArray[3].position = thirdPosition;
	newVertexArray[4].position = zeroPosition;
	
	newVertexArray[0].color = sf::Color::Green;
	newVertexArray[1].color = sf::Color::Magenta;
	newVertexArray[2].color = sf::Color::Cyan;
	newVertexArray[3].color = sf::Color::Blue;

	vertexArray = newVertexArray;

	//zeroPosition = sf::Vector2f(newVertexArray[3].position.x, newVertexArray[2].position.y);
	collisionX1 = newVertexArray[3].position.x;//LEFT
	collisionY1 = newVertexArray[2].position.y;//TOP


	//firstPosition = sf::Vector2f(newVertexArray[1].position.x, newVertexArray[2].position.y);
	//secondPosition = sf::Vector2f(newVertexArray[1].position.x, newVertexArray[0].position.y);
	collisionX2 = newVertexArray[1].position.x;//RIGHT
	collisionY2 = newVertexArray[0].position.y;//BOTTOM

	//thirdPosition = sf::Vector2f(newVertexArray[3].position.x, newVertexArray[0].position.y);
	//zeroPosition = sf::Vector2f(newVertexArray[3].position.x, newVertexArray[2].position.y);

	//sf::VertexArray newCollisionArray(sf::Quads, 5);
	//newCollisionArray[0].position = zeroPosition;
	//newCollisionArray[1].position = firstPosition;
	//newCollisionArray[2].position = secondPosition;
	//newCollisionArray[3].position = thirdPosition;
	//newCollisionArray[4].position = zeroPosition;
	//collisionArray = newCollisionArray;
	rotation.rotate(ang, centerX, centerY);
	transform = rotation;	

}

sf::VertexArray Wall::getVertexArray() {
	return vertexArray;
}

sf::Vector2f Wall::getCollisionArrayCorners(int corner) {
	return collisionArray[corner].position;
}

sf::Vector2f Wall::getBisectOrigin() {
	return bisectOrigin;
}
sf::Vector2f Wall::getBisectEnd() {
	return bisectEnd;
}
sf::Vector2f Wall::getCorners(int position) {
	return vertexArray[position].position;
}
sf::Transform Wall::getTransform() {
	return transform;
}
float Wall::getAngle() {
	return angle;
}
float Wall::getHeight() {
	return height;
}

void Wall::setFourCorners(sf::Vector2f zero, sf::Vector2f one, sf::Vector2f two, sf::Vector2f three) {
	zeroPosition = zero;
	firstPosition = one;
	secondPosition = two;
	thirdPosition = three;
	forthPosition = zero;

	vertexArray[0].position = zero;
	vertexArray[1].position = one;
	vertexArray[2].position = two;
	vertexArray[3].position = three;
	vertexArray[4].position = zero;
}

float Wall::getCollisionX1() {
	return collisionX1;
}float Wall::getCollisionX2() {
	return collisionX2;
}float Wall::getCollisionY1() {
	return collisionY1;
}float Wall::getCollisionY2() {
	return collisionY2;
}