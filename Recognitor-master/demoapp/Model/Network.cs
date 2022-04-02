namespace demoapp.Model
{
    class Network
    {
        public Network(NetworkMode nm) => input_layer = new InputLayer(nm);
        //все слои сети
        private InputLayer input_layer = null;
        public HiddenLayer hidden_layer1 = new HiddenLayer(70, 15, NeuronType.Hidden, nameof(hidden_layer1));
        public HiddenLayer hidden_layer2 = new HiddenLayer(30, 70, NeuronType.Hidden, nameof(hidden_layer2));
        public OutputLayer output_layer = new OutputLayer(10, 30, NeuronType.Output, nameof(output_layer));
        //массив для хранения выхода сети
        public double[] fact = new double[10];
        //непосредственно обучение
        public void Train(Network net)//backpropagation method
        {
            int epoches = 1200;
            for (int k = 0; k < epoches; ++k)
            {
                for (int i = 0; i < net.input_layer.Trainset.Length; ++i)
                {
                    //прямой проход
                    ForwardPass(net, net.input_layer.Trainset[i].Item1);
                    //вычисление ошибки по итерации
                    double[] errors = new double[net.fact.Length];
                    for (int x = 0; x < errors.Length; ++x)
                    {
                        errors[x] = (x == net.input_layer.Trainset[i].Item2) ? -(net.fact[x] - 1.0d) : -net.fact[x];
                    }
                    //обратный проход и коррекция весов
                    double[] temp_gsums1 = net.output_layer.BackwardPass(errors);
                    double[] temp_gsums2 = net.hidden_layer2.BackwardPass(temp_gsums1);
                    net.hidden_layer1.BackwardPass(temp_gsums2);
                }
            }

            //загрузка скорректированных весов в "память"
            net.hidden_layer1.WeightInitialize(MemoryMode.SET, nameof(hidden_layer1));
            net.hidden_layer2.WeightInitialize(MemoryMode.SET, nameof(hidden_layer2));
            net.output_layer.WeightInitialize(MemoryMode.SET, nameof(output_layer));
        }
        //тестирование сети
        public void Test(Network net)
        {
            for (int i = 0; i < net.input_layer.Testset.Length; ++i)
                ForwardPass(net, net.input_layer.Testset[i]);
        }
        public void ForwardPass(Network net, double[] netInput)
        {
            net.hidden_layer1.Data = netInput;
            net.hidden_layer1.Recognize(null, net.hidden_layer2);
            net.hidden_layer2.Recognize(null, net.output_layer);
            net.output_layer.Recognize(net, null);
        }
    }
}
