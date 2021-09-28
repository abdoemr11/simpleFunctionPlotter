#include"inputHandler.h"
using namespace std;
InputHandler::InputHandler()
{
    //!!!!!!!!!!!!!!!!!!!!may raise an error
    size = 50;
    max = 10;
    min = -10;

    step = (max*1.0 -min)/size;
    if(step < 1)
        step = 1;
    cout << step;
    step = int(round(step));
    values = new int[size+size+1];

}
/****************************************************************
 * fillValues:
 * changed the container from int[] to vector<pair<x,y>> to make
 * it easy to convert QList<QPoint>
 *****************************************************************/
void InputHandler::fillValues(Operation *op)
{
    cout << "Minimum is "<<min;
		points.clear();
    for(int i = 0; i < size+size+1; i++)
    {
        // Give each variable a value
        int x = min + (i * step);
        for(int j = 0; j < op->v_values.size(); j++) 
        {
            op->v_values[j] = x;
        }
        // EQUATION
        
        std::string postfix_replaced = replaceVars(op);
        double value = mathParser.Solve(postfix_replaced);
        points.emplace_back(make_pair(x,int(round(value))));
        /// EQUATION
        //value = value/step;
        //values[i] = int(round(value));
    }
}
std::string InputHandler::replaceVars(const Operation *op) {
    std::ostringstream output;
    int offset = 0;
    for(int p = 0; p < op->v_pos.size(); p++) {
        // Add rest of postfix expression from last replaced var
        for(int i = offset; i < op->v_pos[p]; i++) {
            output << op->postfix[i];
        }
        output << op->v_values[p];
        offset = op->v_pos[p]+1;
    }
    // Add the rest of the string if not added
    for(int p = offset; p < op->postfix.length(); p++) {
        output << op->postfix[p];
    }
    return output.str();
}
/****************************************************************
 * getPoints: v1
 * export Points to be drawn
 *****************************************************************/
std::vector<std::pair<int,int>> InputHandler::getPoints(std::string expr)
{
    Operation *op = mathParser.toPostfix(expr);
    //cout << op->postfix;
    fillValues(op);
    return points;
}
