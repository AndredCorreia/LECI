public class Firewall {
        private String nome;
        private Queue<Pacote> filaPacotes;
        private Set<Pedido> pedidosProcessados;
        private List<String> respostas;
    
        public Firewall(String nome) {
            this.nome = nome;
            this.filaPacotes = new LinkedList<>();
            this.pedidosProcessados = new HashSet<>();
            this.respostas = new ArrayList<>();
        }
    
        public void adicionarPacote(Pacote p) {
            filaPacotes.add(p);
        }
        public void removerPacotes(Pacote p){
            filePacotes.remove(p);
        }

    
}
