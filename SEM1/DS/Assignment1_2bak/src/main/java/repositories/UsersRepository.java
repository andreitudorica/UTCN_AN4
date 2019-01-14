package repositories;

import java.util.List;
import java.util.Date;
import java.util.Iterator;

import dao.UserEntity;
import org.hibernate.HibernateException;
import org.hibernate.Session;
import org.hibernate.Transaction;
import org.hibernate.SessionFactory;
import org.hibernate.cfg.Configuration;

public class UsersRepository {
        private final SessionFactory factory;
        public UsersRepository()
        {
            factory = new Configuration().configure().buildSessionFactory();
        }
       /* public static void main (String[]args){

            try {
                factory = new Configuration().configure().buildSessionFactory();
            } catch (Throwable ex) {
                System.err.println("Failed to create sessionFactory object." + ex);
                throw new ExceptionInInitializerError(ex);
            }

            UsersRepository ME = new UsersRepository();

            Integer empID1 = ME.addEmployee("Zara", "Ali", 1000);
            Integer empID2 = ME.addEmployee("Daisy", "Das", 5000);
            Integer empID3 = ME.addEmployee("John", "Paul", 10000);

            ME.listEmployees();

            ME.updateEmployee(empID1, 5000);

            ME.deleteEmployee(empID2);

            ME.listEmployees();
        }*/
        /* Method to CREATE an employee in the database */
        public Integer addUser (String username, String password,String type)
        {

            Session session = factory.openSession();
            Transaction tx = null;
            Integer userID = null;
            try {
                tx = session.beginTransaction();
                UserEntity user = new UserEntity();
                user.setUsername(username);
                user.setPassword(password);
                user.setType(type);
                userID=(Integer)session.save(user);
                tx.commit();
            } catch (HibernateException e) {
                if (tx != null) tx.rollback();
                e.printStackTrace();
            } finally {
                session.close();
            }
            return userID;
        }


    }
