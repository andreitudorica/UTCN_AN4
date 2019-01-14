using System.Collections.Generic;
using System.Linq;
using System.Web.Services;

namespace SOAPServices
{
    /// <summary>
    /// Summary description for ClientService
    /// </summary>
    [WebService(Namespace = "Assignment4")]
    [WebServiceBinding(ConformsTo = WsiProfiles.BasicProfile1_1)]
    [System.ComponentModel.ToolboxItem(false)]
    // To allow this Web Service to be called from script, using ASP.NET AJAX, uncomment the following line. 
    // [System.Web.Script.Services.ScriptService]
    public class ClientService : System.Web.Services.WebService
    {

        [WebMethod]
        public List<PackageDTO> ListPackages(string username)
        {
            var result = new List<PackageDTO>();
            using (var context = new assignmnet4SDEntities())
            {
                foreach (var p in context.Packages.Where(o => (context.Users.Where(t=>t.ID==o.Receiver).FirstOrDefault().username == username) 
                || (context.Users.Where(t => t.ID == o.Sender).FirstOrDefault().username == username)))
                {
                    result.Add(new PackageDTO()
                    {
                        Sender = context.Users.Find(p.Sender).username,
                        Receiver = context.Users.Find(p.Receiver).username,
                        Name = p.Name,
                        Description = p.Description,
                        SenderCity = p.SenderCity,
                        DestinationCity = p.DestinationCity,
                        isTracked = p.isTracked ? "yes" : "no",
                        Tracking = p.Tracking
                    });
                }
            }
            return result;
        }


        [WebMethod]
        public List<PackageDTO> SearchPackages(string username, string searchText)
        {
            var result = new List<PackageDTO>();
            using (var context = new assignmnet4SDEntities())
            {
                foreach (var p in context.Packages.Where(o => o.Name == searchText 
                && ((context.Users.Where(t => t.ID == o.Receiver).FirstOrDefault().username == username)
                || (context.Users.Where(t => t.ID == o.Sender).FirstOrDefault().username == username))))
                {
                    result.Add(new PackageDTO()
                    {
                        Sender = context.Users.Find(p.Sender).username,
                        Receiver = context.Users.Find(p.Receiver).username,
                        Name = p.Name,
                        Description = p.Description,
                        SenderCity = p.SenderCity,
                        DestinationCity = p.DestinationCity,
                        isTracked = p.isTracked ? "yes" : "no",
                        Tracking = p.Tracking
                    });
                }
            }
            return result;
        }

    }
}