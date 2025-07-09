using System.Globalization;

namespace lab14.domain;

public class Document : Entity<string> {
    public string name { get; set; }
    public DateTime issueDate { get; set; }

    public override string ToString() {
        return $"{id}, {name}, {issueDate.ToString("d/M/yyyy", CultureInfo.InvariantCulture)}";
    }
}