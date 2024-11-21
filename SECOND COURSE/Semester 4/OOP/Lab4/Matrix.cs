namespace MMatrix
{
    public class Matrix
    {
        private static uint Counter;
        public uint Id { get; private set; }

        public uint Rows { get; private set; }
        public uint Cols { get; private set; }
        private double[] Table = null;

        public delegate double Del(uint i, uint j);

        public Matrix()
        {
            Id = Counter++;
        }

        public Matrix(int size) : this(size, size, new double[size, size]) { }
        public Matrix(int size, double[,] from) : this(size, size, from) { }
        public Matrix(int rows, int cols) : this(rows, cols, new double[rows, cols]) { }

        public Matrix(int size, Del func) : this(size, size, func) { }

        public Matrix(int rows, int cols, Del func) : this(rows, cols, new double[rows, cols])
        {
            for (uint i = 0; i < Rows; i++)
                for (uint j = 0; j < Cols; j++)
                    Table[i * Cols + j] = func(i, j);
        }
        public Matrix(int rows, int cols, double[,] from)
        {
            Id = Counter++;
            if (rows <= 0)
                throw new ArgumentOutOfRangeException($"Ошибка размерности {rows}", $"Недопустимое количество строк объекта: {Id}");
            if (cols <= 0)
                throw new ArgumentOutOfRangeException($"Ошибка размерности {cols}", $"Недопустимое количество столбцов объекта: {Id}");
         
            Rows = (uint)rows;
            Cols = (uint)cols;
            Table = new double[Rows * Cols];

            for (uint i = 0; i < Rows; i++)
                for (uint j = 0; j < Cols; j++)
                    Table[i * Cols + j] = from[i, j];
        }

        public Matrix(int rows, int cols, double[] from)
        {
            Id = Counter++;
            if (rows <= 0)
                throw new ArgumentOutOfRangeException($"Ошибка размерности {rows}", $"Недопустимое количество строк объекта: {Id}");
            if (cols <= 0)
                throw new ArgumentOutOfRangeException($"Ошибка размерности {cols}", $"Недопустимое количество столбцов объекта: {Id}");
            if (from.Length != cols * rows)
                throw new ArgumentOutOfRangeException($"Ошибка длины массива {from.Length}", $"Недопустимое количество элементов матрицы объекта №{Id}: {rows}x{cols}");

            Rows = (uint)rows;
            Cols = (uint)cols;
            Table = new double[Rows * Cols];

            for (uint i = 0; i < Rows * Cols; i++)
                Table[i] = from[i];
        }


        public Matrix(in Matrix from) : this((int)from.Rows, (int)from.Cols, from.Table) { }

        public static bool CanMltpl(in Matrix a, in Matrix b) => a.Cols == b.Rows;

        public static bool CanAdd(in Matrix a, in Matrix b) => a.Rows == b.Rows && a.Cols == b.Cols;

        public static double MaxValue(in Matrix a)
        {
            double maxValue = Double.MinValue;
            foreach (var elem in a.Table)
                if (elem > maxValue)
                    maxValue = elem;
            return maxValue;
        }

        public static double MinValue(in Matrix a)
        {
            double minValue = Double.MaxValue;
            foreach (var elem in a.Table)
                if (elem < minValue)
                    minValue = elem;
            return minValue;
        }

        public static Matrix operator +(Matrix a, Matrix b)
        {
            if (!CanAdd(a, b))
                throw new ArgumentException($"Операция сложения с данными матрицами недоступна. 1: {a.Id}, 2: {b.Id}");

            Matrix result = new Matrix(a);
            for (int i = 0; i < b.Rows * b.Cols; i++)
                result.Table[i] += b.Table[i];
            return result;
        }
        public static Matrix operator -(Matrix a, Matrix b)
        {
            if (!CanAdd(a, b))
                throw new ArgumentException($"Операция вычитания с данными матрицами недоступна. 1: {a.Id}, 2: {b.Id}");

            Matrix result = new Matrix(a);
            for (int i = 0; i < b.Rows * b.Cols; i++)
                result.Table[i] -= b.Table[i];
            return result;
        }
        public static Matrix operator *(Matrix a, Matrix b)
        {
            if (!CanMltpl(a, b))
                throw new ArgumentException($"Операция умножения с данными матрицами недоступна. 1: {a.Id}, 2: {b.Id}");
            double temp;
            double[] matrix = new double[a.Rows * b.Cols];
            for (uint i = 0; i < a.Rows; ++i)
                for (uint j = 0; j < b.Cols; ++j)
                {
                    temp = 0;
                    for (uint k = 0; k < b.Rows; ++k)
                        temp += a.Table[i * a.Cols + k] * b.Table[k * b.Cols + j];
                    matrix[i * b.Cols + j] = temp;
                }
            return new Matrix((int)a.Rows, (int)b.Cols, matrix);
        }

        public static Matrix operator *(Matrix a, int k)
        {
            Matrix result = new Matrix(a);
            for (int i = 0; i < a.Rows * a.Cols; i++)
                result.Table[i] *= k;
            return result;
        }

        public double this[int i, int j]
        {
            get
            {
                if (i < 0 || i > Rows || j < 0 || j > Cols)
                    throw new ArgumentOutOfRangeException("Выход за пределы матрицы.");
                return Table[i * Cols + j];
            }
            set
            {
                if (i < 0 || i > Rows || j < 0 || j > Cols)
                    throw new ArgumentOutOfRangeException("Выход за пределы матрицы.");
                Table[i * Cols + j] = value;
            }
        }

        public override string ToString()
        {
            string matrixString = "";
            for (int i = 0; i < Rows; i++)
            {
                for (int j = 0; j < Cols; j++)
                    matrixString += Table[i * Cols + j].ToString() + '\t';


                matrixString += '\n';
            }

            return matrixString;
        }
    }
}
