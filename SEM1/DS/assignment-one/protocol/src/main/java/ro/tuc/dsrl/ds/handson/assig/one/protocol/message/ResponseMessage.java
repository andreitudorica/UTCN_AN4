package ro.tuc.dsrl.ds.handson.assig.one.protocol.message;

import ro.tuc.dsrl.ds.handson.assig.one.protocol.encoders.POJOSerializer;

/**
 * @Author: Technical University of Cluj-Napoca, Romania
 *          Distributed Systems, http://dsrl.coned.utcluj.ro/
 * @Module: assignment-one-client
 * @Since: Sep 1, 2015
 * @Description:
 * 	Holds a request message. A request message has the following components:
 * 	 method - the protocol method of the request (e.g. GET, POST)
 * 	 url - the url of the resource accessed
 * 	 queryValues - map of (key,value) holding the parameters that can be passed through the url
 * 	 serializedObject - the BODY part of the request, held in String format (serialized)
 *
 * 	Provides getters and setters for the aforementioned fields and also getDeserializedObject() which returns
 * 	the an Object instance for the serializedObject using the POJOSerializer.
 */
public class ResponseMessage {
    private int statusCode;
    private String serializedObject;

    public ResponseMessage() {
    }

    public int getStatusCode() {
        return statusCode;
    }

    public void setStatusCode(int statusCode) {
        this.statusCode = statusCode;
    }

    public <T> T getDeserializedObject(Class<T> clazz) {
        return POJOSerializer.deserialize(serializedObject, clazz);
    }

    public void setDeserializedObject(Object o) {
        serializedObject = POJOSerializer.serialize(o);
    }

    public String getSerializedObject() {
        return serializedObject;
    }

    public void setSerializedObject(String serializedObject) {
        this.serializedObject = serializedObject;
    }
}
