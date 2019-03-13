package by.gstu.it;

import by.gstu.it.domain.ClassInjector;
import by.gstu.it.domain.IntegralSolver;

import javax.servlet.http.*;
import java.io.IOException;

public class IntegralServlet extends HttpServlet {

    private final IntegralSolver solver = ClassInjector.provideIntegralSolver();

    public void doGet(HttpServletRequest httpServletRequest, HttpServletResponse httpServletResponse)
            throws IOException {
        httpServletResponse.getWriter().print(solver.solve("", new int[5]));
    }

}