using System;
using System.Collections.Generic;
using System.Linq;
using System.Messaging;
using System.Text;
using System.Threading.Tasks;

namespace emailSender
{
    class Program
    {
        private void startListening()
        {
            //message path must be same as sender
            string messageQueuePath = @".\private$\EmailQueue";
            //create message queue instance
            _msmqQueue = new MessageQueue(messageQueuePath);
            //set formatter same as sender
            _msmqQueue.Formatter = new BinaryMessageFormatter();
            _msmqQueue.MessageReadPropertyFilter.SetAll();
            //Raise receive completed event 
            _msmqQueue.ReceiveCompleted += new ReceiveCompletedEventHandler(msmqQueue_ReceiveCompleted);
            //start receiving messages
            _msmqQueue.BeginReceive();
            //In msmqQueue_ReceiveCompleted
            //Extract the actual message 
            EmailEntities.EmailMessage emailMsg = (EmailEntities.EmailMessage)e.Message.Body;
            //Create mail message instance 
            MailMessage mailMesage = new MailMessage();
            //Set the properties
            mailMesage.Subject = emailMsg.Subject;
            mailMesage.Body = emailMsg.Body;
            //Create Smtp client instance
            SmtpClient oclient = new SmtpClient();
            //call the send method 
            oclient.Send(mailMesage);
        }
        static void Main(string[] args)
        {
            startListening();
        }
    }
}
