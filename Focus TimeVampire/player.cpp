#include "utils.h"
#include "gameSprite.h"

Player::Player(string newTexture, float movement, float rotation, float scale) {
	texture.loadFromFile(newTexture);
	circle.setRadius(texture.getSize().x * scale / 2);
	circle.setTexture(&texture);
	circle.setOrigin(texture.getSize().x / 2 * scale, texture.getSize().y / 2 * scale);
	movementSpeed = movement;
	rotationSpeed = rotation;
}
sf::CircleShape Player::getCircle() {
	return circle;
}
void Player::setPosition(sf::Vector2f newPosition) {
	circle.setPosition(newPosition);
}
void Player::setMovementSpeed(float movement) {
	movementSpeed = movement;
}
int Player::getSpriteContactIndex() {
	return spriteContactIndex;
}
void Player::setSpriteContactIndex(int index){
	spriteContactIndex = index;
}

float Player::getPositiveCharge() {
	return charge;
}
float Player::getNegativeCharge() {
	return charge * -1;
}
void Player::setCharge(float newCharge) {
	charge = newCharge;
}

sf::Vector2f Player::getPreviousPosition() {
	return previousPosition;
}
float Player::getVelocity() {
	return velocity;
}
void Player::setVeloity(float newVelo) {
	velocity = newVelo;
}
void Player::calculateVelocity() {
	float elapsedMilli = clock.getElapsedTime().asMilliseconds();
	float distance = std::round(sqrt(pow(abs(abs(circle.getPosition().x) - abs(getPreviousPosition().x)), 2) + pow(abs(abs(circle.getPosition().y) - abs(getPreviousPosition().y)), 2))
		* 100.f) / 100.f;
	velocity = std::round((distance / elapsedMilli) * 100.f) / 100.f;
	clock.restart();
}
int Player::getQuadrant() {
	return quadrant;
}
void Player::setQuadrant(const sf::Sprite& acceptSprite) {
	if (circle.getPosition().x > acceptSprite.getPosition().x && circle.getPosition().y < acceptSprite.getPosition().y) {
		quadrant = 1;
	}
	else if (circle.getPosition().x < acceptSprite.getPosition().x && circle.getPosition().y < acceptSprite.getPosition().y) {
		quadrant = 2;
	}
	else if (circle.getPosition().x < acceptSprite.getPosition().x && circle.getPosition().y > acceptSprite.getPosition().y) {
		quadrant = 3;
	}
	else {
		quadrant = 4;
	}
}

float Player::returnCalculatedDirection(const sf::Sprite& acceptSprite){	
	calc_Dir_y = circle.getPosition().y < acceptSprite.getPosition().y ? acceptSprite.getPosition().y - circle.getPosition().y : circle.getPosition().y - acceptSprite.getPosition().y;
	calc_Dir_x = circle.getPosition().x < acceptSprite.getPosition().x ? acceptSprite.getPosition().x - circle.getPosition().x : circle.getPosition().x - acceptSprite.getPosition().x;
	
	setQuadrant(acceptSprite);
	direction = atan(calc_Dir_y / calc_Dir_x) * 180 / std::_Pi;
	return direction;
}


void Player::spriteForce(float angle, float magnitude) {
	float y = sin(angle * std::_Pi / 180) * magnitude;
	float x = sqrt(pow(magnitude, 2) - pow(y, 2));

	switch (quadrant) {
	case 1:
		circle.setPosition(sf::Vector2f(circle.getPosition().x + x, circle.getPosition().y - y));
		break;
	case 2:
		circle.setPosition(sf::Vector2f(circle.getPosition().x - x, circle.getPosition().y - y));
		break;
	case 3:
		circle.setPosition(sf::Vector2f(circle.getPosition().x - x, circle.getPosition().y + y));
		break;
	case 4:
		circle.setPosition(sf::Vector2f(circle.getPosition().x + x, circle.getPosition().y + y));
		break;
	}
}

