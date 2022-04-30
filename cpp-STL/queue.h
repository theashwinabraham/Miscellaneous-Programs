/*
* AUTHOR: ASHWIN ABRAHAM
*/
#include <iostream>
#define QUEUEMAX 10


class Queue{
    private:
        unsigned int queue[QUEUEMAX];
        int front;
        int num;
    public:
        Queue(): front(0), num(0){return;}
        void add(int id){
            if(num==QUEUEMAX){std::cout << "The Queue is full, please try again later\n"; return;}
            queue[(front+num)%QUEUEMAX] = id;
            ++num;
            return;
        }
        int remove(){
            if(num==0){return -1;}
            int temp = front;
            front = (front+1)%QUEUEMAX;
            --num;
            return queue[temp];
        }
};

