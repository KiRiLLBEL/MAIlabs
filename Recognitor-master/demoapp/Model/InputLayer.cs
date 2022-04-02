namespace demoapp.Model
{
    class InputLayer
    {
        public InputLayer(NetworkMode nm)
        {
            System.Drawing.Bitmap bitmap;
            switch (nm)
            {
                case NetworkMode.Train:
                    bitmap = Properties.Resources.trainset;
                    for (int y = 0; y < bitmap.Height / 5; ++y)
                        for (int x = 0; x < bitmap.Width / 3; ++x)
                        {
                            _trainset[x + y * (bitmap.Width / 3)].Item2 = (byte)y;
                            _trainset[x + y * (bitmap.Width / 3)].Item1 = new double[3 * 5];
                            for (int m = 0; m < 5; ++m)
                                for (int n = 0; n < 3; ++n)
                                {
                                    _trainset[x + y * (bitmap.Width / 3)].Item1[n + 3 * m] =
                                        (bitmap.GetPixel(n + 3 * x, m + 5 * y).R +
                                        bitmap.GetPixel(n + 3 * x, m + 5 * y).G +
                                        bitmap.GetPixel(n + 3 * x, m + 5 * y).B) / (765.0d);
                                }
                        }
                    //перетасовка обучающей выборки методом Фишера-Йетса
                    for (int n = Trainset.Length - 1; n >= 1; --n)
                    {
                        int j = random.Next(n + 1);
                        (double[], byte) temp = _trainset[n];
                        _trainset[n] = _trainset[j];
                        _trainset[j] = temp;
                    }
                    break;
                case NetworkMode.Test:
                    bitmap = Properties.Resources.testset;
                    for (int y = 0; y < bitmap.Height / 5; ++y)
                        for (int x = 0; x < bitmap.Width / 3; ++x)
                        {
                            _testset[x + y * (bitmap.Width / 3)] = new double[3 * 5];
                            for (int m = 0; m < 5; ++m)
                                for (int n = 0; n < 3; ++n)
                                {
                                    _trainset[x + y * (bitmap.Width / 3)].Item1[n + 3 * m] =
                                        (bitmap.GetPixel(n + 3 * x, m + 5 * y).R +
                                        bitmap.GetPixel(n + 3 * x, m + 5 * y).G +
                                        bitmap.GetPixel(n + 3 * x, m + 5 * y).B) / (765.0d);
                                }
                        }
                    break;
            }
        }

        private System.Random random = new System.Random();

        private (double[], byte)[] _trainset = new(double[], byte)[100];//100 изображений в обучающей выборке
        public (double[], byte)[] Trainset { get => _trainset; }

        private double[][] _testset = new double[10][];//10 изображений в тестовой выборке
        public double[][] Testset { get => _testset; }
    }
}
