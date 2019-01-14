using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Services;

namespace SOAPServices
{
    /// <summary>
    /// Summary description for Login
    /// </summary>
    [WebService(Namespace = "Assignment4")]
    [WebServiceBinding(ConformsTo = WsiProfiles.BasicProfile1_1)]
    [System.ComponentModel.ToolboxItem(false)]
    // To allow this Web Service to be called from script, using ASP.NET AJAX, uncomment the following line. 
    // [System.Web.Script.Services.ScriptService]
    public class LoginService : System.Web.Services.WebService
    {

        [WebMethod]
        public string Login(string username, string password)
        {
            string result = "fail";
            using (var context = new assignmnet4SDEntities())
            {
                var user = context.Users.Where(u => u.username == username && u.password == password).FirstOrDefault();
                if (user != null)
                    return user.role;
            }
            return result;
        }
    }
}
