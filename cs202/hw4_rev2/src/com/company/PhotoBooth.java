package com.company;

public class PhotoBooth extends Booth {
    public PhotoBooth() { super(); }

    public PhotoBooth(String company) {
        super(company);
    }

    public void display() {
        System.out.print("Photo Booth with ");
        super.display();
    }
}
