#ifndef GENMAP_JSONHANDLER_H
#define GENMAP_JSONHANDLER_H


#include <vector>

class JsonHandler {

public:
    JsonHandler();
    void toJson(std::vector<int> descriptorVector);
    std::vector<int> jsonToMap();

};


#endif //GENMAP_JSONHANDLER_H
