#include "myList.hpp"

void listMedian (const std::vector<int> * instructions)
{
    //hold insert instructions
    std::list<int> contain;//O(1)
    //hold medians
    std::list<int> output;//O(1)
    //iteratoring every instructions, if is not -1 insert, otherwise find median and insert to output and pop it for contain
    //O(N^2)
    for(auto i : *instructions)//O(N)
    {
        if(i!=-1)
        {
            std::list<int>::iterator pos = std::lower_bound(contain.begin(),contain.end(),i);//O(logN)
            contain.insert(pos,i);//O(N)
        }
        else
        {
            int median_size = (contain.size()-1)/2;//O(1)
            auto it = contain.begin();
            //iteratoring to the middle of a list 
            for(int k = 0;k<median_size;k++)//O(N)
            {
                ++it;
            }
            output.push_back(*it);//O(1)
            contain.erase(it);//O(N)
        }
    }
    //print all medians
    for(auto j : output)
    {
        std::cout<<j<<" ";
    }
}