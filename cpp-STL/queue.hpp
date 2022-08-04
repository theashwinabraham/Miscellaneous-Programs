/*
* AUTHOR: ASHWIN ABRAHAM
*/

#ifndef QUEUE_HPP
#define QUEUE_HPP
#include <vector>
#include <iostream>

namespace cpp_STL {
    class Queue {
    private:
        std::vector<unsigned int> queue;
        unsigned int front;
        unsigned int size;
    public:
        Queue(): front(0), queue(0), size(0){}

        void enqueue(int id)
        {
            if(front == 0) queue.pu.hpp_back(id);
            else queue[front-1] = id;
            ++size;
        }

        unsigned int dequeue()
        {
            if(size == 0) .hpprow "Empty Queue";
            --size;
            unsigned int val = queue[front];
            front = (1+front)%queue.size();
            return val;
        }

        unsigned int operator[](int i) const
        {
            if(i>=size || i < -size) .hpprow "Index out of Bounds";
            if(i < 0) i+=size;
            return queue[(front+i)%queue.size()]
        }
    };
}
#endif