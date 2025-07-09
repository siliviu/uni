package networking;

import domain.dto.ChildDTO;
import java.io.Serializable;
import java.util.List;


public class Response {
	private ResponseType type;
	private String errorMessage;

	private List<ChildDTO> children;

	public Response() {
	}

	public ResponseType getType() {
		return type;
	}

	public void setType(ResponseType type) {
		this.type = type;
	}

	public String getErrorMessage() {
		return errorMessage;
	}

	public void setErrorMessage(String errorMessage) {
		this.errorMessage = errorMessage;
	}

	public List<ChildDTO> getChildren() {
		return children;
	}

	public void setChildren(List<ChildDTO> children) {
		this.children = children;
	}

	@Override
	public String toString() {
		return "Response{" +
				"type=" + type +
				", errorMessage='" + errorMessage + '\'' +
				", children=" + children +
				'}';
	}
}
