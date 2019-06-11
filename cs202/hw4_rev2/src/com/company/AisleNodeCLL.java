package com.company;

/*
================================================================================
Homework 5 for CS202
Bradley Fallon
bfallon@pdx.edu
6/10/2019

This is a node which is to be used with a CLL, and carries an Aisle (booth array).
================================================================================
*/

public class AisleNodeCLL {
    protected AisleNodeCLL next;
    protected Aisle aisle;

    public AisleNodeCLL() {
        this.aisle = new Aisle();
        this.next = null;
    }

    public AisleNodeCLL(Aisle aisle) {
        this.aisle = aisle;
        this.next = null;
    }

    public AisleNodeCLL getNext() {
        return next;
    }

    public void setNext(AisleNodeCLL next) {
        this.next = next;
    }

    public Aisle getAisle() {
        return this.aisle;
    }

    public void setAisle(Aisle data) {
        this.aisle = data;
    }
}
