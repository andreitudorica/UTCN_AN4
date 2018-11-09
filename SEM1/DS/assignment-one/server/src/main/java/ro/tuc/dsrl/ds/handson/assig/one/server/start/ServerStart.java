package ro.tuc.dsrl.ds.handson.assig.one.server.start;

import ro.tuc.dsrl.ds.handson.assig.one.server.communication.Server;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import java.io.IOException;

/**
 * @Author: Technical University of Cluj-Napoca, Romania
 *          Distributed Systems, http://dsrl.coned.utcluj.ro/
 * @Module: assignment-one-server
 * @Since: Sep 1, 2015
 * @Description:
 * 	Serves for starting the server on the specified port
 */
public class ServerStart {
	private static final Log LOGGER = LogFactory.getLog(ServerStart.class);

	private static final int PORT = 8888;

	private ServerStart() {
	}

	public static void main(String[] args) {
		try {
			new Server(PORT);
			LOGGER.info("The server started.");
		} catch (IOException e) {
			LOGGER.error("", e);
		}
	}
}
