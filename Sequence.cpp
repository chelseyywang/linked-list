//
//  Sequence.cpp
//  cs32proj2
//
//  Created by Chelsey Wang on 4/17/19.
//  Copyright © 2019 Chelsey Wang. All rights reserved.
//

#include "Sequence.h"
#include <iostream>
Sequence::Sequence()
{
    m_size = 0;
    head = new Node; 
    head->next = head;
    head->back = head;
}
Sequence::Sequence(const Sequence& other)
{
    m_size = 0;
    head = new Node;
    head->next = head;
    head->back = head;
    for(int i = 0; i < other.size(); i++)
    {
        ItemType val;
        other.get(i, val);
        insert(i, val);
    }
}
Sequence & Sequence::operator=(const Sequence &seq)
{
    if (this != &seq)
    {  Sequence temp = seq;
        swap(temp); }
    return *this;
}
Sequence::~Sequence()
{
    
    while (head->next != head)
    {
        Node* deleteMe = head->back;
        deleteMe->back->next = head;
        head->back = deleteMe->back;
        delete deleteMe;
    }
    delete head;
}
bool Sequence::empty() const
{
    if (m_size == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
int Sequence::size() const
{
    return m_size;
}
int Sequence::insert(int pos, const ItemType& value) //I HAVE QUESTIONS
// Insert value into the sequence so that it becomes the item at
// position pos.  The original item at position pos and those that
// follow it end up at positions one higher than they were at before.
// Return pos if 0 <= pos <= size() and the value could be
// inserted.  (It might not be, if the sequence has a fixed capacity,
// e.g., because it's implemented using a fixed-size array.)  Otherwise,
// leave the sequence unchanged and return -1.  Notice that
// if pos is equal to size(), the value is inserted at the end.
{
    
    if(pos > size() or pos < 0) //check bounds
        return -1;
    Node * temp = new Node; //make new node
    Node * p = head->next; //make an iterator node
    for(int i = 0; i < pos; i++){ //go through list up to position
        p = p->next;
    }
    temp->data = value; //give new node value
    temp->next = p; //point the new node's next pointer to the next node
    temp->back=p->back; //point new node's back pointer to node behind it
    p->back->next = temp; //point node behind new node's next pointer to new node
    p->back = temp; //point iterator to new node
    m_size++; //increase size
    return pos;
}

int Sequence::insert(const ItemType& value)
// Let p be the smallest integer such that value <= the item at
// position p in the sequence; if no such item exists (i.e.,
// value > all items in the sequence), let p be size().  Insert
// value into the sequence so that it becomes the item at position
// p.  The original item at position p and those that follow it end
// up at positions one higher than before.  Return p if the value
// was actually inserted.  Return -1 if the value was not inserted
// (perhaps because the sequence has a fixed capacity and is full).
{
    Node* p = head->next; //make iterator pointer
    int pos = 0;
    while (p!=head) //go through list
    {
        if (value<=p->data) //if you find a node that has a larger value than parameter
            break; //exit loop
        p = p->next; //keep looking
        pos++; //increase position holder
    }
    insert(pos, value); //insert value at position
    return pos;
 
}

bool Sequence::erase(int pos)
//// If 0 <= pos < size(), remove the item at position pos from
//// the sequence (so that all items that followed that item end up at
//// positions one lower than they were at before), and return true.
//// Otherwise, leave the sequence unchanged and return false.
{

    if (pos >= 0 && pos < size())
    {
        Node* p = head; //make an iterator pointer that points to head
        for (int i = 0; i < size(); i++)
        {
            p = p->next; //go through list
            if (i == pos) //if position exists in the list
            {
                Node* die = p;      //make a new node pointer that points to the position
                p->back->next = die->next; //have previous node skip over with next pointer
                p->next->back = die->back; //have next node skip over with back pointer
                delete die; //delete pointer and what it points to
                m_size--; //decrease size
                return true;
            }
        }
    }
    return false;
}

int Sequence::remove(const ItemType& value) //VERY TROUBLESOME
// Erase all items from the sequence that == value.  Return the
// number of items removed (which will be 0 if no item == value).
{
    
    int counter = 0;
    Node* p = head->next;
   while (p != head) //go through the list
    {
        if (p->data == value) //if u get what u want to kill --
        {
            Node* die = p;  //point a new guy at that node
            p->back->next = die->next; //move the other's next pointer to next thing
            p->next->back = die->back; //move the other's back pointer behind that node
            p = p->next;
            delete die; //kill node
            counter++; 
            m_size--;
        }
        else
            p = p->next; 
    }
    return counter;
}

bool Sequence::get(int pos, ItemType& value) const //LOOKS GOOD
// If 0 <= pos < size(), copy into value the item at position pos
// of the sequence and return true.  Otherwise, leave value unchanged
// and return false.
{
    Node* p = head->next;
    if (pos>=0 && pos<size())
    {
        for (int i = 0; i<pos; i++) //iterate up to position you want
        {
            p = p->next;
        }
       value = p->data; //copy data into value
        return true;
    }
    else
    {return false;}
}

bool Sequence::set(int pos, const ItemType& value)
// If 0 <= pos < size(), replace the item at position pos in the
// sequence with value and return true.  Otherwise, leave the sequence
// unchanged and return false.
{
    
    if (pos>=0 && pos < size())
    {
        Node* p = head->next;
        for (int i = 0; i<pos; i++) //go through list until you get to position you want
        {
            p = p->next;
        }
            p->data = value; //copy value into data
            return true;
        }
    return false;
}


int Sequence::find(const ItemType& value) const

// Let p be the smallest integer such that value == the item at
// position p in the sequence; if no such item exists, let p be -1.
// Return p.
{
    int pos = -1;
    Node* p = head->next;
    for (int i = 0; i<size(); i++) //go through list
    {
        p = p->next;
        if (p->data == value) //if you find a node with data that matches the value you want
        {
            pos = i; //set position variable to position
        }
    }
    return pos;
}

void Sequence::swap(Sequence& other)
{
    //swap head
    Node* temp = head;
    head = other.head;
    other.head = temp;
    //swap size
    int tempsize = m_size;
    m_size = other.m_size;
    other.m_size = tempsize;
    
}
void Sequence::dump() const
{
    for (Node* p = head->next; p != head && p != nullptr; p = p->next)
        std::cerr << p->data <<",";
}

int subsequence(const Sequence& seq1, const Sequence& seq2) //no privates!!
{
        if(seq1.size() < seq2.size() or seq2.empty()){
            return -1;
        }
        ItemType firstval;
        ItemType secondval;
        int start; //make variable to hold starting position in seq1
        bool correct = false; //make bool to make it easier to see if there is a subsequence or not
        for(int i = 0; i < seq1.size(); i++) //go through seq1 to see if it contains the first value in seq2
        {
            seq1.get(i,firstval);
            seq2.get(0,secondval);
            if(firstval == secondval)
            {
                start = i; //if first value exists assign spot to start variable
                for(int j = 0, begin = i; j < seq2.size(); j++, begin++) //check if following values match up
                {
                    correct = true;
                    seq1.get(begin, firstval);
                    seq2.get(j, secondval);
                    if(firstval != secondval) //if one value is off, break out
                    {
                        correct = false;
                        break;
                    }
                }
                if(correct == true)
                {
                    return start;
                }
            }
        }
        return -1;
}

void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result)
{
    Sequence temp = result; //avoid aliasing
    while (temp.empty() == false)
    {
        temp.erase(0);
    }
    if (seq1.empty())
    {
        temp = seq2;
    }
    if (seq2.empty())
    {
        temp = seq1;
    }
    ItemType firstval;
    ItemType secondval;
    int i = 0;
    int j = 0;
    int z = 0;
    while (i<seq1.size() || j<seq2.size()) //make a loop so we can go through seq1 and 2 at the same time
    {
        if (i<seq1.size()) //if we haven't run out, insert value from seq1
        {
            seq1.get(i, firstval);
            temp.insert(z, firstval);
            i++;
            z++; //increment temp
        }
        if (j<seq2.size()) //if we haven't run out, insert value from seq1
        {
            seq2.get(j, secondval);
            temp.insert(z, secondval);
            j++;
            z++; //increment temp
        }
    }
    result = temp; 
}

