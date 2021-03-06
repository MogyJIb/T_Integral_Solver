package by.gstu.it.data;

import java.util.Arrays;
import java.util.Objects;

public class FuncDto {
    public String function;
    public int[] args;
    public int mpi;

    public FuncDto(String function, int[] args, int mpi) {
        this.function = function;
        this.args = args;
        this.mpi = mpi;
    }

    public FuncDto() {}

    public String getFunction() {
        return function;
    }

    public void setFunction(String function) {
        this.function = function;
    }

    public int[] getArgs() {
        return args;
    }

    public void setArgs(int[] args) {
        this.args = args;
    }

    public int getMpi() {
        return mpi;
    }

    public void setMpi(int mpi) {
        this.mpi = mpi;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        FuncDto funcDto = (FuncDto) o;
        return mpi == funcDto.mpi &&
                Objects.equals(function, funcDto.function) &&
                Arrays.equals(args, funcDto.args);
    }

    @Override
    public int hashCode() {
        int result = Objects.hash(function, mpi);
        result = 31 * result + Arrays.hashCode(args);
        return result;
    }

    @Override
    public String toString() {
        StringBuilder result = new StringBuilder("");

        result.append(function);

        for (int i = 0; i < args.length ; i++)
            result.append(" " + args[i]);

        return result.toString();
    }
}
