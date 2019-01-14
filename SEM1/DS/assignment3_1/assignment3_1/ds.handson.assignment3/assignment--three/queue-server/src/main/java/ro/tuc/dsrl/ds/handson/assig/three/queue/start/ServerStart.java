package ro.tuc.dsrl.ds.handson.assig.three.queue.start;

import ro.tuc.dsrl.ds.handson.assig.three.queue.communication.Server;

import java.io.IOException;

/**
 * @Author: Technical University of Cluj-Napoca, Romania
 *          Distributed Systems, http://dsrl.coned.utcluj.ro/
 * @Module: assignment-one-server
 * @Since: Sep 1, 2015
 * @Description:
 * 	Serves for starting the server on the specified port.
 */
public class ServerStart {

	private static final int PORT = 8888;

	private ServerStart() {
	}

	public static void main(String[] args) {
		try {
			new Server(PORT);
			System.out.println("Queue server started.");
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
