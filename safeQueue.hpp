#pragma once

#include <mutex>
#include <iostream>

struct Node
{
    int value;
    Node* next;
    std::mutex* node_mutex;
};

class FineGrainedQueue
{
    public:
    Node* head;
    std::mutex* queue_mutex;
    void insert(int value, int pos)
    {
        int counter = 0;
        Node* new_node = new Node();
        new_node->value = value;
        new_node->node_mutex = new std::mutex();

        Node* cur = nullptr;
        Node* prev = nullptr;

        queue_mutex->lock();
        cur = head;
        queue_mutex->unlock();

        while(cur)
        {
            cur->node_mutex->lock();
            if (counter == pos)
            {
                new_node->next = cur;
                prev->next = new_node;
                prev->node_mutex->unlock();
                cur->node_mutex->unlock();
                return;
            }
            if (prev)
            {
                Node* old_prev = prev;
                old_prev->node_mutex->unlock();
            }
            prev = cur;
            cur = cur->next;
            counter++;

        }

        if (pos >= counter)
        {
            prev->next = new_node;
            new_node->next = nullptr;
        }
        prev->node_mutex->unlock();

    }
    void printList()
    {
        Node* cur = head;
        while (cur != nullptr)
        {
            std::cout << cur->value << " ";
            cur = cur->next;
        }
    }    
};
