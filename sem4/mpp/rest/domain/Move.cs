using System.Collections.ObjectModel;

namespace project_cs.domain;

public class Move : Identifiable<int> {
    public String user { set; get; }
    public String configuration { set; get; }
    public int points { get; set; }
    public int duration { get; set; }
    public Collection<Game> moves { get; set; }

    public override string ToString() {
        return "id : " + id + ", config: " + configuration + ", points: " + points;
    }
}