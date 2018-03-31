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
					Directory.createFile(args[1], Integer.parseInt(args[2]));
					break;
				case "CreateFolder":
					Directory.createFolder(args[1]);
					break;
				case "DeleteFile":
					Directory.deleteFile(args[1]);
					break;
				case "DeleteFolder":
					Directory.deleteFolder(args[1]);
					break;
				case "DisplayDiskStructure":
					Directory.root.print(0);
					break;
				case "DisplayDiskStatus":
					MemoryManager.printDiskStatus();
					break;
			}
		}
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
		} catch (ClassNotFoundException c) {
			System.out.println("class not found");
			c.printStackTrace();
		}
	}
}
