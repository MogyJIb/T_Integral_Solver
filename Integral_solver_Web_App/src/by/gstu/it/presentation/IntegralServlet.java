package by.gstu.it.presentation;

import by.gstu.it.data.FuncDto;
import by.gstu.it.data.ResultDto;
import by.gstu.it.domain.ClassInjector;
import by.gstu.it.domain.IntegralSolver;
import by.gstu.it.domain.WorkTimeCounter;
import by.gstu.it.domain.Workable;
import com.google.gson.Gson;

import javax.servlet.http.*;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Arrays;

public class IntegralServlet extends HttpServlet {

    private final IntegralSolver solver = ClassInjector.provideIntegralSolver();
    private final Gson gson = new Gson();

    public void doPost(HttpServletRequest request, HttpServletResponse response)
            throws IOException {

        FuncDto funcDto = readJson(request);

        final double[] res = {0};
        WorkTimeCounter timeCounter = new WorkTimeCounter(() -> res[0] = solver.solve(funcDto));
        timeCounter.makeWork();

        String time = timeCounter.getWorkTimeFormatted();

        String gsonData = gson.toJson(new ResultDto(res[0], time));

        response.setContentType("application/json");
        PrintWriter out = response.getWriter();
        out.print(gsonData);
        out.flush();
    }

    private FuncDto readJson(HttpServletRequest request) {
        FuncDto funcDto = new FuncDto("x*x+y*y+z*z-9", new int[]{0, 2, 0, 2, 0, 2}, 1);
        try {
            StringBuilder sb = new StringBuilder();
            String s;
            while ((s = request.getReader().readLine()) != null) sb.append(s);

            funcDto = gson.fromJson(sb.toString(), FuncDto.class);
        } catch (Exception ignored) {}

        return funcDto;
    }

}