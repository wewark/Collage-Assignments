package vfs;

import java.io.Serializable;

class File implements Serializable {
	private String path;
	private String filename;
	int size;

	AllocationMethod allocationMethod;
	// Best fit
	public int startLocation;
	public int blockCount;

	// Indexed
	public int[] allocatedBlocks;

	// Extent-based
	public Extent firstExtent;

	public File(String path, String filename, int size,
	            AllocationMethod allocationMethod) {
		this.path = path;
		this.filename = filename;
		this.size = size;
		this.allocationMethod = allocationMethod;

		if (allocationMethod == AllocationMethod.EXTENT) {
			MemoryManager.allocateExtent(this);
		}
		else if (allocationMethod == AllocationMethod.BESTFIT) {
			MemoryManager.allocateBestFit(this);
		}
		else {
			MemoryManager.allocateIndexed(this);
		}
	}
}
