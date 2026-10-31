package aula06;

class Contacto {
    private static int contadorID = 1;
    private int id;
    private Pessoa pessoa;
    private String telemovel;
    private String email;

    public Contacto(Pessoa pessoa, String telemovel, String email) {
        this.id = contadorID++;
        this.pessoa = pessoa;
        setTelemovel(telemovel);
        setEmail(email);
    }

    public int getId() {
        return id;
    }

    public Pessoa getPessoa() {
        return pessoa;
    }

    public String getTelemovel() {
        return telemovel;
    }

    public void setTelemovel(String telemovel) {
        if (isValidTelemovel(telemovel)) {
            this.telemovel = telemovel;
        } else {
            throw new IllegalArgumentException("Número de telemóvel inválido!");
        }
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        if (isValidEmail(email)) {
            this.email = email;
        } else {
            throw new IllegalArgumentException("Email inválido!");
        }
    }

    private boolean isValidTelemovel(String telemovel) {
        return telemovel.matches("9\\d{8}");
    }

    private boolean isValidEmail(String email) {
        return email.contains("@") && (email.endsWith(".pt") || email.endsWith(".com"));
    }

    @Override
    public String toString() {
        return "ID: " + id + ", " + pessoa + ", Telemóvel: " + telemovel + ", Email: " + email;
    }
}
