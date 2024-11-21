using Base;


public class Program
{
    static void Main(string[] args)
    {
        Vector a = new Vector();
        Matrix b = new Matrix(a);
        Vector c = new Vector();

        Console.WriteLine(a);
        Console.WriteLine(b);
        b = a;
        Console.WriteLine(b);

        //Console.WriteLine(a);
        //Console.WriteLine(b);

        //a = Vector.Transpose(a);
        //Console.WriteLine(a);
        //Console.WriteLine(b);
        //Console.WriteLine(c);
        //Console.WriteLine(b * a);

        //Matrix d = new Matrix(5);
        //Console.WriteLine(d);
        //Console.WriteLine(d[4, 0]);
    }
}
