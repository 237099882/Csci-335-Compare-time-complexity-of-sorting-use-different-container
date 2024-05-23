// myHeap.hpp
#ifndef MYHEAP_HPP
#define MYHEAP_HPP

#include <iostream>
#include <vector>
#include <queue>

//insert and pop median from instructions
void heapMedian(const std::vector<int>* instructions);
//balance two Heap
void resize(std::priority_queue<int> &maxheap,std::priority_queue<int, std::vector<int>, std::greater<int> > &minheap);
#endif 
