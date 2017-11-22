import java.util.Comparator;

public class process {
    String name;
    int arrival;
    int burst;
    int remaining;
    int lastEntered;
    int waitingTime;
    int TurnAround;
    int priority;

    public process(String name, int arrival, int burst, int remaining, int lastEntered, int waitingTime, int turnAround) {
        this.name = name;
        this.arrival = arrival;
        this.burst = burst;
        this.remaining = remaining;
        this.lastEntered = lastEntered;
        this.waitingTime = waitingTime;
        TurnAround = turnAround;
    }




}
