package ro.tuc.dsrl.ds.handson.assig.one.protocol.servlets;

import ro.tuc.dsrl.ds.handson.assig.one.protocol.encoders.ResponseMessageEncoder;
import ro.tuc.dsrl.ds.handson.assig.one.protocol.enums.StatusCode;
import ro.tuc.dsrl.ds.handson.assig.one.protocol.message.RequestMessage;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * @Author: Technical University of Cluj-Napoca, Romania
 *          Distributed Systems, http://dsrl.coned.utcluj.ro/
 * @Module: assignment-one-client
 * @Since: Sep 1, 2015
 * @Description:
 * 	Provides the abstract class for a Servlet which should handle a request.
 */
public abstract class AbstractServlet {
    private static final Log LOGGER = LogFactory.getLog(AbstractServlet.class);

    /**
    * Execute the request; check the request method and call the appropriate method accordingly.
    * In case the method is not implemented, an UnsupportedOperationException is thrown, in which
    * case the NOT_ALLOWED status code is generated.
     */
    public String doRequest(RequestMessage message) {
        try {
            switch (message.getMethod()) {
                case GET:
                    return doGet(message);
                case POST:
                    return doPost(message);
                case DELETE:
                    return doDelete(message);
                default:
                    return ResponseMessageEncoder.encode(StatusCode.BAD_REQUEST);
            }
        } catch (UnsupportedOperationException e) {
            LOGGER.error("", e);
            return ResponseMessageEncoder.encode(StatusCode.NOT_ALLOWED);
        }
    }

    /**
     * Called when the request method is POST.
     *
     * @param message the request message to be processed
     * @return the response of the processing, serialized
     */
    public abstract String doPost(RequestMessage message);

    /**
     * Called when the request method is GET.
     *
     * @param message the request message to be processed
     * @return the response of the processing, serialized
     */
    public abstract String doGet(RequestMessage message);

    /**
     * Called when the request method is DELETE.
     *
     * @param message the request message to be processed
     * @return the response of the processing, serialized
     */
    public abstract String doDelete(RequestMessage message);
}
