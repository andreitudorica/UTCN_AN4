using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Services;

namespace SOAPServices
{
    /// <summary>
    /// Summary description for Register
    /// </summary>
    [WebService(Namespace = "Assignment4")]
    [WebServiceBinding(ConformsTo = WsiProfiles.BasicProfile1_1)]
    [System.ComponentModel.ToolboxItem(false)]
    // To allow this Web Service to be called from script, using ASP.NET AJAX, uncomment the following line. 
    // [System.Web.Script.Services.ScriptService]
    public class RegisterService : System.Web.Services.WebService
    {

        [WebMethod]
        public string Register(string username, string password)
        {
            using (var context = new assignmnet4SDEntities())
            {
                User u = new User();
                u.username = username;
                u.password = password;
                u.role = "client";
                context.Users.Add(u);
                context.SaveChanges();
            }
                return "Register done";
        }
    }
}
