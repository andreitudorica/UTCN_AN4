//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated from a template.
//
//     Manual changes to this file may cause unexpected behavior in your application.
//     Manual changes to this file will be overwritten if the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

namespace SOAPServices
{
    using System;
    using System.Collections.Generic;
    
    public partial class Package
    {
        public int ID { get; set; }
        public int Sender { get; set; }
        public int Receiver { get; set; }
        public string Name { get; set; }
        public string Description { get; set; }
        public string SenderCity { get; set; }
        public string DestinationCity { get; set; }
        public bool isTracked { get; set; }
        public string Tracking { get; set; }
    
        public virtual User User { get; set; }
        public virtual User User1 { get; set; }
    }
}
