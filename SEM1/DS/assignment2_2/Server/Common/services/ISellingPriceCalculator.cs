using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Common.services
{
    public interface ISellingPriceCalculator
    {
        double ComputeSellingPrice(Car c);
    }
}
