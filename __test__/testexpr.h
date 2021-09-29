#ifndef	TEST_EXPR_H 
#define	TEST_EXPR_H 
struct ExprToPlot
{
	std::string expr;
	int min;
	int max;	
}; 
std::vector<ExprToPlot> exprToPlog 
{
	{"x^2+5", -10, 10},
	{"x^3", -10, 10},
	{"x^2+5", 10, +10},
	{"x", 10, 10},
	{"y^2+5", -10, 10},
	{" ", -10, 10},
	{"", -10, 10},
	{"sinx", -10, 10},
	{"(x+2)^2+5", -10, 10}
};
#endif
