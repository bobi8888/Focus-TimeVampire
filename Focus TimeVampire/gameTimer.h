#pragma once
#include <SFML/Graphics.hpp>
using std::string;

class GameTimer {
	private:
		int precision = 2;
		float elapsedSeconds = 0;
		float timerLength = 1;
		float timeRemaining = timerLength;
		float timeTaken = 0;
		string timerString;

	public:
		GameTimer(float newTimerLength);
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
		sf::Text setTimerString(std::ostringstream& out, static sf::Text &timerText);
		GameTimer manageGameTimer(sf::Clock &clock, GameTimer gameTimer);
		GameTimer pause(sf::Clock &clock, GameTimer gameTimer);
		GameTimer timeUp(GameTimer gameTimer);
		string getString(std::ostringstream& out);
		bool handleMinigamePace(float minigameTime, float minigameSpeed);
};