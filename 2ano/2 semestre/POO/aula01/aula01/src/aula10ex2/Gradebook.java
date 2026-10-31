package aula10ex2;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;

public class Gradebook {

    private Map<String, Student> students;
    private IGradeCalculator calculator;

    public Gradebook() {
        this.students = new HashMap<>();
        this.calculator = new SimpleGradeCalculator(); 
    }

    public void load(String filename) {
        try (BufferedReader reader = new BufferedReader(new FileReader(filename))) {
            String line;

            while ((line = reader.readLine()) != null) {
                String[] parts = line.split("\\|");
                if (parts.length >= 2) {
                    String name = parts[0].trim();
                    List<Double> grades = new ArrayList<>();
                    for (int i = 1; i < parts.length; i++) {
                        grades.add(Double.parseDouble(parts[i].trim()));
                    }
                    Student student = new Student(name, grades);
                    addStudent(student);
                }
            }

        } catch (IOException e) {
            System.err.println("Erro ao ler o ficheiro: " + e.getMessage());
        } catch (NumberFormatException e) {
            System.err.println("Erro ao converter nota: " + e.getMessage());
        }
    }

    public void addStudent(Student student) {
        students.put(student.getName(), student);
    }

    public void removeStudent(String name) {
        students.remove(name);
    }

    public Student getStudent(String name) {
        return students.get(name);
    }

    public double calculateAverageGrade(String name) {
        Student student = students.get(name);
        if (student != null) {
            return calculator.calculate(student.getGrades());
        }
        return 0.0;
    }

    public void printAllStudents() {
        for (Student student : students.values()) {
            double avg = calculateAverageGrade(student.getName());
            System.out.println(student.getName() + " - Notas: " + student.getGrades() + " | Média: " + avg);
        }
    }
}
