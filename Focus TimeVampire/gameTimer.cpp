#include "utils.h"
#include "gameTimer.h"

GameTimer::GameTimer() {}
GameTimer::GameTimer(float newGameTimer) {
	timerLength = newGameTimer;
	timeRemaining = timerLength;
}
void GameTimer::setPrecision() {
	if (timeRemaining < 10) {
		timerPrecision = 2;
	}
	else {
		timerPrecision = 3;
	}
}
float GameTimer::getTimeRemaining() {
	return timeRemaining;
}
void GameTimer::setTimeRemaining(sf::Clock& clock) {
	timeRemaining = timerLength - timeTaken - clock.getElapsedTime().asSeconds();
}
void GameTimer::resetTimer() {
	timeRemaining = timerLength;
	timeTaken = 0;
}
void GameTimer::setTimerLength(float time) {
	timerLength = time;
}
void GameTimer::setTimeTaken() {
	timeTaken = timerLength - timeRemaining;
}
string GameTimer::getTimerString(std::ostringstream& out) {
	out << std::setprecision(timerPrecision) << timeRemaining;
	timerString = out.str();
	out.str("");
	return timerString;
}
//sf::Text GameTimer::setTimerString(std::ostringstream& out, sf::Text& timerText) {
//	out << std::setprecision(timerPrecision) << timeRemaining;
//	timerText.setString(out.str());
//	out.str("");
//	return timerText;
//}
GameTimer* GameTimer::manageGameTimer(sf::Clock& clock, GameTimer* gameTimer) {
	gameTimer->setPrecision();
	gameTimer->setTimeRemaining(clock);
	return gameTimer;
};

GameTimer* GameTimer::pause(sf::Clock& clock, GameTimer* gameTimer) {
	gameTimer->setTimeRemaining(clock);
	gameTimer->setTimeTaken();
	return gameTimer;
}

GameTimer* GameTimer::timeUp(GameTimer* gameTimer) {
	gameTimer->resetTimer();
	return gameTimer;
}
bool GameTimer::handleMinigamePace(float minigameTime, float minigameSpeed){
	if (minigameTime - getTimeRemaining() > minigameSpeed) {
		return true;
	} else {
		return false;
	}
}

bool GameTimer::isWithinMillisecondBounds(sf::Clock& clock, int fractionOfSecond) {
	bool testIsMilli;
	testIsMilli = clock.getElapsedTime().asMilliseconds() % fractionOfSecond ? true : false;
	cout << testIsMilli << "\n";
	return testIsMilli;
}

