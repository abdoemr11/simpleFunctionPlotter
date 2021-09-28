#ifndef INPUT_HANDLER
#define INPUT_HANDLER
#include "mathParser/mathParser.h"
class InputHandler
{

public:
    InputHandler(/* args */);
    //~InputHandler();
    void validateExpr(std::string expr);
    std::vector<std::pair<int,int>> getPoints(std::string);
    
private:
    void fillValues(Operation *op);
    //void fillValues(Operation *op, double t);
    std::string replaceVars(const Operation *op);

    //variables
    Parser mathParser;
    int *values;
    std::vector<std::pair<int,int>> points;
    int min, max;
    //used to determine the step 
    int step;
    int size;
};

#endif