#include "utils.h"
#include "gameText.h"

vector <float> DiscussText::getCharWidthsVector() {
	return charWidths;
}
void DiscussText::setCharWidthsVector(string newString) {
	float prev = 0, next = 0;
	text.setString(newString);
	for (int i = 1; i <= newString.size(); i++) {
		prev = text.getGlobalBounds().width;
		text.setString(newString.substr(i));
		next = text.getGlobalBounds().width;
		charWidths.push_back(prev - next);
	}
	text.setString(newString);
}
void DiscussText::clearCharWidthsVector(){
	charWidths.clear();
}
void DiscussText::drawTextBlockers(vector <sf::RectangleShape> textBlockersVector, sf::RenderWindow& window) {
	for (int i = 0; i < textBlockersVector.size(); i++) {
		if (charToShow == 0 && i != charToShow) {//only displays 1st char
			window.draw(textBlockersVector[i]);
		}
		else if (charToShow == 1 && i != charToShow && i != charToShow - 1) {//only display 1st 2 chars
			window.draw(textBlockersVector[i]);
		}
		else if (i != charToShow && i != charToShow - 1) {//middle
			window.draw(textBlockersVector[i]);
		}
		else if (charToShow == textBlockersVector.size() - 1 && i != charToShow && i != charToShow - 1) {//2nd to last
			window.draw(textBlockersVector[i]);
		}
		else if (charToShow == textBlockersVector.size() && i != charToShow - 1) {//last
			window.draw(textBlockersVector[i]);
		}
	}
}
void DiscussText::charToShowIncrementor(float discussTime, float timeRemaining, float discussSpeed, vector <sf::RectangleShape> textBlockersVector) {
	if (discussTime - timeRemaining > discussSpeed) {
		if (charToShow <= textBlockersVector.size()) {
			charToShow++;
		}
		else {
			charToShow = 0;
		}
	}
}
sf::Color DiscussText::handleColor(sf::Color& color, int redInc, int blueInc, int greenInc) {
	if (color.r > 255) color.r = 0;
	if (color.b > 255) color.b = 0;
	if (color.g > 255) color.g = 0;
	color.r += redInc;
	color.b += blueInc;
	color.g += greenInc;
	return color;
}
vector <sf::RectangleShape> DiscussText::setTextBlockers(vector <sf::RectangleShape> textBlockersVector){
	for (int i = 0; i < getTextString().size(); i++) {
		sf::RectangleShape textBlocker(sf::Vector2f(getCharWidthsVector()[i], getText().getCharacterSize() + 10));
		textBlocker.setOrigin(textBlocker.getSize().x / 2, textBlocker.getSize().y / 2);
		textBlocker.setPosition(sf::Vector2f(getText().findCharacterPos(i).x + textBlocker.getSize().x / 2
			, getText().findCharacterPos(i).y + textBlocker.getSize().y / 2));
		textBlocker.setFillColor(sf::Color::White);
		textBlocker.setOutlineColor(sf::Color::Cyan);
		textBlocker.setOutlineThickness(3);
		textBlockersVector.push_back(textBlocker);
	}
	return textBlockersVector;
}