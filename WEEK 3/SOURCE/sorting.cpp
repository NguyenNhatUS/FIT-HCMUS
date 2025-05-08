#include "sorting.h"

// Selection Sort
// Original Functions
void selection_sort(int a[], int n)
{
    for (int i = 0;  i < n - 1; i++)
    {
      int index=i;
        for (int j = i + 1;  j < n; j++)
        {
            if (a[index] > a[j])
            {
                index=j;
            }
        }if(index!=i){
          int temp=a[index];
          a[index]=a[i];
          a[i]=temp;
        }
    }
}

// Insertion Sort
void insertion_sort(int a[], int n)
{
    for (int i = 1; i < n; i++)
    {
        int j = i - 1;
        int key = a[i];
        while (j >= 0 && a[j] > key)
        {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

// Bubble Sort
void bubble_sort(int a[], int n)
{
    bool swap = true;
    int temp;
    while(swap)
    {
        swap = false;
        for (int j = 0;  j < n - 1; j++)
        {
            if ( a[j] > a[j + 1])
            {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
                swap = true;
            }
        }
    }
}

// Shell Sort
void shell_sort(int arr[], int n)
{
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i++)
        {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
            {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

// Heap Sort
void heapify(int a[], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && a[left] > a[largest])
    {
        largest = left;
    }
    if (right < n && a[right] > a[largest])
    {
        largest = right;
    }
    if (largest != i)
    {
        swap(a[largest], a[i]);
        heapify(a, n, largest);
    }
}

void heap_sort(int a[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(a, n, i);
    }
    for (int i = n - 1; i > 0; i--)
    {
        swap(a[i], a[0]);
        heapify(a, i, 0);
    }
}

// Merge Sort
void merge(int a[], int left, int mid, int right)
{
    if (left >= right)
        return;
    int *temp = new int[right - left + 1];
    int i = left, j = mid + 1, count = 0;
    while (i <= mid && j <= right)
    {
        if (a[i] < a[j])
        {
            temp[count++] = a[i];
            i++;
        }
        else
        {
            temp[count++] = a[j];
            j++;
        }
    }
    while (i <= mid)
    {
        temp[count++] = a[i++];
    }
    while (j <= right)
    {
        temp[count++] = a[j++];
    }
    for (int o = 0; o < count; o++)
    {
        a[left + o] = temp[o];
    }
    delete[] temp;
}

void MergeSort(int a[], int left, int right)
{
    if (right <= left)
        return;
    int mid = left + (right - left) / 2;
    MergeSort(a, left, mid);
    MergeSort(a, mid + 1, right);
    merge(a, left, mid, right);
}

void merge_sort(int a[], int n)
{
    MergeSort(a, 0, n - 1);
}

// Quick Sort

int partition(int a[], int left, int right)
{
    int pivot = a[right];
    int i = left - 1;
    for (int j = left; j < right; j++)
    {
        if (a[j] < pivot)
        {
            i++;
            swap(a[i], a[j]);
        }
    }
    i++;
    swap(a[i], a[right]);
    return i;
}

void quickSort(int a[], int left, int right)
{
    if (left >= right)
        return;
    int pi = partition(a, left, right);
    quickSort(a, left, pi - 1);
    quickSort(a, pi + 1, right);
}

void quick_sort(int a[], int n)
{
    quickSort(a, 0, n - 1);
}

// Counting Sort
void CountingSort(int arr[], int n, int mi, int mx)
{
    int d = 0, cs = mx - mi;
    vector<int> count(cs + 1, 0);
    for (int i = 0; i < n; i++)
    {
        count[arr[i] - mi]++;
    }
    for (int i = 0; i <= cs; i++)
    {
        while(count[i]--)
        {
           arr[d++] = i + mi;
        }
    }
}

void counting_sort(int a[], int n)
{
    int min = a[0], max = a[0];
    for (int i = 1; i < n; i++)
    {
        if (min > a[i])
            min = a[i];
        if (max < a[i])
            max = a[i];
    }
    CountingSort(a, n, min, max);
}

// Radix Sort
void Counting(int a[], int n, int exp)
{
    int output[n];
    int count[10] = {0};
    for (int i = 0; i < n; i++)
    {
        count[(a[i] / exp) % 10]++;
    }
    for (int i = 1; i < 10; i++)
    {
        count[i] += count[i - 1];
    }
    for (int i = n - 1; i >= 0; i--)
    {
        int digit = (a[i] / exp) % 10;
        output[count[digit] - 1] = a[i];
        count[digit]--;
    }
    for (int i = 0; i < n; i++)
    {
        a[i] = output[i];
    }
}

void radix_sort(int a[], int n)
{
    int maxNum = a[0];
    for (int i = 1;i < n; i++)
    {
        if (maxNum < a[i])
            maxNum = a[i];
    }
    for (int exp = 1;  maxNum / exp > 0; exp *= 10)
    {
        Counting(a, n, exp);
    }
}

// Flash Sort
void flash_sort(int a[], int n)
{
    int __L[300000];
    if (n <= 1)
        return;
    int m = n * 0.43;
    if (m <= 2)
        m = 2;
    for (int i = 0; i < m; i++)
        __L[i] = 0;
    int Mx = a[0], Mn = a[0];
    for (int i = 1; i < n; i++)
    {
        if (Mx < a[i])
            Mx = a[i];
        if (Mn > a[i])
            Mn = a[i];
    }
    if (Mx == Mn)
        return;
#define getK(x) 1ll * (m - 1) * (x - Mn) / (Mx - Mn)
    for (int i = 0; i < n; i++)
        ++__L[getK(a[i])];
    for (int i = 1; i < m; i++)
        __L[i] += __L[i - 1];
    int count = 0;
    int i = 0;
    while (count < n)
    {
        int k = getK(a[i]);
        while (i >= __L[k])
            k = getK(a[++i]);
        int z = a[i];
        while (i != __L[k])
        {
            k = getK(z);
            int y = a[__L[k] - 1];
            a[--__L[k]] = z;
            z = y;
            count++;
        }
    }
    for (int k = 1; k < m; k++)
    {
        for (int i = __L[k] - 2; i >= __L[k - 1]; i--)
            if (a[i] > a[i + 1])
            {
                int t = a[i], j = i;
                while (t > a[j + 1])
                {
                    a[j] = a[j + 1];
                    j++;
                }
                a[j] = t;
            }
    }
}

// Shaker Sort
void shaker_sort(int a[], int n)
{
    int left = 0;
    int right = n - 1;
    int k = 0;
    int i;
    while (left < right)
    {
        for (i = left; i < right; i++)
        {
            if (a[i] > a[i + 1])
            {
                swap(a[i], a[i + 1]);
                k = i;
            }
        }
        right = k;
        for (i = right; i > left; i--)
        {
            if (a[i] < a[i - 1])
            {
                swap(a[i], a[i - 1]);
                k = i;
            }
        }
        left = k;
    }
}


template <class T>
void HoanVi(T &a, T &b)
{
    T x = a;
    a = b;
    b = x;
}

//-------------------------------------------------

// Hàm phát sinh mảng dữ liệu ngẫu nhiên
void GenerateRandomData(int a[], int n)
{
    srand((unsigned int)time(NULL));
    for (int i = 0; i < n; i++)
    {
        a[i] = rand() % n;
    }
}

// Hàm phát sinh mảng dữ liệu có thứ tự tăng dần
void GenerateSortedData(int a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        a[i] = i;
    }
}

// Hàm phát sinh mảng dữ liệu có thứ tự ngược (giảm dần)
void GenerateReverseData(int a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        a[i] = n - 1 - i;
    }
}

// Hàm phát sinh mảng dữ liệu gần như có thứ tự
void GenerateNearlySortedData(int a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        a[i] = i;
    }
    srand((unsigned int)time(NULL));
    for (int i = 0; i < 10; i++)
    {
        int r1 = rand() % n;
        int r2 = rand() % n;
        HoanVi(a[r1], a[r2]);
    }
}

void GenerateData(int a[], int n, int dataType)
{
    switch (dataType)
    {
    case 0: // ngẫu nhiên
        GenerateRandomData(a, n);
        break;
    case 1: // có thứ tự
        GenerateSortedData(a, n);
        break;
    case 2: // có thứ tự ngược
        GenerateReverseData(a, n);
        break;
    case 3: // gần như có thứ tự
        GenerateNearlySortedData(a, n);
        break;
    default:
        cout << "Error: unknown data type!" << endl;
    }
    return;
}

int GenerateDataSize()
{
    srand(time(0));
    int dataSize = rand() % 4;
    switch (dataSize)
    {
    case 0:
        return 10000;
    case 1:
        return 30000;
    case 2:
        return 50000;
    case 3:
        return 100000;
    }
    return 0;
}

void GenerateArrayAndWrite(string filename)
{
    ofstream fout;
    fout.open(filename);
    srand(time(0));
    int dataType = rand() % 4;
    int dataSize = GenerateDataSize();
    int *a = new int[dataSize];
    GenerateData(a, dataSize, dataType);
    fout << dataSize << endl;
    for (int i = 0; i < dataSize; i++)
    {
        fout << a[i] << " ";
    }
    fout.close();
    delete[] a;
}

void CopyArr(int a[], int b[], int n)
{
    for (int i = 0; i < n; i++)
    {
        b[i] = a[i];
    }
}

void processSort(string Algo, int a[], int n)
{
    if (Algo == "selection-sort")
    {
        selection_sort(a, n);
    }
    else if (Algo == "insertion-sort")
    {
        insertion_sort(a, n);
    }
    else if (Algo == "bubble-sort")
    {
        bubble_sort(a, n);
    }
    else if (Algo == "radix-sort")
    {
        radix_sort(a, n);
    }
    else if (Algo == "flash-sort")
    {
        flash_sort(a, n);
    }
    else if (Algo == "heap-sort")
    {
        heap_sort(a, n);
    }
    else if (Algo == "shaker-sort")
    {
        shaker_sort(a, n);
    }
    else if (Algo == "shell-sort")
    {
        shell_sort(a, n);
    }
    else if (Algo == "merge-sort")
    {
        merge_sort(a, n);
    }
    else if (Algo == "quick-sort")
    {
        quick_sort(a, n);
    }
    else if (Algo == "counting-sort")
    {
        counting_sort(a, n);
    }
}
