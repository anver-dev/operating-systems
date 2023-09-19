package calculator;

import java.io.Serializable;

public class ServerMessage implements Serializable {
    private static final long serialVersionUID = 1L;
    private String response;

    public String getResponse() {
        return response;
    }

    public void setResponse(String response) {
        this.response = response;
    }
}
