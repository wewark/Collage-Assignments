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
					if (type == 1)
						System.out.println(bestFit(size));
					else if (type == 2)
						System.out.println(worstFit(size));
					else
						System.out.println(firstFit(size));
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

	private static int firstFit(int size) {
		for (Partition cur : memory)
			if (!cur.used && cur.size >= size) {
				cur.allocate(size);
				return cur.start;
			}
		return -1;
	}

	private static int worstFit(int size) {
		Partition worst = new Partition(-1, -1, -1);
		for (Partition cur : memory)
			if (!cur.used && cur.sizeFree() >= size &&
					(worst.start == -1 || cur.size < worst.size))
				worst = cur;
		return worst.start;
	}

	private static int bestFit(int size) {
		Partition best = new Partition(-1, -1, -1);
		for (Partition cur : memory)
			if (!cur.used && cur.sizeFree() >= size &&
					(best.start == -1 || cur.size > best.size))
				best = cur;
		return best.start;
	}

	private static void defragment(int type) {
		// TODO: 12/12/2017  
	}

	private static boolean deallocate(int startAddress) {
		for (Partition cur : memory)
			if (cur.start == startAddress && cur.used) {
				cur.used = false;
				return true;
			}
		return false;
	}

	private static void print() {
		System.out.println("Start\tSize\tSize Allocated\tUsed");
		for (Partition cur : memory)
			System.out.println(cur);
	}
}
