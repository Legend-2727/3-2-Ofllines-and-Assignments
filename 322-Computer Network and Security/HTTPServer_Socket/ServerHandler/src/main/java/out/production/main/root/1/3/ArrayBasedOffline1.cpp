#include<bits/stdc++.h>
using namespace std;

template<class T>
class MyArrayList
{
    T* data;
    int pos;
    int max_curSize;
    int curSize;
public:
    MyArrayList()
    {
        max_curSize=1;
        data=new T[max_curSize];
        pos=0;
        curSize=0;
    }
    MyArrayList(int x)
    {
        max_curSize=x;
        data=new T[curSize];
        pos=0;
        curSize=0;
    }
    int size()
    {
        return curSize;
    }
    void push(T item)
    {
        if(data==NULL) data=new int[max_curSize];
        if(curSize+1>max_curSize)
        {
            expandMaxSize();
        }
        curSize++;
        for(int i=curSize;i>pos;i--)
        {
            data[i]=data[i-1];
        }
        data[pos]=item;
    }
    void expandMaxSize()
    {
        int temp[curSize];
        for(int i=0;i<curSize;i++)
        {
            temp[i]= data[i];
        }
        delete[] data;
        max_curSize*=2;
        data=new T[max_curSize];
        for(int i=0;i<curSize;i++)
        {
            data[i]=temp[i];
        }
    }
    void shrinkMaxSize()
    {
        T temp[curSize];
        for(int i=0;i<curSize;i++)
        {
            temp[i]= data[i];
        }
        delete[] data;
        max_curSize/=2;
        data=new T[max_curSize];
        for(int i=0;i<curSize;i++)
        {
            data[i]=temp[i];
        }
    }
    void pushBack(T item)
    {
        if(data==NULL) data=new T[max_curSize];
        if(curSize>=max_curSize)
        {
            expandMaxSize();
        }
        data[curSize++]=item;
    }
    T erase()
    {
        T temp=data[pos];
        for(int i=0;i<curSize-1;i++)
        {
            data[i]=data[i+1];
        }
        curSize--;
        if(curSize<(max_curSize/2)&& max_curSize>1)
        {
            shrinkMaxSize();
        }
        return temp;
    }
    void setToBegin()
    {
        pos=0;
    }
    void setToEnd()
    {
        pos=curSize-1;
    }
    void prev()
    {
        if(pos!=0) pos--;
    }
    void next()
    {
        if(pos!=(curSize-1)) pos++;
    }
    int currPos()
    {
        return pos;
    }
    void setToPos(int position)
    {
        pos=position;
    }
    T getValue()
    {
        return data[pos];
    }
    int find(T item)
    {
        for(int i=0;i<curSize;i++)
        {
            if(data[i]==item)
            {
                return i;
            }
        }
        return -1;
    }
    void clear()
    {
        pos=0;
        curSize=0;
        max_curSize=10;
        delete [] data;
        data=new T[max_curSize];
    }
    void print(ofstream &output,int x)
    {
        output<<"< ";
        for(int i=0;i<curSize;i++)
        {
            if(i==pos) output<<"| ";
            output<<data[i]<<" ";
        }
        output<<">\n";
        if(x!=-2) output<<x<<"\n";
    }
    ~MyArrayList()
    {
        delete[] data;
    }
}; 
