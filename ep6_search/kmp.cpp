// 字符串模式匹配——kmp算法
// 假设母串s长度为n，子串t长度为m
// 时间复杂度O(n+m)，空间复杂度O(m)（若计入记录全部匹配位置的res数组，总空间为O(n+m)）
// 母串指针不往回走，子串指针根据next数组进行跳转

// 函数签名
void GetNext(char t[], int tlen, int next[]);
void GetNextval(char t[], int tlen, int next[]);
void kmp(char s[], char t[], int slen, int tlen, int res[]);

// 根据子串t求next数组，用于在模式匹配时指示子串t的指针的跳转
// 本质上是在计算每一个字符位置前的部分串的最长公共真前后缀长度
// next[j] 可以理解为上面这句话，也可以理解为往回跳的位置，这个位置是下一次要比较的位置
void GetNext(char t[], int tlen, int next[]) {
    // 初始化
    // i指针之前的子串已经计算好跳转位置，i只向前走不回退
    // j用于计算每一个位置的next
    // next[0]初始化为-1，代表完全没有匹配的片段；不采用牺牲0位置的哨兵设计
    int j = -1, i = 0;
    next[0] = -1;

    // 这里i需要在tlen位置再做一次计算，用于匹配多个可能的位置；
    // 如果只匹配遇到的第一个子串，则不需要在tlen位置做计算，改成tlen-1即可。
    // 同时为了匹配多个子串，传入next数组的时候，next数组的长度要是tlen+1；
    // 只匹配遇到的第一个子串则是tlen。
    while (i < tlen) {
        // 计算时相当于一直在利用之前计算完成的结果
        // 具体过程不方便写成注释，自行手动模拟一次结合最长公共真前后缀就理解了
        if (j == -1 || t[i] == t[j]) {
            i++;
            j++;
            next[i] = j;
        }
        else j = next[j];
    }
}

void GetNextval(char t[], int tlen, int nextval[]) {
    int j = -1, i = 0;
    nextval[0] = -1;

    // 这里采用不提前算next，而是边算next边算nextval
    // 也可以先创建next，再利用下面的核心语句扫描next创建nextval
    while (i < tlen) {
        if (j == -1 || t[i] == t[j]) {
            i++;
            j++;
            nextval[i] = j;
            // 整体代码结构与计算next类似，只是多了下面这句
            // 如果失配之后的跳转位置的字符与当前位置字符一样，直接采用跳转后位置的跳转位置；
            // 如果不一样，则保留自己的跳转位置
            // 另外多补充一个i<tlen的判断，用于防止传入的是字符数组而不是字符串，字符数组结尾缺'\0'字符，可能会解引用失败
            if (i < tlen && t[i] == t[nextval[i]]) nextval[i] = nextval[nextval[i]];
        }
        else j = nextval[j];
    }
}

void kmp(char s[], char t[], int slen, int tlen, int res[]) {
    // 初始化结果数组，用于存储多个匹配结果，字符对应位置标记为1则代表从这个位置匹配到了子串
    for (int i = 0; i < slen; i++)
        res[i] = 0;

    // 计算next数组
    // 注意这里的next的长度，上面求next数组部分有解释
    int next[tlen+1];
    GetNext(t, tlen, next);
    // 如果使用nextval数组，就用下面这句
    // GetNextval(t, tlen, next);

    // 模式匹配
    // 其实kmp匹配和计算next数组的基本逻辑是一样的
    // 只是一个是t匹配s，另一个是t匹配t

    // GetNext从j=-1开始，是为了初始化next[1]=0
    // KMP匹配则从i=0、j=0开始，比较两个串的首字符
    int i = 0, j = 0;
    while (i < slen) {
        if (j == -1 || s[i] == t[j]) {
            i++;
            j++;
        }
        else j = next[j];
        // 当j等于tlen时，代表整个串都被匹配了，代表匹配成功，此时需要在res中记录结果
        // 然后利用next[tlen]指示j进行跳转：这样可以保证前面匹配过的依然成立，不用回退i指针
        if (j == tlen) {
            res[i-j] = 1;
            j = next[j];
        }
    }
}


// 暴力模式匹配，时间复杂度O(nm)
// void PatternMatching(char s[], char t[], int slen, int tlen, int res[]) {
//     for (int i = 0; i < slen; i++)
//         res[i] = 0;

//     int i = 0;
//     while (i <= slen - tlen) {
//         int j = 0;
//         while (j < tlen && s[i] == t[j]) {
//             i++;
//             j++;
//         }
//         if (j == tlen) res[i-j] = 1;
//         i = i - j + 1;
//     }
// }