package aula08.ex2;

public enum AlimentOrigin {
    ANIMAL, VEGAN;

    @Override
    public String toString() {
        return switch (this) {
            case ANIMAL -> "ANIMAL";
            case VEGAN -> "VEGAN";
        };
    }
}
