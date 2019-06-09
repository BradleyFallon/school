package com.company;

public class Tree23 {
    protected BoothNode23 root;

    public Tree23() {
        root = null;
    }

    public void addBooth (Booth booth) {
        // if empty
        if ( ! root.isFull()) {
            root.addValue();
        }

    }

    public Booth lookupBooth(String keyword) {
        return new Booth();
    }
}