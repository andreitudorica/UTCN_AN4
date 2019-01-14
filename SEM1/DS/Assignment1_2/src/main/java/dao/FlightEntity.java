package dao;

import javax.persistence.*;
import java.sql.Timestamp;

@Entity
@Table(name = "flight", schema = "assignment1_2", catalog = "")
public class FlightEntity {
    private int id;
    private int number;
    private String airplaneType;
    private String arrivalLocation;
    private String departureLocation;
    private Timestamp departure;
    private Timestamp arrival;

    @Id
    @Column(name = "ID")
    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    @Basic
    @Column(name = "number")
    public int getNumber() {
        return number;
    }

    public void setNumber(int number) {
        this.number = number;
    }

    @Basic
    @Column(name = "airplane_type")
    public String getAirplaneType() {
        return airplaneType;
    }

    public void setAirplaneType(String airplaneType) {
        this.airplaneType = airplaneType;
    }

    @Basic
    @Column(name = "arrivalLocation")
    public String getArrivalLocation() {
        return arrivalLocation;
    }

    public void setArrivalLocation(String arrivalLocation) {
        this.arrivalLocation = arrivalLocation;
    }

    @Basic
    @Column(name = "departureLocation")
    public String getDepartureLocation() {
        return departureLocation;
    }

    public void setDepartureLocation(String departureLocation) {
        this.departureLocation = departureLocation;
    }


    @Basic
    @Column(name = "departure")
    public Timestamp getDeparture() {
        return departure;
    }

    public void setDeparture(Timestamp departure) {
        this.departure = departure;
    }

    @Basic
    @Column(name = "arrival")
    public Timestamp getArrival() {
        return arrival;
    }

    public void setArrival(Timestamp arrival) {
        this.arrival = arrival;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        FlightEntity that = (FlightEntity) o;

        if (id != that.id) return false;
        if (number != that.number) return false;
        if (airplaneType != null ? !airplaneType.equals(that.airplaneType) : that.airplaneType != null) return false;
        if (departure != null ? !departure.equals(that.departure) : that.departure != null) return false;
        if (arrival != null ? !arrival.equals(that.arrival) : that.arrival != null) return false;

        return true;
    }

    @Override
    public int hashCode() {
        int result = id;
        result = 31 * result + number;
        result = 31 * result + (airplaneType != null ? airplaneType.hashCode() : 0);
        result = 31 * result + (departure != null ? departure.hashCode() : 0);
        result = 31 * result + (arrival != null ? arrival.hashCode() : 0);
        return result;
    }
}
