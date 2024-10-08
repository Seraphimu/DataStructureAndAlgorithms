#include "Array.hpp"

void Array::ArrayInit() {
    memset(A, 0, sizeof(A));
    Size = 0;
}

//尾插
void Array::ArrayPushBack(DataType X) {
    //表满：
    ArrayInsertThisPos(Size, X);

    // 同头插，用ArrayInsertThisPos()方法来代替
    // A[Size] = X;
    // Size++;
}

//头插
void Array::ArrayPushFront(DataType X) {
    ArrayInsertThisPos(0, X);

    //直接用ArrayInsertThisPos()方法来指定插入的位置，然后直接搞定
    // int i;
    // //所有元素后移一位，把首位空出来
    // //这里应该使用自减符号，又写成递增，肌肉记忆啊……，我说程序怎么跑一会就爆了。
    // // for (i = Size; i > 0; i++) {
    // for (i = Size; i > 0; i--) {
    //     A[i] = A[i - 1];
    // }
    //此时i == 0
    // A[i] = X;
    // Size++;
}


void Array::ArrayInsertThisPos(int Pos, DataType X) {
    ArrayIsFull();
    ArrayPosInsertErr(Pos);

    int i;
    for (i = Size; i > Pos; i--) {
        A[i] = A[i - 1];
    }
    A[Pos] = X;

    Size++;
}

void Array::ArrayInsertAfterPos(int Pos, DataType X) {
    //在Pos之后插入，等价于在Pos+1位置上插入
    ArrayInsertThisPos(Pos + 1, X);
}

void Array::ArrayInsertPrePos(int Pos, DataType X) {
    //在Pos之前插入，等价于在Pos - 1位置上插入
    ArrayInsertThisPos(Pos - 1, X);
}

void Array::ArrayDeleteThisPos(int Pos) {
    ArrayIsEmpty();
    ArrayPosErr(Pos);
    // 当Pos = Size时调用函数，确实会出现把最后一位删除的情况，但是这不符合预期，因为Size下标是末位的后一位，
    //看到把最后一位删除的效果仅仅是最后一步的Size--在发挥作用而已
    // ArrayPosInsertErr(Pos);

    //运行到这里说明当前的下标Pos可以进行删除操作
    //思路：把Pos + 1移动到Pos，然后依次类推，把Size - 1位移动到 Size - 2，然后Size--
    //最后一位数仍在内存中，但是不重要，方法已经不会给它被访问到的机会。
    int i;
    for (i = Pos; i < Size - 1; i++) {
        //从A[Pos] = A[Pos + 1]到A[Size - 2] = A[Size - 1]
        A[i] = A[i + 1];
    }
    Size--;
}

void Array::ArrayDeleteAfterPos(int Pos) {
    ArrayDeleteThisPos(Pos + 1);
}

void Array::ArrayDeletePrePos(int Pos) {
    ArrayDeleteThisPos(Pos - 1);
}

void Array::ArrayPopBack() {
    ArrayDeleteThisPos(Size - 1);
}

void Array::ArrayPopFront() {
    ArrayDeleteThisPos(0);
}


void Array::ArrayBubbleSort() {
    int i, j;
    for (i = 0; i < Size - 1; i++) {
        //遍历未排序区
        for (j = 0; j < Size - i - 1; j++) {
            if (A[j] > A[j + 1]) {
                Swap(A[j], A[j + 1]);
            }
        }
    }
}

void Array::ArraySelectionSort() {
    int i, j;
    int MinIndex;
    //遍历0到N
    for (i = 0; i < Size; i++) {
        //遍历i + 1到N，并找出下标i+1到N中的最小值
        MinIndex = i;
        for (j = i + 1; j < Size; j++) {
            if (A[MinIndex] > A[j]) {
                MinIndex = j;
            }
        }
        //把最小值交换到剩余序列的首位
        Swap(A[MinIndex], A[i]);
    }
}

int Array::Partition(DataType A[], int Low, int High) {
    // 选取第一个元素为枢轴
    int PivotKey = A[Low];
    while (Low < High) {
        // 从右向左扫描，找到第一个比枢轴元素小的
        // 本步操作是跳过那些比枢轴元素大的元素
        while (Low < High && A[High] >= PivotKey) {
            High--;
        }
        // 交换，此时枢轴元素是A[High]
        Swap(A[Low], A[High]);

        // 从左向右扫描，找到第一个比枢轴元素大的
        // 本步操作的作用是跳过那些比枢轴元素小的元素
        while (Low < High && A[Low] <= PivotKey) {
            Low++;
        }
        // 交换，此时枢轴元素是A[Low]
        Swap(A[Low], A[High]);
    }

    // 返回枢轴元素所在的位置
    // 此时返回Low和High都行，因为破坏循环的条件是Low == High
    return High;
}

