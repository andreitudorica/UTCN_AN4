using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Common
{
    [Serializable]
    public class Car
    {
        public int year { get; set; }
        public int engineSize { get; set; }
        public double price { get; set; }

        public Car(int y,int e,double p)
        {
            this.year = y;
            this.engineSize = e;
            this.price = p;
        }
    }
}
