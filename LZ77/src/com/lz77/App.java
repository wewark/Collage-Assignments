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
		ArrayList<LZ77.Tag> r = lz.encode(s);
		for (LZ77.Tag tag : r) {
			System.out.println(tag.toString());
		}
	}
}