void Array::QSort(DataType A[], int Low, int High) {
    // 做为枢轴使用
    int Pivot;
    // 若不满足该条件，就意味着一趟排序结束
    if (Low < High) {
        Pivot = Partition(A, Low, High);

        // 对左子表进行排序
        QSort(A, Low, Pivot - 1);
        // 对右子表进行排序
        QSort(A, Pivot + 1, High);
    }

}

void Array::ArrayQuicklySort() {
    Array::QSort(A, 0, Size - 1);
}

DataType Array::ArraySearchByPos(int Pos) {
    ArrayIsEmpty();
    ArrayPosErr(Pos);

    return A[Pos];
}

int Array::ArraySearchByValue(DataType X) {
    ArrayIsEmpty();
    int i;
    for (i = 0; i < Size; i++) {
        if (X == A[i]) {
            return i;
        }
    }
    
    //出循环就是没找到
    return -1;
}

DataType Array::ArrayFindMaxByLoop() {
    ArrayIsEmpty();
    int i;
    int MaxIndex = 0;
    for (i = 0; i < Size; i++) {
        if (A[MaxIndex] < A[i]) {
            MaxIndex = i;
        }
    }

    return A[MaxIndex];
}

DataType Array::ArrayFindMaxBySort() {
    //使用任意一种排序算法
    ArrayIsEmpty();
    ArrayQuicklySort();
    return A[Size - 1];
}

DataType Array::ArrayFindMinByLoop() {
    ArrayIsEmpty();
    int i;
    int MinIndex = 0;
    for (i = 0; i < Size; i++) {
        if (A[MinIndex] > A[i]) {
            MinIndex = i;
        }
    }

    return A[MinIndex];
}
DataType Array::ArrayFindMinBySort() {
    ArrayIsEmpty();
    ArrayQuicklySort();
    return A[0];
}

void Array::ArrayModifyByPos(int Pos, DataType X) {
    ArrayIsEmpty();
    ArrayPosErr(Pos);

    A[Pos] = X;
}

void Array::ArrayModifyByValue(DataType SourceX, DataType X) {
    int Pos = ArraySearchByValue(SourceX);

    A[Pos] = X;
}


void Array::Swap(int & a, int & b) {
    int Tmp = a;
    a = b;
    b = Tmp;
}

//打印
void Array::ArrayPrint() {
    int i;
    for (i = 0; i < Size; i++) {
        cout << A[i] << " ";
    }
    cout << endl;
}

//判断表是否满了
void Array::ArrayIsFull() {
    if (Size >= MAX) {
        cout << "Array Is Full!" << endl;
        exit(-1);
    }
    else {
        return;
    }
}

void Array::ArrayPosInsertErr(int Pos) {
    //不用Pos >= Size是保留了尾插的情况
    if (Pos > Size) {
        cout << "Pos > Size! Pos Error!" << endl;
        exit(-1);
    }
    else if (Pos < 0) {
        cout << "Pos < 0! Pos Error!" << endl;
        exit(-1);
    }
    else {
        return;
    }
}

void Array::ArrayPosErr(int Pos) {
    //删除是不能删除最后一个元素的后一位的，
    //所以在ArrayPosInsertErr()方法中没有考虑到的末位在该函数中将被考虑
    if (Pos == Size) {
        cout << "Pos == Size. Index Error" << endl;
        exit(-1);
    }
    else {
        ArrayPosInsertErr(Pos);
    }
}

void Array::ArrayIsEmpty() {
    if (Size == 0) {
        cout << "Array Is Empty!" << endl;
        exit(-1);
    }
    else {
        return;
    }
}


DataType * Array::TwoNumbersSum(DataType Target) {
    int i, j;

    for (i = 0; i < Size - 1; i++) {
        for (j = i + 1; j < Size; j++) {
            if (A[i] + A[j] == Target) {
                DataType * ReturnSize = (DataType *)malloc(sizeof (DataType) * 2);
                ReturnSize[0] = A[0];
                ReturnSize[1] = A[1];

                return ReturnSize;
            }
        }
    }

    return nullptr;
}