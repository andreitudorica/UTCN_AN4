package ro.tuc.dsrl.ds.handson.assig.one.protocol.encoders;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import java.lang.reflect.Field;
import java.lang.reflect.Type;

/**
 * @Author: Technical University of Cluj-Napoca, Romania
 *          Distributed Systems, http://dsrl.coned.utcluj.ro/
 * @Module: assignment-one-client
 * @Since: Sep 1, 2015
 * @Description:
 * 	Provides static methods for the serialization/deserialization of
 * 	objects to/from the protocol format.
 * 	The format is as follows:
 * 	    f1#f2#f3#...fn#
 * 	where f1, f2,..., fn are the values of the fields of the object.
 * 	The serialized/deserialized is only allowed to have primitive or String
 * 	fields.
 *
 * 	This serialized object can be used as the BODY component of the request or response
 * 	through the communication protocol.
 */
public class POJOSerializer {
    private static final Log LOGGER = LogFactory.getLog(POJOSerializer.class);

    private POJOSerializer() {
    }

    /**
     * Uses reflection to serialize an Object to the communication protocol
     * format.
     * @param o object to serialize
     * @return serialized object
     */
    public static String serialize(Object o) {
        String result = "";
        try {
            //get the class type of the object
            Class c = o.getClass();

            //get the fields of that class
            Field[] fields = c.getDeclaredFields();

            for (Field f : fields) {
                //set accessibility to true (such that they can be read even if private)
                f.setAccessible(true);
                //append the field to the result
                result += f.get(o) + "#";
                f.setAccessible(false);
            }
        } catch (IllegalAccessException e) {
            LOGGER.error("", e);
        }

        return result;
    }

    /**
     * Uses reflection to deserialize an object from String to the specified class.
     * @param m the serialized object
     * @param clazz the class into which to deserialize
     * @return deserialized object, instance of the Class clazz
     */
    public static <T> T deserialize(String m, Class<T> clazz) {
        //split the serialized String by the # separator
        String[] objInfo = m.split("#");

        try {
            //create a new instance of clazz Class
            T result = clazz.newInstance();
            //get the declared fields of that class
            Field[] fields = clazz.getDeclaredFields();

            for (int i = 0; i < objInfo.length && i < fields.length; i++) {
                fields[i].setAccessible(true);
                //set each field with values from the serialized String
                fields[i].set(result, toObject(fields[i].getType(),objInfo[i]));
                fields[i].setAccessible(false);
            }

            return result;
        } catch (InstantiationException | IllegalAccessException e) {
            LOGGER.error("", e);
        }

        return null;
    }


    private static Object toObject( Type type, String value ) {
        if( Boolean.TYPE.equals(type) ) {
            return Boolean.parseBoolean(value);
        }
        if( Byte.TYPE.equals(type) ) {
            return Byte.parseByte(value);
        }
        if( Short.TYPE.equals(type) ) {
            return Short.parseShort(value);
        }
        if( Integer.TYPE.equals(type) ) {
            return Integer.parseInt(value);
        }
        if( Long.TYPE.equals(type) ) {
            return Long.parseLong(value);
        }
        if( Float.TYPE.equals(type) ) {
            return Float.parseFloat(value);
        }
        if( Double.TYPE.equals(type) ) {
            return Double.parseDouble( value );
        }

        return value;
    }
}
