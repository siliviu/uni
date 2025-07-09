using System.Globalization;
using lab14.domain;

namespace lab14.repository;

public class ReceiptFileRepo : InFileRepository<String, Receipt> {
    public ReceiptFileRepo(string fileName, DocumentFileRepo documentRepo) : base(fileName, new ReceiptReader()) {
        Dictionary<string, Document> documents = documentRepo.FindAll().ToDictionary(d => d.id);
        foreach (var (key, value) in entities) {
            Document document = documents[key];
            value.name = document.name;
            value.issueDate = document.issueDate;
        }
    }

    public void LoadPurchases(PurchaseFileRepo purchaseFileRepo) {
        purchaseFileRepo.FindAll().ToList().ForEach(purchase => {
            var receiptId = purchase.receipt.id;
            entities[receiptId].purchases.Add(purchase);
        });
    }
}

public class ReceiptReader : Reader<Receipt> {
    public Receipt Parse(string line) {
        string[] fields = line.Split(", ");
        return new Receipt {
            id = fields[0],
            dueDate = DateTime.ParseExact(fields[1], "d/M/yyyy", CultureInfo.InvariantCulture),
            category = (Category)Enum.Parse(typeof(Category), fields[2])
        };
    }
}