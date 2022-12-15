using std::cout;
using std::stringstream;
using std::string;
using std::setprecision;
using std::vector;

enum mainScreens { startMAIN, gameMAIN, resumeMAIN };
enum gameScreens { rememberENUM, countENUM, assembleENUM, discussENUM, ignoreENUM, driveENUM, retainENUM, pushENUM, bonusENUM, mainENUM };
mainScreens mainScreenENUM = startMAIN;
gameScreens gameScreenENUM = mainENUM;