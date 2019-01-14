package servlets;
import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import repositories.*;

public class Login extends HttpServlet{
    public void doGet(HttpServletRequest req, HttpServletResponse response) throws ServletException, IOException{
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        String title = "Login";
        String docType =
                "<!doctype html public \"-//w3c//dtd html 4.0 " +
                        "transitional//en\">\n";

        out.println(docType +
                        "<html>\n" +
                        "<head><title>" + title + "</title></head>\n" +
                        "<body bgcolor = \"#f0f0f0\">\n" +
                        "<h1 align = \"center\">" + title + "</h1>\n" +
                        "<ul>\n" +
                        "  <li><b>First Name</b>: "
                        + req.getParameter("username") + "\n" +
                        "  <li><b>Last Name</b>: "
                        + req.getParameter("password") + "\n" +
                        "</ul>\n" +
                        "</body>" +
                "</html>"
        );
    }

    // Method to handle POST method request.
    public void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        UsersRepository usersRepository = new UsersRepository();
        Integer loginResult = usersRepository.addUser(request.getParameter("username"), request.getParameter("password"),new String( "admin"));
        System.out.println(loginResult.toString());
    }
}