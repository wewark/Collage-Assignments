package com.example;

import java.io.File;
import java.nio.charset.Charset;
import java.nio.file.*;
import java.util.*;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.zip.Inflater;

public class CLI {
	static String currentDir = System.getProperty("user.dir");

	// Returns the absolute path (e.g "C:\myparent\myfile.txt")
	// instead of the relative path (e.g "myfile.txt" when the current directory is "C:\myparent")
	public static String makeAbsolute(String path) {
		File file = new File(path);
		if (!file.isAbsolute())
			return currentDir + "/" + path;
		return path;
	}

	public static boolean isPath(String path) {
		File file = new File(path);

		if (!file.isAbsolute())
			file = new File(currentDir + "/" + path);

		if (!file.exists()) {
			System.out.println("Directory doesn't exist");
			return false;
		} else if (!file.isDirectory()) {
			System.out.println("This is not a directory");
			return false;
		}
		return true;
	}

	public static String removeDots(String path) {
		path = path.replaceAll("([.])", "");
		return path;
	}

	public static boolean checkArgs(String[] args, int desiredSize) {
		if (args.length > desiredSize) {
			System.out.println("Too many arguments!");
			return false;
		}
		if (args.length < desiredSize) {
			System.out.println("Too few arguments!");
			return false;
		}
		return true;
	}

	public static void clear(String[] args) {
		// :'D
		for (int i = 0; i < 20; i++) {
			System.out.println("\n");
		}
	}

	public static void cd(String[] args) {
		if (args.length < 1 || args.length > 2) return;
		if (args.length == 1) {
			Path path = Paths.get("C:\\");
			path = path.normalize();
			path = Paths.get(removeDots(path.toString()));
			currentDir = path.toString();
			System.setProperty("user.dir", currentDir);
			return;
		}

		if (!isPath(args[1])) return;

		Path path = Paths.get(makeAbsolute(args[1]));

		path = path.normalize();
		path = Paths.get(removeDots(path.toString()));
		currentDir = path.toString();
		System.setProperty("user.dir", currentDir);
	}

	public static String[] ls(String[] args) {
		if (!checkArgs(args, 1)) return new String[0];

		File file = new File(currentDir);
		return file.list();
	}

	public static void cp(String[] args) {
		args[1] = makeAbsolute(args[1]);
		args[2] = makeAbsolute(args[2]);
		Path oldPath = Paths.get(args[1]);
		Path newPath = Paths.get(args[2]);
		try {
			Files.copy(oldPath, newPath, StandardCopyOption.REPLACE_EXISTING);
		} catch (Exception e) {
			System.out.println(e);
		}
	}

	public static String date(String[] args) {
		if (!checkArgs(args, 1)) return "";

		DateFormat dateFormat = new SimpleDateFormat("yyyy/MM/dd HH:mm:ss");
		Date date = new Date();
		return dateFormat.format(date);
	}

	public static void mv(String[] args) {
		cp(args);
		rm(new String[]{args[0], args[1]});
	}

	public static void rm(String args[]) {
		if (!checkArgs(args, 2)) return;
		File file = new File(makeAbsolute(args[1]));
		if (file.delete()) return;
		else System.out.println("File not found");
	}

	public static void mkdir(String args[]) {
		if (!checkArgs(args, 2)) return;
		File file = new File(makeAbsolute(args[1]));
		file.mkdir();

	}

	public static void rmdir(String args[]) {
		if (!checkArgs(args, 2)) return;
		if (!isPath(args[1])) return;
		File file = new File(makeAbsolute(args[1]));
		file.delete();
	}

	public static String[] cat(String[] args) {
		ArrayList<String> lines = new ArrayList<String>();
		for (int i = 1; i < args.length; i++) {
			Path path = Paths.get(makeAbsolute(args[i]));
			try {
				Files.lines(path).forEach(lines::add);
			} catch (Exception e) {
				System.out.println(e);
			}
		}
		return lines.toArray(new String[0]);
	}

	public static void more(String[] args, String[] lines) {
		if (lines.length == 0)
			lines = cat(args);
		Scanner scan = new Scanner(System.in);
		for (int i = 0; i < lines.length; ) {
			for (int j = 0; j < 10 && i < lines.length; j++, i++) {
				System.out.print(lines[i]);
				if (j < 9 && i < lines.length - 1)
					System.out.println();
			}
			if (i != lines.length - 1)
				scan.nextLine();
		}
	}

	public static String pwd(String[] args) {
		return currentDir;
	}

	public static String[] help(String[] args) {
		if (!checkArgs(args, 1)) return new String[]{""};
		return new String[]{
				"args",
				"clear",
				"cd",
				"ls",
				"cp",
				"mv",
				"rm",
				"mkdir",
				"rmdir",
				"cat",
				"more",
				"pwd",
				"",
				"date",
				"exit"
		};
	}

	private static HashMap<String, String> description = new HashMap<String, String>();

