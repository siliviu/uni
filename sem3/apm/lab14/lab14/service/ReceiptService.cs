using lab14.domain;
using lab14.repository;

namespace lab14.service;

public class ReceiptService {
    private ReceiptFileRepo receiptFileRepo;
    public ReceiptService() {
        receiptFileRepo = new ReceiptFileRepo("..\\..\\..\\data\\receipts.txt", new DocumentFileRepo("..\\..\\..\\data\\documents.txt"));
        receiptFileRepo.LoadPurchases(new PurchaseFileRepo("..\\..\\..\\data\\purchases.txt",receiptFileRepo));
    }

    public IEnumerable<Receipt> GetAllReceipts() {
        return receiptFileRepo.FindAll();
    }
}