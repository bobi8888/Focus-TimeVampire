#include "utils.h"
#include "window.h"
#include "gameText.h"
#include "mouse.h"
#include "gameSprite.h"
#include "gameScreen.h"
#include "gameTimer.h"
#include "randomizedData.h"
#include "assembleUtils.h"
#include "discussUtils.h"
#include "gameScreen.h"
#include "ignoreUtils.h"
#include "acceptUtils.h"


//ISSUES
//reset random numbers each playthrough for Remember
//add reset button
//add X_out button
//changing window size and player sprite going past the window
//sprite sizes should be relative the the window size at initialization

//gameTimer = gameTimer.pause(gameTimerClock, gameTimer); so many game timers?

int main() {	
	//WINDOW
	antialiasing.antialiasingLevel = 8;
	window.setVerticalSyncEnabled(true);
	window.setPosition(sf::Vector2i(1400, 400));
	window.setKeyRepeatEnabled(false);

	//TIME
	GameTimer* gameTimerPtr = new GameTimer(100);
	sf::Clock gameTimerClock;
	GameTimer* ignoreTimerPtr = new GameTimer(5);
	sf::Clock ignoreTimerClock;

	//STREAM
	std::ostringstream out;
	std::stringstream stream;
	srand(time(NULL));

	//FONT & TEXT
	sf::Font generalFont;
	loadFont(generalFont);

	GameText* timerTextPtr = new GameText(generalFont, 20, "", 20, window);
	timerTextPtr->getText().setPosition(sf::Vector2f(5,30));
	GameText* bannerTextPtr = new GameText(generalFont, 30,"",0, window);
	bannerTextPtr->getText().setFillColor(sf::Color::Black);
	GameText* playerTextPtr = new GameText(generalFont, 30, "", 400, window);
	playerTextPtr->getText().setFillColor(sf::Color::White);
	GameText* tipTextPtr = new GameText(generalFont, 25, "Enter the missing values!", 55, window);
	playerTextPtr->getText().setFillColor(sf::Color::White);
	GameText* ignorePromptTextPtr = new GameText(generalFont, 30, "",20, window);
	ignorePromptTextPtr->setTextPosition(sf::Vector2f(50, 125));

	//GAME SPRITES

	GameSprite* startButtonPtr = new GameSprite("startSprite.png", 0.5, 0.5);
	startButtonPtr->setPosition(getCenterOfWindow(window));
	GameSprite* questionButtonPtr = new GameSprite("questionButton.png", 0.4, 0.4);
	questionButtonPtr ->setPosition(sf::Vector2f(window.getSize().x/2, 300));
	GameSprite* gobackButtonPtr = new GameSprite("gobackButton.png", 0.35, 0.35);
	gobackButtonPtr->setPosition(sf::Vector2f(window.getSize().x / 4, window.getSize().y - 100));
	GameSprite* skipButtonPtr = new GameSprite ("skipButton.png", 0.35, 0.35);
	skipButtonPtr->setPosition(sf::Vector2f(window.getSize().x / 4 * 3 , window.getSize().y - 100));
	GameSprite* pauseButtonPtr = new GameSprite("pauseSprite.png", 0.25, 0.25);
	pauseButtonPtr->setPosition(sf::Vector2f(window.getSize().x - 35, 40));
	GameSprite* resumeButtonPtr = new GameSprite("resumeSprite.png", 0.5, 0.5);
	resumeButtonPtr->setPosition(getCenterOfWindow(window));
	GameSprite* solutionButtonPtr = new GameSprite("solutionSprite.png", 0.3, 0.3);
	solutionButtonPtr->setPosition(sf::Vector2f(window.getSize().x/2, window.getSize().y - 50));
	GameSprite* bannerSpritePtr = new GameSprite("bannerSprite.png", 1, 1);
	bannerSpritePtr->setPosition(sf::Vector2f(window.getSize().x/2, window.getSize().y - 50));
	bannerTextPtr->getText().setPosition(sf::Vector2f(bannerSpritePtr->getSprite().getPosition().x, bannerSpritePtr->getSprite().getPosition().y - 20));

	//GameSprite* x_outButtonPtr = new GameSprite("x_outSprite.png", 0.25, 0.25);
	//x_outButtonPtr->setPosition(sf::Vector2f(bannerSpritePtr->getSprite().getPosition().x + bannerSpritePtr->getSprite().getGlobalBounds().width/2 - 15
	//, bannerSpritePtr->getSprite().getPosition().y - bannerSpritePtr->getSprite().getGlobalBounds().height / 2 + 30));

	GameSprite* backButtonPtr = new GameSprite("backSprite.png", 0.18, 0.18);
	backButtonPtr->setPosition(sf::Vector2f(window.getSize().x - 55, window.getSize().y - 30));

	GameSprite* acceptSpritePtr = new GameSprite("acceptSprite.png", 0.3, 0.3);
	acceptSpritePtr->setPosition(sf::Vector2f(window.getSize().x/2, window.getSize().y/2));

	GameSprite* wallSpritePtr = new GameSprite("wallSprite.png", 1, 1);
	wallSpritePtr->setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));

	//TRANSFORMABLE SPRITES
	PlayerSprite player("playerSprite.png", 0.4, 0.4);
	player.setPosition(getCenterOfWindow(window));
	player.setMovementSpeed(5);
	player.setRadius(player.getSprite().getGlobalBounds().height/2);
	player.initializeSpriteRadiusCircle(player.getRadius(), 30);


	//DATA SPRITES
	DataSprite minigameSprite("minigameSprite.png", 0.3, 0.3);
	DataSprite fullBubble("fullBubbleSprite.png", 1, 1);
	DataSprite emptyBubble("emptyBubbleSprite.png", 1, 1);
	DataSprite countingSprite("countingSprite.png", 0.5, 0.5);
	
	//SPRITE VECTORS	
	DataSpriteVector minigameSprites(9, minigameSprite);
	minigameSprites.setPositions(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2), 3, 3, 1, 1);
	int bubbleQTY = 3;
	DataSpriteVector rememberFullBubbles(bubbleQTY,fullBubble);
	rememberFullBubbles.setPositions(sf::Vector2f(80, 250), bubbleQTY, 1, 25, 0);

	DataSpriteVector rememberEmptyBubbles(bubbleQTY, emptyBubble);
	rememberEmptyBubbles.setPositions(sf::Vector2f(420, 250), bubbleQTY, 1, 25, 0);
	rememberFullBubbles.setLetters();
	rememberFullBubbles.setLongValues();
	rememberFullBubbles.setStringValues(stream);
	rememberFullBubbles.setFullDataStrings(out);

	int countingQTY = 13;
	DataSpriteVector countingSprites(countingQTY, countingSprite);
	countingSprites.setPositions(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2), 1, countingQTY, 0, 4);

	//MAIN GAME SCREENS
	GameScreen startScreen("FOCUS! Time Vampire", generalFont, 25, 25, window);
	startScreen.addSprite(startButtonPtr ->getSprite());
	GameScreen gameScreen("FOCUS! Time Vampire", generalFont, 25, 25, window);
	GameScreen resumeScreen("FOCUS! Time Vampire", generalFont, 25, 25, window);
	resumeScreen.addSprite(resumeButtonPtr->getSprite());

	//MINIGAMES
	//REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER
	GameScreen remember("REMEMBER!", generalFont, 25, 25, window);
	bannerTextPtr->setTextString("Enter #");
	bannerTextPtr->centerTextOriginOnSprite(bannerSpritePtr->getSprite(),0,0);
	//COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT 
	GameScreen count("COUNT!", generalFont, 25, 25, window);
	stream << countingQTY;
	string countingString = stream.str();
	//ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE 
	GameScreen assembleGameScreen("ASSEMBLE!", generalFont, 25, 25, window);
	assembleGameScreen.addSprite(solutionButtonPtr->getSprite());
	GameScreen assembleSolution("ASSEMBLE Solution", generalFont, 25, 25, window);
	pcbSolvedSprite.setPosition(getCenterOfWindow(window));
	assembleSolution.addSprite(pcbSolvedSprite.getSprite());
	for (int i = 0; i < 9; i++) {assembleDataSpriteVector.addSprite(assemblePartsSpriteVector[i], 1);}
	assembleDataSpriteVector.setPositions(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2 - 10), 3, 3, 90, 120);
	assembleDataSpriteVector.setSpriteToComplete(4);	
	assembleGoal.setOrigin(sf::Vector2f(assembleGoal.getGlobalBounds().width / 2, assembleGoal.getGlobalBounds().height / 2));
	for (int i = 0; i < assembleGoalPositions.size(); i++) {
		assembleGoal.setPosition(assembleGoalPositions[i]);
		assemblePartsGoals.push_back(assembleGoal);
	}
	//DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS 
	GameScreen discuss("DISCUSS!", generalFont, 25, 25, window);
	DiscussText npcText(generalFont, 25, question1, questionY, window);
	npcText.setCharWidthsVector(question1);
	for (int i = 0; i < npcText.getTextString().size(); i++) {
		sf::RectangleShape textBlocker(sf::Vector2f(npcText.getCharWidthsVector()[i], npcText.getText().getCharacterSize() + 10));
		textBlocker.setOrigin(textBlocker.getSize().x/2, textBlocker.getSize().y/2);
		textBlocker.setPosition(sf::Vector2f(npcText.getText().findCharacterPos(i).x + textBlocker.getSize().x / 2, npcText.getText().findCharacterPos(i).y + textBlocker.getSize().y / 2));
		textBlocker.setFillColor(sf::Color::White);
		textBlocker.setOutlineColor(sf::Color::Cyan);
		textBlocker.setOutlineThickness(3);
		textBlockersVector.push_back(textBlocker);
	}
	GameSprite discussBannerSprite("bannerSprite.png", 1.3, 1.1);
	discussBannerSprite.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y - 150));

	GameText leftAnswer(generalFont, 32, response1A, 200, window);
	leftAnswer.getText().setFillColor(sf::Color::Black);
	leftAnswer.setTextPosition(sf::Vector2f(discussBannerSprite.getSprite().getPosition().x - discussBannerSprite.getSprite().getGlobalBounds().width * 0.25
		, discussBannerSprite.getSprite().getPosition().y));
	GameText rightAnswer(generalFont, 32, response1B, 200, window);

	rightAnswer.getText().setFillColor(sf::Color::Black);
	rightAnswer.setTextPosition(sf::Vector2f(discussBannerSprite.getSprite().getPosition().x + discussBannerSprite.getSprite().getGlobalBounds().width * 0.25
		, discussBannerSprite.getSprite().getPosition().y));
	//IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE 
	GameScreen ignorePromptScreen("IGNORE!", generalFont, 25, 25, window);
	ignorePromptScreen.addSprite(questionButtonPtr->getSprite());
	GameScreen ignoreQuestionScreen("IGNORE!", generalFont, 25, 25, window);
	ignoreQuestionScreen.addSprite(gobackButtonPtr->getSprite());
	ignoreQuestionScreen.addSprite(skipButtonPtr->getSprite());

	sf::Music dullBed;
	dullBed.setLoop(true);
	if (!dullBed.openFromFile("dullBed.wav")) std::cout << "Error loading dullBed.wav \n";	
	dullBed.setVolume(dullBedVolume);
	sf::Music convo;
	convo.setLoop(true);
	if (!convo.openFromFile("convo.wav")) std::cout << "Error loading convo.wav \n";
	convo.setVolume(convoVolume);
	sf::SoundBuffer ignoreSoundBuffer;
	if (!ignoreSoundBuffer.loadFromFile("beep.wav")) std::cout << "Error loading beep.wav \n";
	sf::Sound ignoreBeep;
	ignoreBeep.setBuffer(ignoreSoundBuffer);
	ignoreBeep.setVolume(beepVolume);

	beepCountdown = gameTimerPtr->getTimeRemaining() - randomInt(5, 1);

	sf::Text tempText("", generalFont);
	int randomIgnore_Int = randomInt(2, 15);
	int ignoreKey_Int = randomIgnore_Int + 5;
	ignoreKeys[0] = std::to_string(ignoreKey_Int);
	string ignoreKey_String = std::to_string(ignoreKey_Int);
	string randomInt_String = std::to_string(randomIgnore_Int);

	ignorePromptTextPtr = loadPrompt(randomInt_String, tempText, ignorePromptVectors[currentPrompt], ignorePromptTextPtr, window);
	// ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT 
	GameScreen drive("ACCEPT!", generalFont, 25, 25, window);
	//sf::RectangleShape wall(sf::Vector2f(100, 100));
	//wall.setFillColor(sf::Color::White);
	//wall.setPosition(sf::Vector2f(200, 200));
	// RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN 
	GameScreen retain("RETAIN!", generalFont, 25, 25, window);
	// PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH
	GameScreen push("PUSH!", generalFont, 25, 25, window);
	// BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS
	GameScreen bonus("BONUS!", generalFont, 25, 25, window);

	bool deleteKeyWorkaround = false;//both needed for delete workaround
	bool acceptText = false;

	enum mainScreens { startMAIN, gameMAIN, resumeMAIN };
	enum gameScreens { rememberENUM, countENUM, assembleENUM, discussENUM, ignoreENUM, acceptENUM, retainENUM, pushENUM, bonusENUM, mainENUM };
	mainScreens mainScreensENUM = startMAIN;
	gameScreens gameScreensENUM = mainENUM;

	sf::Vertex line[] =
	{
		sf::Vertex(sf::Vector2f(300, 10)),
		sf::Vertex(sf::Vector2f(0, 150))
	};

	sf::VertexArray triangle(sf::Triangles, 3);
	triangle[0].position = sf::Vector2f(10, 10);
	triangle[1].position = sf::Vector2f(100, 10);
	triangle[2].position = sf::Vector2f(100, 100);
	triangle[0].color = sf::Color::Red;
	triangle[1].color = sf::Color::Blue;
	triangle[2].color = sf::Color::Green;


	//GAME LOOP: mainScreensENUM
	sf::Event event;
	while (window.isOpen()) {
		window.display();
		window.clear();
		translatedMousePosition = setMousePosition(window);

		while (window.pollEvent(event)) {//this includes the closed window event & entering text
			if (event.type == sf::Event::Closed)
				window.close();
		
			switch (event.key.code) {
				case sf::Keyboard::Delete://66
				if(!deleteKeyWorkaround){
					playerTextPtr->deleteLastChar();
					playerTextPtr->setIsFull(false);
					deleteKeyWorkaround = true;
				}else
					deleteKeyWorkaround = false;
				break;
			}
			if (event.type == sf::Event::TextEntered) {
				string outString;
				switch (event.text.unicode){
					case 27://ESCAPE
					playerTextPtr->setTextString("");
					playerTextPtr->setIsFull(false);
					break;
					case 8://BACKSPACE
					playerTextPtr->deleteLastChar();
					playerTextPtr->setIsFull(false);
					break;					
				}			
			}
			if (acceptText) {
				if(!playerTextPtr->getIsFull()) {
					if (event.text.unicode < 58 && event.text.unicode >= 48 && event.type != sf::Event::MouseMoved)
						playerTextPtr->appendTextString(event.text.unicode);
				} else playerTextPtr->setTextString("");
			}		
		}

		switch (mainScreensENUM){
			case startMAIN://START SCREEN
			if (validSpriteClick(event, startButtonPtr->getSprite().getGlobalBounds(), translatedMousePosition) == true) {
				gameTimerClock.restart();
				mainScreensENUM = gameMAIN;
				event.type = sf::Event::MouseButtonReleased;
			} else startScreen.drawScreen(window, timerTextPtr->getText());
			break;	 

			case gameMAIN://GAME SCREEN
			window.draw(pauseButtonPtr->getSprite());
			if (gameTimerPtr->getTimeRemaining() > 0) {//game timer
				timerTextPtr->getText().setString(gameTimerPtr->getString(out));
				gameTimerPtr = gameTimerPtr->manageGameTimer(gameTimerClock, gameTimerPtr);
				
				//PAUSE
				if (validSpriteClick(event, pauseButtonPtr->getSprite().getGlobalBounds(), translatedMousePosition) == true) {
					gameTimerPtr = gameTimerPtr->pause(gameTimerClock, gameTimerPtr);
					ignoreTimerPtr = ignoreTimerPtr->pause(ignoreTimerClock, ignoreTimerPtr);
					timerTextPtr->getText().setString(("::Paused::"));
					mainScreensENUM = resumeMAIN;					
				}		

				if(gameScreensENUM != mainENUM){//BACK BUTTON
					if (validSpriteClick (event, backButtonPtr->getSprite().getGlobalBounds(), translatedMousePosition) == true) {
						gameScreensENUM = mainENUM;
						playerTextPtr->getText().setString("");
						acceptText = false;						
					} else window.draw(backButtonPtr->getSprite());
				}

				switch(gameScreensENUM){
					case mainENUM:
					gameScreen.drawScreen(window, timerTextPtr->getText());
					minigameSprites.drawSprites(window, -1);
					dullBed.pause();
					convo.pause();
					//SWITCH FOR WHICH MINIGAME IS SELECTED

					if (event.type == sf::Event::EventType::MouseButtonPressed) {
						for (int i = 0; i < minigameSprites.getDataSpriteVector().size(); i++) {
							if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && minigameSprites.getSingleSprite(i).getSprite().getGlobalBounds().contains(translatedMousePosition)) {
								if (!minigameSprites.getSingleSprite(i).getIsComplete()) { gameScreensENUM = static_cast<gameScreens>(i); }

								event.type = sf::Event::EventType::MouseButtonReleased;
								
								//IGNORE 
								if (gameScreensENUM == ignoreENUM) {
									dullBed.play();
									convo.play();
									ignoreTimerClock.restart();
									bannerSpritePtr->setPosition(getCenterOfWindow(window));
									acceptText = true;
								}

								//ACCEPT
								if (gameScreensENUM == acceptENUM) {	
									player.setMovementSpeed(5);
									player.setPosition(sf::Vector2f(0 + player.getSprite().getGlobalBounds().width/2, window.getSize().y - player.getSprite().getGlobalBounds().height/2));
								}

								if (gameScreensENUM == rememberENUM) { player.setMovementSpeed(15);	}
							}
						}
					}
					break;
					case rememberENUM://REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER 
					//swapping can be used to randomize vectors to increase difficulty
					player.setMovement(window);
					window.draw(tipTextPtr->getText());
					window.draw(player.getSprite()); 
					rememberFullBubbles.drawSprites(window, -1);
					rememberEmptyBubbles.drawSprites(window, -1);
					remember.drawScreen(window, timerTextPtr->getText());

					for (int i = 0; i < rememberFullBubbles.getDataSpriteVector().size(); i++) {//contacting full sprites
						if (player.hasCircleContactWithSprite(rememberFullBubbles.getDataSpriteVector()[i].getSprite(), 0) == true){
							bannerTextPtr->setTextString(rememberFullBubbles.getFullDataStrings(i));
							bannerTextPtr->centerTextOriginOnSprite(bannerSpritePtr->getSprite(), 0, -5);
							window.draw(bannerSpritePtr->getSprite());
							window.draw(bannerTextPtr->getText());
						}
					}		
					player.handleSpriteContactIndex(rememberEmptyBubbles, 0);
					if (player.getSpriteContactIndex() >= 0) {
						if (rememberEmptyBubbles.getSingleSprite(player.getSpriteContactIndex()).getIsComplete()) {//checking if contacted sprite is complete
						} else {//sprite incomplete, check if text can be entered			
							bannerTextPtr->setTextString("Enter " + rememberFullBubbles.getSingleSprite(player.getSpriteContactIndex()).getLetter());
							bannerTextPtr->centerTextOriginOnSprite(bannerSpritePtr->getSprite(), 0, -20);
							playerTextPtr->setTextToMoney(out);
							playerTextPtr->centerTextOriginOnSprite(bannerSpritePtr->getSprite(), 0, +5);
							window.draw(bannerSpritePtr->getSprite());
							window.draw(bannerTextPtr->getText());
							window.draw(playerTextPtr->getText());
							if (playerTextPtr->getTextString().size() <= rememberFullBubbles.getSingleSprite(player.getSpriteContactIndex()).getStringValue().size() - 1) {
								acceptText = true;
							} else {
								acceptText = false;
								if (playerTextPtr->getTextString() == rememberFullBubbles.getSingleSprite(player.getSpriteContactIndex()).getStringValue()) {
									rememberEmptyBubbles.updateIndividualTexture(player.getSpriteContactIndex(), "okBubbleSprite.png");
									rememberEmptyBubbles.setSpriteToComplete(player.getSpriteContactIndex());
								} 
							}
						}
					} else {
						playerTextPtr->setTextString("");
						acceptText = false;
					}
					//win condition		
					if (!rememberEmptyBubbles.getVectorComplete())
						rememberEmptyBubbles.checkForCompletion();
					else {
						playerTextPtr->setTextString("");
						minigameSprites.updateIndividualTexture(rememberENUM, "completedMinigameSprite.png");
						minigameSprites.setSpriteToComplete(rememberENUM);
						gameScreensENUM = mainENUM;	
					}							
					break;
					case countENUM://COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT 
					//acceptText = true;
					count.drawScreen(window, timerTextPtr->getText());
					countingSprites.drawSprites(window, -1);							
					bannerTextPtr->setTextString("How Many?");
					bannerTextPtr->centerTextOriginOnSprite(bannerSpritePtr->getSprite(), 0, -20);
					playerTextPtr->centerTextOriginOnSprite(bannerSpritePtr->getSprite(), 0, +11);
					window.draw(bannerSpritePtr->getSprite());
					window.draw(bannerTextPtr->getText());
					window.draw(playerTextPtr->getText());
					if (playerTextPtr->getTextString().size() < countingString.size()) {
						acceptText = true;
					} else acceptText = false;

					if (playerTextPtr->getText().getString() == countingString) {
						playerTextPtr->setTextString("");
						minigameSprites.updateIndividualTexture(countENUM, "completedMinigameSprite.png");
						minigameSprites.setSpriteToComplete(countENUM);
						gameScreensENUM = mainENUM;
					}
					break;
					case assembleENUM://ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE 
					if (validSpriteClick(event, solutionButtonPtr->getSprite().getGlobalBounds(), translatedMousePosition) == true)
						validMouseClick = true;
					
					if (!solutionButtonPtr->getSprite().getGlobalBounds().contains(translatedMousePosition) || !sf::Mouse::isButtonPressed(sf::Mouse::Left))
						validMouseClick = false;
					if (validMouseClick) assembleScreen = 2;
					else assembleScreen = 1;

					switch (assembleScreen) {
						case 1:
						assembleGameScreen.drawScreen(window, timerTextPtr->getText());
						for (int i = 0; i < assemblePartsSpriteVector.size(); i++) {
							if (i != 4 && !assembleDataSpriteVector.getSingleSprite(i).getIsComplete()) {
								assembleDataSpriteVector.setCanMove(i, event, translatedMousePosition);
								if (assembleDataSpriteVector.getSingleSprite(i).getCanMove()) {
									assembleDataSpriteVector.setSpritePosition(i, translatedMousePosition);
									mouseContactIndex = i;
									if (assemblePartsGoals[i].getGlobalBounds().contains(translatedMousePosition)) {
										assembleDataSpriteVector.getSingleSprite(i).setToComplete();
										assembleDataSpriteVector.setSpritePosition(i,assembleGoalPositions[i]);
										assembleDataSpriteVector.setSpriteToComplete(i);
									}
								} else mouseContactIndex = -1;																				
							}
						}
						if (!assembleDataSpriteVector.getVectorComplete())
							assembleDataSpriteVector.checkForCompletion();
						else {
							minigameSprites.updateIndividualTexture(assembleENUM, "completedMinigameSprite.png");
							minigameSprites.setSpriteToComplete(assembleENUM);
							gameScreensENUM = mainENUM;
						}
						assembleDataSpriteVector.drawSprites(window, 4);
						break;
						case 2:
						assembleSolution.drawScreen(window, timerTextPtr->getText());
						break;
					}

					break;
					case discussENUM://DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS 

					//check that ignore timer is stoping, pausing, restarting etc

						if (discussTime == 0) discussTime = gameTimerPtr->getTimeRemaining();
						npcText.charToShowIncrementor(discussTimePtr,gameTimerPtr->getTimeRemaining(), discussSpeedPtr, textBlockersVector);
						if (gameTimerPtr->handleMinigamePace(discussTime, *discussSpeedPtr)) {
							if (charToShow <= textBlockersVector.size()) discussTime = gameTimerPtr->getTimeRemaining();
							else discussTime = 0;

							blockerFill = npcText.handleColor(blockerFill, redInc, blueInc, greenInc);
						}
						for (int i = 0; i < textBlockersVector.size(); i++){
							textBlockersVector[i].setOutlineColor(blockerFill);
						}

						discuss.drawScreen(window, timerTextPtr->getText());
						window.draw(npcText.getText());
						npcText.drawTextBlockers(textBlockersVector, window);
						window.draw(discussBannerSprite.getSprite());
						window.draw(leftAnswer.getText());
						window.draw(rightAnswer.getText());

						if (validSpriteClick(event, leftAnswer.getText().getGlobalBounds(), translatedMousePosition) == true 
							|| validSpriteClick(event, rightAnswer.getText().getGlobalBounds(), translatedMousePosition) == true) {
							questionNumber++;
							event.type = sf::Event::EventType::MouseButtonReleased;
							switch (questionNumber) {
								case 2:
									npcText.updateNextQuestion(question2, window, questionY);

									leftAnswer.setString_Origin_Position(response2A, sf::Vector2f(discussBannerSprite.getSprite().getPosition().x - discussBannerSprite.getSprite().getGlobalBounds().width * 0.25
										, discussBannerSprite.getSprite().getPosition().y));
									rightAnswer.setString_Origin_Position(response2B, sf::Vector2f(discussBannerSprite.getSprite().getPosition().x + discussBannerSprite.getSprite().getGlobalBounds().width * 0.25
										, discussBannerSprite.getSprite().getPosition().y));
									textBlockersVector = npcText.resetTextBlockers(textBlockersVector);
								break;
								case 3:
									npcText.updateNextQuestion(question3, window, questionY);
									leftAnswer.setString_Origin_Position(response3A, sf::Vector2f(discussBannerSprite.getSprite().getPosition().x - discussBannerSprite.getSprite().getGlobalBounds().width * 0.25
										, discussBannerSprite.getSprite().getPosition().y));
									rightAnswer.setString_Origin_Position(response3B, sf::Vector2f(discussBannerSprite.getSprite().getPosition().x + discussBannerSprite.getSprite().getGlobalBounds().width * 0.25
										, discussBannerSprite.getSprite().getPosition().y));
									textBlockersVector = npcText.resetTextBlockers(textBlockersVector);
								break;
								case 4:
									npcText.updateNextQuestion(question4, window, questionY);
									leftAnswer.setString_Origin_Position(response4A, sf::Vector2f(discussBannerSprite.getSprite().getPosition().x - discussBannerSprite.getSprite().getGlobalBounds().width * 0.25
										, discussBannerSprite.getSprite().getPosition().y));
									rightAnswer.setString_Origin_Position(response4B, sf::Vector2f(discussBannerSprite.getSprite().getPosition().x + discussBannerSprite.getSprite().getGlobalBounds().width * 0.25
										, discussBannerSprite.getSprite().getPosition().y));
									textBlockersVector = npcText.resetTextBlockers(textBlockersVector);
								break;
							}
						}
						
						if (questionNumber == 5) {
							minigameSprites.updateIndividualTexture(discussENUM, "completedMinigameSprite.png");
							minigameSprites.setSpriteToComplete(discussENUM);
							gameScreensENUM = mainENUM;
						}
					break;
					case ignoreENUM://IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE 
						//Sound not stopping when pressing pause
						if (beepCountdown > gameTimerPtr->getTimeRemaining()) {
							ignoreBeep.play();
							beepCountdown = gameTimerPtr->getTimeRemaining() - randomInt(1, 10);
						}

						//win condition and result
						if (currentPrompt == ignorePromptVectors.size() && currentQuestion >= ignoreQuestions.size()) {
							minigameSprites.updateIndividualTexture(ignoreENUM, "completedMinigameSprite.png");
							minigameSprites.setSpriteToComplete(ignoreENUM);
							gameScreensENUM = mainENUM;
							break;
						}

						switch (ignoreScreen) {
						case 1:
							//timer for the prompt screen
							if (ignoreTimerPtr->getTimeRemaining() > 0.02) {
								tipTextPtr->setString_Origin_Position("Time Left: " + ignoreTimerPtr->getString(out), sf::Vector2f(window.getSize().x / 2, 425));
								ignoreTimerPtr = ignoreTimerPtr->manageGameTimer(ignoreTimerClock, ignoreTimerPtr);
							} else { 
								ignoreScreen = 2;
								tipTextPtr->setString_Origin_Position(ignoreQuestions[currentQuestion], sf::Vector2f(window.getSize().x / 2, 95));
							}

							if (validSpriteClick(event, questionButtonPtr->getSprite().getGlobalBounds(), translatedMousePosition) == true) {
								ignoreScreen = 2;
								tipTextPtr->setString_Origin_Position(ignoreQuestions[currentQuestion], sf::Vector2f(window.getSize().x / 2, 95));
								ignoreTimerPtr = ignoreTimerPtr->pause(ignoreTimerClock, ignoreTimerPtr);
							}

							ignorePromptScreen.drawScreen(window, timerTextPtr->getText());
							window.draw(ignorePromptTextPtr->getText());
							window.draw(tipTextPtr->getText());
							event.type = sf::Event::EventType::MouseButtonReleased;
							break;
						case 2:		
							if (playerTextPtr->getTextString().size() <= ignoreKeys[currentKey].size() - 1) {
								acceptText = true;
							} else {
								acceptText = false;
							}
										
							if (validSpriteClick(event, skipButtonPtr->getSprite().getGlobalBounds(), translatedMousePosition) == true || playerTextPtr->getTextString() == ignoreKeys[currentKey]) {
								//for the last prompt,  should it progress even if the answer is wrong?
								ignoreScreen = 1;
								ignorePromptTextPtr->setTextString("");
								playerTextPtr->setTextString("");
								currentKey++;
								currentQuestion++;
								currentPrompt++;
								if (currentPrompt < ignorePromptVectors.size()) {
									ignorePromptTextPtr = loadPrompt("", tempText, ignorePromptVectors[currentPrompt], ignorePromptTextPtr, window);
								}
								ignoreTimerPtr->resetTimer();
								ignoreTimerClock.restart();
							}

							if (validSpriteClick(event, gobackButtonPtr->getSprite().getGlobalBounds(), translatedMousePosition) == true && ignoreTimerPtr->getTimeRemaining() > 0.02) {
								ignoreScreen = 1;
								ignoreTimerClock.restart();								
							}

							ignoreQuestionScreen.drawScreen(window, timerTextPtr->getText());
							window.draw(bannerSpritePtr->getSprite());
							playerTextPtr->centerTextOriginOnSprite(bannerSpritePtr->getSprite(), 0, +5);//where can this be put so it isn't always being called
							window.draw(playerTextPtr->getText());
							window.draw(tipTextPtr->getText());
							event.type = sf::Event::EventType::MouseButtonReleased;
							break;
						}
					break;
					case acceptENUM://ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT
						//need to make a spriteVector for the acceptSprites
						//need to make wallSprite class for the maze? rect?
						//broad and narrow collision detection: only check for detection if actually close enough
						//create sf::Rect for walls? create a sf::lineStrip?
						//get the stutter out of the player movement when contacting a wall
						player.setSpriteRadiusCirclePosition(player.getSprite().getPosition());
						window.draw(triangle);
						window.draw(line, 2, sf::Lines);						
						//window.draw(gsPtr->getSprite());
						player.setMovement(window);
						player.setCollision(wallSpritePtr->getSprite());
						player.handleCollision(wallSpritePtr->getSprite());

						window.draw(wallSpritePtr->getSprite());
						if (!player.getCollision()) window.draw(player.getSprite());
						drive.drawScreen(window, timerTextPtr->getText());
					break;
					case retainENUM://RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN 
						retain.drawScreen(window, timerTextPtr->getText());
					break;
					case pushENUM://PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH 
						push.drawScreen(window, timerTextPtr->getText());
					break;
					case bonusENUM://BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS 
						bonus.drawScreen(window, timerTextPtr->getText());
					break;
				}
			}else{//TIME IS UP
				gameTimerPtr = gameTimerPtr->timeUp(gameTimerPtr);
				timerTextPtr->getText().setString("Time Up!");
				startScreen.setAndCenterTitle("GAME OVER!");
				player.setPosition(getCenterOfWindow(window));
				mainScreensENUM = startMAIN;
				gameScreensENUM = mainENUM;
			}
			break;

			case resumeMAIN://RESUME			
			assert(gameTimerPtr->getTimeRemaining() > 0);
			if (validSpriteClick(event, resumeButtonPtr->getSprite().getGlobalBounds(), translatedMousePosition) == true) {
				gameTimerClock.restart();
				ignoreTimerClock.restart();
				mainScreensENUM = gameMAIN;					
			} else resumeScreen.drawScreen(window, timerTextPtr->getText());
			event.type = sf::Event::EventType::MouseButtonReleased;//this stops clicking through sprites
			break;
		}		
	}
}