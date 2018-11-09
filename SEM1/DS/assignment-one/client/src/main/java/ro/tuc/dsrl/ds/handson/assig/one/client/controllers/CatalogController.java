package ro.tuc.dsrl.ds.handson.assig.one.client.controllers;

import ro.tuc.dsrl.ds.handson.assig.one.client.communication.ServerConnection;
import ro.tuc.dsrl.ds.handson.assig.one.protocol.encoders.ResponseMessageEncoder;
import ro.tuc.dsrl.ds.handson.assig.one.client.entities.Student;
import ro.tuc.dsrl.ds.handson.assig.one.protocol.enums.ProtocolMethod;
import ro.tuc.dsrl.ds.handson.assig.one.protocol.encoders.RequestMessageEncoder;
import ro.tuc.dsrl.ds.handson.assig.one.protocol.enums.StatusCode;
import ro.tuc.dsrl.ds.handson.assig.one.protocol.message.ResponseMessage;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import ro.tuc.dsrl.ds.handson.assig.one.client.views.CatalogView;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;

/**
 * @Author: Technical University of Cluj-Napoca, Romania
 *          Distributed Systems, http://dsrl.coned.utcluj.ro/
 * @Module: assignment-one-client
 * @Since: Sep 1, 2015
 * @Description:
 *  Controller for the interface elements of the client.
 */
public class CatalogController {
	private static final Log LOGGER = LogFactory.getLog(CatalogController.class);

	private static final String ERROR_MESSAGE =
			"An exception occured while trying to send data to server. Please consult logs for more info!";
	private static final String HOST = "localhost";
	private static final int PORT = 8888;

	private CatalogView catalogView;
	private ServerConnection serverConnection;

	public CatalogController() {
		catalogView = new CatalogView();
		catalogView.setVisible(true);

		serverConnection = new ServerConnection(HOST, PORT);

		catalogView.addBtnGetActionListener(new GetActionListener());
		catalogView.addBtnPostActionListener(new PostActionListener());
		catalogView.addBtnDeleteActionListener(new DeleteActionListener());
	}

	public void printStudent(Student student) {
		if (student != null) {
			catalogView.printStudent(student);
		}
	}

	public void displayErrorMessage(String message) {
		catalogView.clear();
		JOptionPane.showMessageDialog(catalogView, message, "Error", JOptionPane.ERROR_MESSAGE);
	}

	public void displayInfoMessage(String message) {
		catalogView.clear();
		JOptionPane.showMessageDialog(catalogView, message, "Success", JOptionPane.PLAIN_MESSAGE);
	}

	/**
	 * Provides functionality for the POST button.
	 */
	class PostActionListener implements ActionListener {
		@Override
		public void actionPerformed(ActionEvent e) {
			String firstname = catalogView.getFirstname();
			String lastname = catalogView.getLastname();
			String mail = catalogView.getMail();

			if (!("".equals(firstname) || "".equals(lastname) || "".equals(mail))) {
				Student student = new Student();
				student.setFirstname(firstname);
				student.setLastname(lastname);
				student.setMail(mail);

				try {
					//encode the request: a POST request, at the url "student", sending the student object
					String encodedRequest = RequestMessageEncoder.encode(ProtocolMethod.POST, "student", student);
					String response = serverConnection.sendRequest(encodedRequest);
					//decode the response from server
					ResponseMessage decodedResponse = ResponseMessageEncoder.decode(response);

					//if server responded OK, then operation was successful, else display error
					if (decodedResponse.getStatusCode() == StatusCode.OK.getCode()) {
						displayInfoMessage("Successfully inserted; id=" + decodedResponse.getSerializedObject());
					} else {
						displayErrorMessage("Status code " + decodedResponse.getStatusCode());
					}

				} catch (IOException ex) {
					LOGGER.info(ex.getMessage());
					displayErrorMessage(ex.getMessage());
				}
			}
			else {
				displayErrorMessage("Please fill all textboxes before submiting!");
			}
		}
	}

	/**
	 * Provides functionality for the GET button.
	 */
	class GetActionListener implements ActionListener {

		@Override
		public void actionPerformed(ActionEvent e) {
			try {
				int studentId = Integer.parseInt(catalogView.getStudentId());
				//encode the request: a GET request, with url "student?id=X" (passing id in url) and no object sent through
				String encodedRequest = RequestMessageEncoder.encode(ProtocolMethod.GET, "student?id=" + studentId);
				String response = serverConnection.sendRequest(encodedRequest);
				ResponseMessage decodedResponse = ResponseMessageEncoder.decode(response);

				if (decodedResponse.getStatusCode() == StatusCode.OK.getCode()) {
					printStudent(decodedResponse.getDeserializedObject(Student.class));
				} else {
					displayErrorMessage("Status code " + decodedResponse.getStatusCode());
				}
			} catch (NumberFormatException ex) {
				displayErrorMessage("Please enter a number!");
			} catch (IOException ex) {
				displayErrorMessage(ERROR_MESSAGE);
				LOGGER.error("", ex);
			}
		}
	}

    /**
     * Provides functionality for the DELETE button.
     */
	class DeleteActionListener implements ActionListener {

        @Override
        public void actionPerformed(ActionEvent e) {
            try {
                int studentId = Integer.parseInt(catalogView.getStudentId());
                //encode the request: a DELETE request, with url "student?id=X" (passing id in url) and no object sent through
                String encodedRequest = RequestMessageEncoder.encode(ProtocolMethod.DELETE, "student?id=" + studentId);
                String response = serverConnection.sendRequest(encodedRequest);
                ResponseMessage decodedResponse = ResponseMessageEncoder.decode(response);

                if (decodedResponse.getStatusCode() == StatusCode.OK.getCode()) {
                    displayInfoMessage("Deleted student with id " + decodedResponse.getDeserializedObject(Student.class).getId());
                } else {
                    displayErrorMessage("Status code " + decodedResponse.getStatusCode());
                }
            } catch (NumberFormatException ex) {
                displayErrorMessage("Please enter a number!");
            } catch (IOException ex) {
                displayErrorMessage(ERROR_MESSAGE);
                LOGGER.error("", ex);
            }
        }
    }
}
