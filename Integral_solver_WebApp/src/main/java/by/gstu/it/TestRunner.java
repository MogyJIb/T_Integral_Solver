package by.gstu.it;

import by.gstu.it.domain.ClassInjector;

public class TestRunner {

    public static void main(String[] args) {
        System.out.println(ClassInjector.provideIntegralSolver().solve("x+y+z", new int[]{0, 2, 0, 2, 0, 2}));
    }
}
