package org.ioopm.calculator.ast;

public class IllegalAssignmentException extends Exception {
    public IllegalAssignmentException() {
        super();
    }

    public IllegalAssignmentException(String msg) {
        super(msg);
    }
}