#pragma once
#include "window.h"

int ignorePromptTimer = 10;
int ignoreScreen = 1;
float beepCountdown = 0;
float beepVolume = 40;
float dullBedVolume = 20;
float convoVolume = 85;
vector <vector <string>> ignorePrompts{ { "A ", "sedan ", "stops ", "next ", "to ", "a ", "motorcyle. "}, {"bicycles ", "approach ", "from ", "the ", "north. "}
	,{"A ", "football ", "player ", "on ", "a ", "unicycle ", "just ", "left. "}};

GameText loadPrompt(sf::Text tempText, vector <vector <string>> ignorePrompts, GameText ignorePromptText, sf::RenderWindow& window) {	
	std::string bikes = std::to_string(randomInt(2,15));
	ignorePrompts[1][0].insert(0, bikes + " ");
	tempText.setPosition(ignorePromptText.getText().getPosition());
	float postAppend = ignorePromptText.getText().getPosition().x;
	float preAppend = 0;
	float stringLength = postAppend;
	float displayLength = 0;

	for (int i = 0; i < ignorePrompts.size(); i++) {
		for (int j = 0; j < ignorePrompts[i].size(); j++) {
			preAppend = tempText.getGlobalBounds().width + tempText.getPosition().x;
			//std::cout << "preAppend is " << preAppend << "\n";
			tempText.setString(tempText.getString() + ignorePrompts[i][j]);
			postAppend = tempText.getGlobalBounds().width + tempText.getPosition().x;
			//std::cout << "postAppend is " << postAppend << "\n";
			stringLength = postAppend - preAppend;
			//std::cout << "stringLength is " << stringLength << "\n";
			displayLength += stringLength;
			//std::cout << "tempText string is: " << tempText.getString().toAnsiString() << "\n";
			if (displayLength < (window.getSize().x - tempText.getPosition().x *1.3)) {
				ignorePromptText.appendTextString(ignorePrompts[i][j]);
				//std::cout << "ignorePromptText is: " << ignorePromptText.getTextString() << "\n \n";
			} else {
				ignorePromptText.appendTextString("\n" + ignorePrompts[i][j]);
				displayLength = stringLength;
			}
		}
	}
	return ignorePromptText;
}