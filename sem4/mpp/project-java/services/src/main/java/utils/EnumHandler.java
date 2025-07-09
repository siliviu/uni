package utils;

import domain.AgeGroup;
import domain.RaceDistance;

import java.util.Arrays;
import java.util.List;

public class EnumHandler {
	public static String getStringFromGroup(AgeGroup ageGroup) {
		if (ageGroup == AgeGroup.SIX_EIGHT)
			return "6-8";
		if (ageGroup == AgeGroup.NINE_ELEVEN)
			return "9-11";
		if (ageGroup == AgeGroup.TWELVE_FIFTEEN)
			return "12-15";
		return null;
	}

	public static String getStringFromDistance(RaceDistance raceDistance) {
		if (raceDistance == RaceDistance.FIFTY)
			return "50m";
		if (raceDistance == RaceDistance.HUNDRED)
			return "100m";
		if (raceDistance == RaceDistance.THOUSAND)
			return "1000m";
		if (raceDistance == RaceDistance.FIFTEEN_HUNDRED)
			return "1500m";
		return null;
	}

	public static List<RaceDistance> getRacesFromAge(AgeGroup ageGroup) {
		int pos = ageGroup.ordinal(), nrAges = AgeGroup.values().length, nrDistances = RaceDistance.values().length;
		return Arrays.stream(RaceDistance.values()).toList().subList(0, nrDistances - nrAges + pos + 1);
	}

	public static AgeGroup getGroupFromAge(int age) {
		if (age < 6)
			return null;
		if (age <= 8)
			return AgeGroup.SIX_EIGHT;
		if (age <= 11)
			return AgeGroup.NINE_ELEVEN;
		if (age <= 15)
			return AgeGroup.TWELVE_FIFTEEN;
		return null;
	}
}
