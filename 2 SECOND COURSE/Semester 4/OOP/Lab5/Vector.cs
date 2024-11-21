namespace Base
{
    public class Vector : Matrix
    {
        public Vector() : base(3, 1) { }
        public Vector(int ROWS) : base(ROWS, 1) { }
        public Vector(int ROWS, int COLUMNS) : base(ROWS, COLUMNS) { }
        //public Vector(int ROWS, int COLUMNS) : base(ROWS, COLUMNS = 1) { }
        public Vector(int ROWS, double[,] array) : base(ROWS, 1, array) { }
        public Vector(int ROWS, int COLUMNS, double[] array) : base(ROWS, 1, array) { }
        public Vector(int ROWS, int COLUMNS, double[,] array) : base(ROWS, 1, array) { }
        public Vector(Vector copy) : base(copy.ROWS, copy.COLUMNS, copy.Array) { }
        public Vector(Matrix copy) : base(copy)
        {
            if (ROWS > 1 && COLUMNS > 1)
                throw new ArgumentException("Невозможно копировать в вектор из матрицы");
        }

        private void Transpose() => (COLUMNS, ROWS) = (ROWS, COLUMNS);

        public static Vector Transpose(Vector vec)
        {
            (vec.COLUMNS, vec.ROWS) = (vec.ROWS, vec.COLUMNS);
            return vec;
        }

        public double GetModule()
        {
            var module = 0.0;
            for (var i = 0; i < ROWS * COLUMNS; i++)
                module += Math.Pow(Array[i], 2);
            return Math.Sqrt(module);
        }

        public Vector Normalize()
        {
            var module = GetModule();
            for (var i = 0; i < ROWS * COLUMNS; i++)
                Array[i] /= module;
            return this;
        }

        public static Vector operator +(Vector A, Vector B)
        {
            if (!Addition(A, B))
                throw new ArgumentException($"Операция сложения с данными векторами недоступна. 1: {A.Id}, 2: {B.Id}");

            var newArray = new double[A.ROWS * A.COLUMNS];
            for (var i = 0; i < A.ROWS * A.COLUMNS; i++)
                newArray[i] = A.Array[i] + B.Array[i];
            return new Vector(A.ROWS, A.COLUMNS, newArray);
        }

        public static Vector operator -(Vector A, Vector B)
        {
            if (!Addition(A, B))
                throw new ArgumentException($"Операция вычитания с данными векторами недоступна. 1: {A.Id}, 2: {B.Id}");

            var newArray = new double[A.ROWS * A.COLUMNS];
            for (var i = 0; i < A.ROWS * A.COLUMNS; i++)
                newArray[i] = A.Array[i] - B.Array[i];
            return new Vector(A.ROWS, A.COLUMNS, newArray);
        }

        public double this[int index]
        {
            get
            {
                if (index >= ROWS || index < 0 || index >= COLUMNS) 
                    throw new IndexOutOfRangeException("Выход за пределы вектора.");
                return Array[index];
            }
            set
            {
                if (index >= ROWS || index < 0 || index >= COLUMNS) 
                    throw new IndexOutOfRangeException("Выход за пределы вектора.");
                Array[index] = value;
            }
        }

    };
}