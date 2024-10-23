using System;

public abstract class Progression
{
    public abstract double CalculateSum(double start, double end, double step);
}

public class Linear : Progression
{
    public override double CalculateSum(double start, double end, double dif)
    {
        double n = ((end - start) / dif) + 1;
        return ((start + end) * n) / 2;
    }
}

public class Exponential : Progression
{
    public override double CalculateSum(double start, double end, double dif)
    {
        return (end * dif - start) / (dif - 1);
    }
}
