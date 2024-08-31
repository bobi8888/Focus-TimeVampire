#pragma once
//#include <SFML/Graphics.hpp>
//using std::string;

class GameTimer {
	private:
		int timerPrecision = 2;
		float elapsedSeconds = 0;
		float timerLength = 1;
		float timeRemaining = timerLength;
		float timeTaken = 0;
		string timerString;

	public:
		GameTimer();
		GameTimer(float newTimerLength);
		void setPrecision();
		float getTimeRemaining();
		void setTimeRemaining(sf::Clock& clock);
		void resetTimer();
		void setTimerLength(float time);
		void setTimeTaken();
		//sf::Text setTimerString(std::ostringstream& out, static sf::Text &timerText);
		GameTimer* manageGameTimer(sf::Clock &clock, GameTimer* gameTimer);
		GameTimer* pause(sf::Clock &clock, GameTimer* gameTimer);
		GameTimer* timeUp(GameTimer* gameTimer);
		string getTimerString(std::ostringstream& out);
		bool handleMinigamePace(float minigameTime, float minigameSpeed);
		bool isWithinMillisecondBounds(sf::Clock& clock, int fractionOfSecond);
};