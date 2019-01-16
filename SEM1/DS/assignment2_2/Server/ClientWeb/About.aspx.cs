using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Runtime.Remoting.Channels;
using System.Runtime.Remoting.Channels.Http; 
using Common.services;
using Common;

namespace ClientWeb
{
    public partial class About : Page
    {
        private HttpChannel channel;
        private ITaxCalculator taxService;
        private ISellingPriceCalculator sellingPriceService;
        protected void Page_Load(object sender, EventArgs e)
        {
            }
        

        protected void btnCompute_Click(object sender, EventArgs e)
        {
            int year=0, engine=0;
            double price=0;
            if (txtYear.Text != "" && txtPurchasingPrice.Text != null && txtEngineSize.Text != "")
            {
                year = Int32.Parse(txtYear.Text);
                price = Double.Parse(txtPurchasingPrice.Text);
                engine = Int32.Parse(txtEngineSize.Text);
                Car c = new Car(year,engine,price);
                channel = new HttpChannel(8002); //Create a new channel
                ChannelServices.RegisterChannel(channel, false);
                taxService = (ITaxCalculator)Activator.GetObject(typeof(ITaxCalculator), "http://localhost:8001/TaxCalculator");
                sellingPriceService = (ISellingPriceCalculator)Activator.GetObject(typeof(ISellingPriceCalculator), "http://localhost:8001/SellingPriceCalculator");
                lblError.Visible = false;
                lblTax.Text= "tax: " + taxService.ComputeTax(c);
                lblSellingPrice.Text= "selling price: " + String.Format("{0:0.00}", sellingPriceService.ComputeSellingPrice(c)) +" LEI";
                ChannelServices.UnregisterChannel(channel);
            }
            else
            {
                lblError.Visible = true;
                lblError.Text = "Some fields are empty!!";
            }

        }
    }
}