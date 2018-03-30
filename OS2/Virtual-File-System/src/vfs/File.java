package vfs;

class File {
	private String path;
	private int[] allocatedBlocks;
	private String filename;
	private int size;

	public File(String path, String filename, int size) {
		this.path = path;
		this.filename = filename;
		this.size = size;
	}
}
