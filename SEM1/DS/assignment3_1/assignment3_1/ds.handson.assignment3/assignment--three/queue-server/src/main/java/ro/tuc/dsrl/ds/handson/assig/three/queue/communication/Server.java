package ro.tuc.dsrl.ds.handson.assig.three.queue.communication;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

/**
 * @Author: Technical University of Cluj-Napoca, Romania
 *          Distributed Systems, http://dsrl.coned.utcluj.ro/
 * @Module: assignment-one-server
 * @Since: Sep 1, 2015
 * @Description:
 * 	Serves for creating a socket that listens, accepts connections and creates
 *	a thread that deals with the communication with the client.
 */
public class Server implements Runnable {
	private ServerSocket serverSocket;

	/**
	 * Create a socket object from the ServerSocket to listen to and accept connections
	 * @param port the port on which the ServerSocket will be bound to
	 * @throws IOException
	 */
	public Server(int port) throws IOException {
		serverSocket = new ServerSocket(port);
		new Thread(this).start();
	}

	/**
	 * Accepts connections from clients and assigns a thread to deal with the messages from and to the respective client.
	 */
	public void run() {
		while (true) {
			try {
				synchronized (this) {
					Socket clientSocket;
					clientSocket = serverSocket.accept();
					Session cThread = new Session(clientSocket);
					cThread.start();
				}
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}

}