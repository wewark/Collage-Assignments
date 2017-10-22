package com.lzw;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.StringJoiner;

public class LZW {
	private String txt;
	private ArrayList<String> dictionary = new ArrayList<>();
	private HashMap<String, Integer> dictionaryIndex = new HashMap<>();

	public int[] encode(String _txt) {
		txt = _txt;
		initializeDictionary();
		ArrayList<Integer> result = new ArrayList<>();

		int a = 0, b = 1;
		while (true) {
			String curStr = Character.toString(txt.charAt(a));
			while (b < txt.length() && dictionaryIndex.containsKey(curStr)) {
				curStr += txt.charAt(b++);
			}
			if (b < txt.length()) {
				addToDictionary(curStr);
			} else {
				if (dictionaryIndex.containsKey(curStr)) {
					result.add(dictionaryIndex.get(curStr));
				} else {
					result.add(dictionaryIndex.get(curStr.substring(0, curStr.length() - 1)));
					result.add(dictionaryIndex.get(Character.toString(curStr.charAt(curStr.length() - 1))));
				}
				break;
			}

			String lastPattern = txt.substring(a, b - 1);
			result.add(dictionaryIndex.get(lastPattern));
			a = b - 1;
		}

		return arrayListToArray(result);
	}

	public String decode(int[] hash) {
		initializeDictionary();
		StringBuilder result = new StringBuilder();
		for (int i = 0; i < hash.length; ++i) {
			if (hash[i] < dictionary.size()) {
				result.append(dictionary.get(hash[i]));
				if (i > 0) {
					addToDictionary(dictionary.get(hash[i - 1]) + dictionary.get(hash[i]).charAt(0));
				}
			} else {
				String curPattern = dictionary.get(hash[i - 1]);
				curPattern += curPattern.charAt(0);
				result.append(curPattern);
				addToDictionary(curPattern);
			}
		}
		return result.toString();
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

	private void initializeDictionary() {
		dictionary = new ArrayList<>();
		dictionaryIndex = new HashMap<>();
		for (char c = 0; c < 256; c++) {
			String curChar = Character.toString(c);
			addToDictionary(curChar);
		}
	}

	private void addToDictionary(String pattern) {
		dictionaryIndex.put(pattern, dictionary.size());
		dictionary.add(pattern);
	}
}
