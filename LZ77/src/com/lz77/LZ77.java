package com.lz77;

import jdk.nashorn.internal.runtime.FindProperty;

import java.sql.Struct;
import java.util.ArrayList;

public class LZ77 {
	public int windowSize;
	public int lookAheadBufferSize;

	public LZ77(int windowSize, int lookAheadBufferSize) {
		this.windowSize = windowSize;
		this.lookAheadBufferSize = lookAheadBufferSize;
	}

	private String txt;

	public class Tag {
		public int offset, length;
		public char nextSymbol;

		public Tag(int offset, int length, char nextSymbol) {
			this.offset = offset;
			this.length = length;
			this.nextSymbol = nextSymbol;
		}

		@Override
		public String toString() {
			return "<" + offset + "," + length + "," + nextSymbol + ">";
		}
	}

	public Tag getMax(int bufferStart) {
		int windowStart = bufferStart - windowSize;
		int bufferEnd = bufferStart + lookAheadBufferSize;
		int maxLength = 0, offset = 0;

		if (windowStart < 0) {
			windowStart = 0;
		}
		if (bufferEnd > txt.length()) {
			bufferEnd = txt.length();
		}

		for (int i = windowStart; i < bufferStart; ++i) {
			int a = i, b = bufferStart;
			while (b < bufferEnd && txt.charAt(a) == txt.charAt(b)) {
				a++; b++;
			}
			if (b - bufferStart > maxLength) {
				maxLength = b - bufferStart;
				offset = bufferStart - i;
			}
		}

		int nextCharIdx = bufferStart + maxLength;
		return new Tag(offset, maxLength, nextCharIdx < txt.length() ? txt.charAt(nextCharIdx) : 0);
	}

	public ArrayList<Tag> encode(String txt) {
		ArrayList<Tag> tags = new ArrayList<Tag>();
		this.txt = txt;
		for (int cur = 0; cur < txt.length();) {
			Tag ret = getMax(cur);
			tags.add(ret);
			cur += ret.length + 1;
		}
		return tags;
	}

	public static String decode(ArrayList<Tag> tags) {
		String result = "";
		for (Tag tag : tags) {
			int c = result.length();
			for (int i = 0; i < tag.offset; ++i) c--;

			for (int i = 0; i < tag.length; ++i) {
				result += result.charAt(c++);
			}
			result += tag.nextSymbol;
		}
		return result;
	}
}
