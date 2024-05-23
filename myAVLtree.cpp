#include "myAVLtree.hpp"

void treeMedian (const std::vector<int> * instructions)
{
    //small store number <= median, large store number > median
    AvlTree small;//O(1)
    AvlTree large;//O(1)
    //store all medians
    //iteratoring every instructions, if is not -1 insert then balance the tree, 
    //otherwise find median and insert to output and pop it for contain, then balance the tree
    std::vector<int> output;//O(1)
    //O(N^2)
    for(auto i : *instructions)//O(N)
    {
        if(i!=-1)
        {
            if(small.isEmpty() || i <= small.findMax())//O(logN)
            {
                small.insert(i);//O(logN)
            }
            else
            {
                large.insert(i);//O(logN)
            }
            resize(small,large);//O(N)
        }
        else
        {
            int middle = small.findMax();//O(logN)
            output.push_back(middle);//O(1)
            small.remove(middle);//O(logN)
            resize(small,large);//O(N)
        }
    }
    for(auto j : output)
    {
        std::cout<<j<<" ";
    }
}
//if size of small is greater than large +1 move one element from small to large
//if size of small is lesser than large move one element from large to small
//O(N)
void resize(AvlTree &small, AvlTree &large)
{
    if(small.getSize() > large.getSize() + 1)//O(N)
    {
        int middle = small.findMax();//O(logN)
        large.insert(middle);//O(logN)
        small.remove(middle);//O(logN)
    }
    else if(large.getSize() > small.getSize())//O(N)
    {
        int middle = large.findMin();//O(logN)
        small.insert(middle);//O(logN)
        large.remove(middle);//O(logN)
    }
    else
    {
        return;
    }
}