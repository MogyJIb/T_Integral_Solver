package by.gstu.it.presentation;

import by.gstu.it.data.FuncDto;
import by.gstu.it.domain.ClassInjector;

public class TestRunner {

    public static void main(String[] args) {
        System.out.println(ClassInjector.provideIntegralSolver().solve(
                new FuncDto("x*x+y*y+z*z-9", new int[]{0, 2, 0, 2, 0, 2}, 1))
        );
    }
}
