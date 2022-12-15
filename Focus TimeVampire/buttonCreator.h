void centerGeometry(sf::Shape& shape, sf::Window& window) {
	shape.setOrigin(shape.getGlobalBounds().width / 2, shape.getGlobalBounds().height / 2);
	shape.setPosition(window.getSize().x / 2, window.getSize().y / 2);
}

sf::CircleShape createCirle(float radius,int points, sf::Window &window) {
	sf::CircleShape circle(radius);
	circle.setOrigin(circle.getRadius(),circle.getRadius());
	circle.setPointCount(points);
	circle.setPosition(window.getSize().x/2, window.getSize().y/2);

	return circle;
}
sf::RectangleShape createRectangle(float width, float height,int outline, int redB, int greenB, int blueB, int alphaB ,
	int redF, int greenF, int blueF, int alphaF, sf::Window &window) {
	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(width,height));
	rectangle.setOrigin(rectangle.getSize().x/2,rectangle.getSize().y/2);
	centerGeometry(rectangle,window);
	rectangle.setOutlineColor(sf::Color(redB,greenB,blueB,alphaB));
	rectangle.setFillColor(sf::Color(redF,greenF,blueF,alphaF));
	rectangle.setOutlineThickness(outline);
	return rectangle;
}
