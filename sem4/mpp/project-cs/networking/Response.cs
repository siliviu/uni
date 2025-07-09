using Newtonsoft.Json;
using project_cs.domain;

namespace networking;

public enum ResponseType {
    OK,
    ERROR,
    CHILDREN_LIST,
    UPDATE_CHILDREN
}

public class Response {
    public ResponseType type { get; set; }
    public string errorMessage { get; set; }
    public List<ChildDto> children { get; set; }
}