package com.company;

public class Main {

    public static void main(String[] args) {

        BoothManager manager = new BoothManager();

        manager.addBooth(1, "FirstBooth");
        manager.addBooth(2, "SecondBooth");
        manager.addBooth(3, "ThirdBooth");
        manager.addBooth(4, "FourthBooth");

        manager.display_map();

        System.out.println("Done with test main.");
    }
}
