#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>

#define NO_FONT_LOADED throw std::exception("Failed to load font");
#define NO_SUCH_TURRET throw exception("Exception: turret does not exist");
#define FIRE_DOES_NOT_EXIST throw exception("WeaponFire does not exist");
#define POINT_OUT_OF_MAP(x, y) throw exception((string("Exception: Given point is out of map: ") + to_string(x) + "," + to_string(y)).c_str());
#define FAILED_TO_LOAD_GAME throw exception("Exception: Failed to load game");
#define NO_MINION_EXCEPTION throw exception("Exception: No such minion");
#define WAVE_DOES_NOT_EXIST throw std::exception("Exception: no such wave exists");
#define OBJ_ID_OVERFLOW(x) throw std::exception(("Exception: Object identificator overflow: " + std::to_string(x)).c_str());
#define UNSIGNED_INTEGER_TO_SMALL throw std::exception("Exception: Unsigned integer is too small for textures");
#define TEXTURE_LOADING_FAILIURE(x) throw std::exception(("Exception: Failed to load texture:\n\t" + std::string(x)).c_str());
#define TEXTURE_DOES_NOT_EXISIT throw std::exception("Exception: Failed to get a texture");


#endif