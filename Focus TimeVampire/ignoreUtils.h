#pragma once
#include "window.h"

int ignoreScreen = 1;
int currentQuestion = 0;
int currentPrompt = 0;
int currentKey = 0;

float beepCountdown = 0;
float beepVolume = 40;
float dullBedVolume = 20;
float convoVolume = 85;

string question_2_color = "pink ";

vector <vector <vector <string>>> ignorePromptVectors{ { { "A ", "sedan ", "stops ", "next ", "to ", "a ", "motorcyle. "}, {"bicycles ", "approach ", "from ", "the ", "north. "}
	,{"A ", "football ", "player ", "on ", "a ", "unicycle ", "just ", "left. "}}, 

	{{"In ", "a ", "pile ", "of ", "Legos ", "you ", "see ", "4 ", "black ", "plates, ", "5 ", "dark ", "green " , "tiles, ", "8 ", "light ", "blue ", "bricks, ",
	"7 ", "tan  ", "plates, ", "1 ", "dark ", "blue ", "tiles, ", "and ", "11 ", "black ", "bricks."}},

	{{"Please ", "add ", "2 ", "values ", "of ", "-2 ", "to ", "2 ", "X ", "12 ", "then ", "divide ", "by ", "5."}}
};

vector <string> ignoreQuestions = { "How many wheels were there?", "How many bricks where there?", "What is your answer?"};
vector <string> ignoreKeys = { "", "19", "4"};

GameText loadPrompt(string randomInt_String, sf::Text tempText, vector <vector <string>> ignorePrompt, GameText ignorePromptText, sf::RenderWindow& window) {	
	if (ignorePrompt.size() > 1)
	ignorePrompt[1][0].insert(0, randomInt_String + " ");

	tempText.setPosition(ignorePromptText.getText().getPosition());
	float postAppend = ignorePromptText.getText().getPosition().x;
	float preAppend = 0;
	float stringLength = postAppend;
	float displayLength = 0;

	for (int i = 0; i < ignorePrompt.size(); i++) {
		for (int j = 0; j < ignorePrompt[i].size(); j++) {
			preAppend = tempText.getGlobalBounds().width + tempText.getPosition().x;
			tempText.setString(tempText.getString() + ignorePrompt[i][j]);
			postAppend = tempText.getGlobalBounds().width + tempText.getPosition().x;
			stringLength = postAppend - preAppend;
			displayLength += stringLength;
			if (displayLength < (window.getSize().x - tempText.getPosition().x *1.3)) {
				ignorePromptText.appendTextString(ignorePrompt[i][j]);
			} else {
				ignorePromptText.appendTextString("\n" + ignorePrompt[i][j]);
				displayLength = stringLength;
			}
		}
	}
	return ignorePromptText;
}