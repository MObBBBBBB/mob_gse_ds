#include<iostream>
#include<vector>

using namespace std;

// 求前缀数组，指示匹配时子串的移动
vector<int> prefix(const string& p)
{
    int n = p.size();
    vector<int> next(n + 1);
    for (int i = 0, j = next[0] = -1; i < n; next[++i] = ++j)
        while (~j && p[i] != p[j]) j = next[j];
    return next;
}

// 优化的前缀数组，需借助原前缀数组求，防止最坏情况kmp退化为暴力
// vector<int> prefix_nextval(const string& p)
// {
//     vector<int> next = prefix(p);
//     vector<int> nextval(next.size());
//     nextval[0] = -1, nextval[1] = 0; 
//     for (int i = 2; i < next.size(); ++i)
//     {
//         if (p[next[i]] == p[i]) nextval[i] = nextval[next[i]];
//         else nextval[i] = next[i];
//     }
//     return nextval;
// }

// 子串匹配，返回所有匹配位置
vector<int> kmp(const string& t, const string& p)
{
    int n = p.size(), m = t.size();
    auto next = prefix(p);
    // auto nextval = prefix_nextval(p);
    vector<int> res;
    for (int i = 0, j = 0; i < m; ++i)
    {
        while (j > 0 && p[j] != t[i]) j = next[j];
        if (p[j] == t[i]) j++;
        if (j == n)
        {
            res.push_back(i - j + 1);
            j = next[j];
        }
    }
    return res;
}

int main()
{
    string t, p;
    getline(cin, t); getline(cin, p);
    auto res = kmp(t, p);
    for (auto x : res) cout << x << ' ';
    cout << endl;
    return 0;
}