package com.company;

public class BoothNode23 {

    protected Booth[] data = new Booth[2];
    protected BoothNode23[] children = new BoothNode23[3];

    public boolean isLeaf() {
        return children[0] == null;
    }
    public boolean isFull() {
        return data[1] != null;
    }

    public BoothNode23 insert(Booth booth) {
        if (data[0] == null) {
            data[0] = booth;
        } else if (data[1] == null) {
            if ( booth.company.compareTo(data[0].company)) {
                data[1] = data[0];
                data[0] = booth;
            } else {
                data[1] = booth;
            }
        } else {

        }
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