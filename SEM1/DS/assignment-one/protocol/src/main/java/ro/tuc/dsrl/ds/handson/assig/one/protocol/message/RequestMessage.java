package ro.tuc.dsrl.ds.handson.assig.one.protocol.message;

import ro.tuc.dsrl.ds.handson.assig.one.protocol.encoders.POJOSerializer;
import ro.tuc.dsrl.ds.handson.assig.one.protocol.enums.ProtocolMethod;

import java.util.HashMap;
import java.util.Map;

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
public class RequestMessage {
    private ProtocolMethod method;
    private String url;
    private Map<String,String> queryValues;
    private String serializedObject;

    public RequestMessage() {
        this.queryValues = new HashMap<String, String>();
    }

    public Map<String, String> getQueryValues() {
        return queryValues;
    }

    public void setQueryValues(Map<String, String> queryValues) {
        this.queryValues = queryValues;
    }

    public ProtocolMethod getMethod() {
        return method;
    }

    public void setMethod(ProtocolMethod method) {
        this.method = method;
    }

    public String getUrl() {
        return url;
    }

    public void setUrl(String url) {
        this.url = url;
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
