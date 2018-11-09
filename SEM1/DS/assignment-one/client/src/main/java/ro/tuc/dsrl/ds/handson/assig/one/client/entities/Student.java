package ro.tuc.dsrl.ds.handson.assig.one.client.entities;

/**
 * @Author: Technical University of Cluj-Napoca, Romania
 *          Distributed Systems, http://dsrl.coned.utcluj.ro/
 * @Module: assignment-one-server
 * @Since: Aug 28, 2015
 * @Description:
 *	Class describing a Student.
 */
public class Student {

	private int id;
	private String firstname;
	private String lastname;
	private String mail;

	public int getId() {
		return id;
	}

	public void setId(int id) {
		this.id = id;
	}

	public String getFirstname() {
		return firstname;
	}

	public void setFirstname(String firstname) {
		this.firstname = firstname;
	}

	public String getLastname() {
		return lastname;
	}

	public void setLastname(String lastname) {
		this.lastname = lastname;
	}

	public String getMail() {
		return mail;
	}

	public void setMail(String mail) {
		this.mail = mail;
	}

	@Override
	public String toString() {
		return "Student\n id: " + id + "\n First name: " + firstname + "\n Last name: " + lastname + "\n Mail: " + mail;
	}

}
