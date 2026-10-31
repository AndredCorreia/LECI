import hashlib
import sys

def calcular_sha256(nome_arquivo):
    try:
        with open(nome_arquivo, "rb") as f:
            conteudo = f.read()
            hash_obj = hashlib.sha256(conteudo)
            sha1_hash = hash_obj.hexdigest()
            return sha1_hash
    except FileNotFoundError:
        return None

def main():
    if len(sys.argv) != 2:
        print("Uso: python programa.py <nome_arquivo>")
        return

    nome_arquivo = sys.argv[1]
    sha1_hash = calcular_sha256(nome_arquivo)

    if sha1_hash:
        print(f"Síntese SHA-256 de {nome_arquivo}: {sha1_hash}")
    else:
        print(f"Erro: O arquivo '{nome_arquivo}' não foi encontrado.")

if __name__ == "__main__":
    main()
