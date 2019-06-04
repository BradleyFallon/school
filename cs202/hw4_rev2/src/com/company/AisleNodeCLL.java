package com.company;

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
