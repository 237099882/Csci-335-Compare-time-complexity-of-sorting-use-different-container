#include "myVector.hpp"

void vectorMedian (const std::vector<int> * instructions)
{
    //hold insert instructions
    std::vector<int> contain;//O(1)
    //hold medians
    std::vector<int> output;//O(1)
    //iterator every instructions, if is not -1 insert, otherwise find median and insert to output and pop it for contain
    //O(N^2)
    for(auto i : *instructions)//O(N)
    {
        if(i!=-1)
        {
            std::vector<int>::iterator pos = std::lower_bound(contain.begin(),contain.end(),i);//O(logN)
            contain.insert(pos,i);//O(N)
        }
        else
        {
            output.push_back(contain.at((contain.size()-1)/2));//O(1)
            contain.erase(contain.begin()+(contain.size()-1)/2);//O(N)
        }
    }
    //print all medians
    for(auto j : output)
    {
        std::cout<<j<<" ";
    }
}