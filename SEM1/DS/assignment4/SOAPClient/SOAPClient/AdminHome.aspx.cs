using System;
using System.Data;
using System.Web.UI.WebControls;

namespace SOAPClient
{
    public partial class AdminHome : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            if (Session["role"] == null || Session["role"].ToString() != "admin")
            {
                Response.Redirect("~/");
            }

            if (!IsPostBack)
            {
                BindGridView();
            }
        }
        // https://code.msdn.microsoft.com/CSASPNETGridView-5b16ce70


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

            Admin.AdminService srv = new Admin.AdminService();
            var packages = srv.GetAllPackages();
            foreach (var p in packages)
            {
                dtPackage.Rows.Add(p.Sender, p.Receiver, p.Name, p.Description, p.SenderCity, p.DestinationCity, p.isTracked, p.Tracking);
            }
            gvPackage.DataSource = dtPackage;
            gvPackage.DataBind();
        }

   
        // GridView.RowDeleting Event 
        protected void RemovePackage(object sender, EventArgs e)
        {

            Admin.AdminService srv = new Admin.AdminService();
            var res = srv.RemovePackage(((LinkButton)sender).CommandArgument);
            BindGridView();
        }

        protected void lbtnAdd_Click(object sender, EventArgs e)
        {
            // Hide the Add button and showing Add panel. 
            lbtnAdd.Visible = false;
            btnStartTrackingPanel.Visible = false;
            btnAddCityPanel.Visible = false;
            pnlStartTracking.Visible = false;
            pnlAdd.Visible = true;
            pnlAddCity.Visible = false;
        }
        protected void btnStartTrackingPanel_Click(object sender, EventArgs e)
        {
            // Hide the Add button and showing Add panel. 
            lbtnAdd.Visible = false;
            btnStartTrackingPanel.Visible = false;
            btnAddCityPanel.Visible = false;
            pnlStartTracking.Visible = true;
            pnlAdd.Visible = false;
            pnlAddCity.Visible = false;
        }

        protected void btnAddCityPanel_Click(object sender, EventArgs e)
        {
            // Hide the Add button and showing Add panel. 
            lbtnAdd.Visible = false;
            btnStartTrackingPanel.Visible = false;
            btnAddCityPanel.Visible = false;
            pnlStartTracking.Visible = false;
            pnlAdd.Visible = false;
            pnlAddCity.Visible = true;
        }
        

        protected void lbtnSubmit_Click(object sender, EventArgs e)
        {

            Admin.AdminService srv = new Admin.AdminService();
            srv.AddPackage(txtSender.Text, txtReceiver.Text, txtName.Text, txtDescription.Text, txtSenderCity.Text, txtDestinationCity.Text);
            txtSender.Text = txtReceiver.Text = txtName.Text = txtDescription.Text = txtSenderCity.Text = txtDestinationCity.Text = "";
            // Show the Add button and hiding the Add panel. 

            lbtnAdd.Visible = true;
            btnStartTrackingPanel.Visible = true;
            btnAddCityPanel.Visible = true;
            pnlAdd.Visible = false;
            BindGridView();
        }

        protected void lnkStartTracking_Click(object sender, EventArgs e)
        {

            Admin.AdminService srv = new Admin.AdminService();
            srv.RegisterPackageForTracking(txtPackageName.Text);
            txtPackageName.Text = "";
            // Show the Add button and hiding the Add panel. 
            lbtnAdd.Visible = true;
            btnStartTrackingPanel.Visible = true;
            btnAddCityPanel.Visible = true;
            pnlAdd.Visible = false;
            pnlStartTracking.Visible = false;
            BindGridView();
        }

        protected void btnAddCity_Click(object sender, EventArgs e)
        {

            Admin.AdminService srv = new Admin.AdminService();
            srv.UpdatePackageTracking(txtPackage.Text,txtCity.Text);
            txtPackage.Text = txtCity.Text = "";
            // Show the Add button and hiding the Add panel. 
            lbtnAdd.Visible = true;
            btnStartTrackingPanel.Visible = true;
            btnAddCityPanel.Visible = true;
            pnlAdd.Visible = false;
            pnlStartTracking.Visible = false;
            pnlAddCity.Visible = false;
            BindGridView();
        }

        protected void lbtnCancel_Click(object sender, EventArgs e)
        {
            txtSender.Text = txtReceiver.Text = txtName.Text = txtDescription.Text = txtSenderCity.Text = txtDestinationCity.Text = "";
            // Show the Add button and hiding the Add panel. 
            lbtnAdd.Visible = true;
            btnStartTrackingPanel.Visible = true;
            btnAddCityPanel.Visible = true;
            pnlAdd.Visible = false;
            pnlStartTracking.Visible = false;
        }

        protected void lnkStartTrackingCancel_Click(object sender, EventArgs e)
        {
            txtPackageName.Text= "";
            // Show the Add button and hiding the Add panel. 
            lbtnAdd.Visible = true;
            btnStartTrackingPanel.Visible = true;
            btnAddCityPanel.Visible = true;
            pnlAdd.Visible = false;
            pnlStartTracking.Visible = false;
        }

        protected void btnCancelCity_Click(object sender, EventArgs e)
        {
            txtPackageName.Text = "";
            // Show the Add button and hiding the Add panel. 
            lbtnAdd.Visible = true;
            btnStartTrackingPanel.Visible = true;
            btnAddCityPanel.Visible = true;
            pnlAdd.Visible = false;
            pnlStartTracking.Visible = false;
            pnlAddCity.Visible = false;
        }
        protected void btnLogOut_Click(object sender, EventArgs e)
        {
            Response.Redirect("~/");
            Session["role"] = "";
        }
    }
}