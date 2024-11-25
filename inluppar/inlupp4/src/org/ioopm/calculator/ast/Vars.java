package org.ioopm.calculator.ast;

public class Vars extends Command {

    private static final Vars theInstance = new Vars();

    private Vars() {}

    public static Vars instance() {
        return theInstance;
    }

    public void execute(Object... args) {
        for (Variable key : ((Environment) args[0]).keySet()) {
            System.out.println(key + " = " + ((Environment) args[0]).get(key));
        }
    }
}
