import java.util.ArrayList;
import java.util.Scanner;

public class Priority {
	public static void prioritySimulation() {
		int n;
		int End = 0;
		System.out.print("Number of processes: ");
		Scanner sc = new Scanner(System.in);
		n = sc.nextInt();
		ArrayList<QProcess> processes = new ArrayList<>();
		ArrayList<QProcess> Finished = new ArrayList<>();
		ArrayList<String> order = new ArrayList<>();
		for (int i = 0; i < n; ++i) {
			System.out.print("QProcess Name: ");
			String name = sc.next();
			int arr = i;
			System.out.print("Burst Time: ");
			int bur = sc.nextInt();
			System.out.print("Priority: ");
			int pr = sc.nextInt();
			QProcess p = new QProcess(name, arr, bur, bur, 0, 0, 0);
			p.priority = pr;
			End += bur;
			processes.add(p);
		}

		int last = -1;
		for (int i = 0; i < End; ) {
			processes.sort((o1, o2) -> {
				if (o1.priority < o2.priority) return -1;
				else return 1;
			});
			System.out.println("Time: " + i);
			for (QProcess process : processes) {
				System.out.println(process.name + " " + process.remaining + " " + process.priority);
			}
			System.out.println("------------------------------------------");
			QProcess p = new QProcess(
					processes.get(0).name,
					processes.get(0).arrival,
					processes.get(0).burst,
					processes.get(0).remaining,
					processes.get(0).lastEntered,
					processes.get(0).waitingTime,
					processes.get(0).TurnAround
			);
			p.priority = processes.get(0).priority;
			p.waitingTime = i;
			i += p.burst;
			order.add(p.name);
			processes.remove(0);
			p.TurnAround = i - p.arrival;
			Finished.add(p);
			for (int j = 0; j < processes.size(); j++) {
				QProcess curProcess = processes.get(j);
				QProcess element = new QProcess(
						curProcess.name,
						curProcess.arrival,
						curProcess.burst,
						curProcess.remaining,
						curProcess.lastEntered,
						curProcess.waitingTime,
						curProcess.TurnAround
				);
				element.priority = curProcess.priority - 1;
				processes.set(j, element);
			}

		}
		double avgWaiting = 0.0, avgTurnaround = 0.0;
		System.out.println("Order of Execution:");
		for (int i = 0; i < order.size(); i++) {
			System.out.print(order.get(i));
			if (i != order.size() - 1) System.out.print("->");
		}
		System.out.println();
		for (QProcess finish : Finished) {
			System.out.println("Name: " + finish.name + " Waiting Time: " + finish.waitingTime + " Turn Around Time: " + finish.TurnAround);
			avgWaiting += finish.waitingTime;
			avgTurnaround += finish.TurnAround;
		}
		avgTurnaround /= n;
		avgWaiting /= n;
		System.out.println("Average Waiting Time : " + avgWaiting);
		System.out.println("Average Turn Around Time : " + avgTurnaround);
	}
}
