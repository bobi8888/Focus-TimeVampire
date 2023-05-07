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

GameText loadPrompt(string randomInt_String, sf::Text tempText, vector <vector <string>> ignorePrompts, GameText ignorePromptText, sf::RenderWindow& window) {	

	ignorePrompts[1][0].insert(0, randomInt_String + " ");

	tempText.setPosition(ignorePromptText.getText().getPosition());
	float postAppend = ignorePromptText.getText().getPosition().x;
	float preAppend = 0;
	float stringLength = postAppend;
	float displayLength = 0;

	for (int i = 0; i < ignorePrompts.size(); i++) {
		for (int j = 0; j < ignorePrompts[i].size(); j++) {
			preAppend = tempText.getGlobalBounds().width + tempText.getPosition().x;
			tempText.setString(tempText.getString() + ignorePrompts[i][j]);
			postAppend = tempText.getGlobalBounds().width + tempText.getPosition().x;
			stringLength = postAppend - preAppend;
			displayLength += stringLength;
			if (displayLength < (window.getSize().x - tempText.getPosition().x *1.3)) {
				ignorePromptText.appendTextString(ignorePrompts[i][j]);
			} else {
				ignorePromptText.appendTextString("\n" + ignorePrompts[i][j]);
				displayLength = stringLength;
			}
		}
	}
	return ignorePromptText;
}