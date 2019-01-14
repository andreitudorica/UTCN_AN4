using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Messaging;
using System.Net.Mail;
using System.Text;
using System.Threading.Tasks;

namespace consumer
{
    class Program
    {
        static void Main(string[] args)
        {
            receiver r = new receiver();
            SmtpClient SmtpServer = new SmtpClient("smtp.gmail.com");
            SmtpServer.Port = 587;
            SmtpServer.Credentials = new System.Net.NetworkCredential("justletmeuseausernameffs", "Andrei1234");
            SmtpServer.EnableSsl = true;
            string msg = "";
            while (true)
            {
                msg = r.RecMsg(msg);
                string path = @".\" + DateTime.Now.ToString("yyyyMMddHHmmssffff") + ".txt";
                System.IO.StreamWriter file = new System.IO.StreamWriter(path);
                file.WriteLine(msg);
                file.Close();

                MailMessage mail = new MailMessage();

                mail.From = new MailAddress("justletmeuseausernameffs@gmail.com");
                mail.To.Add("andreitudoricacj@gmail.com");
                mail.Subject = "The best DVD service ever";
                mail.Body = msg;
                SmtpServer.Send(mail);

            }
        }
    }
}
