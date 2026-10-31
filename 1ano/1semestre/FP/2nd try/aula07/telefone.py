# Complete este programa como pedido no guião da aula.

def AddContacts(contactos): 
    
    nome= input("Insira o nome do contacto: ")
    number= input("Insira o número telefónico: ")
    contactos.update({nome : number})
    print(contactos)

def RemoveContact(contactos):
    numero= input("Que contacto deseja eliminar? ")
    for number in list(contactos.keys()):  

        if numero== number:
            del(contactos[number])

    print(contactos)

def SearchNumber(contactos):
    numero = input("Insira o número para procurar: ")
    nome = contactos.get(numero, None)  
    if nome:
        print(f"O número {numero} pertence a {nome}.")
    else:
        print(f"O número {numero} não está registado, portanto o próprio número é: {numero}.")

def ProcurarContacto(contactos):
    partName= input("Insira o contacto que deseja procurar: ")

    filtered_contacts = filterPartName(contactos, partName)

    if filtered_contacts:
        print(f"Contactos que contêm '{partName}':")
        listContacts(filtered_contacts)
    else:
        print(f"Nenhum contacto encontrado com '{partName}'.")
        




def listContacts(dic):
    """Print the contents of the dictionary as a table, one item per row."""
    print("{:>12s} : {}".format("Numero", "Nome"))
    for num in dic:
        print("{:>12s} : {}".format(num, dic[num]))

def filterPartName(contacts, partName):
    """Returns a new dict with the contacts whose names contain partName."""
    result = {number: nome for number, nome in contacts.items() if partName.lower() in nome.lower()}
    return result


def menu():
    """Shows the menu and gets user option."""
    print()
    print("(L)istar contactos")
    print("(A)dicionar contacto")
    print("(R)emover contacto")
    print("Procurar (N)úmero")
    print("Procurar (P)arte do nome")
    print("(T)erminar")
    op = input("opção? ").upper()   # converts to uppercase...
    return op


def main():
    """This is the main function containing the main loop."""

    # The list of contacts (it's actually a dictionary!):
    contactos = {"234370200": "Universidade de Aveiro", "Rua do vinho"
        "727392822": "Cristiano Aveiro",
        "387719992": "Maria Matos",
        "887555987": "Marta Maia",
        "876111333": "Carlos Martins",
        "433162999": "Ana Bacalhau"
        }

    op = ""
    while op != "T":
        op = menu()
        if op == "T":
            print("Fim")
        elif op == "L":
            print("Contactos:")
            listContacts(contactos)
        elif op=="A":
            AddContacts(contactos)
        elif op=="R":
            RemoveContact(contactos)

        elif op=="N":
            SearchNumber(contactos)
        elif op=="P":
            ProcurarContacto(contactos)
        


        
        else:
            print("Não implementado!")
    

# O programa começa aqui
main()


