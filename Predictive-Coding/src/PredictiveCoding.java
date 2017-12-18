import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;

public class PredictiveCoding {
	private int bits, height, width;

	PredictiveCoding(int bits) {
		this.bits = bits;
	}

	HashResult encode(int[][] img) {
		height = img.length; width = img[0].length;
		int[] img1D = new int[height * width];

		for (int i = 0; i < height; ++i)
			System.arraycopy(img[i], 0, img1D, i * width, width);

		Integer[] diff = new Integer[img1D.length - 1];
		for (int i = 1; i < img1D.length; ++i)
			diff[i - 1] = img1D[i] - img1D[i - 1];

		ArrayList<ArrayList<Integer>> sq = ScalarQuantization.encode(new ArrayList<>(Arrays.asList(diff)), bits);
		HashMap<Integer, Integer> mp = new HashMap<>();
		HashResult result = new HashResult();
		int c = 0;
		for (ArrayList<Integer> curArr : sq) {
			int avg = ScalarQuantization.average(curArr);
			result.quantizer.add(avg);
			for (Integer i : curArr)
				mp.put(i, c);
			c++;
		}

		result.idx.add(img1D[0]);
		for (Integer i : diff)
			result.idx.add(mp.get(i));

		return result;
	}

	static class HashResult {
		ArrayList<Integer> quantizer = new ArrayList<>();
		ArrayList<Integer> idx = new ArrayList<>();

		@Override
		public String toString() {
			StringBuilder ret = new StringBuilder();
			for (int i = 0; i < quantizer.size(); ++i)
				ret.append(i).append(" ").append(quantizer.get(i)).append("\n");
			for (Integer i : idx)
				ret.append(i).append(" ");
			return ret.toString();
		}
	}

	int[][] decode(HashResult hash) {
		int[] img1D = new int[hash.idx.size()];
		img1D[0] = hash.idx.get(0);
		for (int i = 1; i < img1D.length; ++i)
			img1D[i] = img1D[i - 1] - hash.quantizer.get(hash.idx.get(i));

		int[][] img = new int[height][width];
		for (int i = 0; i < height; ++i)
			System.arraycopy(img1D, i * width, img[i], 0, width);
		return img;
	}
}
