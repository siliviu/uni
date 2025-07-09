using lab14.domain;
using lab14.repository;

namespace lab14.service;

public class DocumentService {
    private DocumentFileRepo documentFileRepo;
    public DocumentService() {
        documentFileRepo = new DocumentFileRepo("..\\..\\..\\data\\documents.txt");
    }

    public IEnumerable<Document> GetAllDocuments() {
        return documentFileRepo.FindAll();
    }
}