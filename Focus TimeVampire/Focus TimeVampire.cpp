#include <iostream>
#include <cmath>
#include <iomanip>
#include <cassert>
#include <sstream>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

#include "window.h"
#include "font_and_text.h"
#include "mouse.h"
#include "gameSprite.h"
#include "gameScreen.h"
#include "utils.h"
#include "transformableSprite.h"
#include "timer.h"

//ISSUES
//start, pause, resume...rooms & timer dont draw, but the timer continues
//bool to handle mouse clicks
//add back button to all minigames
int main() {
	
	//WINDOW
	antialiasing.antialiasingLevel = 8;
	window.setVerticalSyncEnabled(true);
	window.setPosition(sf::Vector2i(1300, 400));

	//FONT & TEXT
	loadFont(font);
	GameText tooltip(20, "", 20, window);
	tooltip.setPosition(sf::Vector2f(5,30));

	//SPRITE & TEXTRUE
	float minigameX_Scale = 0.2, minigameY_Scale = 0.2;
	GameSprite minigameSprite("roomSprite.png", minigameX_Scale, minigameY_Scale);
	GameSprite startButton("startSprite.png", 0.5, 0.5);
	startButton.setSpritePosition(getCenterOfWindow(window));
	GameSprite pauseButton("pauseSprite.png", 0.25, 0.25);
	pauseButton.setSpritePosition(sf::Vector2f(window.getSize().x - 35, 40));
	GameSprite resumeButton("resumeSprite.png", 0.5, 0.5);
	resumeButton.setSpritePosition(getCenterOfWindow(window));
	GameSprite fullBubble("fullBubbleSprite.png", 1, 1);
	fullBubble.setPosition(sf::Vector2f(window.getSize().x/4, window.getSize().y/2));	
	GameSprite emptyBubble("emptyBubbleSprite.png", 0.1, 0.1);
	emptyBubble.setPosition(sf::Vector2f(window.getSize().x/4 * 3, window.getSize().y/2));	
	GameSprite banner("bannerSprite.png", 1, 1);
	banner.setPosition(sf::Vector2f(window.getSize().x/2, window.getSize().y - 50));	
	GameSprite backButton("backSprite.png", 0.18, 0.18);
	backButton.setPosition(sf::Vector2f(window.getSize().x - 55, window.getSize().y - 30));

	TransformableSprite player("playerSprite.png", 0.5, 0.5);
	player.setSpritePosition(getCenterOfWindow(window));
	player.setMovementSpeed(2);
	player.setRadius(player.getSprite().getGlobalBounds().height/2);

	//TIME
	GameTimer gameTimer;
	sf::Clock clock;
	sf::Time time;
	std::ostringstream out;

	//MINIGAMES
	vector<sf::Vector2f> minigamePositions;
	vector<GameSprite> minigameVector;	
	minigamePositions = setMinigamePositions(3, 3, minigameSprite.getSprite(), 1, 1);
	minigameVector = setMinigameVector("roomSprite.png", minigamePositions, minigameX_Scale, minigameY_Scale);
	minigameTexture.loadFromFile("roomSprite.png");

	//MAIN GAME SCREENS
	GameScreen startScreen("FOCUS! Time Vampire");
	startScreen.addSprite(startButton.getSprite());
	GameScreen gameScreen("FOCUS! Time Vampire");
	GameScreen resumeScreen("FOCUS! Time Vampire");
	resumeScreen.addSprite(resumeButton.getSprite());
	//MINIGAMES
	GameScreen remember("REMEMBER!");
	remember.addSprite(fullBubble.getSprite());
	remember.addSprite(emptyBubble.getSprite());
	GameScreen count("COUNT!");
	GameScreen assemble("ASSEMBLE!");
	GameScreen discuss("DISCUSS!");
	GameScreen ignore("IGNORE!");
	GameScreen drive("DRIVE!");
	GameScreen retain("RETAIN!");
	GameScreen push("PUSH!");
	GameScreen bonus("BONUS!");

	//GAME LOOP: mainScreenENUM
	sf::Event event;
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.display();
		window.clear();
		translatedMousePosition = setMousePosition(window);

		switch (mainScreenENUM){
			case startMAIN://START SCREEN
				startScreen.drawScreen(window, tooltip.getText());
				//PRESS START TO BEGIN GAME
				if (event.type == sf::Event::EventType::MouseButtonPressed){
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && 
					startButton.getSprite().getGlobalBounds().contains(translatedMousePosition)) {
						clock.restart();
						mainScreenENUM = gameMAIN;
						event.type = sf::Event::MouseButtonReleased;
						}
					}
			break;	 

			case gameMAIN://GAME SCREEN
				window.draw(pauseButton.getSprite());
				if (gameTimer.getTimeRemaining() > 0) {
					tooltip.setString(gameTimer.getString(out));
					gameTimer = gameTimer.manageGameTimer(clock, gameTimer);	
					
					//switch for these 2?
					if (event.type == sf::Event::EventType::MouseButtonPressed) {
						if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && pauseButton.getSprite().getGlobalBounds().contains(translatedMousePosition)) {
							gameTimer = gameTimer.pause(clock, gameTimer);
							tooltip.setString("::Paused::");
							mainScreenENUM = resumeMAIN;
						}
					}		

					if(gameScreenENUM != mainENUM){//BACK BUTTON
						window.draw(backButton.getSprite());
						if (event.type == sf::Event::EventType::MouseButtonPressed) {
							if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && backButton.getSprite().getGlobalBounds().contains(translatedMousePosition)) {
								gameScreenENUM = mainENUM;
							}
						}
					}

					switch(gameScreenENUM){
						case mainENUM:
							gameScreen.drawScreen(window, tooltip.getText());
							drawIdenticalSpriteVector(minigameTexture, minigameVector);//constantly setting textures?
							//SWITCH FOR WHICH MINIGAME IS SELECTED
							if (event.type == sf::Event::EventType::MouseButtonPressed) {
								for (int i = 0; i < minigameVector.size(); i++) {
									if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && minigameVector[i].getSprite().getGlobalBounds().contains(translatedMousePosition)) {
										gameScreenENUM = static_cast<gameScreens>(i);
									}
								}
							}
						break;
						case rememberENUM://REMEMBER
							player.setMovement();	
							window.draw(player.getSprite());
							remember.drawScreen(window, tooltip.getText());
							if(player.hasCircleContact(emptyBubble.getSprite()) == true || player.hasCircleContact(fullBubble.getSprite()) == true){
								window.draw(banner.getSprite());
							}

						break;
						case countENUM://COUNT
							count.drawScreen(window, tooltip.getText());
						break;
						case assembleENUM://ASSEMBLE
							assemble.drawScreen(window, tooltip.getText());
						break;
						case discussENUM://DISCUSS
							discuss.drawScreen(window, tooltip.getText());
						break;
						case ignoreENUM://IGNORE
							ignore.drawScreen(window, tooltip.getText());
						break;
						case driveENUM://DRIVE
							drive.drawScreen(window, tooltip.getText());
						break;
						case retainENUM://RETAIN
							retain.drawScreen(window, tooltip.getText());
						break;
						case pushENUM://PUSH
							push.drawScreen(window, tooltip.getText());
						break;
						case bonusENUM://BONUS
							bonus.drawScreen(window, tooltip.getText());
						break;
					}
				}else{//TIME IS UP
					gameTimer = gameTimer.timeUp(gameTimer);
					tooltip.setString("Time Up!");
					startScreen.setAndCenterTitle("GAME OVER!");
					player.setPosition(getCenterOfWindow(window));
					mainScreenENUM = startMAIN;
					gameScreenENUM = mainENUM;
				}
			break;

			case resumeMAIN://RESUME SCREEN				
				resumeScreen.drawScreen(window, tooltip.getText());
				if (event.type == sf::Event::EventType::MouseButtonPressed) {
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && resumeButton.getSprite().getGlobalBounds().contains(translatedMousePosition)) {
						clock.restart();
						assert(gameTimer.getTimeRemaining() > 0);
						mainScreenENUM = gameMAIN;
					}
				}
			break;
		}

	}
}