package aula09ex2;

import java.util.ArrayList;
import java.util.List;

public class PlaneManager {
    private List<Plane> frota;

    public PlaneManager() {
        frota = new ArrayList<>();
    }

    public void addPlane(Plane plane) {
        frota.add(plane);
    }

    public boolean removePlane(int id) {
        for (int i = 0; i < frota.size(); i++) {
            if (frota.get(i).getId() == id) {
                frota.remove(i);
                return true;
            }
        }
        return false;
    }
    
    public Plane searchPlane(int id) {
        for (Plane p : frota) {
            if (p.getId() == id) {
                return p;
            }
        }
        return null;
    }

    public List<CommercialPlane> getCommercialPlanes() {
        List<CommercialPlane> comerciais = new ArrayList<>();
        for (Plane p : frota) {
            if (p instanceof CommercialPlane) {
                comerciais.add((CommercialPlane) p);
            }
        }
        return comerciais;
    }

    public List<MilitaryPlane> getMilitaryPlanes() {
        List<MilitaryPlane> militares = new ArrayList<>();
        for (Plane p : frota) {
            if (p instanceof MilitaryPlane) {
                militares.add((MilitaryPlane) p);
            }
        }
        return militares;
    }

    public void printAllPlanes() {
        for (Plane p : frota) {
            System.out.println(p);
        }
    }

    public Plane getFastestPlane() {
        if (frota.isEmpty()) return null;

        Plane fastest = frota.get(0);
        for (Plane p : frota) {
            if (p.getVelocidadeMax() > fastest.getVelocidadeMax()) {
                fastest = p;
            }
        }
        return fastest;
    }
}
