package by.gstu.it.data;

import java.io.Serializable;
import java.util.Objects;

public class ResultDto implements Serializable {
    public double solution;
    public String time;

    public ResultDto() {}

    public ResultDto(double solution, String time) {
        this.solution = solution;
        this.time = time;
    }

    public double getSolution() {
        return solution;
    }

    public void setSolution(double solution) {
        this.solution = solution;
    }

    public String getTime() {
        return time;
    }

    public void setTime(String time) {
        this.time = time;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        ResultDto resultDto = (ResultDto) o;
        return Double.compare(resultDto.solution, solution) == 0 &&
                Objects.equals(time, resultDto.time);
    }

    @Override
    public int hashCode() {
        return Objects.hash(solution, time);
    }

    @Override
    public String toString() {
        return "ResultDto{" +
                "solution=" + solution +
                ", time=" + time +
                '}';
    }
}
