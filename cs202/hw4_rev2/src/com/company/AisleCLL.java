package com.company;


/*
================================================================================
Homework 5 for CS202
Bradley Fallon
bfallon@pdx.edu
6/10/2019

This is the CLL class, which contains AisleNodes. Aisles are arrays of booths.
This class is very generic, not intended to do anything special for booths.
This class is extended as BootMap, which has non-generic functionality.
================================================================================
*/


/*
    The way this Circular Linked List is implemented, there is one pointer owned by the list, "rear".
    Rear is the lik the back of a queue. The "next" after rear is the front. This is like the first
    item at the front of a queue.

  front (no member)       rear (insert here)
    |                       |
    v                       v
    []--> []--> []--> []--> []--|
     ^                          |
     |__________________________|

 */

public class AisleCLL {
    protected AisleNodeCLL rear;

    public AisleCLL() {
        this.rear = null;
    }

    public boolean isEmpty() {
        return (rear == null);
    }

    // Insert booth at rear
    public boolean insert(Aisle aisle) {
        AisleNodeCLL newNode = new AisleNodeCLL(aisle);

        if (this.isEmpty()){
            this.rear = newNode;
            newNode.setNext(newNode);
        } else {
            // New node becomes rear, and needs to take the front pointer
            newNode.setNext(
                    // rear.next is the front
                    this.rear.getNext()
            );
            this.rear.setNext(newNode);
            this.rear = newNode;
        }
        return true;
    }

    // Insert booth at index (0 is front)
    public boolean insert(Aisle aisle, int index) {
        AisleNodeCLL newNode;

        // if index is negative, reject
        if (index < 0) return false;
        // If index is 0, use normal insert
        if (index == 0) return insert(aisle);
        // If there was a non-zero index given and the list is empty, return false
        if (this.isEmpty()) return false;
        // Normal condition, recursively insert ahead, starting from front
        newNode = new AisleNodeCLL(aisle);
        return insertAhead(rear.getNext(), newNode, --index);
    }

    protected boolean insertAhead(AisleNodeCLL current, AisleNodeCLL newNode, int index) {
        // If index is 0, insert here
        if (index == 0) {
            newNode.setNext(current.getNext());
            current.setNext(newNode);
            return true;
        }
        return insertAhead(current.getNext(), newNode, --index);
    }

    // Insert booth at end, becoming front
    public boolean insertFront(Aisle aisle) {
        AisleNodeCLL newNode;
        // If is empty, use the normal insert to get started
        if (this.isEmpty()) return insert(aisle);
        // Make a new node and cut at front
        newNode = new AisleNodeCLL(aisle);
        newNode.setNext(this.rear.getNext());
        this.rear.setNext(newNode);
        return true;
    }
}