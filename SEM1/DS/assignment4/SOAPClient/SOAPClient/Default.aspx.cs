using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace SOAPClient
{
    public partial class _Default : Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            Session["role"] = "";
        }

        protected void btnLogin_Click(object sender, EventArgs e)
        {
            Login.LoginService login = new Login.LoginService();
            string result = login.Login(txtUsername.Text, txtPassword.Value);
            if (result == "fail")
            {
                lblStatus.Text = "username or password is incorrect";
            }
            else
            {
                Session["role"] = result;
                Session["username"] = txtUsername.Text;
            }

            if (Session["role"].ToString() == "admin")
            {
                Response.Redirect("~/AdminHome.aspx");
            }

            else if (Session["role"].ToString() == "client")
            {
                Response.Redirect("~/ClientHome.aspx");
            }
            else
            {
                Session["username"]=Session["role"] = "";
            }
        }
    }
}