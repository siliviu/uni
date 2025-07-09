using System.Globalization;

namespace lab14.domain;

public enum Category {
    Utilities, Groceries, Fashion, Entertainment, Electronics
}

public class Receipt : Document {
    public DateTime dueDate { get; set; }
    public List<Purchase> purchases { get; } = new List<Purchase>();
    public Category category { get; set; }
    public override string ToString()
    {
        return base.ToString()+ $", {dueDate.ToString("d/M/yyyy", CultureInfo.InvariantCulture)}, {category}";
    }
}
