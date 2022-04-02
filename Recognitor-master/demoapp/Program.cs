using System;
using System.Windows.Forms;

namespace demoapp
{
    static class Program
    {
        /// <summary>
        /// Главная точка входа для приложения.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            Form1 _form1View = new Form1();
            Model.Network network = new Model.Network(Model.NetworkMode.Demo);
            Presenter presenter = new Presenter(network, _form1View);

            Application.Run(_form1View);
        }
    }
}
