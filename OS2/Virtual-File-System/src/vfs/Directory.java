package vfs;

import java.io.Serializable;
import java.util.HashMap;

class Directory implements Serializable {
	public static Directory root = new Directory();

	private String path;
	private String name;
	HashMap<String, File> files = new HashMap<String, File>();
	HashMap<String, Directory> directories = new HashMap<String, Directory>();

	Directory(String path, String name) {
		this.path = path;
		this.name = name;
	}

	Directory() {

	}

	public void print(int level) {
		for (Directory dir : directories.values()) {
			for (int i = 0; i < level; ++i)
				System.out.print("\t");
			System.out.println("+" + dir.name);
			dir.print(level + 1);
		}
		for (String filename : files.keySet()) {
			for (int i = 0; i < level; ++i)
				System.out.print("\t");
			System.out.println("*" + filename);
		}
	}
}
