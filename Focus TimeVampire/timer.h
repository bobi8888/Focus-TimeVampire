
class GameTimer {
	private:
		int precision = 2;
		float elapsedSeconds = 0;
		float timerLength = 20;
		float timeRemaining = timerLength;
		float timeTaken = 0;

		string timerString;

	public:
		int getPrecision();
		void setPrecision();
		float getTimeRemaining();
		void setTimeRemaining(sf::Clock& clock);
		void resetTimer();
		float getElapsedSeconds();
		void setElapsedSeconds(sf::Clock& clock);
		float getTimerLength();
		void setTimerLength(float time);
		float getTimeTaken();
		void setTimeTaken();
		sf::Text setTimerString(std::ostringstream& out, static sf::Text &tooltip);
		GameTimer manageGameTimer(sf::Clock &clock, GameTimer gameTimer);
		GameTimer pause(sf::Clock &clock, GameTimer gameTimer);
		GameTimer timeUp(GameTimer gameTimer);
		string getString(std::ostringstream& out);
};

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
void GameTimer::setTimeRemaining(sf::Clock &clock) {
	setElapsedSeconds(clock);
	timeRemaining = timerLength - timeTaken - elapsedSeconds;
}
void GameTimer::resetTimer(){
	timeRemaining = timerLength;
	timeTaken = 0;
}
float GameTimer::getElapsedSeconds() {
	return elapsedSeconds;
}
void GameTimer::setElapsedSeconds(sf::Clock &clock){
	elapsedSeconds = clock.getElapsedTime().asSeconds();
}
float GameTimer::getTimerLength(){
	return timerLength;
}
void GameTimer::setTimerLength(float time){
	timerLength = time;
}
float GameTimer::getTimeTaken(){
	return timeTaken;
}
void GameTimer::setTimeTaken(){
	timeTaken = timerLength - timeRemaining;
}
string GameTimer::getString(std::ostringstream& out){
	out << std::setprecision(precision) << timeRemaining;
	timerString = out.str();
	out.str("");
	return timerString;
}
sf::Text GameTimer::setTimerString(std::ostringstream &out, sf::Text &tooltip){
	out << std::setprecision(precision) << timeRemaining;
	tooltip.setString(out.str());
	out.str("");
	return tooltip;
}
GameTimer GameTimer::manageGameTimer(sf::Clock &clock, GameTimer gameTimer){
	gameTimer.setPrecision();
	gameTimer.setTimeRemaining(clock);
	return gameTimer;
};
GameTimer GameTimer::pause(sf::Clock &clock, GameTimer gameTimer) {
	gameTimer.setTimeRemaining(clock);
	gameTimer.setTimeTaken();
	return gameTimer;
}
GameTimer GameTimer::timeUp(GameTimer gameTimer) {
	//tooltipText.setString("Times Up!");
	gameTimer.resetTimer();
	return gameTimer;
}