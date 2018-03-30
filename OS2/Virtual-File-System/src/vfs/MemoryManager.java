package vfs;

public class MemoryManager {
	public static boolean memory[];

	public static void initialize(int memorySize) {
		memory = new boolean[memorySize];
	}

	public static void initialize(int memorySize, Directory root) {
		// TODO
	}

	public static void allocateBestFit(File file) {
		// TODO
	}

	public static void allocateIndexed(File file) {
		// TODO
	}
}
