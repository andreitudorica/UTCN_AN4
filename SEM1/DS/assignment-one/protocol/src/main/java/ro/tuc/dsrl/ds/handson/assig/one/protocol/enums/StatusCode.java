package ro.tuc.dsrl.ds.handson.assig.one.protocol.enums;

/**
 * @Author: Technical University of Cluj-Napoca, Romania
 *          Distributed Systems, http://dsrl.coned.utcluj.ro/
 * @Module: assignment-one-server
 * @Since: Sep 1, 2015
 * @Description:
 *	Specifies the status codes that can be returned by the server in a response
 *  due to processing the request.
 *
 *  OK - successful operation
 *  NOT_FOUND - resource not found
 *  BAD_REQUEST - the request does not respect the protocol format
 *  NOT_ALLOWED - the specified method is not supported/allowed on the specified resource (url)
 */
public enum StatusCode {
	OK(200), NOT_FOUND(404), BAD_REQUEST(400), NOT_ALLOWED(405);

	private int code;

	StatusCode(int code) {
		this.code = code;
	}

	public int getCode() {
		return code;
	}
}