bool Player::isAnyArrowKeyDown() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		return true;
	}
	else return false;
}
void Player::handlePlayerInput(sf::RenderWindow& window) {
	previousPosition = circle.getPosition();
	if (isAnyArrowKeyDown()) {
		//rotation
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) circle.setRotation(circle.getRotation() + rotationSpeed);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) circle.setRotation(circle.getRotation() - rotationSpeed);
		//movement
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) circle.setPosition(circle.getPosition().x - movementSpeed, circle.getPosition().y);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) circle.setPosition(circle.getPosition().x + movementSpeed, circle.getPosition().y);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) circle.setPosition(circle.getPosition().x, circle.getPosition().y - movementSpeed);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) circle.setPosition(circle.getPosition().x, circle.getPosition().y + movementSpeed);
	}
}

bool Player::hasVertexArrayCollision(sf::VertexArray vertexArray) {
	float closestX = (circle.getPosition().x < vertexArray.getBounds().left ? vertexArray.getBounds().left : (circle.getPosition().x
	> vertexArray.getBounds().left + vertexArray.getBounds().width ? vertexArray.getBounds().left + vertexArray.getBounds().width : circle.getPosition().x));

	float closestY = (circle.getPosition().y < vertexArray.getBounds().top ? vertexArray.getBounds().top : (circle.getPosition().y
	> vertexArray.getBounds().top + vertexArray.getBounds().height ? vertexArray.getBounds().top + vertexArray.getBounds().height : circle.getPosition().y));

	float dx = closestX - circle.getPosition().x;
	float dy = closestY - circle.getPosition().y;
	return (dx * dx + dy * dy) <= circle.getRadius() * circle.getRadius();
}
bool Player::hasSpriteCollision(sf::Sprite sprite) {
	float closestX = (circle.getPosition().x < sprite.getGlobalBounds().left ? sprite.getGlobalBounds().left : (circle.getPosition().x
	> sprite.getGlobalBounds().left + sprite.getGlobalBounds().width ? sprite.getGlobalBounds().left + sprite.getGlobalBounds().width : circle.getPosition().x));

	float closestY = (circle.getPosition().y < sprite.getGlobalBounds().top ? sprite.getGlobalBounds().top : (circle.getPosition().y
	> sprite.getGlobalBounds().top + sprite.getGlobalBounds().height ? sprite.getGlobalBounds().top + sprite.getGlobalBounds().height : circle.getPosition().y));

	float dx = closestX - circle.getPosition().x;
	float dy = closestY - circle.getPosition().y;
	return (dx * dx + dy * dy) <= circle.getRadius() * circle.getRadius();
}
void Player::handleScreenBoundsCollision(sf::RenderWindow& window) {
	if (circle.getPosition().x - circle.getRadius() < 0) circle.setPosition(circle.getRadius(), circle.getPosition().y);
	if (circle.getPosition().x + circle.getRadius() > window.getSize().x) circle.setPosition(window.getSize().x - circle.getRadius(), circle.getPosition().y);
	if (circle.getPosition().y - circle.getRadius() < 0) circle.setPosition(circle.getPosition().x, circle.getRadius());
	if (circle.getPosition().y + circle.getRadius() > window.getSize().y) circle.setPosition(circle.getPosition().x, window.getSize().y - circle.getRadius());
}
void Player::handleVertexArrayCollision(sf::VertexArray vertexArray) {
	if (hasVertexArrayCollision(vertexArray)) {
		circle.setPosition(previousPosition);
	}
}

sf::Vector2f Player::handleRepulsion(const sf::Sprite& acceptSprite) {
//need x&yforces
//A particle of charge q moving with a velocity v in an electric field E and a magnetic field B experiences a force(in SI units[1][2]) of
//F=q(E+v*B)
//F = Lorentz F in Newtons 
//float q = 0.1;//charge of particle in coulombs 
	float E = 1; //E = elec field in Volts/meter
	float v = getVelocity();//velo of charge particle in pxl/ms
	float B = 1;//mag field in teslas
	float xCharge = circle.getPosition().x < acceptSprite.getPosition().x ? getNegativeCharge() : getPositiveCharge();
	float yCharge = circle.getPosition().y < acceptSprite.getPosition().y ? getNegativeCharge() : getPositiveCharge();

	float force = charge * (E + v * B);
	sf::Vector2f forceVector(circle.getPosition().x + xCharge, circle.getPosition().y + yCharge);
	//sf::Vector2f forceVector(circle.getPosition().x + force, circle.getPosition().y + force);
	return forceVector;
}

