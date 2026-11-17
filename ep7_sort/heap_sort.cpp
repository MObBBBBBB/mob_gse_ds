typedef int Elemtype;

// 堆与堆排序
// 堆：一颗特殊的完全二叉树，满足所有父节点都大于（或小于）等于其所有孩子，称为大根堆（或小根堆）（后续都以大根堆为例）
// 堆排序：每次直接从堆顶取出元素排序，之后将这个元素排除再调堆，直到所有元素都取出，排序完成
// 时间复杂度：建堆O(n)（因为自底向上建堆时，大量靠近叶子的结点调整高度很小，所有结点的调整代价相加为O(n)，而不是每个结点都需要O(logn)）;
// 每次调堆O(logn)，堆排序复杂度O(nlogn)
// 空间复杂度：O(1)
// 不稳定排序

// 交换数组中两个元素的辅助函数，i和j是数组下标
void Swap(Elemtype heap[], int i, int j) {
    Elemtype tmp = heap[i];
    heap[i] = heap[j];
    heap[j] = tmp;
}

// 调堆函数：在左右子树均为大根堆的前提下，将以i为根的子树调整为大根堆
void Heapify(Elemtype heap[], int len, int i) {
    while (1) {
        // 两个孩子分别在2i+1和2i-1的位置上
        int child1 = 2 * i + 1;
        int child2 = 2 * i + 2;
        
        // 找到三者最大的一个
        int maxpos = i;
        if (child1 < len && heap[child1] > heap[maxpos]) maxpos = child1;
        if (child2 < len && heap[child2] > heap[maxpos]) maxpos = child2;

        // 如果最大的就是i自己，则不做调整；
        if (i == maxpos) break;

        // 如果不是，则i与三者有最大元素的孩子交换，之后迭代调整被交换位置的孩子的子树
        Swap(heap, i, maxpos);
        i = maxpos;
    }
}

// 建堆：将整个数组构建成堆，自底向上构建堆（利用调堆函数的特性）
void BuildHeap(Elemtype heap[], int len) {
    // 由于完全二叉树的特性，i > len/2-1 的位置都是叶子结点，所以从 i = len/2 - 1 的位置自底向上构建堆即可
    for (int i = len/2 - 1; i >= 0; i--) Heapify(heap, len, i);
}

// 堆排序
void HeapSort(Elemtype heap[], int len) {
    // 先建堆
    BuildHeap(heap, len);
    
    // 之后每次都将堆中最大元素（堆顶）与数组末尾元素换位；
    // 这样当前序列最大元素都被排在了当前序列的末尾，之后缩短序列长度（这里的i用于控制要处理的序列长度）；
    // 之后从堆顶自顶向下调堆（其余部分在交换前已经是堆，满足调堆函数的特性）；不断循环，直到所有元素都被选出。
    for (int i = len - 1; i > 0; i--) {
        Swap(heap, 0, i);
        Heapify(heap, i, 0);
    }
}