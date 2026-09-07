// 中缀表达式求值

#include<iostream>
#include<stack>
#include<unordered_map>
#include<cmath>

using namespace std;

stack<char> sym;
stack<int> num;
unordered_map<char, int> pr = {{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'^', 3}};  // 定义二元运算符优先级；添加运算符时还需处理其运算规则和结合性；也需要在cal中注册运算。

void cal()
{
    int b = num.top(); num.pop();
    int a = num.top(); num.pop();
    char c = sym.top(); sym.pop();

    int x;
    if (c == '+') x = a + b;
    else if (c == '-') x = a - b;
    else if (c == '*') x = a * b;
    else if (c == '/') x = a / b;
    else if (c == '^') x = pow(a, b);

    num.push(x);
}

int main()
{
    string ex;
    cin >> ex;
    
    for (int i = 0; i < ex.size(); ++i)
    {
        char c = ex[i];
        if (isdigit(c))  // 存入数字
        {
            int x = 0;
            while (i < ex.size() && isdigit(ex[i]))
                x = x * 10 + ex[i++] - '0';
            i--;
            num.push(x);
        }
        else if (c == '(') sym.push(c);
        else if (c == ')')  // 遇到右括号，直接计算
        {
            while (sym.top() != '(') cal();
            sym.pop();
        }
        else
        {
            // 判断优先级，优先级大的先算
            // while (!sym.empty() && (pr[sym.top()] > pr[c]))
            // 防止左括号索引优先级字典错误，和连续出现乘方符号导致错误
            while (!sym.empty() && sym.top() != '(' && (pr[sym.top()] > pr[c] || (pr[sym.top()] == pr[c] && c != '^'))) cal();
            sym.push(c);
        }
    }
    while (!sym.empty()) cal();

    cout << num.top() << endl;

	return 0;
}

/*

input:
(2+2)*(1+1)
(3*9+2/4)*12
2^3*2+9*1*(5/3+2)

output:
8
324
43

*/