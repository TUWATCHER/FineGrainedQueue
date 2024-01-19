#include "safeQueue.hpp"
#include <thread>
using std::string;


int main()
{
      FineGrainedQueue que;
      que.queue_mutex = new std::mutex();
      que.head = new Node();
      que.head->value = 10;
      que.head->node_mutex = new std::mutex();
      que.head->next = new Node();
      que.head->next->node_mutex = new std::mutex();
      que.head->next->value = 15;
      std::thread t1([&](){que.insert(20,1);});
      std::thread t2([&](){que.insert(40,1);});
      t1.join();
      t2.join();
      que.printList();
}
