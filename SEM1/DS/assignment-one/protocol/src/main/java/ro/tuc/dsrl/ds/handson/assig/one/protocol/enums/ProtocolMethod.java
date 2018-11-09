package ro.tuc.dsrl.ds.handson.assig.one.protocol.enums;

/**
 * @Author: Technical University of Cluj-Napoca, Romania
 *          Distributed Systems, http://dsrl.coned.utcluj.ro/
 * @Module: assignment-one-client
 * @Since: Sep 1, 2015
 * @Description:
 * 	Enum containing the communication protocol methods. It defines
 * 	all the methods that are supported by the communication protocol.
 *  A request message which contains a method not specified here is
 *  invalid.
 */
public enum ProtocolMethod {
	POST, GET, DELETE;
}
