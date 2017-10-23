package com.huffman;

import java.util.*;

class Huffman {
	private String txt;

	static class HashResult {
		Pair[] codeTable;
		String code;
	}

	static class Pair {
		String letter, code;
		int frequency = 0;

		Pair(String letter, int frequency) {
			this.letter = letter;
			this.frequency = frequency;
		}
	}

	private static class Node {
		Node left, right;
		String letter;
		int frequency;
		boolean isLeaf = false;

		Node(Node left, Node right) {
			this.left = left;
			this.right = right;
			frequency = left.frequency + right.frequency;
		}

		Node(String letter, int frequency) {
			this.frequency = frequency;
			this.letter = letter;
			isLeaf = true;
		}

		static class NodePriority implements Comparator<Node> {
			public int compare(Node a, Node b) {
				return a.frequency - b.frequency;
			}
		}
	}

	private HashMap<String, Pair> table;

	HashResult encode(String _txt) {
		txt = _txt;
		table = new HashMap<>();
		calcFrequencies();
		buildTable();

		ArrayList<Pair> codeTable = new ArrayList<>();
		codeTable.addAll(table.values());

		HashResult result = new HashResult();
		result.codeTable = codeTable.toArray(new Pair[0]);

		StringBuilder sb = new StringBuilder();
		for (int i = 0; i < txt.length(); ++i) {
			String curChar = Character.toString(txt.charAt(i));
			sb.append(table.get(curChar).code);
		}
		result.code = sb.toString();

		return result;
	}

	String decode(HashResult hash) {
		table = new HashMap<>();
		for (Pair row : hash.codeTable) {
			table.put(row.code, row);
		}

		StringBuilder result = new StringBuilder();
		String curCode = "";
		boolean foundBefore = false;
		for (int i = 0; i < hash.code.length(); ++i) {
			curCode += Character.toString(hash.code.charAt(i));
			if (!table.containsKey(curCode) && foundBefore) {
				result.append(table.get(curCode.substring(0, curCode.length() - 1)).letter);
				curCode = curCode.substring(curCode.length() - 1);
				foundBefore = false;
			}
			if (table.containsKey(curCode)) {
				foundBefore = true;
			}
		}
		result.append(table.get(curCode).letter);
		return result.toString();
	}

	private void buildTable() {
		PriorityQueue<Node> pq = new PriorityQueue<>(new Node.NodePriority());
		for (Map.Entry<String, Pair> entry : table.entrySet()) {
			String key = entry.getKey();
			Pair value = entry.getValue();
			pq.add(new Node(key, value.frequency));
		}

		while (pq.size() > 1) {
			Node left = pq.remove(), right = pq.remove();
			pq.add(new Node(left, right));
		}

		dfs(pq.peek(), "");
	}

	private void dfs(Node node, String code) {
		if (node.isLeaf) {
			Pair row = table.get(node.letter);
			row.code = code;
			table.put(node.letter, row);
		}
		else {
			dfs(node.left, code + '0');
			dfs(node.right, code + '1');
		}
	}

	private void calcFrequencies() {
		for (int i = 0; i < txt.length(); ++i) {
			String curChar = Character.toString(txt.charAt(i));
			Pair row = table.get(curChar);
			if (row == null) {
				row = new Pair(curChar, 1);
			}
			else {
				row.frequency++;
			}

			table.put(curChar, row);
		}
	}
}
