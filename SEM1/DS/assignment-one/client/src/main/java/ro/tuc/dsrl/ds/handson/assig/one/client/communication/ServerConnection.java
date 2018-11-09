package ro.tuc.dsrl.ds.handson.assig.one.client.communication;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;

/**
 * @Author: Technical University of Cluj-Napoca, Romania
 *          Distributed Systems, http://dsrl.coned.utcluj.ro/
 * @Module: assignment-one-client
 * @Since: Sep 1, 2015
 * @Description:
 * 	Serves for the connection of the client with the server.
 * 	Provides one method which allows for requests to be sent to the server.
 */
public class ServerConnection {
	private static final Log LOGGER = LogFactory.getLog(ServerConnection.class);

	private String host;
	private int port;

	public ServerConnection(String host, int port) {
		this.host = host;
		this.port = port;
	}

	/**
	 * Sends a request to the server and returns the server's response.
	 * It opens a socket connection with the server at the host and port specified
	 * on class constructor, sends the request, waits for the response, then
	 * closes the connection and returns the response.
	 *
	 * @param messageToSend the request to send
	 * @return the response of received from the server
	 * @throws IOException thrown if there is a problem with the connection
	 */
	public String sendRequest(String messageToSend) throws IOException {
		Socket clientSocket = new Socket(host, port);
		ObjectOutputStream outToServer = new ObjectOutputStream(clientSocket.getOutputStream());
		ObjectInputStream inFromServer = new ObjectInputStream(clientSocket.getInputStream());
		outToServer.writeObject(messageToSend);

		String response;
		try {
			response = (String)inFromServer.readObject();
		} catch (ClassNotFoundException e) {
			response = null;
			LOGGER.error("", e);
		}

		outToServer.close();
		inFromServer.close();
		clientSocket.close();

		return response;
	}
}