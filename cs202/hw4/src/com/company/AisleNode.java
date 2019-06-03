package com.company;

public class AisleNode {
    static int LEN_LONG;
    static int LEN_SHORT;

    protected Booth[] array;
    protected AisleNode next;
    protected int length;

    public AisleNode() {
        this.array = new Booth[LEN_SHORT];
        this.next = null;
        this.length = LEN_SHORT;
    }

    public Booth[] getArray() {
        return this.array;
    }

    public void setArray(Booth[] array) {
        this.array = array;
    }

    public AisleNode getNext() {
        return next;
    }

    public void setNext(AisleNode next) {
        this.next = next;
    }
}
