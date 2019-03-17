package by.gstu.it.presentation;

import by.gstu.it.data.FuncDto;
import by.gstu.it.domain.ClassInjector;
import by.gstu.it.domain.IntegralSolver;

import javax.servlet.http.*;
import java.io.IOException;
import java.util.Arrays;

public class IntegralServlet extends HttpServlet {

    private final IntegralSolver solver = ClassInjector.provideIntegralSolver();

    public void doGet(HttpServletRequest httpServletRequest, HttpServletResponse httpServletResponse)
            throws IOException {

        FuncDto funcDto = new FuncDto("x*x+y*y+z*z-9", new int[]{0, 2, 0, 2, 0, 2});

        httpServletResponse.getWriter().println(funcDto.toString());
        httpServletResponse.getWriter().print(solver.solve(funcDto));
    }

}