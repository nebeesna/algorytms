//злиттям
#include <iostream>
using namespace std;

void merge_sort(int * elems, int* tmp_elems, size_t size)
{
    if (size <= 1) { return; } 

    const size_t left_size = size / 2;
    const size_t right_size = size - left_size;

    merge_sort(elems, tmp_elems, left_size);
    merge_sort(elems + left_size, tmp_elems + left_size, right_size);

    int* leftIt = elems; // pointer to walk through left part
    int* const pivot = elems + left_size; //end of left part, start of right  part
    int* rightIt = pivot; // pointer to walk through right part
    int* const end = elems + size;
    int* outputIt = tmp_elems; //pointer to where to write when merging left and right subparts

    while (true)
    {
        if (*leftIt < *rightIt)
        {
            *outputIt++ = *leftIt++;
            if (leftIt == pivot)
            {
                // copy the rest of right part that has not been copied yet
                copy(rightIt,
                    end,
                    outputIt);
                break;
            }
        }
        else
        {
            *outputIt++ = *rightIt++;
            if (rightIt == end)
            {
                // copy the rest of left part that has not been copied yet
                copy(leftIt,
                    pivot,
                    outputIt);
                break;
            }
        }
    }

    copy(tmp_elems,
        tmp_elems + size,
        elems);
}
/*
#include&lt;iostream&gt;

using namespace std;

const int nmax = 1000;

void Merg(int arr[], int begin, int end)
{
    int i = begin,
        t = 0,
        mid = begin + (end - begin) / 2,
        j = mid + 1,
        d[nmax];

    while (i& lt; = mid & amp; &amp; j & lt; = end) {

        if (arr[i] & lt; = arr[j]) {
            d[t] = arr[i]; i++;
        }
        else {
            d[t] = arr[j]; j++;
        }
        t++;
    }

    while (i& lt; = mid) {
        d[t] = arr[i]; i++; t++;

    }

    while (j& lt; = end) {
        d[t] = arr[j]; j++; t++;
    }

    for (i = 0; i & lt; t; i++)
        arr[begin + i] = d[i];
}

void MergSort(int* arr, int left, int right)
{
    int temp;
    if (left& lt; right)
        if (right - left == 1) {
            if (arr[right] & lt; arr[left]) {
                temp = arr[left];
                arr[left] = arr[right];
                arr[right] = temp;
            }
        }
        else {
            MergSort(arr, left, left + (right - left) / 2);
            MergSort(arr, left + (right - left) / 2 + 1, right);
            Merg(arr, left, right);
        }

}

void input(int* m, int& amp; n)
{

    cout& lt; &lt; &quot; Введите количество элементов массива& quot;;
    cin& gt; &gt; n;
    for (int i = 0; i & lt; n; i++)
    {
        cout& lt; &lt; &quot; a[&quot; &lt; &lt; i& lt; &lt; &quot; ] = &quot;;

        cin& gt; &gt; m[i];
    }

}
void print(int* m, int n)
{
    for (int i = 0; i & lt; n; i++)
        cout& lt; &lt; m[i] & lt; &lt; &quot; &quot;;
    cout& lt; &lt; &quot; \n& quot;;

}
void main()
{
    setlocale(LC_ALL, &quot; rus & quot;);
    int n, a[nmax];
    input(a, n);
    cout& lt; &lt; &quot; Исходный массив : \n& quot;;
    print(a, n);
    MergSort(a, 0, n - 1);
    cout& lt; &lt; &quot; Отсортированный массив : \n& quot;;
    print(a, n);
    system(&quot; pause & quot;);

}
*/