void Player::setXForce(float newForce) {
	xForce = newForce;
}
void Player::setYForce(float newForce) {
	yForce = newForce;
}

sf::Vector2f Player::applyForces(DataSpriteVector test) {
//for (int i = 0; i < particles.length; ++i) { //For each particle
	for (int i = 0; i < test.getDataSpriteVector().size(); i++) { //For each second particle (no repeats)
			float dx = circle.getPosition().x - test.getDataSpriteVector()[i].getSprite().getPosition().x;
			float dy = circle.getPosition().y - test.getDataSpriteVector()[i].getSprite().getPosition().y;
			float distance = sqrt(dx * dx + dy * dy);
			float force = charge * charge / (distance * distance);
			if (force > 1000) force = 1000; //Make sure the simulation doesn't explode
			//Find the horizontal and vertical components of the force
			float newXForce = force * (dx / distance);
			float newYForce = force * (dy / distance);
			//Apply forces to particles
			xForce = newXForce;
			yForce = newYForce;
			sf::Vector2f forceVector(circle.getPosition().x + xForce, circle.getPosition().y + yForce);
			return forceVector;
		}
	//}
}

//vector<double> Player::calculateMagneticForce(Player magOne, Player magTwo) {
//	vector<double> force(2, 0.0);
//
//	// Calculate the distance and squared distance between dipoles
//	double dx =  magTwo.x - magOne.x;
//	double dy = magTwo.y - magOne.y;
//	double r_squared = dx * dx + dy * dy;
//
//	// Calculate the magnetic force components using the Biot-Savart law
//	double forceMagnitude = (mu0 * magOne.strength * magTwo.strength) / (4 * 3.14 * r_squared);
//	force[0] = forceMagnitude * dx / std::sqrt(r_squared);
//	force[1] = forceMagnitude * dy / std::sqrt(r_squared);
//
//	return force;
//}

