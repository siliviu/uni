using System.Globalization;
using lab14.domain;

namespace lab14.repository;

public class DocumentFileRepo : InFileRepository<String, Document>
{
    public DocumentFileRepo(string fileName) : base(fileName, new DocumentReader()) { }
}

public class DocumentReader : Reader<Document> {
    public Document Parse(string line) {
        string[] fields = line.Split(", ");
        return new Document {
            id = fields[0],
            name = fields[1],
            issueDate = DateTime.ParseExact(fields[2], "d/M/yyyy", CultureInfo.InvariantCulture)
        };
    }
}