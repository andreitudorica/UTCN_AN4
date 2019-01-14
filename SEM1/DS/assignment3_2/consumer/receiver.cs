using System;
using System.Collections.Generic;
using System.Linq;
using System.Messaging;
using System.Text;
using System.Threading.Tasks;

namespace consumer
{
    class receiver
    {
        private string queueName = @".\Private$\EmailQueue";
        private MessageQueue messageQueue;
        public receiver()
        {
            //From Windows application
            messageQueue = new MessageQueue(queueName);
            messageQueue.Formatter = new BinaryMessageFormatter();
        
        }
        public string RecMsg(string prev)
        {
            Message message = messageQueue.Peek();
            while(message.Body.ToString() == prev)
                message = messageQueue.Peek();
            return message.Body.ToString();
        }
    }
}
