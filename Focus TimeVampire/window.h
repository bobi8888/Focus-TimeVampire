#pragma once

int screenWidth = 500, screenHeight = 500;
sf::Vector2f center;
sf::ContextSettings antialiasing;
sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "FOCUS Time Vampire", sf::Style::Default, antialiasing);
sf::Vector2f getCenterOfWindow(sf::Window& window) {
	float x = window.getSize().x / 2;
	float y = window.getSize().y / 2;
	center = sf::Vector2f(x, y);
	return center;
}