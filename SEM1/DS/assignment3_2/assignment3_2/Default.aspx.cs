using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Messaging;
using System.Net.Mail;

namespace assignment3_2
{
    public partial class _Default : Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
        }

        protected void btnAddDVD_Click(object sender, EventArgs e)
        {
            DVD dvd = new DVD();
            dvd.title = txtTitle.Text;
            dvd.description = txtDescription.Text;
            dvd.year=Int32.Parse(txtYear.Text);

            string msmqQueuePath = @".\Private$\EmailQueue";
            //From Windows Service, use this code
            MessageQueue messageQueue = null;
            if (MessageQueue.Exists(msmqQueuePath))
                messageQueue = new MessageQueue(msmqQueuePath);
            else
            {
                // Create the Queue
                MessageQueue.Create(msmqQueuePath);
                messageQueue = new MessageQueue(@".\Private$\SomeTestName");
            }
            // Create new instance of Message object
            Message msmqMsg = new Message();
            // Assign email information to the Message body
            msmqMsg.Body = "A new DVD has been added to the library: \ntitle: " + dvd.title + "\ndescription: " + dvd.description + "\nyear: " + dvd.year;
            //set Recoverable which indicates message is guaranteed 
            msmqMsg.Recoverable = true;
            //Set Formatter to serialize the object,I’m using binary //serialization
            msmqMsg.Formatter = new BinaryMessageFormatter();
            messageQueue.Formatter = new BinaryMessageFormatter();
            messageQueue.Purge();
            messageQueue.Send(msmqMsg);
        }
    }
}