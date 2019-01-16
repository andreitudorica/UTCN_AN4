using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Common;
using Common.services;

namespace Server
{
    public class TaxCalculator : MarshalByRefObject, ITaxCalculator
    {
        public double ComputeTax(Car c)
        {
            double tax;
            if (c.engineSize < 1600)
                tax = (c.engineSize / 200) * 8;
            else if (c.engineSize < 2000)
                tax = (c.engineSize / 200) * 18;
            else if(c.engineSize < 2600)
                tax = (c.engineSize / 200) * 72;
            else if(c.engineSize < 3000)
                tax = (c.engineSize / 200) * 144;
            else 
                tax = (c.engineSize / 200) * 290;
            return tax;
        }
    }
}
