package aula11ex2;

import java.util.LinkedList;
import java.util.List;

public class GradebookTester {
    public static void main(String[] args) {
        Gradebook gradebook = new Gradebook();

        gradebook.load("datafiles/aula11/ex2/alunos.txt");

        Student newStudent = new Student("Johny May", new LinkedList<>(List.of(10.0, 15.0, 19.0)));
        gradebook.addStudent(newStudent);

        gradebook.removeStudent("Jane Smith");

        Student student = gradebook.getStudent("John Doe");

        double averageGrade = gradebook.calculateAverageGrade("John Doe");
        System.out.println("Average grade for John Doe: " + averageGrade);

        gradebook.printAllStudents();
    }
}