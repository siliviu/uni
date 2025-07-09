using lab14.domain;
using lab14.repository;

namespace lab14.service;

public class PurchaseService {
    private PurchaseFileRepo purchaseFileRepo;

    public PurchaseService() {
        purchaseFileRepo = new PurchaseFileRepo("..\\..\\..\\data\\purchases.txt",
            new ReceiptFileRepo("..\\..\\..\\data\\receipts.txt",
                new DocumentFileRepo("..\\..\\..\\data\\documents.txt")));
    }

    public IEnumerable<Purchase> GetAllPurchases() {
        return purchaseFileRepo.FindAll();
    }
}