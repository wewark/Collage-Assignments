import java.util.ArrayList;

public class ScalarQuantization {
	static ArrayList<ArrayList<Integer>> encode(ArrayList<Integer> nums, int bits) {
		ArrayList<ArrayList<Integer>> num = new ArrayList<>();
		num.add(nums);

		for (int i = 0; i < bits; ++i)
			num = split(num, true);

		ArrayList<ArrayList<Integer>> tmpArr = num;
		do {
			num = tmpArr;
			tmpArr = split(num, false);
		} while (!tmpArr.equals(num));

		return num;
	}

	private static ArrayList<ArrayList<Integer>> split(ArrayList<ArrayList<Integer>> num, boolean splitIt) {
		ArrayList<ArrayList<Integer>> ret = new ArrayList<>();
		int size = splitIt ? num.size() * 2 : num.size();
		for (int i = 0; i < size; ++i)
			ret.add(new ArrayList<>());

		ArrayList<Integer> avg = new ArrayList<>();
		for (ArrayList<Integer> curArr : num) {
			int curAvg = average(curArr);
			if (splitIt) {
				avg.add(curAvg - 1);
				avg.add(curAvg + 1);
			}
			else avg.add(curAvg);
		}

		for (ArrayList<Integer> curArr : num) {
			for (Integer cur : curArr) {
				int mn = (int) 1e9, mni = -1;
				for (int i = 0; i < avg.size(); ++i) {
					if (Math.abs(avg.get(i) - cur) < mn) {
						mn = Math.abs(avg.get(i) - cur);
						mni = i;
					}
				}

				ret.get(mni).add(cur);
			}
		}

		return ret;
	}

	static int average(ArrayList<Integer> num) {
		int ret = 0;
		for (Integer i : num)
			ret += i;
		return ret / num.size();
	}
}
