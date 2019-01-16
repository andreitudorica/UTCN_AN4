using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Common;
using Common.services;

namespace Server
{
    public class SellingPriceCalculator : MarshalByRefObject, ISellingPriceCalculator
    {
        public double ComputeSellingPrice(Car c)
        {
            double price=0;
            if (2018 - c.year < 7)
                price = c.price - (c.price / 7) * (2018 - c.year);
            return price;
        }
    }
}
