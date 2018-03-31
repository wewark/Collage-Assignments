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

	public static void createFile(String pathStr, int size) {
		String[] path = pathStr.split("/");
		if (!valid(path)) {
			System.out.println("invalid path");
			return;
		}

		Directory cur = getParent(path);
		String filename = path[path.length - 1];
		if (cur.files.containsKey(filename)) {
			System.out.println("file already exists");
			return;
		}

		System.out.println("File created");
		cur.files.put(filename,
				new File(pathStr, filename, size, AllocationMethod.BESTFIT)); // temp
	}

	public static void createFolder(String pathStr) {
		String[] path = pathStr.split("/");
		if (!valid(path)) {
			System.out.println("invalid path");
			return;
		}

		Directory cur = getParent(path);
		String dirname = path[path.length - 1];
		if (cur.directories.containsKey(dirname)) {
			System.out.println("directory already exists");
			return;
		}

		System.out.println("Folder created");
		cur.directories.put(dirname, new Directory(pathStr, dirname));
	}

	public static void deleteFile(String pathStr) {
		String[] path = pathStr.split("/");
		if (!valid(path)) {
			System.out.println("invalid path");
			return;
		}

		Directory cur = getParent(path);
		String filename = path[path.length - 1];
		if (!cur.files.containsKey(filename)) {
			System.out.println("file doesn't exist");
			return;
		}

		System.out.println("File deleted");
		MemoryManager.deallocate(cur.files.get(filename));
		cur.files.remove(filename);
	}

	public static void deleteFolder(String pathStr) {
		String[] path = pathStr.split("/");
		if (!valid(path)) {
			System.out.println("invalid path");
			return;
		}

		Directory cur = getParent(path);
		String dirname = path[path.length - 1];
		if (!cur.directories.containsKey(dirname)) {
			System.out.println("directory doesn't exist");
			return;
		}

		System.out.println("Folder deleted");
		cur.directories.remove(dirname);
	}

	private static boolean valid(String[] path) {
		if (!path[0].equals("root")) return false;
		Directory cur = root;
		for (int i = 1; i < path.length - 1; ++i) {
			if (!cur.directories.containsKey(path[i]))
				return false;
			cur = cur.directories.get(path[i]);
		}

		return true;
	}

	private static Directory getParent(String[] path) {
		Directory ret = root;
		for (int i = 1; i < path.length - 1; ++i) {
			ret = ret.directories.get(path[i]);
		}
		return ret;
	}
}
