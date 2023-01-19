#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

#include <iostream>
#include <cmath>
#include <iomanip>
#include <cassert>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <random>
#include <time.h>

using std::cout;
using std::stringstream;
using std::string;
using std::setprecision;
using std::vector;
using std::srand;
using std::rand;
using std::time;
using std::random_device;

enum mainScreens { startMAIN, gameMAIN, resumeMAIN };
enum gameScreens { rememberENUM, countENUM, assembleENUM, discussENUM, ignoreENUM, driveENUM, retainENUM, pushENUM, bonusENUM, mainENUM };
mainScreens mainScreenENUM = startMAIN;
gameScreens gameScreenENUM = mainENUM;