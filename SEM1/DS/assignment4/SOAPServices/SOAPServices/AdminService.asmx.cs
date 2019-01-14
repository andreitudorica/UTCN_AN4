using System.Collections.Generic;
using System.Linq;
using System.Web.Services;

namespace SOAPServices
{
    /// <summary>
    /// Summary description for AdminService
    /// </summary>
    [WebService(Namespace = "Assignment4")]
    [WebServiceBinding(ConformsTo = WsiProfiles.BasicProfile1_1)]
    [System.ComponentModel.ToolboxItem(false)]
    // To allow this Web Service to be called from script, using ASP.NET AJAX, uncomment the following line. 
    // [System.Web.Script.Services.ScriptService]
    public class AdminService : System.Web.Services.WebService
    {
        [WebMethod]
        public List<PackageDTO> GetAllPackages()
        {
            var result = new List<PackageDTO>();
            using (var context = new assignmnet4SDEntities())
            {
                foreach (var p in context.Packages)
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
        public string AddPackage(string sender, string receiver, string name, string description, string senderCity, string destinationCity)
        {
            try
            {
                Package p = new Package();
                using (var context = new assignmnet4SDEntities())
                {
                    p.Sender = context.Users.Where(u => u.username == sender).FirstOrDefault().ID;
                    p.Receiver = context.Users.Where(u => u.username == receiver).FirstOrDefault().ID;
                    p.Name = name;
                    p.Description = description;
                    p.SenderCity = senderCity;
                    p.DestinationCity = destinationCity;
                    p.isTracked = false;
                    p.Tracking = "";
                    context.Packages.Add(p);
                    context.SaveChanges();
                }
                return "Added";
            }
            catch
            {
                return "Failed";
            }
        }

        [WebMethod]
        public string RemovePackage(string name)
        {
            try
            {
                using (var context = new assignmnet4SDEntities())
                {
                    context.Packages.Remove(context.Packages.Where(p => p.Name == name).FirstOrDefault());
                    context.SaveChanges();
                }
                return "removed";
            }
            catch
            {
                return "failed";
            }
        }

        [WebMethod]
        public string RegisterPackageForTracking(string name)
        {
            try
            {
                using (var context = new assignmnet4SDEntities())
                {
                    context.Packages.Where(p => p.Name == name).FirstOrDefault().isTracked=true;
                    context.SaveChanges();
                }
                return "registered";
            }
            catch
            {
                return "failed";
            }
        }

        [WebMethod]
        public string UpdatePackageTracking(string name, string cityDate)
        {
            try
            {
                using (var context = new assignmnet4SDEntities())
                {
                    context.Packages.Where(p => p.Name == name).FirstOrDefault().Tracking= context.Packages.Where(p => p.Name == name).FirstOrDefault().Tracking==""?cityDate: context.Packages.Where(p => p.Name == name).FirstOrDefault().Tracking+"~"+cityDate;
                    context.SaveChanges();
                }
                return "updated";
            }
            catch
            {
                return "failed";
            }
        }
    }
}
