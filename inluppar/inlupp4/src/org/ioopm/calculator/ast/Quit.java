package org.ioopm.calculator.ast;

public class Quit extends Command {

    private static final Quit theInstance = new Quit();

    public Quit() {
    }

    public static Quit instance() {
        return theInstance;
    }

    public void execute(Object... args) {
        System.out.println(
                "You have chosen to quit :/\n" +
                "Total expressions: " + args[1] + "\n" +
                "Successfully evaluated:" + args[2] + "\n" +
                "Fully evaluated: " + args[3]);
        System.exit(0);
    }
}
