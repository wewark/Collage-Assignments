import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;

public class PredictiveCoding {
	private int bits;

	PredictiveCoding(int bits) {
		this.bits = bits;
	}

	HashResult encode(int[][] img) {
		int height = img.length, width = img[0].length;
		int[] img1D = new int[height * width];

		for (int i = 0; i < height; ++i)
			for (int j = 0; i < width; ++j)
				img1D[j + i * height] = img[i][j];

		Integer[] diff = new Integer[img1D.length];
		diff[0] = img1D[0];
		for (int i = 1; i < img1D.length; ++i)
			diff[i] = img1D[i] - img1D[i - 1];

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

		for (int i = 0; i < img1D.length; ++i)
			result.idx.add(mp.get(diff[i]));

		return result;
	}

	static class HashResult {
		ArrayList<Integer> quantizer = new ArrayList<>();
		ArrayList<Integer> idx;
	}
}
