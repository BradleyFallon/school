package com.company;

/*
================================================================================
Homework 5 for CS202
Bradley Fallon
bfallon@pdx.edu
6/10/2019

This is the 23Tree. Most of the meat is in the node class. This class just handles
root and has wrappers to get the recursion started.
================================================================================
*/

public class Tree23 {
    protected BoothNode23 root;

    public Tree23() {
        root = null;
    }

    public boolean addBooth (Booth booth) {
        boolean wasAdded;

        if (root == null) {
            root = new BoothNode23(booth);
            wasAdded = true;
        } else {
            wasAdded = root.add(booth);
            if (root.isFull()) {
                root = root.split();
            }
        }
        return wasAdded;
    }

    public Booth lookupBooth(String keyword) {
        if (root == null) return null;
        return root.lookup(keyword);
    }

    public void display() {
        if (root != null) root.display();
    }


    public static void main(String[] args) {
        Tree23 tree = new Tree23();
        FoodBooth newBooth;
        boolean wasAdded;

        String[] testStrings = {
                "Q", "W", "E", "R", "T", "Y", "U", "I", "O",
                "P", "A", "S", "D", "F", "G", "H", "J", "K",
                "L", "Z", "X", "C", "V", "B", "N", "M"};

        for (int i = 0; i < testStrings.length; ++i) {
            System.out.println((i+1) + " Adding " + testStrings[i]);
            newBooth = new FoodBooth(testStrings[i]);
            wasAdded = tree.addBooth(newBooth);
            System.out.println(wasAdded);
            System.out.println("Root is now ");
            tree.root.display();
            System.out.println("\n\n\n");
        }

    }
}