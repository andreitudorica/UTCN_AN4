package servlets;

import dao.FlightEntity;
import dao.LocationEntity;
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
import java.net.URL;
import java.net.URLConnection;

import org.jdom2.Document;
import org.jdom2.Element;
import org.jdom2.input.SAXBuilder;

import java.sql.Timestamp;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class ClientServlet extends HttpServlet {
    private SessionFactory sessionFactory = HibernateUtil.getSessionFactory();

    public void init() throws ServletException {
    }

    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        Cookie[] cookies = request.getCookies();
        if (cookies == null || cookies.length < 1) {
            response.sendRedirect("Login");
        } else {
            if (!cookies[0].getValue().equalsIgnoreCase("user")) {
                response.sendRedirect("Login");
            }
        }
        boolean local = false;

        if (!(request.getParameter("localTime") == null || request.getParameter("localTime").equalsIgnoreCase(""))) {
            if (request.getParameter("localTime").equalsIgnoreCase("yes")) {
                local = true;
            } else {
                local = false;
            }
        } else {
            local = false;
        }

        List<FlightEntity> flights = null;
        List<LocationEntity> locations = null;

        Session session = sessionFactory.openSession();
        try {
            session.beginTransaction();
            Query query = session.createQuery("FROM FlightEntity");
            flights = query.list();
            session.getTransaction().commit();
            session.beginTransaction();
            query = session.createQuery("FROM LocationEntity ");
            locations = query.list();
            session.getTransaction().commit();
        } catch (Exception e) {
            if (session.getTransaction() != null) session.getTransaction().rollback();
            e.printStackTrace();
        } finally {
            session.close();
        }

        String table = "<table border=1>\n";
        table += "<thead><th>Departure location</th><th>Arrival location</th><th>Flight number</th><th>Airplane type</th><th>Departure time</th><th>Arrival time</th></thead>";
        for (int i = 0; i < flights.size(); i++) {
            table += "<tr>\n";
            table += "<td>" + flights.get(i).getDepartureLocation() + "</td>\n";
            table += "<td>" + flights.get(i).getArrivalLocation() + "</td>\n";
            table += "<td>" + flights.get(i).getNumber() + "</td>\n";
            table += "<td>" + flights.get(i).getAirplaneType() + "</td>\n";
            table += "<td>" + flights.get(i).getDeparture() + "</td>\n";

            if (local) {
                LocationEntity dest = getLocationEntity(locations, flights.get(i).getArrivalLocation());
                LocationEntity orig = getLocationEntity(locations, flights.get(i).getDepartureLocation());

                String destLocalTime = getLocalTime(dest.getLongitude(), dest.getLatitude());
                String origLocalTime = getLocalTime(orig.getLongitude(), orig.getLatitude());

                Timestamp destLocalDatetime = getTimestampFromString(destLocalTime);
                Timestamp origLocalDatetime = getTimestampFromString(origLocalTime);

                Timestamp delta = new Timestamp(destLocalDatetime.getTime() - origLocalDatetime.getTime());

                table += "<td>" + new Timestamp(flights.get(i).getArrival().getTime() + delta.getTime()) + "</td>\n";
            } else {
                table += "<td>" + flights.get(i).getArrival() + "</td>\n";
            }
            table += "</tr>\n";
        }
        table += "</table>";

        response.getWriter().println(
                "<!doctype html public \"-//w3c//dtd html 4.0 " + "transitional//en\">\n" +
                        "<html>\n" +
                        "<head><title>Client</title>\n" +
                        "</head>\n" +
                        "<body>\n" +

                        "<div style='float: right'>\n" +
                        "<a href=\"/Login\">Logout</a> <br>\n" +
                        "</div>" +

                        "<div style='float: left'>\n" +
                        "<h3>Convert arrival time to local time?</h3>"+
                        "<form action=\"\">\n" +
                        "  <input type=\"radio\" name=\"localtime\" onClick=\"window.location='/user?localTime=yes'\"> Yes\n" +
                        "<br>\n" +
                        "  <input type=\"radio\" name=\"localtime\" onClick=\"window.location='/user?localTime=no'\"> No\n" +
                        "<br>\n" +
                        "</form>" +
                        "<br>\n" +
                        table +
                        "</div>\n" +
                        "</body\n" +
                        "</html>"
        );

    }

    private LocationEntity getLocationEntity(List<LocationEntity> locations, String name) {
        for (int i = 0; i < locations.size(); i++) {
            if (locations.get(i).getName().equalsIgnoreCase(name)) {
                return locations.get(i);
            }
        }
        return new LocationEntity();
    }

    private String getLocalTime(double longitude, double latitude) {

        try {
            String urlString = "http://www.new.earthtools.org/timezone-1.1/" + latitude + "/" + longitude;
            URL url = new URL(urlString);
            URLConnection conn = url.openConnection();
            SAXBuilder saxBuilder = new SAXBuilder();
            Document jdomDoc = saxBuilder.build(conn.getInputStream());
            Element e = jdomDoc.getRootElement().getChild("localtime");
            return e.getValue();
        } catch (Exception e) {
            e.printStackTrace();
        }
        return null;
    }

    private Timestamp getTimestampFromString(String in) {
        ArrayList<String> months = new ArrayList<String>(
                Arrays.asList("Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"));
        String[] splitDate = in.split(" ");
        Timestamp ts = new Timestamp(0);
        ts.setDate(Integer.parseInt(splitDate[0]));
        ts.setYear(Integer.parseInt(splitDate[2]) - 1900);
        ts.setMonth(months.indexOf(splitDate[1]));

        String[] splitTime = splitDate[3].split(":");
        ts.setHours(Integer.parseInt(splitTime[0]));
        ts.setMinutes(Integer.parseInt(splitTime[1]));
        ts.setSeconds(Integer.parseInt(splitTime[2]));

        return ts;
    }
}