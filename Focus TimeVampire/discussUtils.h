#pragma once

sf::Color blockerFill(0,0,0);
sf::Color blockerBorder(0,0,0);
vector <sf::RectangleShape> textBlockersVector; 
float discussTime = 0, discussSpeed = 0.01;
float questionY = 200;
int charToShow = 0;
int red = 0, blue = 0, green = 0;
int redInc = 1, blueInc = 5, greenInc = 3;
int questionNumber = 1;
string question1 = "How many minigames are there?", response1A = "123456", response1B = "9879879879";
string question2 = "Are they too easy?", response2A = "Yes", response2B = "True";
string question3 = "Thank you for giving them a try!", response3A = "What?", response3B = "You're welcome!";
string question4 = "I hope you find the secret ending…", response4A = "Me too!", response4B = "After lunch.";
