using System;
using System.Runtime.Remoting.Channels; //To support and handle Channel and channel sinks
using System.Runtime.Remoting;
using System.Runtime.Remoting.Channels.Http; //For HTTP channel
using System.IO;
using Common.services;

namespace Server
{
    
    //Test service class
    public class Service : MarshalByRefObject, ItestService
    {
        public int WriteMessage(int num1, int num2)
        {
            Console.WriteLine(Math.Max(num1, num2));
            return Math.Max(num1, num2);
        }
    }


    //Server Class
    public class Server
    {
        public static void Main()
        {
            HttpChannel channel = new HttpChannel(8001); //Create a new channel
            ChannelServices.RegisterChannel(channel, false); //Register channel
            RemotingConfiguration.RegisterWellKnownServiceType(typeof(Service), "Service", WellKnownObjectMode.Singleton);
            RemotingConfiguration.RegisterWellKnownServiceType(typeof(SellingPriceCalculator), "SellingPriceCalculator", WellKnownObjectMode.Singleton);
            RemotingConfiguration.RegisterWellKnownServiceType(typeof(TaxCalculator), "TaxCalculator", WellKnownObjectMode.Singleton);
            Console.WriteLine("Server ON at port number:8001");
            Console.WriteLine("Please press enter to stop the server.");
            Console.ReadLine();
        }
    }
}