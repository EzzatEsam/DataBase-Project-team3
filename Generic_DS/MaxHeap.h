#pragma once

template< typename T>
class MaxHeap
{
private:
    T * arr;
    int CurrentIndex = -1;
    int getparent(int i)
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
            T temp = arr[i];
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
            T temp = arr[i];
            arr[i] = arr[Index];
            arr[Index] = temp;
            HeapDown(Index);
        }
    }
   /* void remove(int i)
    {
        arr[i] = getMax() + 1;
        HeapUp(i);
        BeHead();
    }*/
    void max_Heapify(int i)
    {
        int largest = 0;
        int l = getleft(i);
        int r = getright(i);
        if (l <= CurrentIndex && arr[l] > arr[i]) {
            largest = l;
        }
        else {
            largest = i;
        }
        if (r< CurrentIndex && arr[r]>arr[largest]) {
            largest = r;
        }
        if (largest != i) {
            T temp = arr[i];
            arr[i] = arr[largest];
            arr[largest] = temp;
            max_Heapify(largest);
        }
        
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
        CurrentIndex += 1;
        arr[CurrentIndex] = pri;
        HeapUp(CurrentIndex);
    }


    bool BeHead(T& it)
    {
        RefreshTheHeap();
        if (CurrentIndex == -1)
        {
            return false;
        }
        it = arr[0];
        arr[0] = arr[CurrentIndex];
        CurrentIndex = CurrentIndex - 1;
        HeapDown(0);
        
        return true;
    }
    T getMax()
    {
        return arr[0];
    }
    void RefreshTheHeap()
    {
        max_Heapify(0);
    }
    T* toArray(int& size)
    {
        size = CurrentIndex + 1;
        T* output = new T[size];
        for (int i = 0; i < size; i++)
        {
            output[i] = arr[i];
        }
        return output;
    }

   
  
};


