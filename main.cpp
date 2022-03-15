
#include <iostream>
#include <ctime>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <chrono>
using namespace std;
ifstream f("teste.in");

void generare(vector <long long> v, long long N, long long max){
    srand((unsigned)time(0));

    for(int i = 0; i < N; i++){
        v.push_back((rand()*rand())%max+1);}


    }

long long nrMaxim(vector<long long> v, long long N){
    int Max = v[0];

    for (int i = 1; i < N; i++)
        if (v[i] > Max)
            Max = v[i];

    return Max;
}

//radix sort
void NumarareRadix(vector<long long> &v, int n, int exp,int baza)
{
    vector<long long> result;

    int i;
    for(i = 0; i<= n; i++)
    {
        result.push_back(0);
    }


    vector<int> counter;

    for(i = 0; i<= baza; i++)
    {
        counter.push_back(0);
    }
    for (i =0; i <n; i++)
        counter[(v[i] / exp) % baza]++;

    for (i =1; i<baza; i++)
        counter[i] += counter[i-1];

    for (i =n-1; i>= 0; i--)
    {
        result[counter[(v[i] / exp) % baza] - 1] = v[i];
        counter[(v[i] / exp) % baza]--;
    }
    for (i =0; i <n; i++)
        v[i] = result[i];

    result.clear();
    counter.clear();
}
void radixsort(vector<long long> &v, int n,int baza)
{
    int exp, i;
    i = nrMaxim(v,n);
    for (exp = 1; i/exp > 0; exp *= baza)
        NumarareRadix(v, n, exp,baza);
}


//merge sort
void merge(vector <long long> &v, int const left, int const mid, int const right)
{
    auto const sub1 = mid - left + 1;
    auto const sub2 = right - mid;

    auto *leftArray = new int[sub1],
            *rightArray = new int[sub2];

    for (auto i = 0; i < sub1; i++)
        leftArray[i] = v[left + i];
    for (auto j = 0; j < sub2; j++)
        rightArray[j] = v[mid + 1 + j];

    auto indexsub1 = 0,
    indexsub2 = 0;
    int indexOfMergedArray = left;

    while (indexsub1 < sub1 && indexsub2 < sub2) {
        if (leftArray[indexsub1] <= rightArray[indexsub2]) {
            v[indexOfMergedArray] = leftArray[indexsub1];
            indexsub1++;
        }
        else {
            v[indexOfMergedArray] = rightArray[indexsub2];
            indexsub2++;
        }
        indexOfMergedArray++;
    }

    while (indexsub1 < sub1) {
        v[indexOfMergedArray] = leftArray[indexsub1];
        indexsub1++;
        indexOfMergedArray++;
    }

    while (indexsub2 < sub2) {
        v[indexOfMergedArray] = rightArray[indexsub2];
        indexsub2++;
        indexOfMergedArray++;
    }
}

void mergeSort(vector <long long> &v, int const begin, int const end)
{
    if (begin >= end)
        return;
    auto mid = begin + (end - begin) / 2;
    mergeSort(v, begin, mid);
    mergeSort(v, mid + 1, end);
    merge(v, begin, mid, end);
}
//shell sort
void shellsort(vector <long long> &v, long long N)
{
    for (int g = N/2; g > 0; g /= 2)
    {
        for (int i = g; i < N; i++)
        {
            int t = v[i];
            int j;
            for (j = i; j >= g && v[j - g] > t; j -= g)
                v[j] = v[j - g];

            v[j] = t;
        }
    }
}

//bucket sort

void bucketSort(vector <long long> &v, long long N)
{
    vector<long long> b[N];

    for (int i = 0; i < N; i++) {
        int bi = N* v[i];
        b[bi].push_back(v[i]);
    }

    for (int i = 0; i < N; i++)
        sort(b[i].begin(), b[i].end());

    int index = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < b[i].size(); j++)
            v[index++] = b[i][j];
}

