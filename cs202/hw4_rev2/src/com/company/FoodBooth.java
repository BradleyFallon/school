package com.company;

public class FoodBooth extends Booth {
    public FoodBooth() { super(); }

    public FoodBooth(String company) {
        super(company);
    }

    public void display() {
        System.out.print("Food Vending by ");
        super.display();
    }
}
