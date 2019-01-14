package servlets;

import dao.FlightEntity;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.Transaction;
import org.hibernate.query.Query;
import util.HibernateUtil;

import javax.servlet.ServletException;
import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;
import java.sql.Timestamp;
import java.util.List;

public class AdminServlet extends HttpServlet {
    private SessionFactory sessionFactory = HibernateUtil.getSessionFactory();

    public void init() throws ServletException {
    }

    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        Cookie[] cookies = request.getCookies();
        if (cookies == null) {
            response.sendRedirect("Login");
        } else {
            if (!cookies[0].getValue().equalsIgnoreCase("admin")) {
                response.sendRedirect("Login");
            }
        }

        if (request.getParameter("idGet") == null) {
            response.getWriter().println(
                    "<!doctype html public \"-//w3c//dtd html 4.0 " + "transitional//en\">\n" +
                            "<html>\n" +
                            "<head><title>Admin</title>\n" +
                            "</head>\n" +
                            "<body>\n" +

                            "<div style='float: right'>\n" +
                            "<a href=\"/Login\">Logout</a> <br>\n" +
                            "</div>" +

                            "<div style='float: left'>\n" +
                            "<h3>Get:</h3>" +
                            "<label for='idGet'>ID</label>\n" +
                            "<br>\n" +
                            "<input type=\"text\" id=\"idGet\" \">\n" +
                            "<br>\n" +
                            "<input type=\"button\" value=\"Get\" id='getButton' onClick=\"window.location='admin?idGet='+document.getElementById('idGet').value\">\n" +
                            "</div>" +

                            "<div style='float: left'>\n" +
                            "<h3>Add:</h3>" +
                            "<form action = \"admin\" method = \"POST\">\n" +
                            "<label for='id'>Flight ID</label>\n" +
                            "<br />\n" +
                            "<input type = \"text\" name = \"id\" id='id'/>\n" +
                            "<br />\n" +
                            "<label for='origin'>Origin</label>\n" +
                            "<br />\n" +
                            "<input type = \"text\" name = \"origin\"  id='origin'/>\n" +
                            "<br />\n" +
                            "<label for='destination'>Destination</label>\n" +
                            "<br />\n" +
                            "<input type = \"text\" name = \"destination\"  id='destination'/>\n" +
                            "<br />\n" +
                            "<label for='flightnr'>Flight number</label>\n" +
                            "<br />\n" +
                            "<input type = \"text\" name = \"flightnr\"  id='flightnr'/>\n" +
                            "<br />\n" +
                            "<label for='planetype'>Plane type</label>\n" +
                            "<br />\n" +
                            "<input type = \"text\" name = \"planetype\"  id='planetype'/>\n" +
                            "<br />\n" +
                            "<input type = \"submit\" value = \"Add\" />" +
                            "</form>" +
                            "</div>" +

                            "<div style='float: left'>\n" +
                            "<h3>Edit:</h3>" +
                            "<form action = \"admin\" method = \"POST\">\n" +
                            "<input type=\"hidden\" name=\"_method\" value=\"put\" \n />" +
                            "<label for='idEdit'>Flight ID</label>\n" +
                            "<br />\n" +
                            "<input type = \"text\" name = \"idEdit\" id='idEdit'/>\n" +
                            "<br />\n" +
                            "<label for='originEdit'>Origin</label>\n" +
                            "<br />\n" +
                            "<input type = \"text\" name = \"originEdit\"  id='originEdit'/>\n" +
                            "<br />\n" +
                            "<label for='destinationEdit'>Destination</label>\n" +
                            "<br />\n" +
                            "<input type = \"text\" name = \"destinationEdit\"  id='destinationEdit'/>\n" +
                            "<br />\n" +
                            "<label for='flightnrEdit'>Flight number</label>\n" +
                            "<br />\n" +
                            "<input type = \"text\" name = \"flightnrEdit\"  id='flightnrEdit'/>\n" +
                            "<br />\n" +
                            "<label for='planetypeEdit'>Plane type</label>\n" +
                            "<br />\n" +
                            "<input type = \"text\" name = \"planetypeEdit\"  id='planetypeEdit'/>\n" +
                            "<br />\n" +
                            "<input type = \"submit\" value = \"Edit\" />" +
                            "</form>" +
                            "</div>" +

                            "<div style='float: left'>\n" +
                            "<h3>Delete:</h3>" +
                            "<form action = \"admin\" method = \"POST\">\n" +
                            "<input type=\"hidden\" name=\"_method\" value=\"delete\" \n />" +
                            "<label for='idDelete'>ID</label>\n" +
                            "<br>\n" +
                            "<input type=\"text\" id=\"idDelete\" name=\"idDelete\">\n" +
                            "<br>\n" +
                            "<input type = \"submit\" value = \"Delete\" />" +
                            "</form>" +
                            "</div>" +

                            "</body>" +
                            "</html>"
            );
        } else {
            Session session = sessionFactory.openSession();

            List<FlightEntity> flights = null;
            try {
                session.beginTransaction();
                Query query = session.createQuery("FROM FlightEntity WHERE  id = :planeId");
                query.setParameter("planeId", Integer.parseInt(request.getParameter("idGet")));
                flights = query.list();
                session.getTransaction().commit();
            } catch (Exception e) {
                if (session.getTransaction() != null) session.getTransaction().rollback();
                e.printStackTrace();
            } finally {
                session.close();
            }

            if (flights == null || flights.size() < 1) {
                response.getWriter().println(
                        "<!doctype html public \"-//w3c//dtd html 4.0 " + "transitional//en\">\n" +
                                "<html>\n" +
                                "<head><title>Admin panel</title></head>\n" +
                                "<body>\n" +
                                "<div style='float: right'>\n" +
                                "<a href=\"/admin\">Back</a> <br>\n" +
                                "</div>\n" +
                                "<br>\n" +
                                "No flight with ID " + request.getParameter("idGet") + " found\n" +
                                "</body>" +
                                "</html>"
                );
            } else {

                PrintWriter out = response.getWriter();
                String docType = "<!doctype html public \"-//w3c//dtd html 4.0 " + "transitional//en\">\n";

                out.println(docType +
                        "<html>\n" +
                        "<head><title>Admin panel</title></head>\n" +
                        "<body>\n" +
                        "<div style='float: right'>\n" +
                        "<a href=\"/admin\">Back</a> <br>\n" +
                        "</div>\n" +
                        "<div style='float: left'>\n" +
                        "<br>\n" +
                        "Flight ID :" +
                        "<br>" + flights.get(0).getId() + "\n" +
                        "<br>\n" +
                        "Flight number :" +
                        "<br>" + flights.get(0).getNumber() + "\n" +
                        "<br>\n" +
                        "Departure time :" +
                        "<br>" + flights.get(0).getDeparture() + "\n" +
                        "<br>\n" +
                        "Arrival time :" +
                        "<br>" + flights.get(0).getArrival() + "\n" +
                        "<br>\n" +
                        "Departure location :" +
                        "<br>" + flights.get(0).getDepartureLocation() + "\n" +
                        "<br>\n" +
                        "Arrival location :" +
                        "<br>" + flights.get(0).getArrivalLocation() + "\n" +
                        "<br>\n" +
                        "Airplane type :" +
                        "<br>" + flights.get(0).getAirplaneType() + "\n" +
                        "</div>\n" +
                        "</body>\n" +
                        "</html>\n"
                );
            }
        }
    }

    public void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        if (request.getParameter("_method") != null) {
            if (request.getParameter("_method").equalsIgnoreCase("put")) {
                doPut(request, response);
            } else if (request.getParameter("_method").equalsIgnoreCase("delete")) {
                doDelete(request, response);
            }
        } else {
            response.setContentType("text/html");

            int id = Integer.parseInt(request.getParameter("id"));
            String origin = request.getParameter("origin");
            String destination = request.getParameter("destination");
            int flightnr;
            try {
                flightnr = Integer.parseInt(request.getParameter("flightnr"));
            } catch (NumberFormatException e) {
                flightnr = -1;
            }
            String airplane = request.getParameter("planetype");

            Session session = sessionFactory.openSession();
            try {
                session.beginTransaction();
                FlightEntity flight = new FlightEntity();
                flight.setId(id);
                flight.setDepartureLocation(origin);
                flight.setArrivalLocation(destination);
                flight.setNumber(flightnr);
                flight.setAirplaneType(airplane);
                flight.setArrival(new Timestamp(2018 - 1900, 4, 6, 16, 22, 0, 0));
                flight.setDeparture(new Timestamp(2018 - 1900, 4, 6, 10, 50, 0, 0));
                session.save(flight);
                session.getTransaction().commit();
            } catch (Exception e) {
                if (session.getTransaction() != null) session.getTransaction().rollback();
                e.printStackTrace();
            } finally {
                session.close();
            }
            response.sendRedirect("admin");
        }
    }

    public void doPut(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html");


        int id = Integer.parseInt(request.getParameter("idEdit"));
        String origin = request.getParameter("originEdit");
        String destination = request.getParameter("destinationEdit");
        int flightnr;
        try {
            flightnr = Integer.parseInt(request.getParameter("flightnrEdit"));
        } catch (NumberFormatException e) {
            flightnr = -1;
        }
        String airplane = request.getParameter("planetypeEdit");

        Session session = sessionFactory.openSession();

        FlightEntity flight = null;
        try {
            session.beginTransaction();
            flight = session.get(FlightEntity.class, id);
            session.getTransaction().commit();

        } catch (Exception e) {
            if (session.getTransaction() != null) session.getTransaction().rollback();
            e.printStackTrace();
        } finally {
            session.close();
        }

        if (flight != null) {
            if (origin != "") {
                flight.setDepartureLocation(origin);
            }
            if (destination != "") {
                flight.setArrivalLocation(destination);
            }
            if (flightnr != -1) {
                flight.setNumber(flightnr);
            }
            if (airplane != "") {
                flight.setAirplaneType(airplane);
            }

            session = sessionFactory.openSession();
            try {
                session.beginTransaction();
                session.update(flight);
                session.getTransaction().commit();
            } catch (Exception e) {
                if (session.getTransaction() != null) session.getTransaction().rollback();
                e.printStackTrace();
            } finally {
                session.close();
            }
            response.sendRedirect("admin");
        } else {
            response.getWriter().println(
                    "<!doctype html public \"-//w3c//dtd html 4.0 " + "transitional//en\">\n" +
                            "<html>\n" +
                            "<head><title>Admin panel</title></head>\n" +
                            "<body>\n" +
                            "<div style='float: right'>\n" +
                            "<a href=\"/admin\">Back</a> <br>\n" +
                            "</div>\n" +
                            "<br>\n" +
                            "No flight with ID " + id + " found\n" +
                            "</body>" +
                            "</html>"
            );
        }
    }

    public void doDelete(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html");

        int id = Integer.parseInt(request.getParameter("idDelete"));

        Session session = sessionFactory.openSession();

        FlightEntity flight = null;
        try {
            session.beginTransaction();
            flight = session.get(FlightEntity.class, id);
            session.getTransaction().commit();
        } catch (Exception e) {
            if (session.getTransaction() != null) session.getTransaction().rollback();
            e.printStackTrace();
        } finally {
            session.close();
        }

        if (flight == null) {
            response.getWriter().println(
                    "<!doctype html public \"-//w3c//dtd html 4.0 " + "transitional//en\">\n" +
                            "<html>\n" +
                            "<head><title>Admin panel</title></head>\n" +
                            "<body>\n" +
                            "<div style='float: right'>\n" +
                            "<a href=\"/admin\">Back</a> <br>\n" +
                            "</div>\n" +
                            "<br>\n" +
                            "No flight with ID " + id + " found\n" +
                            "</body>" +
                            "</html>"
            );
        } else {
            session = sessionFactory.openSession();
            try {
                session.beginTransaction();
                session.delete(flight);
                session.getTransaction().commit();

            } catch (Exception e) {
                if (session.getTransaction() != null) session.getTransaction().rollback();
                e.printStackTrace();
            } finally {
                session.close();
            }
            response.sendRedirect("admin");
        }
    }
}