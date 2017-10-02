package com.example;

import java.util.Scanner;

public class CLI {
	static String currentDirectory = System.getProperty("user.dir");

	public static void main(String[] args) {
		while (true) {
			System.out.print(currentDirectory + ": ");
			Scanner scan = new Scanner(System.in);
			String cmd = scan.nextLine();
			System.out.println(cmd);
		}
	}
}
