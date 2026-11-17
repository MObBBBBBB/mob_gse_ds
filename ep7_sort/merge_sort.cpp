typedef int Elemtype;
#define MAX_SIZE 100

// 归并排序
// 将序列递归对半切分，直到不能再切分，再两两比较归并，最终排序完成
// 时间复杂度：每一层归并——所有子序列合计处理n个元素，归并总层数O(logn)，总体排序O(nlogn)
// 空间复杂度：O(n)的辅助数组以及O(logn)的递归栈，总体O(n)
// 稳定排序

// 辅助数组：用来暂存每次归并排序的中间结果（实际上这里开到len大小即可，这里只是为了省事，实际需结合题目开合适的大小）
int tmp[MAX_SIZE];

// 与快排的low和high一样
void MergeSort(Elemtype a[], int low, int high) {
    // 递归
    // 递归出口
    if (low >= high) return;
    // 每次从序列中间切分序列，递归切分，直到达到上面的递归出口——也就是切分到每个子序列只剩一个元素
    int mid = (low + high) / 2;
    // 先递归调用，这样可以先处理左右子区间，后处理当前区间
    MergeSort(a, low, mid);
    MergeSort(a, mid + 1, high);

    // 合并
    // 以mid为界限，划分为两个序列；两两比较两个序列中的数，每次挑出较小的一个放入辅助数组tmp中
    int k = 0, l = low, h = mid + 1;
    while (l <= mid && h <= high) {
        if (a[l] <= a[h]) tmp[k++] = a[l++];
        else tmp[k++] = a[h++];
    }
    // 上面的循环会在某一个序列被全部放到tmp中时终止；
    // 另外一个序列可能还有元素未被处理，剩余元素一定大于等于之前的元素，直接全部顺序放到tmp的后面即可
    // 这两个循环只有一个会执行
    while (l <= mid) tmp[k++] = a[l++];
    while (h <= high) tmp[k++] = a[h++];

    // 将tmp中暂存的序列放回原序列中
    for (l = low, h = 0; l <= high; l++, h++) a[l] = tmp[h];
}