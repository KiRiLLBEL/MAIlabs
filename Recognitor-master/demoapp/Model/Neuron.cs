using static System.Math;

namespace demoapp.Model
{
    class Neuron
    {
        public Neuron(double[] inputs, double[] weights, NeuronType type)
        {
            _type = type;
            _weights = weights;
            _inputs = inputs;
        }
        private NeuronType _type;//тип нейрона
        private double[] _weights;//его веса
        private double[] _inputs;//его входы
        private double _output;//его выход
        private double _derivative;
        //константы для функции активации
        private double a = 0.01d;
        public double[] Weights { get => _weights; set => _weights = value; }
        public double[] Inputs { get => _inputs; set => _inputs = value; }
        public double Output { get => _output; }
        public double Derivative { get => _derivative; }
        public void Activator(double[] i, double[] w)//нелинейные преобразования
        {
            double sum = w[0];//аффиное преобразование через смещение(нулевой вес)
            for (int l = 0; l < i.Length; ++l)
                sum += i[l] * w[l + 1];//линейные преобразования
            switch (_type)
            {
                case NeuronType.Hidden://для нейронов скрытого слоя
                    _output = LeakyReLU(sum);
                    _derivative = LeakyReLU_Derivativator(sum);
                    break;
                case NeuronType.Output://для нейронов выходного слоя
                    _output = Exp(sum);
                    break;
            }
        }
        private double LeakyReLU(double sum) => (sum >= 0) ? sum : a * sum;
        private double LeakyReLU_Derivativator(double sum) => (sum >= 0) ? 1 : a;
    }
}
