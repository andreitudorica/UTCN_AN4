package ro.tuc.dsrl.ds.handson.assig.one.server.servlets;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import ro.tuc.dsrl.ds.handson.assig.one.protocol.servlets.AbstractServlet;

import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;

/**
 * @Author: Technical University of Cluj-Napoca, Romania
 *          Distributed Systems, http://dsrl.coned.utcluj.ro/
 * @Module: assignment-one-server
 * @Since: Sep 1, 2015
 * @Description:
 *  Used to create specific servlets from URLs
 */
public class ServletFactory {
    private static final Log LOGGER = LogFactory.getLog(ServletFactory.class);

    private ServletFactory() {
    }

    /**
     * Create an AbstractServlet from the given URL
     * @param url the URL given to create the servlet
     * @return specific instance of AbstractServlet
     * @throws ClassNotFoundException
     */
    public static AbstractServlet createServlet(String url) throws ClassNotFoundException {
        // The class name will be used to create an instance of AbstractServlet, i.e.:
        //  URL      ->      Servlet
        // student          StudentServlet
        // abc              AbcServlet

        // The name must be complete so we also add at the beginning the name of the packages where the class is
        String className = "ro.tuc.dsrl.ds.handson.assig.one.server.servlets.";
        className += url.replace(url.charAt(0),Character.toUpperCase(url.charAt(0)));
        className += "Servlet";

        AbstractServlet abstractServlet = null;

        Class<?> clazz;
        try {
            // Get Class object associated with the class having the specified name.
            clazz = Class.forName(className);

            if (clazz == null) {
                return null;
            }

            // Create new instance of the class represented by clazz object
            Constructor<?> ctor = clazz.getConstructor();
            abstractServlet = (AbstractServlet)ctor.newInstance();
        } catch (InvocationTargetException | NoSuchMethodException | IllegalAccessException | InstantiationException | ClassNotFoundException e) {
            LOGGER.error("", e);
        }

        return abstractServlet;
    }
}
