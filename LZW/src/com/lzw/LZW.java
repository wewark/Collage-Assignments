package com.lzw;

import java.util.ArrayList;
import java.util.HashMap;

public class LZW {
	String txt;
	ArrayList<String> dictionary = new ArrayList<>();
	HashMap<String, Integer> dictionaryIndex = new HashMap<>();

	public int[] encode(String _txt) {
		txt = _txt;
		getAlphabet();
		ArrayList<Integer> result = new ArrayList<>();

		boolean end = false;
		int a = 0, b = 1;
		while (!end) {
			String curStr = Character.toString(txt.charAt(a));
			while (b < txt.length() && dictionaryIndex.containsKey(curStr)) {
				curStr += txt.charAt(b++);
			}
			if (b < txt.length()) {
				dictionaryIndex.put(curStr, dictionary.size());
				dictionary.add(curStr);
			}
			else end = true;

			String lastPattern = txt.substring(a, b - 1);
			result.add(dictionaryIndex.get(lastPattern));
			a = b - 1;
		}

		return arrayListToArray(result);
	}

	private int[] arrayListToArray(ArrayList<Integer> arrayList) {
		int[] ret = new int[arrayList.size()];
		for (int i = 0; i < arrayList.size(); ++i) {
			if (arrayList.get(i) != null) {
				ret[i] = arrayList.get(i);
			}
		}
		return ret;
	}

	private void getAlphabet() {
		for (int i = 0; i < txt.length(); ++i) {
			String curChar = Character.toString(txt.charAt(i));
			if (!dictionaryIndex.containsKey(curChar)) {
				dictionaryIndex.put(curChar, dictionary.size());
				dictionary.add(curChar);
			}
		}
	}
}
