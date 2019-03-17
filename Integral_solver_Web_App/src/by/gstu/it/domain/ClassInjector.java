package by.gstu.it.domain;

public class ClassInjector {

    private static IntegralSolver integralSolver;

    public static IntegralSolver provideIntegralSolver() {
        if (integralSolver == null) integralSolver = new IntegralSolver();
        return integralSolver;
    }

}
