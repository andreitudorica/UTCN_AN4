package ro.tuc.dsrl.ds.handson.assig.three.queue.communication;

import java.io.Serializable;

/**
 * @Author: Technical University of Cluj-Napoca, Romania
 *          Distributed Systems, http://dsrl.coned.utcluj.ro/
 * @Module: assignment-one-client
 * @Since: Sep 1, 2015
 * @Description:
 *	Message class, serializable, used by the socket communication between the
 * components. It represents the exchange mechanism between the clients and the queue server.
 *
 * It has 2 fields:
 *  - type: the type of the message
 *          SEND - inserting a content into the queue
 *          READ - retrieving a content from the queue
 *          ACK - operation successful on the server side
 *          ERR - operation failed on the server side
 *  - content: content associated with the message.
 */
public class Message implements Serializable {
    private String type;
    private String content;

    public Message(String type, String content) {
        this.type = type;
        this.content = content;
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    public String getContent() {
        return content;
    }

    public void setContent(String content) {
        this.content = content;
    }
}
