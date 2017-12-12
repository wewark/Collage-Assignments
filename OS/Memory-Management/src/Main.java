import java.util.ArrayList;
import java.util.Scanner;

public class Main {
	static ArrayList<Partition> memory = new ArrayList<>();

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int initialSize = sc.nextInt();

		memory.add(new Partition(0, initialSize, 0));

		while (true) {
			int x = sc.nextInt();
			switch (x) {
				case 1:
					int size = sc.nextInt();
					int type = sc.nextInt();
					if (type == 1) bestFit(size);
					else if (type == 2) worstFit(size);
					else firstFit(size);
					break;
				case 2:
					int startAddress = sc.nextInt();
					deallocate(startAddress);
					break;
				case 3:
					type = sc.nextInt();
					defragment(type);
					break;
				case 4:
					print();
					break;
			}
		}
	}

	private static void firstFit(int size) {
		// TODO: 12/12/2017
	}

	private static void worstFit(int size) {
		// TODO: 12/12/2017
	}

	private static void bestFit(int size) {
		// TODO: 12/12/2017
	}

	private static void defragment(int type) {
		// TODO: 12/12/2017  
	}

	private static void deallocate(int startAddress) {
		// TODO: 12/12/2017  
	}

	private static void print() {
		// TODO: 12/12/2017
	}
}
