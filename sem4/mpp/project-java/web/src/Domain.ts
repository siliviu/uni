
export interface Child {
    id: string;
    name?: string;
    age?: string;
}

export enum AgeGroup {
    SIX_EIGHT = "6-8",
    NINE_ELEVEN = "9-11",
    TWELVE_FIFTEEN = "12-15"
}

export enum RaceDistance {
    FIFTY = "50m",
    HUNDRED = "100m",
    THOUSAND = "1000m",
    FIFTEEN_HUNDRED = "1500m"
}


export interface Signup {
    id?: string;
    child: Child;
    ageGroup: string;
    raceDistance: string;
}
