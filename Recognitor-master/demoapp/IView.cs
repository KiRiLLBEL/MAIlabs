using System;

namespace demoapp
{
    public interface IView
    {
        double[] InputPixels{ get; }
        double[] NetOutput { set; }
        event EventHandler<EventArgs> GotResult;
    }
}
