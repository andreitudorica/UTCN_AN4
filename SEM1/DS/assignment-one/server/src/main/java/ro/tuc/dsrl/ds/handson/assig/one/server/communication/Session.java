package ro.tuc.dsrl.ds.handson.assig.one.server.communication;

import ro.tuc.dsrl.ds.handson.assig.one.protocol.encoders.RequestMessageEncoder;
import ro.tuc.dsrl.ds.handson.assig.one.protocol.enums.StatusCode;
import ro.tuc.dsrl.ds.handson.assig.one.protocol.encoders.ResponseMessageEncoder;
import ro.tuc.dsrl.ds.handson.assig.one.protocol.message.RequestMessage;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import ro.tuc.dsrl.ds.handson.assig.one.protocol.servlets.AbstractServlet;
import ro.tuc.dsrl.ds.handson.assig.one.server.servlets.ServletFactory;

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
 * 	(receiving messages, decoding them and sending a response)
 */
public class Session extends Thread {
	private static final Log LOGGER = LogFactory.getLog(Session.class);

	private Socket clientSocket;
	private ObjectInputStream inFromClient;
	private ObjectOutputStream outToClient;

	public Session(Socket cSocket) {
		this.clientSocket = cSocket;
		try {
			inFromClient = new ObjectInputStream(clientSocket.getInputStream());
			outToClient = new ObjectOutputStream(clientSocket.getOutputStream());
		} catch (IOException e) {
			LOGGER.error("", e);
		}
	}

	@Override
	public void run() {
		String messageReceived;

		try {
			// Wait for message from client
			messageReceived = (String) inFromClient.readObject();

			// Decode the request from the received message
			RequestMessage decodedRequest = RequestMessageEncoder.decode(messageReceived);

			String response;

			// Prepare response
            if (decodedRequest != null) {
				// Attempt creating the servlet that handles the request for the provided URL
                AbstractServlet abstractServlet = ServletFactory.createServlet(decodedRequest.getUrl());

				// Servlet successfully created, actually process the request
                if (abstractServlet != null) {
                    response = abstractServlet.doRequest(decodedRequest);
                }
				// Servlet could not be created for the URL, mapping not found
				else {
                    response = ResponseMessageEncoder.encode(StatusCode.NOT_FOUND, null);
                }
            } else {
                response = ResponseMessageEncoder.encode(StatusCode.BAD_REQUEST, null);
            }

			// Send encoded response
            sendMessageToClient(response);
		} catch (ClassNotFoundException | IOException e) {
			LOGGER.error("", e);
		}

		closeAll();
	}

	public void sendMessageToClient(String messageToSend) {
		try {
			outToClient.writeObject(messageToSend);
		} catch (IOException e) {
			LOGGER.error("", e);
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
			LOGGER.error("", e);
		} finally {
			inFromClient = null;
			outToClient = null;
			clientSocket = null;
		}
	}
}
