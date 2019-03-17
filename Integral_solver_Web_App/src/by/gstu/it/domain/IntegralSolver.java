package by.gstu.it.domain;

import by.gstu.it.data.FuncDto;

public class IntegralSolver {
    private static final String INPUT = "input.txt";
    private static final String OUTPUT = "output.txt";
    private static final String SOLVER = "Integral_solver_Core.exe";

    public double solve(FuncDto funcDto) {
        FileHelper.writeRes(INPUT, funcDto.toString());
        ProcessHelper.runAndWait(buildCommands());
        String content = FileHelper.readRes(OUTPUT);
        return parseResult(content);
    }

    private double parseResult(String content) {
        double result = 0.0;
        try {
            result = Double.parseDouble(content);
        } catch (Exception ignored) {}
        return result;
    }

    private String[] buildCommands() {
        String path = this.getClass().getClassLoader().getResource(SOLVER).getFile();
        if (path.startsWith("/") || path.startsWith("\\"))
            path = path.substring(1);
        path = path.substring(0, path.length() - SOLVER.length());

        return new String[]{ path + SOLVER, path };
    }

}
