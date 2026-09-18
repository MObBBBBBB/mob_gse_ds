#include<iostream>
#include<vector>
#include<string>

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

// nextval 跳过必然重复失败的比较；普通 next 版 KMP 已具有 O(n+m) 时间复杂度。
vector<int> prefix_nextval(const string& p)
{
    int n = p.size();
    vector<int> next = prefix(p);
    vector<int> nextval = next;
    // 从下标 1 开始优化；nextval[0] 保持为 -1。
    for (int j = 1; j < n; ++j)
    {
        if (p[j] == p[next[j]]) nextval[j] = nextval[next[j]];
    }
    // nextval[n] 保留 next[n]，用于完整匹配后继续寻找重叠匹配。
    return nextval;
}

// 子串匹配，返回所有匹配位置（下标从 0 开始）。
vector<int> kmp(const string& t, const string& p)
{
    int n = p.size(), m = t.size();
    vector<int> res;
    // 空模式串匹配主串的所有边界位置。
    if (n == 0)
    {
        for (int i = 0; i <= m; ++i) res.push_back(i);
        return res;
    }
    // 下列两行二选一，后续匹配代码完全相同。
    auto next = prefix_nextval(p);
    // auto next = prefix(p);
    for (int i = 0, j = 0; i < m; ++i)
    {
        while (j >= 0 && p[j] != t[i]) j = next[j];
        ++j; // 匹配成功时前进；退到 -1 时恢复为 0，并跳过当前主串字符。
        if (j == n)
        {
            res.push_back(i - j + 1);
            j = next[n]; // 两种数组的第 n 项相同，均为普通 next[n]。
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
