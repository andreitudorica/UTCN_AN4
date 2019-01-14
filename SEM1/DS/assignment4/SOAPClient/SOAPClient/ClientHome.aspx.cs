using System;
using System.Data;

namespace SOAPClient
{
    public partial class ClientHome : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            if (Session["role"] == null || Session["role"].ToString() != "client")
            {
                Response.Redirect("~/");
            }

            if (!IsPostBack)
            {
                BindGridView();
            }
        }

        private void BindGridView()
        {
            DataTable dtPackage = new DataTable();


            // Add four columns to the DataTable. 
            dtPackage.Columns.Add("Sender");
            dtPackage.Columns.Add("Receiver");
            dtPackage.Columns.Add("Name");
            dtPackage.Columns.Add("Description");
            dtPackage.Columns.Add("SenderCity");
            dtPackage.Columns.Add("DestinationCity");
            dtPackage.Columns.Add("isTracked");
            dtPackage.Columns.Add("Tracking");

            Client.ClientService srv = new Client.ClientService();
            var packages = srv.ListPackages(Session["username"].ToString());
            foreach (var p in packages)
            {
                dtPackage.Rows.Add(p.Sender, p.Receiver, p.Name, p.Description, p.SenderCity, p.DestinationCity, p.isTracked, p.Tracking);
            }
            gvPackage.DataSource = dtPackage;
            gvPackage.DataBind();
        }

        protected void lbtnRebind_Click(object sender, EventArgs e)
        {
            BindGridView();
        }

        protected void lbtnSearch_Click(object sender, EventArgs e)
        {
            DataTable dtPackage = new DataTable();


            // Add four columns to the DataTable. 
            dtPackage.Columns.Add("Sender");
            dtPackage.Columns.Add("Receiver");
            dtPackage.Columns.Add("Name");
            dtPackage.Columns.Add("Description");
            dtPackage.Columns.Add("SenderCity");
            dtPackage.Columns.Add("DestinationCity");
            dtPackage.Columns.Add("isTracked");
            dtPackage.Columns.Add("Tracking");

            Client.ClientService srv = new Client.ClientService();
            var packages = srv.SearchPackages(Session["username"].ToString(), txtSearch.Text);
            foreach (var p in packages)
            {
                dtPackage.Rows.Add(p.Sender, p.Receiver, p.Name, p.Description, p.SenderCity, p.DestinationCity, p.isTracked, p.Tracking);
            }
            gvPackage.DataSource = dtPackage;
            gvPackage.DataBind();
        }


        protected void btnLogOut_Click(object sender, EventArgs e)
        {
            Response.Redirect("~/");
            Session["username"] = Session["role"] = "";
        }

    }
}