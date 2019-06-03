package com.company;

public class BoothNode23 {

    protected Booth[] data = new Booth[2];
    protected BoothNode23[] children = new BoothNode23[3];

    boolean isLeaf() {
        return children[0] == null;
    }
    boolean isFull() {
        return data[1] != null;
    }

    // new Nodes always are 2-nodes (1 value).  The node may be
    // a leaf, or has 2 children.
    BoothNode23(Booth booth) {
        data[0] = booth;
    }

    BoothNode23(Booth booth, BoothNode23 left, BoothNode23 right) {
        data[0] = booth;
        children[0] = left;
        children[1] = null;
        children[2] = right;
    }

}