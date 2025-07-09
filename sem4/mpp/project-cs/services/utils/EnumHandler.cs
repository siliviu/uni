using project_cs.domain;

namespace project_cs.utils;

public static class EnumHandler {
    public static String? GetStringFromGroup(AgeGroup ageGroup) {
        if (ageGroup == AgeGroup.SIX_EIGHT)
            return "6-8";
        if (ageGroup == AgeGroup.NINE_ELEVEN)
            return "9-11";
        if (ageGroup == AgeGroup.TWELVE_FIFTEEN)
            return "12-15";
        return null;
    }

    public static String? GetStringFromDistance(RaceDistance raceDistance) {
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

    public static AgeGroup? GetGroupFromString(string ageGroupString) {
		foreach (AgeGroup group in Enum.GetValues(typeof(AgeGroup)))
			if (GetStringFromGroup(group) == ageGroupString)
				return group;
        return null;
    }

	public static RaceDistance? GetRaceFromString(string raceDistanceString) {
		foreach (RaceDistance distance in Enum.GetValues(typeof(RaceDistance)))
			if (GetStringFromDistance(distance) == raceDistanceString)
				return distance;
        return null;
	}

	public static List<RaceDistance> GetRacesFromAge(AgeGroup ageGroup) {
        int pos = (int)ageGroup, nrAges = Enum.GetNames(typeof(AgeGroup)).Length, nrDistances = Enum.GetNames(typeof(RaceDistance)).Length;
        return Enum.GetValues(typeof(RaceDistance)).OfType<RaceDistance>().Skip(0).Take(nrDistances-nrAges+pos+1).ToList();
    }

    public static AgeGroup? GetGroupFromAge(int age) {
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