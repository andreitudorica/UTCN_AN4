package ro.tuc.dsrl.ds.handson.assig.one.client.start;


import ro.tuc.dsrl.ds.handson.assig.one.client.controllers.CatalogController;

/**
 * @Author: Technical University of Cluj-Napoca, Romania
 *          Distributed Systems, http://dsrl.coned.utcluj.ro/
 * @Module: assignment-one-client
 * @Since: Sep 1, 2015
 * @Description:
 *	Starting point for the Client application.
 */
public class ClientStart {

	private ClientStart() {
	}

	public static void main(String[] args) {
		new CatalogController();
	}
}
