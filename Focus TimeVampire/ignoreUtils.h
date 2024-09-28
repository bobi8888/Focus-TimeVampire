#pragma once
//#include "window.h"
//#include "utils.h"

static int ignoreScreen;
static int currentQuestion = 0;
static int currentPrompt = 0;
static int currentKey = 0;

static float beepCountdown = 0;
static float beepVolume = 40;
static float dullBedVolume = 20;
static float convoVolume = 85;

string question_2_color = "pink ";

struct testStruct {
	vector <vector <string>> ignoreP1{ { "A ", "sedan ", "stops ", "next ", "to ", "a ", "motorcyle. "}, {"bicycles ", "approach ", "from ", "the ", "north. "}
	,{"A ", "football ", "player ", "on ", "a ", "unicycle ", "just ", "left. "} };
	vector <vector <string>> ignoreP2{ {"In ", "a ", "pile ", "of ", "Legos ", "you ", "see ", "4 ", "black ", "plates, ", "5 ", "dark ", "green " , "tiles, ", "8 ", "light ", "blue ", "bricks, ", "7 ", "tan  ", "plates, ", "1 ", "dark ", "blue ", "tiles, ", "and ", "11 ", "black ", "bricks."} };
	vector <vector <string>> ignoreP3{ {"Please ", "add ", "2 ", "values ", "of ", "-2 ", "to ", "2 ", "X ", "12 ", "then ", "divide ", "by ", "5."} };

	vector <vector <vector <string>>> ignorePromptVectors{ ignoreP1, ignoreP2, ignoreP3 };
};

vector <string> ignoreQuestions = { "How many wheels were there?", "How many bricks where there?", "What is your answer?"};
vector <string> ignoreKeys = { "", "19", "4"};

//GameText* loadPrompts(vector <vector <string>> ignorePrompt, GameText* ignorePromptTextPtr, sf::RenderWindow& window, const std::optional<std::string>& randomInt_String = std::nullopt) {
//	//i believe this is used for adding a random int to a prompt
//	// this is very hard coded and inflexible...
//	if (ignorePrompt.size() > 1)
//	ignorePrompt[1][0].insert(0, *randomInt_String + " ");
//	sf::Text tempText;
//	tempText.setPosition(ignorePromptTextPtr->getText().getPosition());
//	float postAppend = ignorePromptTextPtr->getText().getPosition().x;
//	float preAppend = 0;
//	float stringLength = postAppend;
//	float displayLength = 0;
//
//	for (int i = 0; i < ignorePrompt.size(); i++) {
//		for (int j = 0; j < ignorePrompt[i].size(); j++) {
//			preAppend = tempText.getGlobalBounds().width + tempText.getPosition().x;
//			tempText.setString(tempText.getString() + ignorePrompt[i][j]);
//			postAppend = tempText.getGlobalBounds().width + tempText.getPosition().x;
//			stringLength = postAppend - preAppend;
//			displayLength += stringLength;
//			if (displayLength < (window.getSize().x - tempText.getPosition().x *1.3)) {
//				ignorePromptTextPtr->appendTextString(ignorePrompt[i][j]);
//			} else {
//				ignorePromptTextPtr->appendTextString("\n" + ignorePrompt[i][j]);
//				displayLength = stringLength;
//			}
//		}
//	}
//	return ignorePromptTextPtr;
//}