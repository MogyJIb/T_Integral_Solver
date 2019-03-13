package by.gstu.it.domain;

public class IntegralSolver {

    static { System.loadLibrary("Integral_solver_MPI"); }

    public native double solve(String function, int[] args);

}
