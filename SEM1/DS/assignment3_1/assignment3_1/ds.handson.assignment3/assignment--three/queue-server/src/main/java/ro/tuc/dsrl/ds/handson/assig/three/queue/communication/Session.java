package ro.tuc.dsrl.ds.handson.assig.three.queue.communication;

import ro.tuc.dsrl.ds.handson.assig.three.queue.queue.Queue;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;

/**
 * @Author: Technical University of Cluj-Napoca, Romania
 *          Distributed Systems, http://dsrl.coned.utcluj.ro/
 * @Module: assignment-one-server
 * @Since: Sep 1, 2015
 * @Description:
 * 	Serves for dealing with the connection to a client
 * 	(receiving messages, decoding them and sending a response).
 */
public class Session extends Thread {

	private Socket clientSocket;
	private ObjectInputStream inFromClient;
	private ObjectOutputStream outToClient;

	public Session(Socket cSocket) {
		this.clientSocket = cSocket;
		try {
			inFromClient = new ObjectInputStream(clientSocket.getInputStream());
			outToClient = new ObjectOutputStream(clientSocket.getOutputStream());
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	@Override
	public void run() {
		Message messageReceived;

		try {
			// Wait for message from client
			messageReceived = (Message) inFromClient.readObject();

			// Treat messages according to the type of the message
			switch (messageReceived.getType()){
				case "SEND":
					try {
						//insert the message into the queue
						Queue.getInstance().put(messageReceived.getContent());
						sendMessageToClient(new Message("ACK", null));
					} catch (InterruptedException e) {
						e.printStackTrace();
						sendMessageToClient(new Message("ERR", null));
					}
					break;
				case "READ":
					try {
						//retrieve a message from the queue
						//since the underlying queue is a BlockingQueue, this method call will wait if the queue is empty
						String content = Queue.getInstance().get();
						sendMessageToClient(new Message("ACK",content));
					} catch (InterruptedException e) {
						e.printStackTrace();
						sendMessageToClient(new Message("ERR",null));
					}
					break;
			}

		} catch (ClassNotFoundException | IOException e) {
			e.printStackTrace();
		}

		closeAll();
	}

	public void sendMessageToClient(Message messageToSend) {
		try {
			outToClient.writeObject(messageToSend);
		} catch (IOException e) {
			e.printStackTrace();
		}

	}

	public void closeAll() {
		try {
			// Close the input stream
			if (inFromClient != null) {
				inFromClient.close();
			}
			// Close the output stream
			if (outToClient != null) {
				outToClient.close();
			}
			// Close the socket
			if (clientSocket != null) {
				clientSocket.close();
			}
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			inFromClient = null;
			outToClient = null;
			clientSocket = null;
		}
	}
}
