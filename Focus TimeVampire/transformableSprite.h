class TransformableSprite : public GameSprite {
private:
	float movementSpeed;
	float radius;
public:
	using GameSprite::GameSprite;
	float getMovementSpeed();
	void setMovementSpeed(float speed);
	float getRadius();
	void setRadius(float newRadius);
	sf::Sprite setMovement();
	bool hasCircleContact(const sf::Sprite &sprite);
};

float TransformableSprite::getMovementSpeed() {
	return movementSpeed;
}
void TransformableSprite::setMovementSpeed(float speed) {
	movementSpeed = speed;
}
float TransformableSprite::getRadius() {
	return radius;
}
void TransformableSprite::setRadius(float newRadius) {
	radius = newRadius;
}
sf::Sprite TransformableSprite::setMovement() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {

		setRotation(getSprite().getRotation() - getMovementSpeed());

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			setPosition(sf::Vector2f(getSprite().getPosition().x - getMovementSpeed(), getSprite().getPosition().y));
			if (getSprite().getPosition().x - getRadius() < 0) {
				setSpritePosition(sf::Vector2f(getRadius(), getSprite().getPosition().y));
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			setPosition(sf::Vector2f(getSprite().getPosition().x + getMovementSpeed(), getSprite().getPosition().y));
			if (getSprite().getPosition().x + getRadius() > window.getSize().x) {
				setSpritePosition(sf::Vector2f(window.getSize().x - getRadius(), getSprite().getPosition().y));
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			setPosition(sf::Vector2f(getSprite().getPosition().x, getSprite().getPosition().y - getMovementSpeed()));
			if (getSprite().getPosition().y - getRadius() < 0) {
				setSpritePosition(sf::Vector2f(getSprite().getPosition().x, getRadius()));
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			setPosition(sf::Vector2f(getSprite().getPosition().x, getSprite().getPosition().y + getMovementSpeed()));
			if (getSprite().getPosition().y + getRadius() > window.getSize().y) {
				setSpritePosition(sf::Vector2f(getSprite().getPosition().x, window.getSize().y - getRadius()));
			}
		}
		return getSprite();
	}
}
bool TransformableSprite::hasCircleContact(const sf::Sprite& sprite) {
	float a, b, c, minDist;

	minDist = getRadius() + sprite.getGlobalBounds().height / 2;
	a = getSprite().getPosition().y - sprite.getPosition().y;
	if (a < 0) { a = a * -1; }
	b = getSprite().getPosition().x - sprite.getPosition().x;
	if (b < 0) { b = b * -1; }
	c = sqrt(a * a + b * b);
	if (c < minDist) {
		return true;
	}
	else {
		return false;
	}
}

