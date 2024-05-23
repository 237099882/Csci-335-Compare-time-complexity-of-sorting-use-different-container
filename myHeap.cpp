#include "myHeap.hpp"

void heapMedian (const std::vector<int> * instructions)
{
    //small store number <= median, large store number > median
    std::priority_queue<int> small;//O(1)
    std::priority_queue<int, std::vector<int>, std::greater<int> > large;//O(1)
    //store medians
    std::vector<int> output;//O(1)
    //iteratoring every instructions, if is not -1 insert then balance the heap, 
    //otherwise find median and insert to output and pop it for contain, then balance the heap
    //O(NlogN)
    for(auto i : *instructions)//O(N)
    {
        if(i!=-1)
        {
            if(small.empty() || i <= small.top())//O(1)
            {
                small.push(i);//O(logN)
            }
            else
            {
                large.push(i);//O(logN)
            }
            resize(small,large);//O(logN)
        }
        else
        {
            output.push_back(small.top());//O(1)
            small.pop();//O(1)
            resize(small,large);//O(logN)
        }
    }
    for(auto j : output)
    {
        std::cout<<j<<" ";
    }
}
//if size of small is greater than large +1 move one element from small to large
//if size of small is lesser than large move one element from large to small
//O(logN)
void resize(std::priority_queue<int> &small,std::priority_queue<int, std::vector<int>, std::greater<int> > &large)
{
    if(small.size() > large.size() + 1)//O(1)
    {
        large.push(small.top());//O(logN)
        small.pop();//O(1)
    }
    else if(large.size() > small.size())
    {
        small.push(large.top());//O(logN)
        large.pop();//O(1)
    }
    else
    {
        return;
    }
}