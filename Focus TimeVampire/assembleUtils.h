#pragma once
int assembleScreen = 1;

sf::Vector2f resistorGoal (296, 313);
sf::Vector2f capacitorGoal (341, 228);
sf::Vector2f microchipGoal (266, 270);
sf::Vector2f diodeGoal (256, 313);
sf::Vector2f pcbGoal (-50,-50);
sf::Vector2f heatsinkGoal (307, 202);
sf::Vector2f usbPortGoal (202, 329);
sf::Vector2f relayGoal (239, 185);
sf::Vector2f jackGoal (144, 214);
vector <sf::Vector2f> assembleGoalPositions {resistorGoal, capacitorGoal, microchipGoal, diodeGoal, pcbGoal, heatsinkGoal, usbPortGoal, relayGoal, jackGoal};

sf::RectangleShape assembleGoal(sf::Vector2f(20, 20));
vector <sf::RectangleShape> assemblePartsGoals;

DataSprite resistorSprite("resistorSprite.png", 0.02, 0.02);
DataSprite capacitorSprite("capacitorSprite.png", 0.015, 0.015);
DataSprite microchipSprite("microchipSprite.png", 0.02, 0.02);
DataSprite diodeSprite("diodeSprite.png", 0.04, 0.04);
DataSprite pcbSprite("pcbSprite.png", 1, 1);
DataSprite heatsinkSprite("heatsinkSprite.png", 0.02, 0.02);
DataSprite usbPortSprite("usbPortSprite.png", 0.15, 0.15);
DataSprite relaySprite("relaySprite.png", 0.024, 0.024);
DataSprite jackSprite("jackSprite.png", 0.08, 0.08);
vector <DataSprite> assemblePartsSpriteVector{ resistorSprite, capacitorSprite, microchipSprite, diodeSprite, pcbSprite, heatsinkSprite, usbPortSprite, relaySprite, jackSprite };

DataSpriteVector assembleDataSpriteVector;
GameSprite pcbSolvedSprite("pcbSolvedSprite.png", 0.75, 0.75);