package org.ioopm.calculator.ast;

public class Clear extends Command {

    private static final Clear theInstance = new Clear();

    private Clear() {}

    public static Clear instance() {
        return theInstance;
    }

    public void execute(Object... args) {
        ((Environment) args[0]).clear();
    }
}
