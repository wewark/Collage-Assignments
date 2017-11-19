import java.util.ArrayList;
import java.util.HashMap;

public class ArithmaticCoding {
	private HashMap<Character, Pair> symbolLimits;
	private int K;
	int txtSize;

	ArithmaticCoding(ArrayList<Character> symbols, ArrayList<Double> probs) {
		symbolLimits = new HashMap<>();
		K = 1;

		for (int i = 1; i < probs.size(); ++i)
			probs.set(i, probs.get(i) + probs.get(i - 1));

		for (int i = 0; i < symbols.size(); ++i)
			symbolLimits.put(symbols.get(i), new Pair(i == 0 ? 0.0 : probs.get(i - 1), probs.get(i)));

		Double minRange = 1.0;
		for (Pair pair : symbolLimits.values())
			minRange = pair.range() < minRange ? pair.range() : minRange;

		while (Math.pow(2, -K) >= minRange) ++K;
		K += 3;
	}

	private Pair cur;
	private StringBuilder result;

	String encode(String txt) {
		txtSize = txt.length();
		result = new StringBuilder();
		cur = new Pair(0.0, 1.0);

		for (int i = 0; i < txt.length(); ++i) {
			updateCur(txt.charAt(i));

			while (true) {
				if (cur.upper <= 0.5)
					E1(true);
				else if (cur.lower >= 0.5)
					E2(true);
				else break;
			}
		}

		result.append(1);
		for (int i = 1; i < K; ++i)
			result.append(0);

		return result.toString();
	}

	String decode(String hash) {
		StringBuilder curHash = new StringBuilder();
		for (int i = 0; i < K; ++i)
			curHash.append(hash.charAt(i));

		Double pin = 0.0;
		String curHashStr = curHash.toString();
		for (int i = 0; i < curHashStr.length(); ++i)
			if (curHashStr.charAt(i) == '1')
				pin += Math.pow(2, -(i + 1));

		cur = new Pair(0.0, 1.0);
		result = new StringBuilder();
		result.append(getSymbol(pin));

		for (int i = K; result.length() < txtSize; ) {
			updateCur(result.charAt(result.length() - 1));

			boolean finish = false;
			while (!finish) {
				finish = true;
				if (cur.upper <= 0.5) {
					E1(false);
					finish = false;
				}
				else if (cur.lower >= 0.5) {
					E2(false);
					finish = false;
				}

				if (!finish) {
					if (hash.charAt(i - K) == '1')
						pin -= 0.5;
					pin *= 2;
					if (hash.charAt(i) == '1')
						pin += Math.pow(2, -K);
					i++;
				}
			}

			Double code = (pin - cur.lower) / cur.range();
			result.append(getSymbol(code));
		}
		return result.toString();
	}

	// TODO: Replace this with binary search
	private Character getSymbol(Double pin) {
		for (HashMap.Entry<Character, Pair> pair : symbolLimits.entrySet())
			if (pin >= pair.getValue().lower && pin <= pair.getValue().upper)
				return pair.getKey();
		return '\0';
	}

	private void updateCur(Character curChar) {
		Pair newLimits = new Pair();
		newLimits.lower = cur.lower + cur.range() * symbolLimits.get(curChar).lower;
		newLimits.upper = cur.lower + cur.range() * symbolLimits.get(curChar).upper;
		cur = newLimits;
	}

	private void E1(boolean append) {
		cur.lower = cur.lower * 2;
		cur.upper = cur.upper * 2;
		if (append) result.append(0);
	}

	private void E2(boolean append) {
		cur.lower = (cur.lower - 0.5) * 2;
		cur.upper = (cur.upper - 0.5) * 2;
		if (append) result.append(1);
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
