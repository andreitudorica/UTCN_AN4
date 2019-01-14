using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace SOAPServices
{
    public class PackageDTO
    {
        public string Sender { get; set; }
        public string Receiver { get; set; }
        public string Name { get; set; }
        public string Description { get; set; }
        public string SenderCity { get; set; }
        public string DestinationCity { get; set; }
        public string isTracked { get; set; }
        public string Tracking { get; set; }
    }
}