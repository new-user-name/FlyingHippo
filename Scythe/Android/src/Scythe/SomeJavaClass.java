package Scythe;

public class SomeJavaClass {

    public static int counter = 0;
    public int id;

    public SomeJavaClass() {
        this.id = counter;
        System.out.println("Created SomeJavaClass object with id: " + this.id);
        counter++;
    }

    public String sayHello() {
        return "SomeJavaClass object number: " + id + " say hello :)";
    }

    public static int multiply(int a, int b) {
        return  a * b;
    }
}
