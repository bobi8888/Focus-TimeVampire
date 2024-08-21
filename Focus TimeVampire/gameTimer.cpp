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
GameTimer* GameTimer::manageGameTimer(sf::Clock& clock, GameTimer* gameTimerPtr) {
	gameTimerPtr->setPrecision();
	gameTimerPtr->setTimeRemaining(clock);
	return gameTimerPtr;
};

GameTimer* GameTimer::pause(sf::Clock& clock, GameTimer* gameTimerPtr) {
	gameTimerPtr->setTimeRemaining(clock);
	gameTimerPtr->setTimeTaken();
	return gameTimerPtr;
}

GameTimer* GameTimer::timeUp(GameTimer* gameTimerPtr) {
	gameTimerPtr->resetTimer();
	return gameTimerPtr;
}
bool GameTimer::handleMinigamePace(float minigameTime, float minigameSpeed){
	if (minigameTime - getTimeRemaining() > minigameSpeed) {
		return true;
	} else {
		return false;
	}
}