//heap sort
void heapify(vector <long long> &v, int n, int i)
{
    long long  largest = i;
    long long l = 2 * i + 1;
    long long r = 2 * i + 2;

    if (l < n && v[l] > v[largest])
        largest = l;

    if (r < n && v[r] > v[largest])
        largest = r;

    if (largest != i) {
        swap(v[i], v[largest]);

        heapify(v, n, largest);
    }
}

void heapSort(vector <long long> &v, int N)
{
    for (int i = N/ 2 - 1; i >= 0; i--)
        heapify(v, N, i);

    for (int i = N - 1; i > 0; i--) {
        swap(v[0], v[i]);

        heapify(v, i, 0);
    }
}

//verificare
bool test_sort( vector <long long> v, long long N){
    for(int i=0; i<N-1; i++)
        if( v[i]>v[i+1])
            return false;
    return true;
}

int main()
{
    long long nrteste, N, max;
    vector<long long> v;
    f>>nrteste;
    vector <long long> v1;
    vector <long long> b;
    for(int i = 0; i <= 10000000; i++)
    {
        v.push_back(0);https:
        b.push_back(0);
    }

    std::srand(std::time(nullptr));
    for(int k=1;k<=nrteste; k++){
        f>>N>>max;
        cout<<"Test:"<<k<<" "<<"Nr elemente:"<<N<<" "<<"Valoarea maxima:"<<max<<'\n';
        generare(v, N, max);
    
        v1=v;
        vector <long long> c(N);
        for(int j=0;j<N; j++)
            c[j]=v[j];

        v=v1;
        cout<<">Radix Sort(baza 2):";
        auto start = std::chrono::high_resolution_clock::now();
        radixsort(v,N,2);
        auto stop = std::chrono::high_resolution_clock::now();
        auto durata=std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
        if(test_sort(v, N) == false)
            cout << "Gresit";
        else
            cout << "Corect!--- timp: " <<durata << " microsecunde. \n";
        v=v1;
        cout<<">Radix Sort(baza 128):";
         start = std::chrono::high_resolution_clock::now();
        radixsort(v,N,128);
        stop = std::chrono::high_resolution_clock::now();
        durata=std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
        if(test_sort(v, N) == false)
            cout << "Gresit";
        else
            cout << "Corect!--- timp: " <<durata << " microsecunde. \n";

        v=v1;
        cout<<">Merge Sort:";
        b.assign(N, 0);
        start = std::chrono::high_resolution_clock::now();
        mergeSort(v,0,N);
        stop = std::chrono::high_resolution_clock::now();
        durata=std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
        if(test_sort(v, N) == false)
            cout << "Gresit";
        else
            cout << "Corect!--- timp: " <<durata << " microsecunde. \n";
        v=v1;
        cout<<">Shell Sort:";
        start = std::chrono::high_resolution_clock::now();
        shellsort(v, N);
        stop = std::chrono::high_resolution_clock::now();
        durata=std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
        if(test_sort(v, N) == false)
            cout << "Gresit";
        else
            cout << "Corect!--- timp: " <<durata << " microsecunde. \n";

        v=v1;
        cout<<">Heap Sort:";
        start = std::chrono::high_resolution_clock::now();
        heapSort(v, N);
        stop = std::chrono::high_resolution_clock::now();
        durata=std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
        if(test_sort(v, N) == false)
            cout << "Gresit";
        else
            cout << "Corect!--- timp: " <<durata << " microsecunde. \n";

        v=v1;
        cout<<">Bucket Sort:";
        start = std::chrono::high_resolution_clock::now();
        bucketSort(v, N);
        stop = std::chrono::high_resolution_clock::now();
        durata=std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
        if(test_sort(v, N) == false)
            cout << "Gresit";
        else
            cout << "Corect!--- timp: " <<durata << " microsecunde. \n";
        cout<<'\n';


    }


    return 0;
}

