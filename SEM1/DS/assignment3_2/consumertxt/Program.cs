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
            string msg = "";
            while (true)
            {
                msg = r.RecMsg(msg);
                string path = @".\" + DateTime.Now.ToString("yyyyMMddHHmmssffff") + ".txt";
                System.IO.StreamWriter file = new System.IO.StreamWriter(path);
                file.WriteLine(msg);
                file.Close();
            }
        }
    }
}
