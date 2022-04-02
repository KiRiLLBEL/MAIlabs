using System;

namespace demoapp
{
    class Presenter
    {
        private Model.Network _net;
        private IView _view;

        public Presenter(Model.Network model, IView view)
        {
            _net = model;
            _view = view;
            _view.GotResult += new EventHandler<EventArgs>(OnGotResult);
        }

        private void OnGotResult (object sender, EventArgs e)
        {
            _net.ForwardPass(_net, _view.InputPixels);
            UpdateView();
        }

        private void UpdateView() => _view.NetOutput = _net.fact;
    }
}
