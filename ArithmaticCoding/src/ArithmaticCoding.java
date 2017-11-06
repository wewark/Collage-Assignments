import java.util.ArrayList;
import java.util.HashMap;

public class ArithmaticCoding {
	private ArrayList<Character> symbols;
	private ArrayList<Double> probs;
	private HashMap<Character, Pair> symbolLimits;
	private int K;

	ArithmaticCoding(ArrayList<Character> symbols, ArrayList<Double> probs) {
		this.symbols = symbols;
		this.probs = probs;
		cur = new Pair(0.0, 1.0);
		result = new StringBuilder();
		symbolLimits = new HashMap<>();
		K = 1;

		for (int i = 1; i < probs.size(); ++i)
			probs.set(i, probs.get(i) + probs.get(i - 1));

		for (int i = 0; i < symbols.size(); ++i)
			symbolLimits.put(symbols.get(i), new Pair(i == 0 ? 0.0 : probs.get(i - 1), probs.get(i)));

		Double minRange = 1.0;
		for (Pair pair : symbolLimits.values())
			minRange = pair.range() < minRange ? pair.range() : minRange;

		while (Math.pow(2, -K) > minRange) ++K;
	}

	private Pair cur;
	private StringBuilder result;

	String encode(String txt) {
		for (int i = 0; i < txt.length(); ++i) {
			updateCur(txt.charAt(i));

			while (true) {
				if (cur.lower < 0.5 && cur.upper < 0.5)
					E1();
				else if (cur.lower > 0.5 && cur.upper > 0.5)
					E2();
				else break;
			}
		}

		Double mid = (cur.lower + cur.upper) / 2.0;
		System.out.println(mid);
		for (int i = 1; i <= K; ++i) {
			Double x= Math.pow(2,-i);
			if (Math.pow(2, -i) <= mid) {
				result.append(1);
				mid -= Math.pow(2, -i);
			}
			else result.append(0);
		}

		return result.toString();
	}

	private void updateCur(Character curChar) {
		Pair newLimits = new Pair();
		newLimits.lower = cur.lower + cur.range() * symbolLimits.get(curChar).lower;
		newLimits.upper = cur.lower + cur.range() * symbolLimits.get(curChar).upper;
		cur = newLimits;
	}

	private void E1() {
		Pair newLimits = new Pair();
		newLimits.lower = cur.lower * 2;
		newLimits.upper = cur.upper * 2;
		cur = newLimits;
		result.append(0);
	}

	private void E2() {
		Pair newLimits = new Pair();
		newLimits.lower = (cur.lower - 0.5) * 2;
		newLimits.upper = (cur.upper - 0.5) * 2;
		cur = newLimits;
		result.append(1);
	}

	private class Pair {
		Double upper, lower;

		Pair() {}

		Pair(Double lower, Double upper) {
			this.upper = upper;
			this.lower = lower;
		}

		Double range() {
			return upper - lower;
		}
	}
}
