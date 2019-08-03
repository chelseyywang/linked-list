//
//  Sequence.hpp
//  cs32proj2
//
//  Created by Chelsey Wang on 4/17/19.
//  Copyright © 2019 Chelsey Wang. All rights reserved.
//
#include <string>
#ifndef Sequence_h
#define Sequence_h

using ItemType = std::string;

class Sequence
{
public:
    Sequence();
    Sequence(const Sequence& other);
    Sequence& operator=(const Sequence& seq);
   ~Sequence();
    bool empty() const;
    int size() const;
    int insert(int pos, const ItemType& value);
    int insert(const ItemType& value);
    bool erase(int pos);
    int remove(const ItemType& value);
    bool get(int pos, ItemType& value) const;
    bool set(int pos, const ItemType& value);
    int find(const ItemType& value) const;
    void swap(Sequence& other);
    void dump() const;
    
private:
    struct Node
    {
        ItemType data;
        Node* next;
        Node* back;
    };
    Node* head;
    int m_size;
};

int subsequence(const Sequence& seq1, const Sequence& seq2); //no privates!!
void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result); //no privates!!
#endif /* Sequence_hpp */
