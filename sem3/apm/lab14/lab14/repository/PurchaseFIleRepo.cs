using System.Globalization;
using lab14.domain;

namespace lab14.repository;

public class PurchaseFileRepo : InFileRepository<String, Purchase> {
    public PurchaseFileRepo(string fileName, ReceiptFileRepo receiptRepo) : base(fileName, new PurchaseReader()) {
        Dictionary<string, Receipt> receipts = receiptRepo.FindAll().ToDictionary(r => r.id);
        foreach (var purchase in entities.Values) {
            var receiptId = purchase.receipt.id;
            purchase.receipt = receipts[receiptId];
        }
    }
}

public class PurchaseReader : Reader<Purchase> {
    public Purchase Parse(string line) {
        string[] fields = line.Split(", ");
        return new Purchase {
            id = fields[0],
            product = fields[1],
            quantity = Int32.Parse(fields[2]),
            productPrice = Double.Parse(fields[3]),
            receipt = new Receipt { id = fields[4] }
        };
    }
}