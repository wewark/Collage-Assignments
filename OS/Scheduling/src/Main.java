import java.util.Scanner;

public class Main {
	public static void main(String[] args) {
		while (true) {
			System.out.println("1: preemptive Shortest- Job First (SJF) Scheduling");
			System.out.println("2: Round Robin (RR)");
			System.out.println("3: Priority Scheduling");
			System.out.println("4: AG Scheduling");
			System.out.println("5: Exit");
			System.out.print("Input: ");
			Scanner sc = new Scanner(System.in);
			int input = sc.nextInt();
			switch (input) {
				case 1:
					SJF.sjfSimulation();
					break;
				case 2:
					RR.rrSimulation();
					break;
				case 3:
					Priority.prioritySimulation();
					break;
				case 4:
					AG.agSimulation();
					break;
				case 5:
					return;
				default:
					System.out.println("Invalid Input");
					break;
			}
			for (int i = 0; i < 13; i++) System.out.println();
		}


	}
}
