package servlets;

import dao.UserEntity;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.Transaction;
import org.hibernate.query.Query;
import util.HibernateUtil;

import java.io.*;
import java.util.List;
import javax.servlet.*;
import javax.servlet.http.*;

public class LoginServlet extends HttpServlet {

    private SessionFactory sessionFactory = HibernateUtil.getSessionFactory();

    public void init() throws ServletException {

    }

    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        response.setContentType("text/html");

        Cookie cookie = new Cookie("type", "");
        cookie.setPath("/admin");
        response.addCookie(cookie);

        cookie = new Cookie("type", "");
        cookie.setPath("/user");
        response.addCookie(cookie);

        response.getWriter().println(
                "<!doctype html public \"-//w3c//dtd html 4.0 " + "transitional//en\">\n" +
                        "<html>\n" +
                        "<head><title>Login</title></head>\n" +
                        "<body>\n" +
                        "<h1> Login </h1>\n" +
                        "<form action = \"Login\" method = \"POST\">\n" +
                        "<label for=\"un\">Username</label>" +
                        "<input type = \"text\" name = \"user\" id=\"un\"/>\n" +
                        "<label for=\"pw\">Password</label>" +
                        "<input type = \"password\" name = \"pass\" id=\"pw\"/>\n" +
                        "<br>\n" +
                        "<input type = \"submit\" value = \"Login\" />" +
                        "</body>" +
                        "</html>"
        );
    }

    public void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        response.setContentType("text/html");

        String username = request.getParameter("user");
        String password = request.getParameter("pass");

        Session session = sessionFactory.openSession();

        List<UserEntity> users = null;
        try {
            session.beginTransaction();
            Query query = session.createQuery("FROM UserEntity WHERE  username = :us");
            query.setParameter("us", username);
            users = query.list();
            session.getTransaction().commit();
        } catch (Exception e) {
            if (session.getTransaction() != null) session.getTransaction().rollback();
            e.printStackTrace();
        } finally {
            session.close();
        }

        if (users == null) {
            response.sendRedirect("");
        } else {
            if (users.get(0).getPassword().equalsIgnoreCase(password)) {
                //add cookie and redirect by type
                String type = users.get(0).getType();
                Cookie cookie = new Cookie("type", type);
                cookie.setPath("/"+type);
                response.addCookie(cookie);
                response.sendRedirect(type);
            } else {
                response.sendRedirect("Login");
            }
        }
    }

    public void destroy() {
    }
}
