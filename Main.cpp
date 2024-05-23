#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "myVector.hpp"
#include "myList.hpp"
#include "myHeap.hpp"
#include "myAVLtree.hpp"
#include <chrono>
using namespace std::chrono;
using namespace std;

int main()
{
    //input and output vector
    vector<int> input;
    //open file
    string filename = "testinput.txt";
    ifstream fin(filename);
    string line;
    while(getline(fin,line))
    {
        stringstream ss(line);
        string in;
        ss>>in;
        if(in == "pop")
        {
            input.push_back(-1);
        }
        else
        {
            int a;
            ss >> a;
            input.push_back(a);
        }
    }
    auto start1 = high_resolution_clock::now();
    vectorMedian(&input);
    auto stop1 = high_resolution_clock::now();
    cout<<endl;
    auto start2 = high_resolution_clock::now();
    listMedian(&input);
    auto stop2 = high_resolution_clock::now();
    cout<<endl;
    auto start3 = high_resolution_clock::now();
    heapMedian(&input);
    auto stop3 = high_resolution_clock::now();
    cout<<endl;
    auto start4 = high_resolution_clock::now();
    treeMedian(&input);
    auto stop4 = high_resolution_clock::now();
    cout<<endl;
    auto duration1 = duration_cast<microseconds>(stop1 - start1);
    auto duration2 = duration_cast<microseconds>(stop2 - start2);
    auto duration3 = duration_cast<microseconds>(stop3 - start3);
    auto duration4 = duration_cast<microseconds>(stop4 - start4);

    cout<<duration1.count()<<" "<<duration2.count()<<" "<<duration3.count()<<" "<<duration4.count()<<endl;
    return 0;
}