namespace lab14.domain;

public class Purchase : Entity<string> {
    public string product { get; set; }
    public int quantity { get; set; }
    public double productPrice { get; set; }
    public Receipt receipt { get; set; }
    public override string ToString() {
        return $"{id}, {product}, {quantity}, {productPrice}, {receipt.id}";
    }
}