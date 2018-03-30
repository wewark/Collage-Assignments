package vfs;

import java.io.*;
import java.util.Scanner;

public class Main {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		load();

		MemoryManager.initialize(10000, Directory.root);

		while (true) {
			String cmd = sc.nextLine();
			args = cmd.split(" ");

			switch (args[0]) {
				case "exit":
					save();
					return;
				case "CreateFile":
					createFile(args[1], Integer.parseInt(args[2]));
					break;
				case "CreateFolder":
					createFolder(args[1]);
					break;
				case "DeleteFile":
					deleteFile(args[1]);
					break;
				case "DeleteFolder":
					deleteFolder(args[1]);
					break;
				case "DisplayDiskStructure":
					Directory.root.print(0);
					break;
				case "DisplayDiskStatus":
					// TODO
					break;
			}
		}
	}

	private static void createFile(String pathStr, int size) {
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

	private static void createFolder(String pathStr) {
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

	private static void deleteFile(String pathStr) {
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
		cur.files.remove(filename);
	}

	private static void deleteFolder(String pathStr) {
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
		Directory cur = Directory.root;
		for (int i = 1; i < path.length - 1; ++i) {
			if (!cur.directories.containsKey(path[i]))
				return false;
			cur = cur.directories.get(path[i]);
		}

		return true;
	}

	private static Directory getParent(String[] path) {
		Directory ret = Directory.root;
		for (int i = 1; i < path.length - 1; ++i) {
			ret = ret.directories.get(path[i]);
		}
		return ret;
	}

	private static void save() {
		try {
			FileOutputStream fileOut =
					new FileOutputStream("vfs.ser");
			ObjectOutputStream out = new ObjectOutputStream(fileOut);
			out.writeObject(Directory.root);
			out.close();
			fileOut.close();
			System.out.print("Serialized data is saved in /vfs.ser");
		} catch (IOException i) {
			i.printStackTrace();
		}
	}

	private static void load() {
		try {
			FileInputStream fileIn = new FileInputStream("vfs.ser");
			ObjectInputStream in = new ObjectInputStream(fileIn);
			Directory.root = (Directory) in.readObject();
			in.close();
			fileIn.close();
		} catch (IOException i) {
			i.printStackTrace();
			return;
		} catch (ClassNotFoundException c) {
			System.out.println("class not found");
			c.printStackTrace();
			return;
		}
	}
}
