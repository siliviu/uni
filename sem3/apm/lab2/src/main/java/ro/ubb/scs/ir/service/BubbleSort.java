package ro.ubb.scs.ir.service;

import java.util.ArrayList;

public class BubbleSort extends AbstractSorter {
	@Override
	public void sort(ArrayList<Integer> list) {
		int n = list.size();
		boolean ok = true;
		while (ok) {
			ok = false;
			for (int i = 1; i < n; ++i) {
				if (list.get(i) < list.get(i - 1)) {
					var temp = list.get(i);
					list.set(i, list.get(i - 1));
					list.set(i - 1, temp);
					ok = true;
				}
			}
		}
	}
}
