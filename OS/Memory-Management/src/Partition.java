public class Partition {
	int start, size, sizeAllocated;
	boolean used = false;

	Partition(int start, int size, int sizeAllocated) {
		this.start = start;
		this.size = size;
		this.sizeAllocated = sizeAllocated;
	}

	public boolean allocate(int size) {
		if (!used) {
			this.sizeAllocated = size;
			this.used = true;
			return true;
		}
		return false;
	}
}
