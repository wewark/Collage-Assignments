package com.lz77;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;

public class App {
	private JPanel panelMain;

	public static void main(String[] args) {
//		JFrame frame = new JFrame("App");
//		frame.setContentPane(new App().panelMain);
//		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
//		frame.pack();
//		frame.setResizable(false);
//		frame.setVisible(true);
		LZ77 lz = new LZ77(5, 5);
		String s = "cabracadabrarrarrad";
		ArrayList<LZ77.Tag> tags = lz.encode(s);
		for (LZ77.Tag tag : tags) {
			System.out.println(tag.toString());
		}
		System.out.println(LZ77.decode(tags));
		if (LZ77.decode(tags).equals(s))
			System.out.println("Equal!!");
	}
}