	static {
		description.put("clear", "clear: Clears the window and the line buffer, Example: clear");
		description.put("cd", "cd directory: Changes your current directory to the directory specified, Example:cd bin, Changes directory to the bin directory");
		description.put("ls", "ls: Lists all the non hidden files and directories, Example:ls, Lists all non hidden files and directories in the current directory");
		description.put("cp", "cp old new: Copy the contents of the file old to the file new , Example:cp old.txt new.txt, Copy the containts of the file old.txt to the file new.txt");
		description.put("mv", "mv old new: Move the contents of the file old to the file new and delete the old file , Example:mv old.txt new.txt, move the contents of the file old.txt to the file new.txt and delete old.txt");
		description.put("rm", "rm file: Deletes file, Example rm xyz, Deletes a file named xyz");
		description.put("mkdir", "mkdir dirName: Deletes file, Example rm xyz, Deletes a file named xyz");
		description.put("rmdir", "rmdir directory: Deletes directory, Example rmdir xyz, Deletes directory named xyz");
		description.put("cat", "cat file1: show contents of file1, Example cat file1, This prints the file1 file to the screen");
		description.put("more", "more file: Prints content of the given file one screen(10 lines) at a time.");
		description.put("date", "date: Writes the current date to the screen");
		description.put("help", "help: list all user commands");
		description.put("pwd", "pwd: Prints the current directory to the screen");
		description.put("exit", "exit: exit the terminal");
	}

	// When '?' is written before a command
	public static String[] helpCmd(String[] args) {
		if (!checkArgs(args, 2)) return new String[]{" "}; ;

		ArrayList<String> ret = new ArrayList<String>();
		String result = description.get(args[1]);
		if (result != null) {
			ret.add(result);
		} else {
			ret.add("'" + args[1] + "' is not recognized as an internal or external command,\n" + "operable program or batch file.");
		}
		return ret.toArray(new String[0]);
	}

	public static String[] args(String args[]) {
		ArrayList<String> ret = new ArrayList<String>();
		ret.addAll(description.values());
		return ret.toArray(new String[0]);
	}

	public static String[] removeQuotes(String cmd) {
		ArrayList<String> ret = new ArrayList<String>();
		int a = 0, b = 0;

		cmd = cmd.trim();
		String[] words = cmd.split(" ");

		while (a < words.length) {
			if (words[a].length() > 0 && words[a].charAt(0) == '"') {
				if (words[a].charAt(words[a].length() - 1) == '"') {
					ret.add(words[a].substring(1, words[a].length() - 1));
					a++; b = a;
					continue;
				}
				ret.add(words[a].substring(1));
				b++;

				while (b < words.length && words[b].charAt(words[b].length() - 1) != '"') {
					String lastWord = ret.get(ret.size() - 1);
					ret.set(ret.size() - 1, lastWord + " " + words[b]);
					b++;
				}
				if (b < words.length) {
					String lastWord = ret.get(ret.size() - 1);
					ret.set(ret.size() - 1, lastWord + " " + words[b].substring(0, words[b].length() - 1));
				}
				b++; a = b;
			} else {
				ret.add(words[a++]);
				b = a;
			}
		}

		return ret.toArray(new String[0]);
	}

	public static void writeToFile(String filePath, String[] lines, boolean append) {
		List<String> linesList = Arrays.asList(lines);
		Path path = Paths.get(makeAbsolute(filePath));
		try {
			if (append)
				Files.write(path, linesList, Charset.defaultCharset(), StandardOpenOption.APPEND);
			else
				Files.write(path, linesList, Charset.defaultCharset());
		} catch (Exception e) {
			System.out.println(e);
		}
	}

	public static String[] executeCmd(String cmd, String[] prevOutput) {
		String[] args = removeQuotes(cmd);
		String[] output = new String[0];

		switch (args[0]) {
			case "clear":
				clear(args);
				break;
			case "cd":
				cd(args);
				break;
			case "ls":
				output = ls(args);
				break;
			case "cp":
				cp(args);
				break;
			case "mv":
				mv(args);
				break;
			case "rm":
				rm(args);
				break;
			case "mkdir":
				mkdir(args);
				break;
			case "rmdir":
				rmdir(args);
				break;
			case "cat":
				output = cat(args);
				break;
			case "more":
				more(args, prevOutput);
				break;
			case "date":
				output = new String[]{date(args)};
				break;
			case "help":
				output = help(args);
				break;
			case "?":
				output = helpCmd(args);
				break;
			case "args":
				output = args(args);
				break;
			case "pwd":
				output = new String[]{pwd(args)};
				break;
			case "exit":
				System.exit(0);
			default:
				output = new String[]{"'" + args[0] + "' is not recognized as an internal or external command,\n" +
						"operable program or batch file."};
		}
		return output;
	}

	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		while (true) {
			System.out.print(currentDir + ": ");
			String input = scan.nextLine();

			String filePath = "";
			boolean append = false;
			if (input.contains(">>")) {
				filePath = input.substring(input.indexOf(">>") + 2);
				filePath = filePath.trim();
				input = input.substring(0, input.indexOf(">>"));
				append = true;
			} else if (input.contains(">")) {
				filePath = input.substring(input.indexOf(">") + 1);
				filePath = filePath.trim();
				input = input.substring(0, input.indexOf(">"));
			}

			String[] cmds = input.split("[|]");
			String[] output = new String[0];

			for (String cmd : cmds) {
				output = executeCmd(cmd, output);
			}

			if (!filePath.equals("")) {
				writeToFile(filePath, output, append);
			} else {
				for (String line : output) {
					System.out.println(line);
				}
			}
		}
	}
}
