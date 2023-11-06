#include <iostream>
#include <stack>

using namespace std;

class Solution
{
public:
    string infixToPostfix(string infix)
    {
        stack<char> operators;
        string postFix = "";
        for (int i = 0; i < infix.length(); i++)
        {
            if (infix[i] == '(')
                operators.push(infix[i]);
            else if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/' || infix[i] == ')')
            {
                while (!operators.empty() && operators.top() != '(' && precedence(infix[i]) <= precedence(operators.top()))
                {
                    postFix += operators.top();
                    operators.pop();
                }

                if (infix[i] == ')')
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
                postFix += infix[i];
            }
        }
        while (!operators.empty())
        {
            postFix += operators.top();
            operators.pop();
        }

        return postFix;
    }

    int postFixSol(string postFix)
    {
        stack<int> numbers;
        int result = 0;
        for (int i = 0; i < postFix.length(); i++)
        {
            if (postFix[i] >= '0' && postFix[i] <= '9')
            {
                int num = postFix[i] - '0';
                numbers.push(num);
            }
            else if (postFix[i] == '+' || postFix[i] == '-' || postFix[i] == '*' || postFix[i] == '/')
            {
                int top = numbers.top();
                numbers.pop();
                int top1 = numbers.top();
                numbers.pop();
                result = operations(postFix[i], top1, top);
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
    string postFix = solution.infixToPostfix("5*(6+2)/4");
}