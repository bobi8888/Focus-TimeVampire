#include"utils.h"

# include "gameTimer.h"

int GameTimer::getPrecision() {
	return precision;
}
void GameTimer::setPrecision() {
	if (timeRemaining < 10) {
		precision = 2;
	}
	else {
		precision = 3;
	}
}
float GameTimer::getTimeRemaining() {
	return timeRemaining;
}
void GameTimer::setTimeRemaining(sf::Clock& clock) {
	setElapsedSeconds(clock);
	timeRemaining = timerLength - timeTaken - elapsedSeconds;
}
void GameTimer::resetTimer() {
	timeRemaining = timerLength;
	timeTaken = 0;
}
float GameTimer::getElapsedSeconds() {
	return elapsedSeconds;
}
void GameTimer::setElapsedSeconds(sf::Clock& clock) {
	elapsedSeconds = clock.getElapsedTime().asSeconds();
}
float GameTimer::getTimerLength() {
	return timerLength;
}
void GameTimer::setTimerLength(float time) {
	timerLength = time;
}
float GameTimer::getTimeTaken() {
	return timeTaken;
}
void GameTimer::setTimeTaken() {
	timeTaken = timerLength - timeRemaining;
}
string GameTimer::getString(std::ostringstream& out) {
	out << std::setprecision(precision) << timeRemaining;
	timerString = out.str();
	out.str("");
	return timerString;
}
sf::Text GameTimer::setTimerString(std::ostringstream& out, sf::Text& timerText) {
	out << std::setprecision(precision) << timeRemaining;
	timerText.setString(out.str());
	out.str("");
	return timerText;
}
GameTimer GameTimer::manageGameTimer(sf::Clock& clock, GameTimer gameTimer) {
	gameTimer.setPrecision();
	gameTimer.setTimeRemaining(clock);
	return gameTimer;
};
GameTimer GameTimer::pause(sf::Clock& clock, GameTimer gameTimer) {
	gameTimer.setTimeRemaining(clock);
	gameTimer.setTimeTaken();
	return gameTimer;
}
GameTimer GameTimer::timeUp(GameTimer gameTimer) {
	gameTimer.resetTimer();
	return gameTimer;
}
bool GameTimer::handleMinigamePace(float minigameTime, float minigameSpeed){
	if (minigameTime - getTimeRemaining() > minigameSpeed) {
		return true;
	} else {
		return false;
	}
}