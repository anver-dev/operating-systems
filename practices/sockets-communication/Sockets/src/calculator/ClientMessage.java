package calculator;

import java.io.Serializable;
import java.util.List;

public class ClientMessage implements Serializable {
    private static final long serialVersionUID = 1L;
    private String nickname;
    private String operationType;
    private List<Double> numbers;

    public String getNickname() {
        return nickname;
    }

    public void setNickname(String nickname) {
        this.nickname = nickname;
    }

    public String getOperationType() {
        return operationType;
    }

    public void setOperationType(String operationType) {
        this.operationType = operationType;
    }

    public List<Double> getNumbers() {
        return numbers;
    }

    public void setNumbers(List<Double> numbers) {
        this.numbers = numbers;
    }
}
