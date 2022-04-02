namespace demoapp.Model
{
    enum MemoryMode//режимы работы памяти
    {
        GET,
        SET
    }
    enum NeuronType//тип нейрона
    {
        Hidden,
        Output
    }
    enum NetworkMode//режимы работы сети
    {
        Train,
        Test,
        Demo
    }
}