#include <iostream>
#include <stack>

using namespace std;

class Solution
{
public:
    string infixToPrefix(string infix)
    {
        // Testcase
        //"5*(6+2)/4" --> "/*5+624"

        stack<char> operators;
        string preFix = "";
        for (int i = infix.length() - 1; i >= 0; i--)
        {
            if (infix[i] == ')')
                operators.push(infix[i]);
            else if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/' || infix[i] == '(')
            {
                while (!operators.empty() && operators.top() != ')' && precedence(infix[i]) < precedence(operators.top()))
                {
                    preFix = operators.top() + preFix;
                    operators.pop();
                }

                if (infix[i] == '(')
                {
                    operators.pop();
                }
                else
                {
                    operators.push(infix[i]);
                }
            }
            else
            {
                preFix = infix[i] + preFix;
            }
        }
        while (!operators.empty())
        {
            preFix = operators.top() + preFix;
            operators.pop();
        }

        return preFix;
    }

    int preFixSol(string preFix)
    {
        stack<int> numbers;
        int result = 0;
        for (int i = preFix.length() - 1; i >= 0; i--)
        {
            if (preFix[i] >= '0' && preFix[i] <= '9')
            {
                int num = preFix[i] - '0';
                numbers.push(num);
            }
            else if (preFix[i] == '+' || preFix[i] == '-' || preFix[i] == '*' || preFix[i] == '/')
            {
                int top = numbers.top();
                numbers.pop();
                int top1 = numbers.top();
                numbers.pop();
                result = operations(preFix[i], top, top1);
                numbers.push(result);
            }
        }
        return result;
    }

private:
    int precedence(char op)
    {
        if (op == '+' || op == '-')
            return 1;
        else if (op == '*' || op == '/')
            return 2;
        return 0;
    }
    int operations(char op, int top1, int top)
    {
        int result = 0;
        if (op == '+')
            result = top1 + top;
        else if (op == '-')
            result = top1 - top;
        else if (op == '*')
            result = top1 * top;
        else if (op == '/')
            result = top1 / top;
        return result;
    }
};

int main()
{
    Solution solution;
    string preFix = solution.infixToPrefix("(2+3)*4");
}