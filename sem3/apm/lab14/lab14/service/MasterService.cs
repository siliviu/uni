using lab14.domain;

namespace lab14.service;

public class MasterService {
    DocumentService documentService;
    ReceiptService receiptService;
    PurchaseService purchaseService;

    public MasterService() {
        documentService = new DocumentService();
        receiptService = new ReceiptService();
        purchaseService = new PurchaseService();
    }

    private void Task1() {
        Console.WriteLine("1: ");
        documentService.GetAllDocuments()
            .Where(d => d.issueDate.Year.Equals(2023))
            .Select(d => new { d.name, d.issueDate })
            .ToList()
            .ForEach(Console.WriteLine);
        Console.WriteLine("---");
    }

    private void Task2() {
        Console.WriteLine("2: ");
        receiptService.GetAllReceipts()
            .Where(r => r.dueDate.Year.Equals(DateTime.Today.Year) && r.dueDate.Month.Equals(DateTime.Today.Month))
            .Select(r => new { r.name, r.dueDate })
            .ToList()
            .ForEach(Console.WriteLine);
        Console.WriteLine("---");
    }

    private void Task3() {
        Console.WriteLine("3: ");
        receiptService.GetAllReceipts()
            .Select(r => new
                { r.name, count = r.purchases.Sum(p => p.quantity) })
            .Where(r => r.count >= 3)
            .ToList()
            .ForEach(Console.WriteLine);
        Console.WriteLine("---");
    }

    private void Task4() {
        Console.WriteLine("4: ");
        purchaseService.GetAllPurchases()
            .Join(receiptService.GetAllReceipts().Where(r => r.category.Equals(Category.Utilities)),
                purchase => purchase.receipt.id,
                receipt => receipt.id,
                (purchase, receipt) => new { purchase.product, receipt.name })
            .ToList()
            .ForEach(Console.WriteLine);
        Console.WriteLine("---");
    }

    private void Task5() {
        Console.WriteLine("5: ");
        var result =
            receiptService.GetAllReceipts()
                .Select(r => new
                    { r.category, price = r.purchases.Sum(p => p.quantity * p.productPrice) })
                .GroupBy(r => r.category,
                    r => r.price,
                    (category, prices) => new { category, price = prices.Sum() })
                .OrderByDescending(r => r.price)
                .First();
        Console.WriteLine($"{result.category} ({result.price})");
    }

    public void Go() {
        Task1();
        Task2();
        Task3();
        Task4();
        Task5();
    }
}