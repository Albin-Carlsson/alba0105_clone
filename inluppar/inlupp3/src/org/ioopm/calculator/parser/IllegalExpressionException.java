package org.ioopm.calculator.parser;

public class IllegalExpressionException extends RuntimeException {
    public IllegalExpressionException() {
        super();
    }

    public IllegalExpressionException(String msg) {
        super(msg);
    }
}