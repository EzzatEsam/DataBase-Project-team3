#pragma once

template< typename T>
class MaxHeap
{
private:
    T * arr;
    int Index = -1;
    T getparent(int i)
    {
        return (i - 1) / 2;
    }
    int getleft(int i)
    {

        return ((2 * i) + 1);
    }
    int getright(int i)
    {

        return ((2 * i) + 2);
    }

    void HeapUp(int i)
    {
        while (i > 0 && arr[getparent(i)] < arr[i])
        {
            int temp = arr[i];
            arr[i] = arr[getparent(i)];
            arr[getparent(i)] = temp;
            i = getparent(i);
        }
    }
    void HeapDown(int i)
    {
        int Index = i;
        int l = getleft(i);
        if (l <= Index && arr[l] > arr[Index])
        {
            Index = l;
        }
        int r = getright(i);

        if (r <= Index && arr[r] > arr[Index])
        {
            Index = r;
        }

        if (i != Index)
        {
            int temp = arr[i];
            arr[i] = arr[Index];
            arr[Index] = temp;
            HeapDown(Index);
        }
    }
    void remove(int i)
    {
        arr[i] = getMax() + 1;
        HeapUp(i);
        BeHead();
    }
    void max_Heapify(int i)
    {
        int largest = 0;
        int l = getleft(i);
        int r = getright(i);
        if (l <= Index && arr[l] > arr[i]) {
            largest = l;
        }
        else {
            largest = i;
        }
        if (r< Index && arr[r]>arr[largest]) {
            largest = r;
        }
        if (largest != i) {
            int temp = arr[i];
            arr[i] = arr[largest];
            arr[largest] = temp;
        }
        max_Heapify(largest);
    }
public:
    MaxHeap(int Max = 5000)
    {
        arr = new T[Max];
    }
    ~MaxHeap()
    {
        delete[] arr;
    }
    


    void insert(T pri)
    {
        Index += 1;
        arr[Index] = pri;
        HeapUp(Index);
    }


    bool BeHead(T& it)
    {
        if (Index == -1)
        {
            return false;
        }
        T result = arr[0];
        arr[0] = arr[Index];
        Index = Index - 1;
        HeapDown(0);
        it = result;
        return true;
    }
    T getMax()
    {
        return arr[0];
    }
    void RefreshTheHeap()
    {

    }

   
  
};