//#include <iostream>
//#include <vector>
//#include <cmath>
//
//// Define constants
//const double mu0 = 4 * M_PI * 1e-7; // Permeability of free space
//
//// Structure to represent a magnetic dipole
//struct MagneticDipole {
//	double strength;
//	double x, y;
//};
//
//// Calculate the magnetic force between two dipoles
//std::vector<double> calculateMagneticForce(const MagneticDipole& dipole1, const MagneticDipole& dipole2) {
//	std::vector<double> force(2, 0.0);
//
//	// Calculate the distance and squared distance between dipoles
//	double dx = dipole2.x - dipole1.x;
//	double dy = dipole2.y - dipole1.y;
//	double r_squared = dx * dx + dy * dy;
//
//	// Calculate the magnetic force components using the Biot-Savart law
//	double forceMagnitude = (mu0 * dipole1.strength * dipole2.strength) / (4 * M_PI * r_squared);
//	force[0] = forceMagnitude * dx / std::sqrt(r_squared);
//	force[1] = forceMagnitude * dy / std::sqrt(r_squared);
//
//	return force;
//}
//
//int main() {
//	// Create magnetic dipoles
//	MagneticDipole dipole1 = { 1.0, 0.0, 0.0 };
//	MagneticDipole dipole2 = { 1.0, 1.0, 0.0 };
//	// Simulation parameters
//	double timeStep = 0.01;
//	double simulationTime = 1.0;
//	// Initial velocities
//	std::vector<double> velocity1 = { 0.0, 0.0 };
//	std::vector<double> velocity2 = { 0.5, 0.0 };
//
//
//
//	return 0;
//}
//// Define constants
//const double mu0 = 4 * M_PI * 1e-7; // Permeability of free space
//
//// Structure to represent a magnetic dipole
//struct MagneticDipole {
//	double strength;
//	double x, y, z;
//};
//
//// Structure to represent a physics object with position, velocity, and mass
//struct PhysicsObject {
//	double mass;
//	double x, y, z;
//	double vx, vy, vz;
//};
//
//// Calculate the magnetic field due to a magnetic dipole at a given point
//std::vector<double> calculateMagneticField(const std::vector<double>& r, const MagneticDipole& dipole) {
//	std::vector<double> B(3, 0.0); // Initialize the magnetic field components
//
//	// Calculate the vector from the dipole to the position
//	double dx = r[0] - dipole.x;
//	double dy = r[1] - dipole.y;
//	double dz = r[2] - dipole.z;
//
//	// Calculate the distance and cube of distance
//	double r_squared = dx * dx + dy * dy + dz * dz;
//	double r_cubed = r_squared * std::sqrt(r_squared);
//
//	// Calculate the magnetic field components using the Biot-Savart law
//	B[0] = (mu0 / (4 * M_PI)) * (3 * dx * (dx * dipole.strength + dy * 0 + dz * 0) / r_cubed - dipole.strength / r_cubed);
//	B[1] = (mu0 / (4 * M_PI)) * (3 * dy * (dx * 0 + dy * dipole.strength + dz * 0) / r_cubed - dipole.strength / r_cubed);
//	B[2] = (mu0 / (4 * M_PI)) * (3 * dz * (dx * 0 + dy * 0 + dz * dipole.strength) / r_cubed - dipole.strength / r_cubed);
//
//	return B;
//}
//
//int main() {
//	// Create magnetic dipoles
//	MagneticDipole dipole1 = { 1.0, 0.0, 0.0, 0.0 };
//	MagneticDipole dipole2 = { 1.0, 1.0, 0.0, 0.0 };
//
//	// Create physics objects
//	PhysicsObject object1 = { 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0 };
//	PhysicsObject object2 = { 1.0, 1.5, 0.0, 0.0, -0.5, 0.0, 0.0 };
//
//	// Simulation parameters
//	double timeStep = 0.01;
//	double simulationTime = 1.0;
//
//	for (double t = 0.0; t < simulationTime; t += timeStep) {
//		// Calculate magnetic forces and update object velocities
//		// ...
//
//		// Integrate object positions using Euler's method
//		object1.x += object1.vx * timeStep;
//		object1.y += object1.vy * timeStep;
//		object1.z += object1.vz * timeStep;
//
//		object2.x += object2.vx * timeStep;
//		object2.y += object2.vy * timeStep;
//		object2.z += object2.vz * timeStep;
//
//		// Collision detection and handling
//		// ...
//
//		// Output object positions at each time step
//		std::cout << "Time: " << t << "\n";
//		std::cout << "Object 1: (" << object1.x << ", " << object1.y << ", " << object1.z << ")\n";
//		std::cout << "Object 2: (" << object2.x << ", " << object2.y << ", " << object2.z << ")\n\n";
//	}//
//	return 0;
//}
//function updateparticles() {
//	for (var i = 0; i < particles.length; ++i) {
//		//Update particle velocities
//		particles[i].xspeed += particles[i].xforce / particles[i].mass;
//		particles[i].yspeed += particles[i].yforce / particles[i].mass;
//		//Update particle positions
//		particles[i].x += particles[i].xspeed;
//		particles[i].y += particles[i].yspeed;
//	}
//}
//A particle of charge q moving with a velocity v in an electric field E and a magnetic field B experiences a force(in SI units[1][2]) of
// velo is distance/time, or pixels/ms?
//F=q(E+v*B)
//F = Lorentz F in Newtons 
//q = charge of particle in coulombs
//E = elec field in V/m
//v = velo of charge particle in m/s
//B = mag field in teslas
void Player::handlePlayerMovement(sf::RenderWindow& window, DataSpriteVector test, sf::Sprite acceptSprite) {
	handleScreenBoundsCollision(window);
	calculateVelocity();
	handlePlayerInput(window);
	//setPosition(handleRepulsion(acceptSprite));
	//setPosition(applyForces(test));
}

//bool PlayerSprite::hasCircleContactWithSprite(const sf::Sprite& sprite, int boundry) {
//	float a, b, c, minDist;
//
//	minDist = getRadius() + boundry + sprite.getGlobalBounds().height / 2;
//	a = getSprite().getPosition().y - sprite.getPosition().y;
//	if (a < 0) { a = a * -1; }
//	b = getSprite().getPosition().x - sprite.getPosition().x;
//	if (b < 0) { b = b * -1; }
//	c = sqrt(a * a + b * b);
//	if (c < minDist) {
//		return hasContact = true;
//	}
//	else {
//		return hasContact = false;
//	}
//}