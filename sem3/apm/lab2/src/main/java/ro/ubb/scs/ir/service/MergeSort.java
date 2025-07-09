package ro.ubb.scs.ir.service;

import java.util.ArrayList;

public class MergeSort extends AbstractSorter {
	public void sortUtil(ArrayList<Integer> list, int left, int right) {
		if (left == right)
			return;
		int m = (left + right) / 2;
		sortUtil(list, left, m);
		sortUtil(list, m + 1, right);
		ArrayList<Integer> result = new ArrayList<>();
		int i = left, j = m + 1;
		while (i <= m && j <= right)
			if (list.get(i) < list.get(j))
				result.add(list.get(i++));
			else
				result.add(list.get(j++));
		while (i < m + 1)
			result.add(list.get(i++));
		while (j < right)
			result.add(list.get(j++));
		for (int t = left; t <= right; ++t)
			list.set(t, result.get(t-left));
	}

	@Override
	public void sort(ArrayList<Integer> list) {
		int n = list.size();
		if (n == 0)
			return;
		sortUtil(list, 0, n - 1);
	}
}
