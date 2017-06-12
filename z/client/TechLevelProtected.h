#ifndef Z_TECHLEVELPROTECTED_H
#define Z_TECHLEVELPROTECTED_H


#include <mutex>

class TechLevelProtected {
private:
    std::mutex mut;
    int techLevel;

public:
    TechLevelProtected(int techL);
    void setTechLevel(int newLevel);
    int getTechLevel();

};


#endif //Z_TECHLEVELPROTECTED_H
