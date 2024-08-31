#pragma once

const int screenWidth = 500, screenHeight = 500;
sf::ContextSettings antialiasing;
sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "FOCUS Time Vampire", sf::Style::Default, antialiasing);
sf::Vector2f centerOfScreen(window.getSize().x / 2, window.getSize().y / 2);